#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "mycolormap.h"
#pragma GCC diagnostic pop

MyColorMap::MyColorMap()
  : QwtLinearColorMap( Qt::darkCyan, Qt::red)
{
  addColorStop( 0.1, Qt::cyan );
  addColorStop( 0.6, Qt::green );
  addColorStop( 0.95, Qt::yellow );
}
