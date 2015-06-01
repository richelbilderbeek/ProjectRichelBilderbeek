#include <cassert>
#include <cmath>
#include <string>
#include <string>
#include <sstream>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>


#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QwtPlotCurve * const curve = new QwtPlotCurve("Sine");
  QwtPlot * const plot = new QwtPlot(QwtText("CppQwtExample1"));

  plot->setGeometry(0,0,640,400);
  plot->setAxisScale(QwtPlot::xBottom, 0.0,2.0 * M_PI);
  plot->setAxisScale(QwtPlot::yLeft,-1.0,1.0);
  std::vector<double> xs;
  std::vector<double> ys;
  for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
  {
    xs.push_back(x);
    ys.push_back(std::sin(x));
  }
  #if QWT_VERSION >= 0x060100 || !WIN32
  curve->setData(new QwtPointArrayData(&xs[0],&ys[0],ys.size()));
  #else
  m_curve->setData(&v_x[0],&v_y[0],v_y.size());
  #endif
  curve->attach(plot);
  plot->replot();
  plot->show();
  return a.exec();
}


