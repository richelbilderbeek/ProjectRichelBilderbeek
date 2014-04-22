//---------------------------------------------------------------------------

#ifndef UnitAreaH
#define UnitAreaH
//---------------------------------------------------------------------------
#include <vector>
#include <boost/shared_ptr.hpp>
struct Background;
struct Player;
struct Sprite;
namespace Extctrls { struct TImage; }
//---------------------------------------------------------------------------
struct Area
{
  Area(const boost::shared_ptr<Background> m_background);
  void Start();
  void Restart();
  void Tick();
  void InitBuffer(Extctrls::TImage* const buffer) const;
  void Draw(Extctrls::TImage* const buffer) const;
  const bool HasFinished() const { return m_area_finished; }
  const bool HasDied() const;

  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();

  void AddPlayer();
  void AddRock();
  void AddRollingBall();

  private:
  std::vector<boost::shared_ptr<Sprite> > m_sprites;
  static boost::shared_ptr<Player> m_player;
  boost::shared_ptr<Background> m_background;
  bool m_area_finished;
};
//---------------------------------------------------------------------------
#endif
