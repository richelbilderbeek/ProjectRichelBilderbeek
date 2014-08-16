#include "qtdialog.h"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"

#include "alphafilter.h"
#include "alphabetafilter.h"
#include "ui_qtdialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_curve_inputs(new QwtPlotCurve("Inputs")),
  m_curve_outputs(new QwtPlotCurve("Outputs"))
{
  ui->setupUi(this);

  #ifdef _WIN32
  ui->plot->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  ui->plot->setCanvasBackground(QColor(255,255,255));
  #endif

  m_curve_inputs->attach(ui->plot);
  m_curve_inputs->setStyle(QwtPlotCurve::Lines);
  m_curve_inputs->setPen(QPen(QColor(128,128,128)));

  m_curve_outputs->attach(ui->plot);
  m_curve_outputs->setStyle(QwtPlotCurve::Lines);
  m_curve_outputs->setPen(QPen(QColor(0,0,0)));

  QObject::connect(ui->alpha,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->beta,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->dt,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  ui->box_type->setCurrentIndex(1);
  Run();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::Run()
{
  const int timesteps = 100;
  std::vector<double> inputs;
  std::vector<double> outputs;
  const double alpha
    = 1.0 * static_cast<double>(ui->alpha->value())
    / static_cast<double>(ui->alpha->maximum());
  const double beta
    = 2.0 * static_cast<double>(ui->beta->value())
    / static_cast<double>(ui->beta->maximum());
  const double dt
    = 1.0 * static_cast<double>(ui->dt->value())
    / static_cast<double>(ui->dt->maximum());

  ui->value_alpha->setText(QString::number(alpha));
  ui->value_beta->setText(QString::number(beta));
  ui->value_dt->setText(QString::number(dt));

  if (ui->box_type->currentIndex() == 0)
  {
    AlphaFilter filter(alpha,dt);
    for (int i=0; i!=timesteps; ++i)
    {
      const double input = static_cast<double>((rand() >> 4) % 100);
      const double output = filter.Estimate(input);
      inputs.push_back(input);
      outputs.push_back(output);
    }
  }
  else
  {
    AlphaBetaFilter filter(alpha,beta,dt);
    for (int i=0; i!=timesteps; ++i)
    {
      const double input = static_cast<double>((rand() >> 4) % 100);
      const double output = filter.Estimate(input);
      inputs.push_back(input);
      outputs.push_back(output);
    }
  }
  //Plot
  {
    std::vector<double> timeseries;
    for (int i=0; i!=timesteps; ++i)
    {
      timeseries.push_back(static_cast<double>(i));
    }
    #if QWT_VERSION >= 0x060100 || !WIN32
    m_curve_inputs->setData(new QwtPointArrayData(&timeseries[0],&inputs[0],inputs.size()));
    m_curve_outputs->setData(new QwtPointArrayData(&timeseries[0],&outputs[0],outputs.size()));
    #else
    m_curve_inputs->setData(&timeseries[0],&inputs[0],inputs.size());
    m_curve_outputs->setData(&timeseries[0],&outputs[0],outputs.size());
    #endif
    ui->plot->replot();
  }
}

void QtDialog::on_box_type_currentIndexChanged(int index)
{
  ui->beta->setVisible( index == 1 );
  ui->label_beta->setVisible( index == 1 );
  ui->value_beta->setVisible( index == 1 );
  Run();
}
