

#ifndef UnitBackgroundH
#define UnitBackgroundH

#include "athleticlandfwd.h"
#include "athleticlandsprite.h"

namespace ribi {
namespace athl {

struct Background : public NonMovingSprite
{
  Background(
    QPixmap * const image,
    const int walk_height,
    const int right_x)
  : NonMovingSprite(0,0,image),
    m_walk_height(walk_height),
    m_right_x(right_x)
  {

  }

  ~Background() {}
  const int m_walk_height; //Height where feet walk on
  const int m_right_x; //X coordinat of rock or fire
};

struct BackgroundAlForest : public Background
{
  BackgroundAlForest(QPixmap * const image);
};

const boost::shared_ptr<Background> CreateBackgroundAlForest(QPixmap * const image);

} //~namespace ribi
} //~namespace athl

#endif
