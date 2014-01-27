#include "maziakmaindialog.h"

#include <cassert>

#include "maziakkey.h"

ribi::maziak::MainDialog::MainDialog()
{
}

void ribi::maziak::MainDialog::OnKeyPress(const maziak::Key key)
{
  //if (m_fighting_frame > 0) repaint();
  m_keys.insert(key);

  switch (key)
  {
    case Key::Left : m_keys.erase(Key::right); break;
    case Key::right: m_keys.erase(Key::left ); break;
    case Key::up   : m_keys.erase(Key::down ); break;
    case Key::down : m_keys.erase(Key::up   ); break;
  }
}

void ribi::maziak::MainDialog::OnTimerPressKey(const maziak::Key key)
{
  if (m_fighting_frame > 0) return;
  if (m_keys.empty()) { m_move_now = PlayerMove::none; return; }

  for(const Key key: m_keys)
  {
    //Check the keys pressed
    switch (key)
    {
      case Key::left:
        m_direction = PlayerDirection::pdLeft;
        if (!m_maze->CanMoveTo(m_x-1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::left1 ? PlayerMove::left2 : PlayerMove::left1);
        --m_x;
        break;
      case Key::right:
        m_direction = PlayerDirection::pdRight;
        if (!m_maze->CanMoveTo(m_x+1,m_y,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::right1 ? PlayerMove::right2 : PlayerMove::right1);
        ++m_x;
        break;
      case Key::up:
        m_direction = PlayerDirection::pdUp;
        if (!m_maze->CanMoveTo(m_x,m_y-1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::up1 ? PlayerMove::up2 : PlayerMove::up1);
        --m_y;
        break;
      case Key::down:
        m_direction = PlayerDirection::pdDown;
        if (!m_maze->CanMoveTo(m_x,m_y+1,m_has_sword,m_do_show_solution))
        {
          m_move_now = PlayerMove::none;
          continue;
        }
        m_move_now = (m_move_now == PlayerMove::down1 ? PlayerMove::down2 : PlayerMove::down1);
        ++m_y;
        break;
      default:
        m_move_now = PlayerMove::none;
        continue;
    }
  }
}
