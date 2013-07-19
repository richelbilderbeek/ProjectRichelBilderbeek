#include <cassert>
#include <cmath>
#include <string>
#include <string>
#include <sstream>

#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>


#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_text.h"

#ifdef _WIN32
#include "qwt_point_data.h"
#endif

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QwtPlotCurve * const m_curve = new QwtPlotCurve("Sine");
  QwtPlot * const m_plot = new QwtPlot(QwtText("CppHelloQwtQtCreatorLubuntu"));

  m_plot->setGeometry(0,0,640,400);
  m_plot->setAxisScale(QwtPlot::xBottom, 0.0,2.0 * M_PI);
  m_plot->setAxisScale(QwtPlot::yLeft,-1.0,1.0);
  std::vector<double> xs;
  std::vector<double> ys;
  for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
  {
    xs.push_back(x);
    ys.push_back(std::sin(x));
  }
  QwtPointArrayData * const data = new QwtPointArrayData(&xs[0],&ys[0],xs.size());
  m_curve->setData(data);
  m_curve->attach(m_plot);
  m_plot->replot();
  m_plot->show();

  return a.exec();
}


