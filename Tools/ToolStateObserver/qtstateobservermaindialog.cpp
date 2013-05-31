#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtstateobservermaindialog.h"

#include <cassert>
#include <stdexcept>

#include "qwt_legend.h"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"

#include "alphafilter.h"
#include "alphabetafilter.h"
#include "lsqfilter.h"
#include "alphabetagammafilter.h"
#include "multialphafilter.h"
#include "noisefunctionparser.h"
#include "slidingmodeobserver.h"
#include "ui_qtstateobservermaindialog.h"

QtStateObserverMainDialog::QtStateObserverMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStateObserverMainDialog),
  m_curve_inputs(new QwtPlotCurve("Inputs")),
  m_curve_outputs_alpha(new QwtPlotCurve("Alpha filter estimations")),
  m_curve_outputs_alpha_beta(new QwtPlotCurve("Alpha beta filter estimations")),
  m_curve_outputs_alpha_beta_gamma(new QwtPlotCurve("Alpha beta gamma filter estimations")),
  m_curve_outputs_lsq(new QwtPlotCurve("LSQ filter estimations")),
  m_curve_outputs_ma(new QwtPlotCurve("Multi alpha filter estimations"))
{
  ui->setupUi(this);

  #ifdef _WIN32
  ui->plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  ui->plot->setCanvasBackground(QColor(255,255,255));
  #endif
  ui->plot->setAxisAutoScale(QwtPlot::xBottom);
  ui->plot->setAxisAutoScale(QwtPlot::yLeft);

  m_curve_inputs->attach(ui->plot);
  m_curve_inputs->setStyle(QwtPlotCurve::Lines);
  m_curve_inputs->setPen(QPen(QColor(128,128,128)));

  m_curve_outputs_alpha->attach(ui->plot);
  m_curve_outputs_alpha->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha->setPen(QPen(QColor(255,0,0)));

  m_curve_outputs_alpha_beta->attach(ui->plot);
  m_curve_outputs_alpha_beta->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha_beta->setPen(QPen(QColor(0,196,0)));

  m_curve_outputs_alpha_beta_gamma->attach(ui->plot);
  m_curve_outputs_alpha_beta_gamma->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_alpha_beta_gamma->setPen(QPen(QColor(196,196,0)));

  m_curve_outputs_lsq->attach(ui->plot);
  m_curve_outputs_lsq->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_lsq->setPen(QPen(QColor(0,0,255)));

  m_curve_outputs_ma->attach(ui->plot);
  m_curve_outputs_ma->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs_ma->setPen(QPen(QColor(0,196,196)));

  //Add grid
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
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

  QObject::connect(ui->box_alpha_a,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_alpha_ab,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_alpha_abg,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_beta_ab,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_beta_abg,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_gamma_abg,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->slider_shift,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->box_timesteps,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->edit_noise,SIGNAL(textChanged(QString)),this,SLOT(Run()));
  QObject::connect(ui->box_ma_1,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_ma_2,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  Run();
}

QtStateObserverMainDialog::~QtStateObserverMainDialog()
{
  delete ui;
}

void QtStateObserverMainDialog::Run()
{
  const int timesteps = ui->box_timesteps->value();
  const double alpha_a  = ui->box_alpha_a->value();
  const double alpha_ab = ui->box_alpha_ab->value();
  const double alpha_abg = ui->box_alpha_abg->value();

  const double ma_1 = ui->box_ma_1->value();
  const double ma_2 = ui->box_ma_2->value();

  const double beta_ab = ui->box_beta_ab->value();
  const double beta_abg = ui->box_beta_abg->value();
  const double dt = 1.0;

  const double gamma_abg = ui->box_gamma_abg->value();

  const int shift = ui->slider_shift->value();

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
  std::vector<double> outputs_ma;


  ui->label_value_dt_a->setText(QString::number(dt));

  ui->label_value_shift->setText(QString::number(shift));

  //Use filters
  {
    AlphaFilter filter_alpha(alpha_a,dt);
    AlphaBetaFilter filter_alpha_beta(alpha_ab,beta_ab,dt);
    AlphaBetaGammaFilter filter_alpha_beta_gamma(alpha_abg,beta_abg,gamma_abg,dt);
    LsqFilter filter_lsq(shift);
    MultiAlphaFilter filter_ma( { ma_1, ma_2 } );
    for (int t=0; t!=timesteps; ++t)
    {
      const double measurement             = noise_function.Evaluate(static_cast<double>(t));
      const double output_alpha            = filter_alpha.Estimate(measurement);
      const double output_alpha_beta       = filter_alpha_beta.Estimate(measurement);
      const double output_alpha_beta_gamma = filter_alpha_beta_gamma.Estimate(measurement);
      const double output_lsq              = filter_lsq.Estimate(measurement);
      const double output_ma               = filter_ma.Estimate(measurement);
      inputs.push_back(measurement);
      outputs_alpha.push_back(output_alpha);
      outputs_alpha_beta.push_back(output_alpha_beta);
      outputs_alpha_beta_gamma.push_back(output_alpha_beta_gamma);
      outputs_lsq.push_back(output_lsq);
      outputs_ma.push_back(output_ma);
    }
  }
  //Plot
  {
    std::vector<double> timeseries;
    for (int i=0; i!=timesteps; ++i)
    {
      timeseries.push_back(static_cast<double>(i));
    }
    #ifdef _WIN32
    m_curve_inputs->setData(new QwtPointArrayData(&timeseries[0],&inputs[0],inputs.size()));
    m_curve_outputs_alpha->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha[0],outputs_alpha.size()));
    m_curve_outputs_alpha_beta->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha_beta[0],outputs_alpha_beta.size()));
    m_curve_outputs_alpha_beta_gamma->setData(new QwtPointArrayData(&timeseries[0],&outputs_alpha_beta_gamma[0],outputs_alpha_beta_gamma.size()));
    m_curve_outputs_lsq->setData(new QwtPointArrayData(&timeseries[0],&outputs_lsq[0],outputs_lsq.size()));
    m_curve_outputs_ma->setData(new QwtPointArrayData(&timeseries[0],&outputs_ma[0],outputs_ma.size()));
    #else
    m_curve_inputs->setData(&timeseries[0],&inputs[0],inputs.size());
    m_curve_outputs_alpha->setData(&timeseries[0],&outputs_alpha[0],outputs_alpha.size());
    m_curve_outputs_alpha_beta->setData(&timeseries[0],&outputs_alpha_beta[0],outputs_alpha_beta.size());
    m_curve_outputs_alpha_beta_gamma->setData(&timeseries[0],&outputs_alpha_beta_gamma[0],outputs_alpha_beta_gamma.size());
    m_curve_outputs_lsq->setData(&timeseries[0],&outputs_lsq[0],outputs_lsq.size());
    m_curve_outputs_ma->setData(&timeseries[0],&outputs_ma[0],outputs_ma.size());
    #endif
    ui->plot->replot();
  }
}

void QtStateObserverMainDialog::on_button_rerun_clicked()
{
  this->Run();
}
