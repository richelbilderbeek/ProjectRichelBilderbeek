#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "myzoomer.h"
#pragma GCC diagnostic pop

MyZoomer::MyZoomer(QWidget *canvas)
  : QwtPlotZoomer(canvas)
{
  setTrackerMode(AlwaysOn);
}

QwtText MyZoomer::trackerTextF(const QPointF& pos) const
{
  QColor bg( Qt::white );
  bg.setAlpha( 200 );

  QwtText text = QwtPlotZoomer::trackerTextF( pos );
  text.setBackgroundBrush( QBrush( bg ) );
  return text;
}
