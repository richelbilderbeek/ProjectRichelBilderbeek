#include "athleticlandplayerstate.h"

#include <QPixmap>

#include "athleticlandsprites.h"
#include "athleticlandplayer.h"

ribi::athl::PlayerState::PlayerState(Player& player)
  : m_player(player),
    m_sprite(0),
    m_walk_speed(7.5),
    m_jump_up_speed(10.0),
    m_gravity(1.0),
    m_ddx(0.25)
{

}

int ribi::athl::PlayerState::GetHeight() const
{
  assert(m_sprite);
  return m_sprite->height();
}

int ribi::athl::PlayerState::GetWidth() const
{
  assert(m_sprite);
  return m_sprite->width();
}

ribi::athl::PlayerJump::PlayerJump(Player& player)
  : PlayerState(player),
    m_dx(0.0), m_dy(0.0),
    m_jump_left{}, //(FormSprites->ImageMainCharJumpLeft),
    m_jump_right{} //(FormSprites->ImageMainCharJumpRight),
{

}

void ribi::athl::PlayerJump::EndJump()
{
  m_player.SetStateStand(m_dx >= 0.0);
}

ribi::athl::PlayerLeft::PlayerLeft(Player& player)
  : PlayerState(player),
    m_walk_left_1{}, //(FormSprites->ImageMainCharWalkLeft1),
    m_walk_left_2{} //(FormSprites->ImageMainCharWalkLeft2)
{

}

void ribi::athl::PlayerLeft::PressKeyRight()
{
  m_player.SetStateRight();
}

void ribi::athl::PlayerLeft::PressKeyJump()
{
  m_player.SetStateJump(-m_walk_speed);
}

void ribi::athl::PlayerLeft::PressNoKey()
{
  m_player.SetStateStand(false);
}

ribi::athl::PlayerRight::PlayerRight(Player& player)
  : PlayerState(player),
    m_walk_right_1{}, //(FormSprites->ImageMainCharWalkRight1),
    m_walk_right_2{} //(FormSprites->ImageMainCharWalkRight2)
{

}

void ribi::athl::PlayerRight::PressKeyLeft()
{
  m_player.SetStateLeft();
}

void ribi::athl::PlayerRight::PressKeyJump()
{
  m_player.SetStateJump(m_walk_speed);
}

void ribi::athl::PlayerRight::PressNoKey()
{
  m_player.SetStateStand(true);
}

ribi::athl::PlayerStand::PlayerStand(Player& player)
  : PlayerState(player),
    m_stand_left{}, //(FormSprites->ImageMainCharStandLeft),
    m_stand_right{} //(FormSprites->ImageMainCharStandRight)
{

}

void ribi::athl::PlayerStand::PressKeyLeft()
{
  m_player.SetStateLeft();
}

void ribi::athl::PlayerStand::PressKeyRight()
{
  m_player.SetStateRight();
}

void ribi::athl::PlayerStand::PressKeyJump()
{
  m_player.SetStateJump( m_face_right ? 0.0001 : -0.0001);
}


