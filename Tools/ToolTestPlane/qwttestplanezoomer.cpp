#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwttestplanezoomer.h"

#include "qwt_plot_canvas.h"
#pragma GCC diagnostic pop

ribi::QwtTestPlaneZoomer::QwtTestPlaneZoomer(QWidget * const canvas)
  : QwtPlotZoomer(dynamic_cast<QwtPlotCanvas *>(canvas))
{
  setTrackerMode(AlwaysOn);
}

QwtText ribi::QwtTestPlaneZoomer::trackerTextF(const QPointF& pos) const
{
  const QColor bg(0,0,0,200);
  QwtText text = QwtPlotZoomer::trackerTextF(pos);
  text.setBackgroundBrush(QBrush(bg));
  return text;
}
