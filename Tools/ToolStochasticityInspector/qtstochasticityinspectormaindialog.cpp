#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstochasticityinspectormaindialog.h"

#include <cassert>
#include <stdexcept>

#include <QDesktopWidget>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

#include "ornsteinuhlenbeck.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtstochasticityinspectormaindialog.h"

#if QWT_VERSION >= 0x060100
#include <qwt_point_data.h>
#endif

#pragma GCC diagnostic pop

ribi::QtStochasticityInspectorMainDialog::QtStochasticityInspectorMainDialog(
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStochasticityInspectorMainDialog),
    m_curve_ou(new QwtPlotCurve("Ornstein-Uhlenbeck"))
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  #ifdef _WIN32
  ui->plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  ui->plot->setCanvasBackground(QColor(255,255,255));
  #endif
  ui->plot->setAxisAutoScale(QwtPlot::xBottom);
  ui->plot->setAxisAutoScale(QwtPlot::yLeft);

  m_curve_ou->attach(ui->plot);
  m_curve_ou->setStyle(QwtPlotCurve::Lines);
  m_curve_ou->setPen(QPen(QColor(0,0,0)));

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(0,0,0)));
    grid->attach(ui->plot);

  }
  //Add zoomer
  {
    new QwtPlotZoomer(ui->plot->canvas());
  }

  //Add legend
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  QObject::connect(ui->box_dt,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_init_x,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_t_end,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_lambda,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_mu,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_sigma,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }

  OnAnyChange();
}

ribi::QtStochasticityInspectorMainDialog::~QtStochasticityInspectorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtStochasticityInspectorMainDialog::OnAnyChange() noexcept
{
  //Clear all plots
  #if (QWT_VERSION >= 0x060000)
  m_curve_ou->setData(new QwtPointArrayData(0,0,0));
  #else
  m_curve_ou->setData(0,0,0);
  #endif

  const double init_x{ui->box_init_x->value()};
  const double dt{ui->box_dt->value()};
  const double t_end{ui->box_t_end->value() + dt};
  const double lambda{ui->box_lambda->value()};
  const double mu{ui->box_mu->value()};
  const double sigma{ui->box_sigma->value()};
  const int seed{ui->box_seed->value()};

  if (dt <= 0.0) return;
  if (lambda <= 0.0) return;

  OrnsteinUhlenbeck sim(lambda,mu,sigma,seed);

  double x = init_x;
  std::vector<double> xs;
  std::vector<double> timeseries;

  for (double t=0.0; t<t_end; t+=dt)
  {
    xs.push_back(x);
    timeseries.push_back(t);
    x = sim.CalcNext(x,dt);
  }


  //Plot
  #if (QWT_VERSION >= 0x060000)
  m_curve_ou->setData(new QwtPointArrayData(&timeseries[0],&xs[0],xs.size()));
  #else
  m_curve_ou->setData(&timeseries[0],&inputs[0],inputs.size());
  #endif

  ui->plot->replot();
}

#ifndef NDEBUG
void ribi::QtStochasticityInspectorMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
