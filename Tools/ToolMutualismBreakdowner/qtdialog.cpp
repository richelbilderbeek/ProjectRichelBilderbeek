#include "qtdialog.h"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"

#include "alphabetafilter.h"
#include "ui_qtdialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog),
  m_curve_seagrass_density(new QwtPlotCurve("Inputs")),
  m_curve_sulfide_concentration(new QwtPlotCurve("Outputs"))
{
  ui->setupUi(this);
  #ifdef _WIN32
  ui->plot_seagrass_density->setCanvasBackground(QBrush(QColor(255,255,255)));
  ui->plot_sulfide_concentration->setCanvasBackground(QBrush(QColor(255,255,255)));
  #else
  ui->plot_seagrass_density->setCanvasBackground(QColor(200,255,200));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,200,200));
  #endif

  m_curve_seagrass_density->attach(ui->plot_seagrass_density);
  m_curve_seagrass_density->setStyle(QwtPlotCurve::Lines);
  m_curve_seagrass_density->setPen(QPen(QColor(128,255,128)));

  m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
  m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_sulfide_concentration->setPen(QPen(QColor(0,0,0)));

  //QObject::connect(ui->alpha,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  //QObject::connect(ui->beta,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  //Object::connect(ui->dt,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  Run();
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::Run()
{
  const int timesteps{100};
  std::vector<double> seagrass_densities;
  std::vector<double> sulfide_concentrations;
  std::vector<double> timeseries;
  for (int i=0; i!=timesteps; ++i)
  {
    seagrass_densities.push_back(0.1);
    sulfide_concentrations.push_back(0.2);
    timeseries.push_back(static_cast<double>(i));

  }
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );
  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
}
