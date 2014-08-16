#include "qwtplotwidget.h"

#include <cassert>
#include <deque>
#include <iostream>

#include <QVBoxLayout>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QwtPlotWidget::QwtPlotWidget(const int sz)
  : m_curve(new QwtPlotCurve),
    m_plot(new QwtPlot),
    m_xs(CreateXs(sz))
{

  m_plot->setTitle("QwtPlotWidget");
  m_plot->setAxisTitle(QwtPlot::yLeft,"Y coordinat");
  m_plot->setAxisTitle(QwtPlot::xBottom,"Time");
  m_curve->attach(m_plot);
  //Add grid
  { QwtPlotGrid * const grid = new QwtPlotGrid; grid->setPen(QPen(QColor(196,196,196))); grid->attach(m_plot); }
  //Add zoomer
  //{ new QwtPlotZoomer(m_plot->canvas()); }
  this->setGeometry(-100.0,-100.0,200,200);
  //Add some data
  {
    for (int i=0; i!=sz; ++i)
    {
      const double y_val = 0.0;
      m_ys.push_back(y_val);
    }
    #if QWT_VERSION >= 0x060100 || !WIN32
    m_curve->setData(new QwtPointArrayData(&m_xs[0],&m_ys[0],m_ys.size()));
    #else
    m_curve->setData(&m_xs[0],&m_ys[0],m_ys.size());
    #endif
    //m_curve->setData(new QwtPointArrayData(&m_xs[0],&m_ys[0],m_xs.size()));
  }

  {
    QVBoxLayout * const layout = new QVBoxLayout;
    layout->addWidget(m_plot);
    assert(!this->layout());
    this->setLayout(layout);
  }
}

void QwtPlotWidget::AddY(const double y)
{
  //Pop first, append y
  std::deque<double> d(m_ys.begin(),m_ys.end());
  d.pop_front();
  d.push_back(y);
  m_ys = std::vector<double>(d.begin(),d.end());
  assert(m_xs.size() == m_ys.size());

  m_curve->setData(new QwtPointArrayData(&m_xs[0],&m_ys[0],m_xs.size()));
  m_plot->replot(); //No replot, no glory
}

const std::vector<double> QwtPlotWidget::CreateXs(const int n)
{
  std::vector<double> v(n);
  for (int i=0; i!=n; ++i) { v[i] = static_cast<double>(i); }
  return v;
}
