#ifndef MYDATA_H
#define MYDATA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwt_matrix_raster_data.h"
#pragma GCC diagnostic pop

///The spectrogram data
struct MyData: public QwtRasterData
{
  MyData();

  double value( double x, double y ) const;
};

#endif // MYDATA_H
