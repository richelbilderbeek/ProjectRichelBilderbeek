#ifndef PLAYER_H
#define PLAYER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>

#include <boost/cast.hpp>
#include <boost/shared_ptr.hpp>

#include <QColor>
#include "tronworldtype.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tron {

struct Player
{
  Player(
    const QColor& color)
  : m_color{color}
  {

  }
  const QColor& GetColor() const noexcept { return m_color; }

  const QColor m_color;
  static boost::shared_ptr<WorldType> m_world;

  //bool IsDead() const { return m_dead; }
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
    const QColor& color)
    : Player(color),
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
    #ifdef TODO_RJCB
    this->m_world->RespondToPlayer(dx,dy,m_dead);
    #endif
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

} //~namespace tron
} //~namespace ribi

#endif // PLAYER_H
