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
    m_curve_ou(new QwtPlotCurve("Ornstein-Uhlenbeck")),
    m_ts{},
    m_xs{}
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

  QObject::connect(ui->box_cand_lambda,SIGNAL(valueChanged(double)),this,SLOT(OnCalculateLikelihood()));
  QObject::connect(ui->box_cand_mu,SIGNAL(valueChanged(double)),this,SLOT(OnCalculateLikelihood()));
  QObject::connect(ui->box_cand_sigma,SIGNAL(valueChanged(double)),this,SLOT(OnCalculateLikelihood()));

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
  m_ts.clear();
  m_xs.clear();

  for (double t=0.0; t<t_end; t+=dt)
  {
    m_xs.push_back(x);
    m_ts.push_back(t);
    x = sim.CalcNext(x,dt);
  }


  //Plot
  #if (QWT_VERSION >= 0x060000)
  m_curve_ou->setData(new QwtPointArrayData(&m_ts[0],&m_xs[0],m_xs.size()));
  #else
  m_curve_ou->setData(&timeseries[0],&inputs[0],inputs.size());
  #endif

  ui->plot->replot();

  OnCalculateLikelihood();


  //Recover the parameters with Ornstein-Uhlenbeck
  {
    double lambda_hat = 0.0;
    double mu_hat = 0.0;
    double sigma_hat = 0.0;
    OrnsteinUhlenbeck::CalcMaxLikelihood(m_xs,dt,lambda_hat,mu_hat,sigma_hat);
    ui->edit_lambda_hat->setText(std::to_string(lambda_hat).c_str());
    ui->edit_mu_hat->setText(std::to_string(mu_hat).c_str());
    ui->edit_sigma_hat->setText(std::to_string(sigma_hat).c_str());
    const double max_log_likelihood{
      OrnsteinUhlenbeck::CalcLogLikelihood(m_xs,dt,lambda_hat,mu_hat,sigma_hat)
    };
    ui->edit_max_log_likelihood->setText(std::to_string(max_log_likelihood).c_str());
  }
}

void ribi::QtStochasticityInspectorMainDialog::OnCalculateLikelihood() noexcept
{
  const double dt{ui->box_dt->value()};
  const double cand_lambda{ui->box_cand_lambda->value()};
  const double cand_mu{ui->box_cand_mu->value()};
  const double cand_sigma{ui->box_cand_sigma->value()};

  if (dt <= 0.0) return;
  if (m_xs.size() <= 2) return;
  if (cand_lambda <= 0.0) return;

  const double log_likelihood{
    OrnsteinUhlenbeck::CalcLogLikelihood(m_xs,dt,cand_lambda,cand_mu,cand_sigma)
  };
  ui->edit_log_likelihood->setText(std::to_string(log_likelihood).c_str());
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
