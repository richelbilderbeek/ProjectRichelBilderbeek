#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstochasticityinspectormaindialog.h"

#include <cassert>
#include <stdexcept>

#include <QLabel>
#include <QDesktopWidget>

#include <qwt_legend.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>

#include "brownianmotion.h"
#include "ornsteinuhlenbeck.h"
#include "testtimer.h"
#include "trace.h"
#include "qtornsteinuhlenbecklikelihoodwidget.h"
#include "qtornsteinuhlenbeckmaxlikelihoodwidget.h"
#include "qtbrownianmotionparameterswidget.h"
#include "qtbrownianmotionmaxlikelihoodwidget.h"
#include "qtbrownianmotionlikelihoodwidget.h"
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
    m_bm_likelihood_widget{new QtBrownianMotionLikelihoodWidget},
    m_bm_max_likelihood_widget{new QtBrownianMotionMaxLikelihoodWidget},
    m_bm_parameters_widget{new QtBrownianMotionParametersWidget},
    m_curve(new QwtPlotCurve),
    m_ou_likelihood_widget{new QtOrnsteinUhlenbeckLikelihoodWidget},
    m_ou_max_likelihood_widget{new QtOrnsteinUhlenbeckMaxLikelihoodWidget},
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

  m_curve->attach(ui->plot);
  m_curve->setStyle(QwtPlotCurve::Lines);
  m_curve->setPen(QPen(QColor(0,0,0)));

  //Brownian motion widget
  {
    assert(!ui->page_bm->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_bm->setLayout(my_layout);
    my_layout->addWidget(m_bm_parameters_widget);
  }
  //Ornstein-Uhlenbeck widget
  {
    assert(!ui->page_ou->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_ou->setLayout(my_layout);
    my_layout->addWidget(m_ou_parameters_widget);
  }
  //Ornstein-Uhlenbeck likelihood widget
  {
    assert(!ui->widget_likelihoods->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->widget_likelihoods->setLayout(my_layout);

    my_layout->addWidget(new QLabel("Brownian motion"));
    my_layout->addWidget(new QLabel("Likelihood"));
    my_layout->addWidget(m_bm_likelihood_widget);
    my_layout->addWidget(new QLabel("Max likelihood"));
    my_layout->addWidget(m_bm_max_likelihood_widget);


    my_layout->addWidget(new QLabel("Ornstein-Uhlenbeck"));
    my_layout->addWidget(new QLabel("Likelihood"));
    my_layout->addWidget(m_ou_likelihood_widget);
    my_layout->addWidget(new QLabel("Max likelihood"));
    my_layout->addWidget(m_ou_max_likelihood_widget);
  }

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(0,0,0)));
    grid->attach(ui->plot);

  }
  if (!"Add zoomer")
  {
    new QwtPlotZoomer(ui->plot->canvas());
  }
  if (!"Add legend")
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  QObject::connect(m_bm_likelihood_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnCalculateLikelihood()));
  QObject::connect(m_bm_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChangeBrownian()));
  QObject::connect(m_ou_likelihood_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnCalculateLikelihood()));
  QObject::connect(m_ou_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChangeOrnsteinUhlenbeck()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10, screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }

  OnAnyChangeBrownian();
  //OnAnyChangeOrnsteinUhlenbeck();
}

ribi::QtStochasticityInspectorMainDialog::~QtStochasticityInspectorMainDialog() noexcept
{
  delete ui;
}

void ribi::QtStochasticityInspectorMainDialog::OnAnyChangeBrownian() noexcept
{
  m_curve->setData(new QwtPointArrayData(0,0,0));

  const double init_x{m_bm_parameters_widget->GetInitValue()};
  const int t_end{m_bm_parameters_widget->GetEndTime() + 1};
  const double volatility{m_bm_parameters_widget->GetVolatility()};
  const int seed{m_bm_parameters_widget->GetSeed()};

  if (volatility < 0.0) return;

  BrownianMotion sim(volatility,seed);

  double x = init_x;
  m_ts.clear();
  m_xs.clear();

  for (int i=0; i < t_end; ++i)
  {
    m_xs.push_back(x);
    m_ts.push_back(static_cast<double>(i));
    x = sim.CalcNext(x);
  }


  //Plot
  m_curve->setData(new QwtPointArrayData(&m_ts[0],&m_xs[0],m_xs.size()));
  ui->plot->replot();

  OnCalculateLikelihood();
}

void ribi::QtStochasticityInspectorMainDialog::OnAnyChangeOrnsteinUhlenbeck() noexcept
{
  m_curve->setData(new QwtPointArrayData(0,0,0));

  const double init_x{m_ou_parameters_widget->GetInitValue()};
  const double dt{m_ou_parameters_widget->GetTimestep()};
  const double t_end{m_ou_parameters_widget->GetEndTime() + dt};
  const double lambda{m_ou_parameters_widget->GetMeanReversionRate()};
  const double mu{m_ou_parameters_widget->GetTargetMean()};
  const double sigma{m_ou_parameters_widget->GetVolatility()};
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
  m_curve->setData(new QwtPointArrayData(&m_ts[0],&m_xs[0],m_xs.size()));
  ui->plot->replot();

  OnCalculateLikelihood();
}

void ribi::QtStochasticityInspectorMainDialog::OnCalculateLikelihood() noexcept
{
  const double dt{m_ou_parameters_widget->GetTimestep()};
  m_bm_likelihood_widget->CalcLikelihood(m_xs);
  m_ou_likelihood_widget->CalcLikelihood(m_xs,dt);

  m_bm_max_likelihood_widget->CalcMaxLikelihood(m_xs);
  m_ou_max_likelihood_widget->CalcMaxLikelihood(m_xs,dt);

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
