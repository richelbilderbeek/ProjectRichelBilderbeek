#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstateobservermaindialog.h"

#include <cassert>
#include <stdexcept>

#include "qwt_legend.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"

#include "alphabetafilter.h"
#include "alphabetagammafilter.h"
#include "alphafilter.h"
#include "integeralphafilter.h"
#include "integersymmetricalphafilter.h"
#include "multialphafilter.h"
#include "multiintegerstateobserver.h"
#include "noisefunctionparser.h"
#include "slidingmodeobserver.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtstateobservermaindialog.h"

#if QWT_VERSION >= 0x060100
#include <qwt_point_data.h>
#endif

#pragma GCC diagnostic pop

ribi::QtStateObserverMainDialog::QtStateObserverMainDialog(
  QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtStateObserverMainDialog),
    m_curve_inputs(new QwtPlotCurve("Inputs")),
    m_curve_outputs_alpha(new QwtPlotCurve("Alpha filter estimations")),
    m_curve_outputs_alpha_beta(new QwtPlotCurve("Alpha beta filter estimations")),
    m_curve_outputs_alpha_beta_gamma(new QwtPlotCurve("Alpha beta gamma filter estimations")),
    m_curve_outputs_lsq(new QwtPlotCurve("LSQ filter estimations")),
    m_curve_outputs_slsq(new QwtPlotCurve("SLSQ filter estimations")),
    m_curve_outputs_ma(new QwtPlotCurve("Multi alpha filter estimations")),
    m_curve_outputs_miso(new QwtPlotCurve("Multi integer state observer estimations"))
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

  m_curve_inputs->attach(ui->plot);
  m_curve_inputs->setStyle(QwtPlotCurve::Dots);
  {
    QPen pen;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(2);
    m_curve_inputs->setPen(pen);
  }

  m_curve_outputs_alpha->attach(ui->plot);
  m_curve_outputs_alpha->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha->setPen(QPen(QColor(196,0,0)));

  m_curve_outputs_alpha_beta->attach(ui->plot);
  m_curve_outputs_alpha_beta->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha_beta->setPen(QPen(QColor(255,127,0)));

  m_curve_outputs_alpha_beta_gamma->attach(ui->plot);
  m_curve_outputs_alpha_beta_gamma->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha_beta_gamma->setPen(QPen(QColor(212,212,0)));

  //LSQ
  {
    m_curve_outputs_lsq->attach(ui->plot);
    m_curve_outputs_lsq->setStyle(QwtPlotCurve::Lines);
    QPen pen;
    pen.setColor(QColor(0,196,0));
    pen.setWidth(3);
    pen.setDashPattern( {2.0,2.0} );
    m_curve_outputs_lsq->setPen(pen);
  }

  //SLSQ
  {
    m_curve_outputs_slsq->attach(ui->plot);
    m_curve_outputs_slsq->setStyle(QwtPlotCurve::Lines);
    QPen pen;
    pen.setColor(QColor(0,196,196));
    pen.setWidth(3);
    pen.setDashPattern( {2.0,3.0} );
    m_curve_outputs_slsq->setPen(pen);
  }

  m_curve_outputs_ma->attach(ui->plot);
  m_curve_outputs_ma->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_ma->setPen(QPen(QColor(0,0,212)));

  //MI
  {
    m_curve_outputs_miso->attach(ui->plot);
    m_curve_outputs_miso->setStyle(QwtPlotCurve::Lines);
    QPen pen;
    pen.setColor(QColor(196,0,196));
    pen.setWidth(3);
    pen.setDashPattern( {3.0,3.0} );
    m_curve_outputs_miso->setPen(pen);
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
  //Add panner
  //{
  //  QwtPlotPanner * const panner = new QwtPlotPanner(ui->plot->canvas());
  //  panner->setMouseButton(Qt::MiddleButton);
  //}
  //Add legend
  {
    QwtLegend * const legend = new QwtLegend;
    legend->setFrameStyle(QFrame::Box|QFrame::Sunken);
    ui->plot->insertLegend(legend, QwtPlot::RightLegend);
  }

  QObject::connect(ui->box_alpha_a,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_alpha_ab,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_alpha_abg,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_beta_ab,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_beta_abg,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_gamma_abg,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_lsq_shift,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->check_miso_1,static_cast<void (QAbstractButton::*)(bool)>(&QAbstractButton::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->check_miso_2,static_cast<void (QAbstractButton::*)(bool)>(&QAbstractButton::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_slsq_shift,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_miso_shift_1,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_miso_shift_2,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_timesteps,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->edit_noise,static_cast<void (QLineEdit::*)(const QString&)>(&QLineEdit::textChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_ma_1,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->box_ma_2,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupbox_abg,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupbox_alpha,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupbox_beta,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupbox_lsq,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupBox_ma,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupBox_miso,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  QObject::connect(ui->groupBox_slsq,static_cast<void (QGroupBox::*)(bool)>(&QGroupBox::clicked),this,&ribi::QtStateObserverMainDialog::Run);
  Run();
}

ribi::QtStateObserverMainDialog::~QtStateObserverMainDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<ribi::AlphaFilter> ribi::QtStateObserverMainDialog::CreateAlphaFilter() const noexcept
{
  const double alpha  = ui->box_alpha_a->value();
  const double dt = CreateDt();
  const boost::shared_ptr<AlphaFilter> filter(new AlphaFilter(alpha,dt));
  assert(filter);
  return filter;
}

const boost::shared_ptr<ribi::AlphaBetaFilter> ribi::QtStateObserverMainDialog::CreateAlphaBetaFilter() const noexcept
{
  const double alpha = ui->box_alpha_ab->value();
  const double beta = ui->box_beta_ab->value();
  const double dt = CreateDt();
  const boost::shared_ptr<AlphaBetaFilter> filter(new AlphaBetaFilter(alpha,beta,dt));
  assert(filter);
  return filter;
}

const boost::shared_ptr<ribi::AlphaBetaGammaFilter> ribi::QtStateObserverMainDialog::CreateAlphaBetaGammaFilter() const noexcept
{
  const double alpha = ui->box_alpha_abg->value();
  const double beta = ui->box_beta_abg->value();
  const double gamma = ui->box_gamma_abg->value();
  const double dt = CreateDt();
  const boost::shared_ptr<AlphaBetaGammaFilter> filter(new AlphaBetaGammaFilter(alpha,beta,gamma,dt));
  assert(filter);
  return filter;
}

const boost::shared_ptr<ribi::IntegerAlphaFilter> ribi::QtStateObserverMainDialog::CreateLsqFilter() const noexcept
{
  const int shift_lsq = ui->box_lsq_shift->value();
  const boost::shared_ptr<IntegerAlphaFilter> filter(new IntegerAlphaFilter(shift_lsq));
  assert(filter);
  return filter;
}

const boost::shared_ptr<ribi::IntegerSymmetricalAlphaFilter> ribi::QtStateObserverMainDialog::CreateSlsqFilter() const noexcept
{
  const int shift_slsq = ui->box_slsq_shift->value();
  const boost::shared_ptr<IntegerSymmetricalAlphaFilter> filter(new IntegerSymmetricalAlphaFilter(shift_slsq));
  assert(filter);
  return filter;
}


const boost::shared_ptr<ribi::MultiAlphaFilter> ribi::QtStateObserverMainDialog::CreateMultiAlphaFilter() const noexcept
{
  const double ma_1 = ui->box_ma_1->value();
  const double ma_2 = ui->box_ma_2->value();
  const std::vector<double> alphas = { ma_1, ma_2 };
  const boost::shared_ptr<MultiAlphaFilter> filter(new MultiAlphaFilter(alphas));
  assert(filter);
  return filter;
}

const boost::shared_ptr<ribi::MultiIntegerStateObserver> ribi::QtStateObserverMainDialog::CreateMiso() const noexcept
{
  std::vector<boost::shared_ptr<IntegerStateObserver> > state_observers;
  {
    const bool is_symmetric = ui->check_miso_1->isChecked();
    const int alpha = ui->box_miso_shift_1->value();
    boost::shared_ptr<IntegerStateObserver> state_observer;
    if (!is_symmetric) state_observer.reset(new IntegerAlphaFilter(alpha));
    else state_observer.reset(new IntegerSymmetricalAlphaFilter(alpha));
    assert(state_observer);
    state_observers.push_back(state_observer);
  }
  {
    const bool is_symmetric = ui->check_miso_2->isChecked();
    const int alpha = ui->box_miso_shift_2->value();
    boost::shared_ptr<IntegerStateObserver> state_observer;
    if (!is_symmetric) state_observer.reset(new IntegerAlphaFilter(alpha));
    else state_observer.reset(new IntegerSymmetricalAlphaFilter(alpha));
    assert(state_observer);
    state_observers.push_back(state_observer);
  }

  const boost::shared_ptr<MultiIntegerStateObserver> filter(new MultiIntegerStateObserver(state_observers));
  assert(filter);
  return filter;
}

void ribi::QtStateObserverMainDialog::Run() noexcept
{
  const int timesteps = ui->box_timesteps->value();
  const std::string noise_function_str = ui->edit_noise->text().toStdString();
  try
  {
    NoiseFunctionParser(noise_function_str,"t");
  }
  catch (std::runtime_error&)
  {
    //Invalid function
    return;
  }
  NoiseFunctionParser noise_function(noise_function_str,"t");

  std::vector<double> inputs;
  std::vector<double> outputs_alpha;
  std::vector<double> outputs_alpha_beta;
  std::vector<double> outputs_alpha_beta_gamma;
  std::vector<double> outputs_lsq;
  std::vector<double> outputs_slsq;
  std::vector<double> outputs_ma;
  std::vector<double> outputs_miso;

  ui->label_value_dt_a->setText(QString::number(CreateDt()));

  //Use filters
  {
    const auto filter_alpha = CreateAlphaFilter();
    const auto filter_alpha_beta = CreateAlphaBetaFilter();
    const auto filter_alpha_beta_gamma = CreateAlphaBetaGammaFilter();
    const auto filter_lsq = CreateLsqFilter();
    const auto filter_slsq = CreateSlsqFilter();
    const auto filter_ma = CreateMultiAlphaFilter();
    const auto filter_miso = CreateMiso();
    for (int t=0; t!=timesteps; ++t)
    {
      const double measurement = noise_function.Evaluate(static_cast<double>(t));

      filter_alpha->Update(measurement);
      filter_alpha_beta->Update(measurement);
      filter_alpha_beta_gamma->Update(measurement);
      filter_lsq->Update(measurement);
      filter_slsq->Update(measurement);
      filter_ma->Update(measurement);
      filter_miso->Update(measurement);

      const double output_alpha            = filter_alpha->GetEstimate();
      const double output_alpha_beta       = filter_alpha_beta->GetEstimate();
      const double output_alpha_beta_gamma = filter_alpha_beta_gamma->GetEstimate();
      const double output_lsq              = filter_lsq->GetEstimate();
      const double output_slsq             = filter_slsq->GetEstimate();
      const double output_ma               = filter_ma->GetEstimate();
      const double output_miso             = filter_miso->GetEstimate();
      inputs.push_back(measurement);
      outputs_alpha.push_back(output_alpha);
      outputs_alpha_beta.push_back(output_alpha_beta);
      outputs_alpha_beta_gamma.push_back(output_alpha_beta_gamma);
      outputs_lsq.push_back(output_lsq);
      outputs_slsq.push_back(output_slsq);
      outputs_ma.push_back(output_ma);
      outputs_miso.push_back(output_miso);
    }
  }
  //Clear all plots
  #if (QWT_VERSION >= 0x060000)
  m_curve_outputs_alpha->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_alpha_beta->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_alpha_beta_gamma->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_lsq->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_slsq->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_ma->setData(new QwtPointArrayData(0,0,0));
  m_curve_outputs_miso->setData(new QwtPointArrayData(0,0,0));
  #else
  m_curve_outputs_alpha->setData(0,0,0);
  m_curve_outputs_alpha_beta->setData(0,0,0);
  m_curve_outputs_alpha_beta_gamma->setData(0,0,0);
  m_curve_outputs_lsq->setData(0,0,0);
  m_curve_outputs_slsq->setData(0,0,0);
  m_curve_outputs_ma->setData(0,0,0);
  m_curve_outputs_miso->setData(0,0,0);
  #endif
  //Plot
  {
    std::vector<double> timeseries;
    for (int i=0; i!=timesteps; ++i)
    {
      timeseries.push_back(static_cast<double>(i));
    }
    #if (QWT_VERSION >= 0x060000)
    m_curve_inputs->setData(new QwtPointArrayData(&timeseries[0],&inputs[0],inputs.size()));
    if (ui->groupbox_alpha->isChecked())
    {
      m_curve_outputs_alpha->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha[0],outputs_alpha.size()));
    }
    if (ui->groupbox_beta->isChecked())
    {
      m_curve_outputs_alpha_beta->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha_beta[0],outputs_alpha_beta.size()));
    }
    if (ui->groupbox_abg->isChecked())
    {
      m_curve_outputs_alpha_beta_gamma->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha_beta_gamma[0],outputs_alpha_beta_gamma.size()));
    }
    if (ui->groupbox_lsq->isChecked())
    {
      m_curve_outputs_lsq->setData(new QwtPointArrayData(&timeseries[0],&outputs_lsq[0],outputs_lsq.size()));
    }
    if (ui->groupBox_slsq->isChecked())
    {
      m_curve_outputs_slsq->setData(new QwtPointArrayData(&timeseries[0],&outputs_slsq[0],outputs_slsq.size()));
    }
    if (ui->groupBox_ma->isChecked())
    {
      m_curve_outputs_ma->setData(new QwtPointArrayData(&timeseries[0],&outputs_ma[0],outputs_ma.size()));
    }
    if (ui->groupBox_miso->isChecked())
    {
      m_curve_outputs_miso->setData(new QwtPointArrayData(&timeseries[0],&outputs_miso[0],outputs_miso.size()));
    }
    #else
    m_curve_inputs->setData(&timeseries[0],&inputs[0],inputs.size());
    if (ui->groupbox_alpha->isChecked())
    {
      m_curve_outputs_alpha->setData(&timeseries[0],&outputs_alpha[0],outputs_alpha.size());
    }
    if (ui->groupbox_beta->isChecked())
    {
      m_curve_outputs_alpha_beta->setData(&timeseries[0],&outputs_alpha_beta[0],outputs_alpha_beta.size());
    }
    if (ui->groupbox_abg->isChecked())
    {
      m_curve_outputs_alpha_beta_gamma->setData(&timeseries[0],&outputs_alpha_beta_gamma[0],outputs_alpha_beta_gamma.size());
    }
    if (ui->groupbox_lsq->isChecked())
    {
      m_curve_outputs_lsq->setData(&timeseries[0],&outputs_lsq[0],outputs_lsq.size());
    }
    if (ui->groupBox_slsq->isChecked())
    {
      m_curve_outputs_slsq->setData(&timeseries[0],&outputs_slsq[0],outputs_slsq.size());
    }
    if (ui->groupBox_ma->isChecked())
    {
      m_curve_outputs_ma->setData(&timeseries[0],&outputs_ma[0],outputs_ma.size());
    }
    if (ui->groupBox_miso->isChecked())
    {
      m_curve_outputs_miso->setData(&timeseries[0],&outputs_miso[0],outputs_miso.size());
    }
    #endif
    ui->plot->replot();
  }
}

void ribi::QtStateObserverMainDialog::on_button_rerun_clicked() noexcept
{
  this->Run();
}

#ifndef NDEBUG
void ribi::QtStateObserverMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
