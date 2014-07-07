#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwtsurfaceplotterzoomer.h"

#include "qwt_plot_canvas.h"
#pragma GCC diagnostic pop

ribi::MyZoomer::MyZoomer(QWidget * const canvas)
  : QwtPlotZoomer(dynamic_cast<QwtPlotCanvas *>(canvas))
{
  setTrackerMode(AlwaysOn);
}

QwtText ribi::MyZoomer::trackerTextF(const QPointF& pos) const
{
  QColor bg( Qt::white );
  bg.setAlpha( 200 );

  QwtText text = QwtPlotZoomer::trackerTextF( pos );
  text.setBackgroundBrush( QBrush( bg ) );
  return text;
}
