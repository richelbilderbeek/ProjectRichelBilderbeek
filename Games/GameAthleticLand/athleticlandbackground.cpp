#include "athleticlandbackground.h"
#include "athleticlandsprites.h"

ribi::athl::BackgroundAlForest::BackgroundAlForest()
  : Background(":/GameAthleticLand/Background1.png",
    256, //walk_y
    400  //right_x
    )
{

}

const boost::shared_ptr<ribi::athl::Background> ribi::athl::CreateBackgroundAlForest()
{
  return boost::shared_ptr<Background>(new BackgroundAlForest);
}
