#ifndef KNOKFIGHTERPLAYER_H
#define KNOKFIGHTERPLAYER_H

#include <iosfwd>

#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>

namespace Knokfighter {

struct PlayerState;
struct Key;

struct Player
{
  Player();

  ///Respond to a key press
  void PressKey(const Key& key);

  ///Respond to a main timer tick
  void Tick();

  ///State machinery, used by the States themselves
  PlayerState * GetIdleState();
  PlayerState * GetWalkState();
  PlayerState * GetAttackState();
  const PlayerState * GetState() const;
  void SetState(PlayerState * const state);

  private:
  virtual ~Player() {}
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(Player* x);

  ///Player is attacking
  boost::scoped_ptr<PlayerState> m_attack_state;

  ///Player is idle
  boost::scoped_ptr<PlayerState> m_idle_state;

  ///Player is walking
  boost::scoped_ptr<PlayerState> m_walk_state;

  ///The current state
  PlayerState * m_state;
};

std::ostream& operator<<(std::ostream& os, const Player& gumballMachine);

} //~namespace Knokfighter

#endif // KNOKFIGHTERPLAYER_H
