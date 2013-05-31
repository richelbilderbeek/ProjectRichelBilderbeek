//---------------------------------------------------------------------------
#include <cassert>
#include <iostream>
//---------------------------------------------------------------------------
#include "nsanabrosstlheader.h"
//---------------------------------------------------------------------------
///m_dy_jump denotes the change in the vertical direction when a player presses jump
const double NsanaBrosPlayer::m_dy_jump = 0.25;
///m_dx_walk denotes the change in the horizontal direction when a player walks
const double NsanaBrosPlayer::m_dx_walk  = 0.25;
//---------------------------------------------------------------------------
NsanaBrosPlayer::NsanaBrosPlayer()
  : m_sprite(
      new NsanaBrosSprite(
        (NsanaBrosGame::GetWidth() / 2.0) - 0.5,
        NsanaBrosGame::GetHeight()-3.0,
        1.0,
        2.0,
        255,
        255,
        255)
      ),
  m_dx(0.0),
  m_dy(0.0)

{

}
//---------------------------------------------------------------------------
double NsanaBrosPlayer::GetHeight() const
{
  return GetSprite()->GetHeight();
}
//---------------------------------------------------------------------------
const NsanaBrosSprite * NsanaBrosPlayer::GetSprite() const
{
  return m_sprite.get();
}
//---------------------------------------------------------------------------
double NsanaBrosPlayer::GetWidth() const
{
  return GetSprite()->GetWidth();
}
//---------------------------------------------------------------------------
double NsanaBrosPlayer::GetX() const
{
  return GetSprite()->GetX();
}
//---------------------------------------------------------------------------
double NsanaBrosPlayer::GetY() const
{
  return GetSprite()->GetY();
}
//---------------------------------------------------------------------------
///Move translates the player's coordinats
void NsanaBrosPlayer::Move()
{
  Translate(m_dx,m_dy);
}
//---------------------------------------------------------------------------
void NsanaBrosPlayer::RespondToKeys(const NsanaBrosKeys * const keys)
{
  switch (keys->GetHorizontal())
  {
    case -1: m_dx = -m_dx_walk; break;
    case  0:                    break;
    case  1: m_dx =  m_dx_walk; break;
  }

  switch (keys->GetVertical())
  {
    case -1:
    {
      //Start jumping
      if (GetDy() == 0.0) m_dy = -m_dy_jump;
    }
    break;
    case  0: break;
    case  1: break;
  }
}
//---------------------------------------------------------------------------
void NsanaBrosPlayer::SetDx(const double dx)
{
  assert(dx > -10.0 && dx < 10.0);
  m_dx = dx;
}
//---------------------------------------------------------------------------
void NsanaBrosPlayer::SetDy(const double dy)
{
  assert(dy > -10.0 && dy < 10.0);
  m_dy = dy;
}
//---------------------------------------------------------------------------
void NsanaBrosPlayer::Translate(const double dx, const double dy)
{
  m_sprite->Translate(dx,dy);
}
//---------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const NsanaBrosPlayer * const p)
{
  os << p->GetSprite() << '\n'
     << "Speed vector: " << p->GetDx()
     << " x " << p->GetDy();
  return os;
}
//---------------------------------------------------------------------------
