#ifndef MYCOLORMAP_H
#define MYCOLORMAP_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwt_color_map.h"
#pragma GCC diagnostic pop

namespace ribi {

struct MyColorMap: public QwtLinearColorMap
{
  MyColorMap();
};

} //~namespace ribi

#endif // MYCOLORMAP_H
