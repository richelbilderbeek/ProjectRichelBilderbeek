#ifndef QWTTESTPLANEZOOMER_H
#define QWTTESTPLANEZOOMER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <qwt_plot_zoomer.h>
#pragma GCC diagnostic pop

namespace ribi {

struct QwtTestPlaneZoomer: public QwtPlotZoomer
{
  QwtTestPlaneZoomer(QWidget * const canvas);
  QwtText trackerTextF(const QPointF &pos) const;
};

} //~namespace ribi

#endif // QWTTESTPLANEZOOMER_H
