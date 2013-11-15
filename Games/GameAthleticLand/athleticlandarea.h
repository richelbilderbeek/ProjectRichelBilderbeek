

#ifndef UnitAreaH
#define UnitAreaH

#include <vector>
#include <boost/shared_ptr.hpp>
#include "athleticlandfwd.h"

namespace ribi {
namespace athl {

struct Background;
struct Player;
struct Sprite;

struct Area
{
  Area(const boost::shared_ptr<Background> m_background);
  void Start();
  void Restart();
  void Tick();
  void InitBuffer(QPixmap * const buffer) const;
  void Draw(QPixmap * const buffer) const;
  bool HasFinished() const { return m_area_finished; }
  bool HasDied() const;

  void PressKeyLeft();
  void PressKeyRight();
  void PressKeyJump();
  void PressNoKey();

  void AddPlayer();
  void AddRock();
  void AddRollingBall();

  private:
  bool m_area_finished;
  boost::shared_ptr<Background> m_background;
  static boost::shared_ptr<Player> m_player;
  std::vector<boost::shared_ptr<Sprite> > m_sprites;
};

} //~namespace ribi
} //~namespace athl

#endif
