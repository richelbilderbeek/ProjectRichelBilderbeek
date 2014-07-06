#ifndef MYZOOMER_H
#define MYZOOMER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <qwt_plot_zoomer.h>
#pragma GCC diagnostic pop

struct MyZoomer: public QwtPlotZoomer
{
  MyZoomer(QWidget * const canvas);
  QwtText trackerTextF(const QPointF &pos) const;
};

#endif // MYZOOMER_H
