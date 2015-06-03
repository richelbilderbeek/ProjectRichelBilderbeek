#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstochasticityinspectormaindialog.h"

#include <cassert>
#include <stdexcept>

#include <QLabel>
#include <QDesktopWidget>

#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_point_data.h>

#include "brownianmotionprocess.h"
#include "ornsteinuhlenbeckparameters.h"
#include "ornsteinuhlenbeckprocess.h"
#include "testtimer.h"
#include "trace.h"
#include "qtornsteinuhlenbecklikelihoodwidget.h"
#include "qtornsteinuhlenbeckmaxlikelihoodwidget.h"
#include "qtbrownianmotionparameterswidget.h"
#include "qtbrownianmotionmaxlikelihoodwidget.h"
#include "qtbrownianmotionlikelihoodwidget.h"
#include "qtornsteinuhlenbeckparameterswidget.h"
#include "ui_qtstochasticityinspectormaindialog.h"
#include "qtstochasticityinspectorsupportwidget.h"
#include "qtstochasticityinspectormodelcolors.h"

#pragma GCC diagnostic pop



ribi::QtStochasticityInspectorMainDialog::QtStochasticityInspectorMainDialog(
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStochasticityInspectorMainDialog),
    m_bm_likelihood_widget{new QtBrownianMotionLikelihoodWidget},
    m_bm_max_likelihood_widget{new QtBrownianMotionMaxLikelihoodWidget},
    m_bm_parameters_widget{new QtBrownianMotionParametersWidget},
    m_curve(new QwtPlotCurve),
    m_main_dialog{},
    m_ou_likelihood_widget{new QtOrnsteinUhlenbeckLikelihoodWidget},
    m_ou_max_likelihood_widget{new QtOrnsteinUhlenbeckMaxLikelihoodWidget},
    m_ou_parameters_widget{new QtOrnsteinUhlenbeckParametersWidget},
    m_support_widget{new QtStochasticityInspectorSupportWidget}
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
    assert(!ui->page_bm_input->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_bm_input->setLayout(my_layout);
    my_layout->addWidget(m_bm_parameters_widget);
  }
  //Ornstein-Uhlenbeck widget
  {
    assert(!ui->page_ou_input->layout());
    QGridLayout * const my_layout{new QGridLayout};
    ui->page_ou_input->setLayout(my_layout);
    my_layout->addWidget(m_ou_parameters_widget);
  }
  //Brownian motion analysis widget
  {
    assert(!ui->page_bm_analysis->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->page_bm_analysis->setLayout(my_layout);
    my_layout->addWidget(new QLabel("Likelihood"));
    my_layout->addWidget(m_bm_likelihood_widget);
    my_layout->addWidget(new QLabel("Max likelihood"));
    my_layout->addWidget(m_bm_max_likelihood_widget);
  }

  //OU analysis widget
  {
    assert(!ui->page_ou_analysis->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->page_ou_analysis->setLayout(my_layout);
    my_layout->addWidget(new QLabel("Likelihood"));
    my_layout->addWidget(m_ou_likelihood_widget);
    my_layout->addWidget(new QLabel("Max likelihood"));
    my_layout->addWidget(m_ou_max_likelihood_widget);
  }

  //Support widget
  {
    assert(!ui->page_likelihoods->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->page_likelihoods->setLayout(my_layout);
    my_layout->addWidget(m_support_widget);
  }

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(0,0,0)));
    grid->attach(ui->plot);

  }

  QObject::connect(m_bm_likelihood_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnNewData()));
  QObject::connect(m_bm_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChangeBrownian()));
  QObject::connect(m_ou_likelihood_widget,SIGNAL(signal_parameters_changed()),this,SLOT(OnNewData()));
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

  ribi::bm::Parameters parameters(volatility,seed);

  m_main_dialog = StochasticityInspectorMainDialog(init_x,t_end,parameters);

  //Plot
  const auto ts = m_main_dialog.GetTimePoints();
  const auto xs = m_main_dialog.GetValues();

  m_curve->setPen(ribi::QtStochasticityInspectorModelColors::m_bm_color);
  m_curve->setData(new QwtPointArrayData(&ts[0],&xs[0],xs.size()));
  ui->plot->replot();

  OnNewData();
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

  ribi::ou::Parameters parameters(lambda,mu,sigma,seed);

  m_main_dialog = StochasticityInspectorMainDialog(init_x,dt,t_end,parameters);

  //Plot
  const auto ts = m_main_dialog.GetTimePoints();
  const auto xs = m_main_dialog.GetValues();

  m_curve->setPen(ribi::QtStochasticityInspectorModelColors::m_ou_color);
  m_curve->setData(new QwtPointArrayData(&ts[0],&xs[0],xs.size()));
  ui->plot->replot();

  OnNewData();
}

void ribi::QtStochasticityInspectorMainDialog::OnNewData() noexcept
{
  const auto xs = m_main_dialog.GetValues();

  const double dt{m_ou_parameters_widget->GetTimestep()};
  m_bm_likelihood_widget->CalcLikelihood(xs);
  m_ou_likelihood_widget->CalcLikelihood(xs,dt);

  m_bm_max_likelihood_widget->SetData(xs);
  m_ou_max_likelihood_widget->SetData(xs,dt);

  m_support_widget->ShowSupport(
    m_bm_max_likelihood_widget->GetMaxLogLikelihood(),
    m_ou_max_likelihood_widget->GetMaxLogLikelihood()
  );
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
