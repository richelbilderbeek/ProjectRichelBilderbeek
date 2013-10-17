//---------------------------------------------------------------------------

#ifndef UnitBackgroundH
#define UnitBackgroundH
//---------------------------------------------------------------------------
#include "UnitSprite.h"
//---------------------------------------------------------------------------
struct Background : public NonMovingSprite
{
  Background(
    Extctrls::TImage * const image,
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
//---------------------------------------------------------------------------
struct BackgroundAlForest : public Background
{
  BackgroundAlForest();
};
//---------------------------------------------------------------------------
const boost::shared_ptr<Background> CreateBackgroundAlForest();
//---------------------------------------------------------------------------

#endif
