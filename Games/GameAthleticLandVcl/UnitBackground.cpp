//---------------------------------------------------------------------------


#pragma hdrstop

#include "UnitBackground.h"
#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
BackgroundAlForest::BackgroundAlForest()
  : Background(FormSprites->ImageAlForest,
    256, //walk_y
    400  //right_x
    )
{

}
//---------------------------------------------------------------------------
const boost::shared_ptr<Background> CreateBackgroundAlForest()
{
  return boost::shared_ptr<Background>(new BackgroundAlForest);
}
//---------------------------------------------------------------------------




#pragma package(smart_init)
