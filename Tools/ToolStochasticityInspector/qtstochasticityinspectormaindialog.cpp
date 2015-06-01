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
#include <qwt_column_symbol.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_multi_barchart.h>

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
    m_support_plot{new QwtPlot(QwtText("Support for different models"))},
    m_support_plot_barchart{new QwtPlotMultiBarChart},
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
  //Prepare support widget
  {
    for (int i=0; i!=2; ++i)
    {
      QwtColumnSymbol * symbol{new QwtColumnSymbol(QwtColumnSymbol::Box)};
      QPalette bar_color{i == 0 ? Qt::red : Qt::blue};
      symbol->setPalette(bar_color);
      m_support_plot_barchart->setSymbol(i,symbol);
    }
    QList<QwtText> titles;
    titles.push_back(QwtText("Brownian motion"));
    titles.push_back(QwtText("Ornstein-Uhlenbeck"));
    m_support_plot_barchart->setBarTitles(titles);

    QVector<QVector<double>> data;
    {
      const double a{0.6};
      const double b{1.0-a};
      QVector<double> this_bar = {a,b};
      data.push_back(this_bar);
    }
    m_support_plot_barchart->setSamples(data);
    m_support_plot_barchart->setStyle(QwtPlotMultiBarChart::Stacked);


    //plot is used to display the bar_plot on screen
    m_support_plot_barchart->attach(m_support_plot);
    m_support_plot->setAxisScale(QwtPlot::xBottom,0.0,1.0,1.0);
    m_support_plot->setAxisScale(QwtPlot::yLeft,0.0,1.0,0.1);
    m_support_plot->setAxisTitle(QwtPlot::xBottom,"Sample");
    m_support_plot->setAxisTitle(QwtPlot::yLeft,"Fractions");

    {
      QwtLegend * const legend = new QwtLegend;
      legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
      m_support_plot->insertLegend(legend, QwtPlot::RightLegend);
    }

  }
  //Likelihood widgets and support widget
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
    my_layout->addWidget(m_support_plot);


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

  OnNewData();
}

void ribi::QtStochasticityInspectorMainDialog::OnNewData() noexcept
{
  const double dt{m_ou_parameters_widget->GetTimestep()};
  m_bm_likelihood_widget->CalcLikelihood(m_xs);
  m_ou_likelihood_widget->CalcLikelihood(m_xs,dt);

  m_bm_max_likelihood_widget->SetData(m_xs);
  m_ou_max_likelihood_widget->SetData(m_xs,dt);

  //Calculate support
  QVector<QVector<double>> data;
  {
    const double a{m_bm_max_likelihood_widget->GetMaxLogLikelihood()};
    const double b{m_ou_max_likelihood_widget->GetMaxLogLikelihood()};
    QVector<double> this_bar = {a / (a+b),b / (a+b)};
    data.push_back(this_bar);
  }
  m_support_plot_barchart->setSamples(data);
  m_support_plot->replot();

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
