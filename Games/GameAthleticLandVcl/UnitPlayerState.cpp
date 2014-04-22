//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitFormSprites.h"
#include "UnitPlayer.h"
#include "UnitPlayerState.h"
//---------------------------------------------------------------------------
PlayerState::PlayerState(Player& player)
  : m_player(player),
    m_sprite(0),
    m_walk_speed(7.5),
    m_jump_up_speed(10.0),
    m_gravity(1.0),
    m_ddx(0.25)
{

}
//---------------------------------------------------------------------------
const int PlayerState::GetHeight() const
{
  assert(m_sprite);
  return m_sprite->Picture->Bitmap->Height;
}
//---------------------------------------------------------------------------
const int PlayerState::GetWidth() const
{
  assert(m_sprite);
  return m_sprite->Picture->Bitmap->Width;
}
//---------------------------------------------------------------------------
PlayerJump::PlayerJump(Player& player)
  : PlayerState(player),
    m_jump_left(FormSprites->ImageMainCharJumpLeft),
    m_jump_right(FormSprites->ImageMainCharJumpRight),
    m_dx(0.0), m_dy(0.0)
{

}
//---------------------------------------------------------------------------
void PlayerJump::EndJump()
{
  m_player.SetStateStand(m_dx >= 0.0);
}
//---------------------------------------------------------------------------
PlayerLeft::PlayerLeft(Player& player)
  : PlayerState(player),
    m_walk_left_1(FormSprites->ImageMainCharWalkLeft1),
    m_walk_left_2(FormSprites->ImageMainCharWalkLeft2)
{

}
//---------------------------------------------------------------------------
void PlayerLeft::PressKeyRight()
{
  m_player.SetStateRight();
}
//---------------------------------------------------------------------------
void PlayerLeft::PressKeyJump()
{
  m_player.SetStateJump(-m_walk_speed);
}
//---------------------------------------------------------------------------
void PlayerLeft::PressNoKey()
{
  m_player.SetStateStand(false);
}
//---------------------------------------------------------------------------
PlayerRight::PlayerRight(Player& player)
  : PlayerState(player),
    m_walk_right_1(FormSprites->ImageMainCharWalkRight1),
    m_walk_right_2(FormSprites->ImageMainCharWalkRight2)
{

}
//---------------------------------------------------------------------------
void PlayerRight::PressKeyLeft()
{
  m_player.SetStateLeft();
}
//---------------------------------------------------------------------------
void PlayerRight::PressKeyJump()
{
  m_player.SetStateJump(m_walk_speed);
}
//---------------------------------------------------------------------------
void PlayerRight::PressNoKey()
{
  m_player.SetStateStand(true);
}
//---------------------------------------------------------------------------
PlayerStand::PlayerStand(Player& player)
  : PlayerState(player),
    m_stand_left(FormSprites->ImageMainCharStandLeft),
    m_stand_right(FormSprites->ImageMainCharStandRight)
{

}
//---------------------------------------------------------------------------
void PlayerStand::PressKeyLeft()
{
  m_player.SetStateLeft();
}
//---------------------------------------------------------------------------
void PlayerStand::PressKeyRight()
{
  m_player.SetStateRight();
}
//---------------------------------------------------------------------------
void PlayerStand::PressKeyJump()
{
  m_player.SetStateJump( m_face_right ? 0.0001 : -0.0001);
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
