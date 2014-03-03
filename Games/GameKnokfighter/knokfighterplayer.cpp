#include <iostream>

#include "knokfighterplayer.h"
#include "knokfighterplayerstate.h"

namespace Knokfighter {

Player::Player()
 :  m_attack_state(new PlayerStateAttack(this)),
    m_idle_state(new PlayerStateIdle(this)),
    m_state{nullptr},
    m_walk_state(new PlayerStateWalk(this))
{
  SetState(GetIdleState());
}

PlayerState * Player::GetAttackState()
{
  return m_attack_state.get();
}

PlayerState * Player::GetIdleState()
{
  return m_idle_state.get();
}

PlayerState * Player::GetWalkState()
{
  return m_walk_state.get();
}

const PlayerState * Player::GetState() const
{
  return m_state;
}

void Player::PressKey(const Key& key)
{
  m_state->PressKey(key);
}

void Player::Tick()
{
  m_state->Tick();
}

void Player::SetState(PlayerState * const state)
{
  assert(state);
  //No need to delete the old m_state, this is done
  //by the boost::scoped_ptr's
  m_state = state;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
  os << player.GetState()->ToStr() << '\n';
  return os;
}

} //~namespace Knokfighter
