#ifndef CONNECTTHREEMOVE_H
#define CONNECTTHREEMOVE_H

#include "connectthreeplayer.h"

namespace ribi {
namespace con3 {

struct Move
{
  Move(const int x, const int y, const Player player)
    : m_player{player}, m_x{x}, m_y{y} {}

  Player GetPlayer() const noexcept { return m_player; }
  int GetX() const noexcept { return m_x; }
  int GetY() const noexcept { return m_y; }

  private:
  const Player m_player;
  const int m_x;
  const int m_y;
};

} //~namespace con3
} //~namespace ribi

#endif // CONNECTTHREEMOVE_H
