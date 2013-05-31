#ifndef PLAYER_H
#define PLAYER_H

#include <cassert>

#include <boost/cast.hpp>
#include <boost/shared_ptr.hpp>

#include "worldtype.h"

struct Player
{
  Player(
    const unsigned char r,
    const unsigned char g,
    const unsigned char b)
  : m_r(r), m_g(g), m_b(b), m_dead(false)
  {

  }

  const unsigned char m_r;
  const unsigned char m_g;
  const unsigned char m_b;
  bool m_dead;

  static boost::shared_ptr<WorldType> m_world;

  bool IsDead() const { return m_dead; }
  virtual int GetX() const = 0;
  virtual int GetY() const = 0;
  virtual void Advance() = 0;
  virtual void TurnLeft() = 0;
  virtual void TurnRight() = 0;

  protected:
  virtual ~Player() {}
};

struct ClassicPlayer : public Player
{
  ClassicPlayer(
    const int x,
    const int y,
    const int direction,
    const unsigned char r,
    const unsigned char g,
    const unsigned char b)
    : Player(r,g,b),
      m_x(x), m_y(y),
      m_direction(direction)
  {
    assert(m_direction % 4 == m_direction
      && "Direction must be in set {0,1,2,3}");
  }
  int GetX() const { return m_x; }
  int GetY() const { return m_y; }
  void Advance()
  {
    switch(m_direction % 4)
    {
      case 0: --m_y; break;
      case 1: ++m_x; break;
      case 2: ++m_y; break;
      case 3: --m_x; break;
    }
    double dx = boost::numeric_cast<double>(m_x);
    double dy = boost::numeric_cast<double>(m_y);
    this->m_world->RespondToPlayer(dx,dy,m_dead);
    m_x = boost::numeric_cast<int>(dx);
    m_y = boost::numeric_cast<int>(dy);
  }
  void TurnLeft()
  {
    --m_direction;
  }
  void TurnRight()
  {
    ++m_direction;
  }

  private:
  int m_x;
  int m_y;
  int m_direction;
};

#endif // PLAYER_H
