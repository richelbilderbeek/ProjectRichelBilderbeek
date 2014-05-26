#include "tankbattaliongamewidget.h"

#include <cassert>

#include "tankbattalionhelper.h"
#include "tankbattalionkeys.h"
#include "trace.h"

ribi::taba::GameWidget::GameWidget()
  : m_arena(CreateArena()),
    m_direction{Direction::up},
    m_keys{},
    m_x{sm_n_columns / 2},
    m_y{sm_n_rows / 2}
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::array<std::array<int,ribi::taba::GameWidget::sm_n_columns>,ribi::taba::GameWidget::sm_n_rows> ribi::taba::GameWidget::CreateArena() noexcept
{
  std::array<std::array<int,sm_n_columns>,sm_n_rows> v;
  return v;
}

bool ribi::taba::GameWidget::GetIsBrick(const int x, const int y) const noexcept
{
  assert(x >= 0);
  assert(x < sm_n_columns);
  assert(y >= 0);
  assert(y < sm_n_rows);
  assert(m_arena.at(y).at(x) >= 0);
  return m_arena[y][x];
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
  const int n = static_cast<int>(m_keys.size());
  for (int i=0; i!=n; ++i)
  {
    if (m_keys[i] == key)
    {
      std::swap(m_keys[i], m_keys[n-1]);
      m_keys.pop_back();
      if (m_keys.size() == 1)
      {
        m_direction = Helper().KeyToDirection(m_keys[0]);
      }
    }
  }
}



#ifndef NDEBUG
void ribi::taba::GameWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::taba::GameWidget::Test");
  Keys();
  TRACE("Finished ribi::taba::GameWidget::Test successfully");
}
#endif
