//---------------------------------------------------------------------------

#ifndef UnitPlayerH
#define UnitPlayerH
//---------------------------------------------------------------------------
//#include "UnitSprite.h"
#include <boost/shared_ptr.hpp>
namespace Extctrls { struct TImage; }
namespace Graphics { struct TCanvas; }
struct Background;
struct PlayerState;
struct PlayerLeft;
struct PlayerRight;
struct PlayerJump;
struct PlayerStand;
//---------------------------------------------------------------------------
struct Player
{
  Player();
  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();
  void Tick();
  void Draw(Graphics::TCanvas * const canvas) const;

  void SetToWalkingHeight(const Background* const background);
  void SetToStartingPosition(const Background* const background);
  void RespondToBackground(const Background* const background);

  const int GetX() const { return static_cast<int>(m_x); }
  const int GetY() const { return static_cast<int>(m_y); }
  const int GetHeight() const;
  const int GetWidth() const;
  void Move(const int dx, const int dy);
  void SetStateLeft();
  void SetStateRight();
  void SetStateJump(const double dx);
  void SetStateStand(const bool face_right);
  void Die() { m_has_died = true; }
  const bool HasDied() { return m_has_died; }

  private:
  PlayerState * m_cur_state;
  double m_x;
  double m_y;
  bool m_has_died;
  //States
  boost::shared_ptr<PlayerLeft> m_state_left;
  boost::shared_ptr<PlayerRight> m_state_right;
  boost::shared_ptr<PlayerJump> m_state_jump;
  boost::shared_ptr<PlayerStand> m_state_stand;
};
//---------------------------------------------------------------------------
#endif
