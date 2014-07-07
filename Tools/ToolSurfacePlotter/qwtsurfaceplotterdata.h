#ifndef MYDATA_H
#define MYDATA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwt_matrix_raster_data.h"
#pragma GCC diagnostic pop

namespace ribi {

///The spectrogram data
struct MyData: public QwtRasterData
{
  MyData();

  double value( double x, double y ) const;
};

} //~namespace ribi


#endif // MYDATA_H
