#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestsimplelinearregressionmaindialog.h"

#include <cassert>
#include <sstream>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

#include "simplelinearregression.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestsimplelinearregressionmaindialog.h"

#pragma GCC diagnostic pop

ribi::QtToolTestSimpleLinearRegressionMainDialog::QtToolTestSimpleLinearRegressionMainDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolTestSimpleLinearRegressionMainDialog),
    m_curve_approximation(new QwtPlotCurve),
    m_curve_values(new QwtPlotCurve),
    m_plot(new QwtPlot),
    m_xs{},
    m_ys{}
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  //Set up the plot
  assert(m_plot);
  m_plot->setTitle("SimpleLinearRegression");
  m_plot->setAxisTitle(QwtPlot::xBottom,"X");
  m_plot->setAxisTitle(QwtPlot::yLeft,"Y");
  #ifdef _WIN32
  m_plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  m_plot->setCanvasBackground(QColor(255,255,255));
  #endif

  //Create plots
  assert(m_curve_values);
  m_curve_values->setTitle("Points");
  m_curve_values->attach(m_plot.get());
  m_curve_values->setStyle(QwtPlotCurve::Dots);
  m_curve_values->setPen(QPen(QColor(255,0,0),5));

  assert(m_curve_approximation);
  m_curve_approximation->setTitle("Trendline");
  m_curve_approximation->attach(m_plot.get());
  m_curve_approximation->setStyle(QwtPlotCurve::Dots);
  m_curve_approximation->setPen(QPen(QColor(0,0,255),3));

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(m_plot.get());
  }
  //Add zoomer
  {
    new QwtPlotZoomer(m_plot->canvas());
  }
  {
    // legend
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    m_plot->insertLegend(legend, QwtPlot::RightLegend);
  }
  assert(ui->verticalLayout->layout());
  ui->verticalLayout->layout()->addWidget(m_plot.get());

  m_plot->setAxisScale(
    QwtPlot::xBottom,
    static_cast<double>(ui->box_int_x->minimum()),
    static_cast<double>(ui->box_int_x->maximum())
  );
  m_plot->setAxisScale(
    QwtPlot::yLeft,
    static_cast<double>(ui->box_double_y->minimum()),
    static_cast<double>(ui->box_double_y->maximum())
  );

  //Add some nice testing values
  ui->box_int_x->setValue(ui->box_int_x->minimum() / 2);
  ui->box_double_y->setValue(ui->box_double_y->maximum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->minimum() / 4);
  ui->box_double_y->setValue(ui->box_double_y->minimum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->maximum() / 4);
  ui->box_double_y->setValue(ui->box_double_y->maximum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(ui->box_int_x->maximum() / 2);
  ui->box_double_y->setValue(ui->box_double_y->minimum() / 2.0);
  on_button_clicked();

  ui->box_int_x->setValue(0);
  ui->box_double_y->setValue(0.0);

  TRACE_FUNC();
}

ribi::QtToolTestSimpleLinearRegressionMainDialog::~QtToolTestSimpleLinearRegressionMainDialog() noexcept
{
  delete ui;
}

void ribi::QtToolTestSimpleLinearRegressionMainDialog::on_button_clicked() noexcept
{
  const int x = ui->box_int_x->value();
  const double y = ui->box_double_y->value();
  m_xs.push_back(x);
  m_ys.push_back(y);
  Plot();
}

void ribi::QtToolTestSimpleLinearRegressionMainDialog::Plot() noexcept
{
  //Plot values
  {
    #if QWT_VERSION >= 0x060100 || !WIN32
    m_curve_values->setData(new QwtPointArrayData(&m_xs[0],&m_ys[0],m_xs.size()));
    #else
    m_curve_values->setData(&m_xs[0],&m_y[0],m_xs.size());
    #endif
  }

  const double min_x = static_cast<double>(ui->box_int_x->minimum());
  const double max_x = static_cast<double>(ui->box_int_x->maximum());

  //Plot approximation
  {
    const std::pair<double,double> p
      = SimpleLinearRegression::CalculateBestFit(m_xs,m_ys);
    const double slope = p.first;
    const double intercept = p.second;
    {
      std::stringstream s;
      s << "y = " << slope << ".x" << (intercept >= 0.0 ? "+":"") << intercept;
      this->setWindowTitle(s.str().c_str());
    }
    std::vector<double> xs;
    std::vector<double> ys;
    for (double t=min_x; t < max_x; t+=0.5)
    {
      const double x = static_cast<double>(t);
      const double y = intercept + (slope * x);
      ys.push_back(y);
      xs.push_back(x);
    }
    assert(m_curve_approximation);
    #if QWT_VERSION >= 0x060000
    m_curve_approximation->setData(new QwtPointArrayData(&xs[0],&ys[0],xs.size()));
    #else
    m_curve_approximation->setData(&xs[0],&y[0],xs.size());
    #endif
  }
  assert(m_plot);
  m_plot->replot();
}

#ifndef NDEBUG
void ribi::QtToolTestSimpleLinearRegressionMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
