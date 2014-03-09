#include <iostream>

#include "knokfighterplayer.h"
#include "knokfighterplayerstate.h"

ribi::knok::Player::Player()
 :  m_attack_state(new PlayerStateAttack(this)),
    m_idle_state(new PlayerStateIdle(this)),
    m_state{nullptr},
    m_walk_state(new PlayerStateWalk(this))
{
  SetState(GetIdleState());
}

ribi::knok::PlayerState * ribi::knok::Player::GetAttackState()
{
  return m_attack_state.get();
}

ribi::knok::PlayerState * ribi::knok::Player::GetIdleState()
{
  return m_idle_state.get();
}

ribi::knok::PlayerState * ribi::knok::Player::GetWalkState()
{
  return m_walk_state.get();
}

const ribi::knok::PlayerState * ribi::knok::Player::GetState() const
{
  return m_state;
}

void ribi::knok::Player::PressKey(const Key& key)
{
  m_state->PressKey(key);
}

void ribi::knok::Player::Tick()
{
  m_state->Tick();
}

void ribi::knok::Player::SetState(PlayerState * const state)
{
  assert(state);
  //No need to delete the old m_state, this is done
  //by the boost::scoped_ptr's
  m_state = state;
}

std::ostream& ribi::knok::operator<<(std::ostream& os, const Player& player)
{
  os << player.GetState()->ToStr() << '\n';
  return os;
}
