#include "tankbattaliongamewidget.h"

#include <cassert>

#include "tankbattalionarena.h"
#include "tankbattalionhelper.h"
#include "tankbattalionkeys.h"
#include "testtimer.h"
#include "trace.h"

ribi::taba::GameWidget::GameWidget()
  : m_arena(new Arena),
    m_direction{Direction::up},
    m_keys{},
    m_x{Arena::GetColumns() / 2},
    m_y{Arena::GetRows() / 2}
{
  #ifndef NDEBUG
  Test();
  #endif
}

void ribi::taba::GameWidget::OnTimer() noexcept
{
  if (m_keys.empty()) return;
  switch (m_keys[0])
  {
    case Key::up   : --m_y; break;
    case Key::right: ++m_x; break;
    case Key::down : ++m_y; break;
    case Key::left : --m_x; break;
    case Key::fire :        break;
    case Key::n_keys: assert(!"Should never use ribi::taba::Key::n_keys"); break;
  }
}

void ribi::taba::GameWidget::PressKey(const Key key)
{
  m_keys.push_back(key);
  switch (m_keys.size())
  {
    case 1: break;
    case 2: std::swap(m_keys[0],m_keys[1]); break;
    case 3:
    {
      const int n_keys = static_cast<int>(m_keys.size());
      for (int i=0; i!=n_keys - 1; ++i)
      {
        if (Keys().IsOpposite(m_keys[i],m_keys[n_keys - 1]))
        {
          std::swap(m_keys[i],m_keys[n_keys - 1]);
          break;
        }
      }
    }
    break;
    default: break;
    case 0: assert(!"Should not get here");
  }
  assert(!m_keys.empty());
  m_direction = Helper().KeyToDirection(m_keys[0]);
}

void ribi::taba::GameWidget::ReleaseKey(const Key key)
{
  m_keys.erase(std::remove(m_keys.begin(),m_keys.end(),key),m_keys.end());
  if (m_keys.empty()) return;
  const auto iter = std::find(m_keys.begin(),m_keys.end(),Keys().GetOpposite(key));
  if (iter != m_keys.end())
  {
    std::swap(*m_keys.begin(),*iter);
    assert(m_keys[0] == Keys().GetOpposite(key));
  }
  m_direction = Helper().KeyToDirection(m_keys[0]);
}

#ifndef NDEBUG
void ribi::taba::GameWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    Keys();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  //Key presses: single key, does the player change direction?
  {
    GameWidget w;
    for (const auto key: Keys().GetAll())
    {
      if (!Keys().IsMovement(key)) continue;
      w.PressKey(key);
      assert(w.GetDirection() == Helper().KeyToDirection(key)
        && "A single key changes the direction of the player");
      w.ReleaseKey(key);
      assert(w.GetDirection() == Helper().KeyToDirection(key)
        && "Releasing the only single key, maintains the direction of the player");
    }
  }
  //Key presses: two keys: does the player keep both if perpendicular
  {
    GameWidget w;
    for (const auto key_a: Keys().GetAll())
    {
      if (!Keys().IsMovement(key_a)) continue;
      for (const auto key_b: Keys().GetAll())
      {
        if (!Keys().IsMovement(key_b)) continue;
        w.PressKey(key_a);
        w.PressKey(key_b);
        if (verbose)
        {
          TRACE(Keys().ToStr(key_a));
          TRACE(Keys().ToStr(key_b));
        }
        if (Keys().IsOpposite(key_a,key_b))
        {
          assert(w.GetDirection() == Helper().KeyToDirection(key_b)
            && "If an opposite key is pressed, change direction to it");
          w.ReleaseKey(key_b);
          assert(w.GetDirection() == Helper().KeyToDirection(key_a)
            && "If that opposite key is released, reverse the player's direction");
          w.ReleaseKey(key_a);
          assert(w.GetDirection() == Helper().KeyToDirection(key_a)
            && "Maintain that player's direction");
        }
        else
        {
          assert(w.GetDirection() == Helper().KeyToDirection(key_b)
            && "If a second perpendicular key is pressed, change direction to it");
          w.ReleaseKey(key_b);
          assert(w.GetDirection() == Helper().KeyToDirection(key_a)
            && "If the primary key is released, make the other key the new primary one");
          w.ReleaseKey(key_a);
          assert(w.GetDirection() == Helper().KeyToDirection(key_a)
            && "Maintain that player's direction");
        }
      }
    }
  }
  TRACE("Finished ribi::taba::GameWidget::Test successfully");
}
#endif
