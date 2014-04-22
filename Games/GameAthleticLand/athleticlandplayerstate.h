

#ifndef UnitPlayerStateH
#define UnitPlayerStateH

#include <boost/shared_ptr.hpp>
#include "athleticlandfwd.h"

namespace ribi {
namespace athl {

enum class State
{
  stand_left,
  stand_right
};

/*
struct Player;

struct PlayerState
{
  PlayerState(Player& player);
  PlayerState(const PlayerState&) = delete;
  PlayerState& operator=(const PlayerState&) = delete;
  virtual ~PlayerState() {}
  virtual void PressKeyLeft()  = 0;
  virtual void PressKeyRight() = 0;
  virtual void PressKeyJump()  = 0;
  virtual void PressNoKey()    = 0;
  virtual void Tick(const double x, const double y) = 0;
  const boost::shared_ptr<const QPixmap> GetSprite() const { return m_sprite; }
  int GetHeight() const;
  int GetWidth() const;

  protected:
  Player& m_player;
  boost::shared_ptr<QPixmap> m_sprite;
  const double m_walk_speed;
  const double m_jump_up_speed;
  const double m_gravity;
  const double m_ddx; //Change of dx on key press left and right 
};

struct PlayerJump : public PlayerState
{
  PlayerJump(Player& player);
  PlayerJump(const PlayerJump&) = delete;
  PlayerJump& operator=(const PlayerJump&) = delete;
  void PressKeyLeft() { m_dx-=m_ddx; }
  void PressKeyRight() { m_dx+=m_ddx;}
  void PressKeyJump() {}
  void PressNoKey() {}
  void Tick(double& x, double& y)
  {
    x+=m_dx;
    y+=m_dy;
    m_dy+=m_gravity;
  }
  void StartJump(const double dx) //Is jump forward, backwards or up?
  {
    m_dy = -m_jump_up_speed;
    m_dx = dx;
    m_sprite = m_dx >= 0.0 ? m_jump_right : m_jump_left;
  }
  void EndJump();

  double m_dx;
  double m_dy;

  private:
  const boost::shared_ptr<QPixmap> m_jump_left;
  const boost::shared_ptr<QPixmap> m_jump_right;
};

struct PlayerLeft : public PlayerState
{
  PlayerLeft(Player& player);
  PlayerLeft(const PlayerLeft&) = delete;
  PlayerLeft& operator=(const PlayerLeft&) = delete;
  void PressKeyLeft() {}
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();
  void StartLeft()
  {
    m_sprite = m_walk_left_1;
  }
  void Tick(const double x, const double y)
  {
    //m_x-=m_walk_speed;
    //m_sprite = m_sprite == m_walk_left_2 ? m_walk_left_1 : m_walk_left_2;
  }

  private:
  const boost::shared_ptr<QPixmap> m_walk_left_1;
  const boost::shared_ptr<QPixmap> m_walk_left_2;

};

struct PlayerRight : public PlayerState
{
  PlayerRight(Player& player);
  PlayerRight(const PlayerRight&) = delete;
  PlayerRight& operator=(const PlayerRight&) = delete;
  void PressKeyLeft();
  void PressKeyRight() {}
  void PressKeyJump();
  void PressNoKey();
  void StartRight()
  {
    m_sprite = m_walk_right_1;
  }
  void Tick(const double x, const double y)
  {
    //m_x+ = m_walk_speed;
    m_sprite = (m_sprite == m_walk_right_2 ? m_walk_right_1 : m_walk_right_2);
  }

  private:
  const boost::shared_ptr<QPixmap> m_walk_right_1;
  const boost::shared_ptr<QPixmap> m_walk_right_2;

};

struct PlayerStand : public PlayerState
{
  PlayerStand(Player& player);
  PlayerStand(const PlayerStand&) = delete;
  PlayerStand& operator=(const PlayerStand&) = delete;
  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey() {}
  void StartStand(const bool face_right)
  {
    m_face_right = face_right;
    m_sprite = m_face_right ? m_stand_right : m_stand_left;
  }
  void Tick(double& x, double& y) {}

  private:

  bool m_face_right; //Facing right direction
  const boost::shared_ptr<QPixmap> m_stand_left;
  const boost::shared_ptr<QPixmap> m_stand_right;
};
*/

} //~namespace ribi
} //~namespace athl



#endif
