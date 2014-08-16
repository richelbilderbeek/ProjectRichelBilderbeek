#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/math/constants/constants.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QApplication>

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  const auto curve = boost::make_shared<QwtPlotCurve>("Sine");
  const auto plot = boost::make_shared<QwtPlot>();
  const double tau = boost::math::constants::two_pi<double>();

  plot->setGeometry(8,32,640,400);
  plot->setAxisScale(QwtPlot::xBottom,0.0,tau);
  plot->setAxisScale(QwtPlot::yLeft,-1.0,1.0);
  std::vector<double> xs;
  std::vector<double> ys;
  for (double x = 0.0; x < tau; x+= (tau / 100.0))
  {
    xs.push_back(x);
    ys.push_back(std::sin(x));
  }
  #if QWT_VERSION >= 0x060100 || !WIN32
  const auto data = boost::make_shared<QwtPointArrayData>(&xs[0],&ys[0],xs.size());
  curve->setData(data.get());
  #else
  curve->setData(&xs[0],&ys[0],xs.size());
  #endif
  curve->attach(plot.get());
  plot->replot();
  plot->show();
  return a.exec();
}


