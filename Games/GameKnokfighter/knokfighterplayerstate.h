#ifndef KNOKFIGHTERPLAYERSTATE_H
#define KNOKFIGHTERPLAYERSTATE_H

#include <string>

namespace Knokfighter {

struct Attack;
struct Key;
struct Player;

struct PlayerState
{
  enum class Direction { left, right };

  PlayerState(const PlayerState&) = delete;
  PlayerState& operator=(const PlayerState&) = delete;

  ///The State needs access to the Player it is a state of
  PlayerState(Player * const player);

  virtual ~PlayerState() {}

  ///Respond to a key press
  virtual void PressKey(const Key& key) = 0;

  ///Respond to the main timer ticking
  virtual void Tick() = 0;

  ///Convert the state to (part of) a filename, for example 'HighKickLeft'
  virtual const std::string ToStr() const = 0;

  protected:

  ///The Direction the player has
  Direction m_direction;

  ///The Player the PlayerState is a State of
  Player * const m_player;
};


struct PlayerStateAttack : public PlayerState
{
  ///The State needs access to the Player it is a state of
  PlayerStateAttack(Player * const player) : PlayerState(player) {}

  ///Respond to a key press
  void PressKey(const Key& key);

  ///Set the type of Attack and how many ticks it will last
  void StartAttack(const Attack& attack, const int n_ticks);

  ///Respond to the main timer ticking
  void Tick();

  ///Convert the state to (part of) a filename, for example 'HighKickLeft'
  const std::string ToStr() const;

  private:
  ///The Attack being done
  //Attack m_attack;

  ///The number of ticks this attack will last before Player goes back to PlayerStateIdle
  int m_ticks_left;
};

struct PlayerStateIdle : public PlayerState
{
  ///The State needs access to the Player it is a state of
  PlayerStateIdle(Player * const player) : PlayerState(player) {}

  ///Respond to a key press
  void PressKey(const Key& key);

  ///Respond to the main timer ticking
  void Tick();

  ///Convert the state to (part of) a filename, for example 'HighKickLeft'
  const std::string ToStr() const;
};

struct PlayerStateWalk : public PlayerState
{
  ///The State needs access to the Player it is a state of
  PlayerStateWalk(Player * const player) : PlayerState(player) {}

  ///Respond to a key press
  void PressKey(const Key& key);

  ///Respond to the main timer ticking
  void Tick();

  ///Convert the state to (part of) a filename, for example 'HighKickLeft'
  const std::string ToStr() const;
};

} //~namespace Knokfighter

#endif // KNOKFIGHTERPLAYERSTATE_H
