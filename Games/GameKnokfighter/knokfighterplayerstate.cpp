#include "knokfighterplayerstate.h"

ribi::knok::PlayerState::PlayerState(
  Player * const player)
  : m_direction{Direction::right},
    m_player(player)
{

}
