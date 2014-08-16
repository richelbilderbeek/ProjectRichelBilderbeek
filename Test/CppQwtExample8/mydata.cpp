#include "mydata.h"

MyData::MyData()
{
  setInterval( Qt::XAxis, QwtInterval( -1.5, 1.5 ) );
  setInterval( Qt::YAxis, QwtInterval( -1.5, 1.5 ) );
  setInterval( Qt::ZAxis, QwtInterval( 0.0, 10.0 ) );
}

double MyData::value( double x, double y ) const
{
  const double c = 0.842;

  const double v1 = x * x + ( y - c ) * ( y + c );
  const double v2 = x * ( y + c ) + x * ( y + c );

  return 1.0 / ( v1 * v1 + v2 * v2 );
}
