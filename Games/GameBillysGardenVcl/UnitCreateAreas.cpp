//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitBackground.h"
#include "UnitCreateAreas.h"
#include "UnitSprite.h"

//---------------------------------------------------------------------------
const std::vector<Area> CreateAreas()
{
  std::vector<Area> v;
  {
    Area a(CreateBackgroundAlForest());
    a.AddRollingBall();
    v.push_back(a);
  }
  {
    Area a(CreateBackgroundAlForest());
    a.AddRock();
    v.push_back(a);
  }
  {
    Area a(CreateBackgroundAlForest());
    v.push_back(a);
  }
  return v;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
