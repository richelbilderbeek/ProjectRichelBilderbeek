#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtdialog.h"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"
#include "ui_qtdialog.h"

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_curve_inputs(new QwtPlotCurve("Inputs")),
  m_curve_outputs(new QwtPlotCurve("Outputs"))
{
  ui->setupUi(this);
  m_curve_inputs->attach(ui->plot);
  m_curve_outputs->attach(ui->plot);

  ui->button->click();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_button_clicked()
{
  //Run with an alpha-beta filter
  const int timesteps = 100;
  double output = 0.0;
  double hidden = 0.0;
  std::vector<double> inputs;
  std::vector<double> outputs;

  for (int i=0; i!=timesteps; ++i)
  {
    const double dt    = 1.0 ;
    const double alpha = 0.1 ;
    const double beta  = 0.01;

    const double input = static_cast<double>((rand() >> 4) % 10);

    double new_output = output + ( hidden * dt );
    double new_hidden = hidden;

    const double difference = input - new_output;

    new_output += alpha * difference;
    new_hidden += beta  * difference / dt;

    output = new_output;
    hidden = new_hidden;

    inputs.push_back(input);
    outputs.push_back(output);
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
    m_curve_outputs->setData(new QwtPointArrayData(&timeseries[0],&outputs[0],outputs.size()));
    #else
    m_curve_inputs->setData(&timeseries[0],&inputs[0],inputs.size());
    m_curve_outputs->setData(&timeseries[0],&outputs[0],outputs.size());
    #endif
    ui->plot->replot();
  }
}

