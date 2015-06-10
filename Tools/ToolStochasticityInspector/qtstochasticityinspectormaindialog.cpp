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
#include "qtstochasticityinspectoraicwidget.h"
#include "qtstochasticityinspectorhlrtwidget.h"
#include "qtstochasticityinspectormodelcolors.h"

#pragma GCC diagnostic pop



ribi::QtStochasticityInspectorMainDialog::QtStochasticityInspectorMainDialog(
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStochasticityInspectorMainDialog),
    m_aic_widget{new QtStochasticityInspectorAicWidget},
    m_bm_likelihood_widget{new QtBrownianMotionLikelihoodWidget},
    m_bm_max_likelihood_widget{new QtBrownianMotionMaxLikelihoodWidget},
    m_bm_parameters_widget{new QtBrownianMotionParametersWidget},
    m_curve(new QwtPlotCurve),
    m_hlrt_widget{new QtStochasticityInspectorHlrtWidget},
    m_main_dialog{},
    m_ou_likelihood_widget{new QtOrnsteinUhlenbeckLikelihoodWidget},
    m_ou_max_likelihood_widget{new QtOrnsteinUhlenbeckMaxLikelihoodWidget},
    m_ou_parameters_widget{new QtOrnsteinUhlenbeckParametersWidget}
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

  //Hierarchical Likelihood Ratio Test widget
  {
    assert(!ui->page_hlrt->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->page_hlrt->setLayout(my_layout);
    my_layout->addWidget(m_hlrt_widget);
  }
  //Hierarchical Likelihood Ratio Test widget
  {
    assert(!ui->page_aic->layout());
    QVBoxLayout * const my_layout{new QVBoxLayout};
    ui->page_aic->setLayout(my_layout);
    my_layout->addWidget(m_aic_widget);
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
  const int t_end{m_bm_parameters_widget->GetEndTime()};
  const auto volatility
    = m_bm_parameters_widget->GetVolatility() / boost::units::si::second;
  const int seed{m_bm_parameters_widget->GetSeed()};

  if (volatility < 0.0 / boost::units::si::second) return;

  ribi::bm::Parameters parameters(volatility,seed);

  m_main_dialog = ribi::StochasticityInspectorMainDialog(init_x,t_end,parameters);

  //Plot
  const auto ts_with_unit = m_main_dialog.GetTimePoints();
  const auto xs = m_main_dialog.GetValues();

  //Strip units
  std::vector<double> ts;
  std::transform(begin(ts_with_unit),end(ts_with_unit),
    std::back_inserter(ts),
    [](const auto t) { return t.value();}
  );
  assert(ts.size() == ts_with_unit.size());
  assert(ts.size() == xs.size());

  m_curve->setPen(ribi::QtStochasticityInspectorModelColors::m_bm_color);
  m_curve->setData(new QwtPointArrayData(&ts[0],&xs[0],xs.size()));
  ui->plot->replot();

  OnNewData();
}

void ribi::QtStochasticityInspectorMainDialog::OnAnyChangeOrnsteinUhlenbeck() noexcept
{
  m_curve->setData(new QwtPointArrayData(0,0,0));

  const double init_x{m_ou_parameters_widget->GetInitValue()};
  const auto dt = m_ou_parameters_widget->GetTimestep();
  const auto t_end = m_ou_parameters_widget->GetEndTime() + dt;
  const auto mean_reversion_rate = m_ou_parameters_widget->GetMeanReversionRate();
  const double mu{m_ou_parameters_widget->GetTargetMean()};
  const auto sigma = m_ou_parameters_widget->GetVolatility();
  const int seed{m_ou_parameters_widget->GetSeed()};

  if (dt <= 0.0 * boost::units::si::second) return;
  if (mean_reversion_rate <= 0.0 / boost::units::si::second) return;

  ribi::ou::Parameters parameters(mean_reversion_rate,mu,sigma,seed);

  m_main_dialog = ribi::StochasticityInspectorMainDialog(init_x,dt,t_end,parameters);

  //Plot
  const auto ts_with_unit = m_main_dialog.GetTimePoints();
  const auto xs = m_main_dialog.GetValues();

  //Strip units
  std::vector<double> ts;
  std::transform(begin(ts_with_unit),end(ts_with_unit),
    std::back_inserter(ts),
    [](const auto t) { return t.value();}
  );
  assert(ts.size() == ts_with_unit.size());

  m_curve->setPen(ribi::QtStochasticityInspectorModelColors::m_ou_color);
  m_curve->setData(new QwtPointArrayData(&ts[0],&xs[0],xs.size()));
  ui->plot->replot();

  OnNewData();
}

void ribi::QtStochasticityInspectorMainDialog::OnNewData() noexcept
{
  const auto xs = m_main_dialog.GetValues();

  const auto dt = m_ou_parameters_widget->GetTimestep();
  m_bm_likelihood_widget->CalcLikelihood(xs);
  m_ou_likelihood_widget->CalcLikelihood(xs,dt);

  m_bm_max_likelihood_widget->SetData(xs);
  m_ou_max_likelihood_widget->SetData(xs,dt);

  m_hlrt_widget->ShowHlrt(
    m_bm_max_likelihood_widget->GetMaxLogLikelihood(),
    m_ou_max_likelihood_widget->GetMaxLogLikelihood()
  );

  m_aic_widget->ShowAic(
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
