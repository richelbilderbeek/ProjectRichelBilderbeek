#ifndef ATHLETICLANDPLAYER_H
#define ATHLETICLANDPLAYER_H

//#include "athleticlandsprite.h"
#include <boost/shared_ptr.hpp>
#include "athleticlandfwd.h"
#include "athleticlandplayerstate.h"
struct QPixmap;

namespace ribi {
namespace athl {


//struct Background;
//struct PlayerState;
//struct PlayerLeft;
//struct PlayerRight;
//struct PlayerJump;
//struct PlayerStand;

struct Player
{
  Player();
  Player(const Player&) = delete;
  Player& operator=(const Player&) = delete;
  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();
  //void Tick();
  //void Draw(QPixmap * const canvas) const;

  //void SetToWalkingHeight(const Background* const background);
  //void SetToStartingPosition(const Background* const background);
  //void RespondToBackground(const Background* const background);

  const State GetState() const noexcept { return m_state; }
  double GetX() const noexcept { return m_x; }
  double GetY() const noexcept { return m_y; }
  //int GetHeight() const;
  //int GetWidth() const;
  //void Move(const int dx, const int dy);
  //void SetStateLeft();
  //void SetStateRight();
  //void SetStateJump(const double dx);
  //void SetStateStand(const bool face_right);
  //void Die() { m_has_died = true; }
  //bool HasDied() const { return m_has_died; }

  private:
  //PlayerState * m_cur_state;
  //bool m_has_died;
  State m_state;

  //The fraction the player is left
  double m_x;

  //The fraction the player is top
  double m_y;

  //States
  //boost::shared_ptr<PlayerLeft> m_state_left;
  //boost::shared_ptr<PlayerRight> m_state_right;
  //boost::shared_ptr<PlayerJump> m_state_jump;
  //boost::shared_ptr<PlayerStand> m_state_stand;
};

} //~namespace ribi
} //~namespace athl

#endif //#ifndef ATHLETICLANDPLAYER_H
