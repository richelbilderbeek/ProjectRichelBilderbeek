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
#include "qtornsteinuhlenbeckparameterswidget.h"
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
    m_ou_parameters_widget{new QtOrnsteinUhlenbeckParametersWidget},
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

  //Ornstein-Uhlenbeck widget
  {
    assert(!ui->page_ou->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_ou->setLayout(my_layout);
    my_layout->addWidget(m_ou_parameters_widget);
  }

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
  if (!"Add legend")
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  QObject::connect(m_ou_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));



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

  const double init_x{m_ou_parameters_widget->GetInitValue()};
  const double dt{m_ou_parameters_widget->GetTimestep()};
  const double t_end{m_ou_parameters_widget->GetEndTime() + dt};
  const double lambda{m_ou_parameters_widget->GetLambda()};
  const double mu{m_ou_parameters_widget->GetMu()};
  const double sigma{m_ou_parameters_widget->GetSigma()};
  const int seed{m_ou_parameters_widget->GetSeed()};

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
  m_ou_parameters_widget->CalcLikelihood(m_xs);
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
