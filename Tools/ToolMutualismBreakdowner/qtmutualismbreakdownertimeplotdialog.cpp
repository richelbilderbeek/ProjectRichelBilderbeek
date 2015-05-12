#include "qtmutualismbreakdownertimeplotdialog.h"

#include <cassert>
#include <fstream>
#include <iostream>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QGridLayout>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "simulation.h"
#include "ui_qtmutualismbreakdownertimeplotdialog.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtMutualismBreakdownerTimePlotDialog::QtMutualismBreakdownerTimePlotDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerTimePlotDialog),
  m_curve_loripes_density(new QwtPlotCurve),
  m_curve_seagrass_density(new QwtPlotCurve),
  m_curve_sulfide_concentration(new QwtPlotCurve),
  m_curve_organic_matter_density(new QwtPlotCurve),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  assert(this->ui->widget->layout());
  this->ui->widget->layout()->addWidget(m_parameters_widget);


  ui->plot_loripes_density->setTitle("Loripes density");
  ui->plot_seagrass_density->setTitle("Seagrass density");
  ui->plot_sulfide_concentration->setTitle("Sulfide concentration");
  ui->plot_organic_matter_density->setTitle("Organic matter density");

  //Add grid
  for (const auto plot:
    {
      ui->plot_loripes_density,
      ui->plot_organic_matter_density,
      ui->plot_seagrass_density,
      ui->plot_sulfide_concentration
    }
  )
  {
    QwtPlotGrid * const grid = new QwtPlotGrid;
    grid->setPen(QPen(QColor(128,128,128)));
    grid->attach(plot);
    new QwtPlotZoomer(plot->canvas());
  }

  ui->plot_loripes_density->setCanvasBackground(QColor(255,255,255));
  ui->plot_seagrass_density->setCanvasBackground(QColor(226,255,226));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,226,226));
  ui->plot_organic_matter_density->setCanvasBackground(QColor(226,226,255));

  m_curve_loripes_density->attach(ui->plot_loripes_density);
  m_curve_loripes_density->setStyle(QwtPlotCurve::Lines);
  m_curve_loripes_density->setPen(QPen(QColor(0,0,0)));

  m_curve_seagrass_density->attach(ui->plot_seagrass_density);
  m_curve_seagrass_density->setStyle(QwtPlotCurve::Lines);
  m_curve_seagrass_density->setPen(QPen(QColor(0,255,0)));

  m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
  m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_sulfide_concentration->setPen(QPen(QColor(255,0,0)));

  m_curve_organic_matter_density->attach(ui->plot_organic_matter_density);
  m_curve_organic_matter_density->setStyle(QwtPlotCurve::Lines);
  m_curve_organic_matter_density->setPen(QPen(QColor(0,0,255)));


  on_button_run_clicked();

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(on_button_run_clicked()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtMutualismBreakdownerTimePlotDialog::~QtMutualismBreakdownerTimePlotDialog()
{
  delete ui;
}

Parameters QtMutualismBreakdownerTimePlotDialog::GetParameters() const noexcept
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerTimePlotDialog::SetParameters(const Parameters& parameters) noexcept
{
  assert(m_parameters_widget);
  m_parameters_widget->SetParameters(parameters);
}

void QtMutualismBreakdownerTimePlotDialog::on_button_run_clicked()
{
  const auto parameters = GetParameters();
  std::clog << parameters << std::endl;
  Simulation simulation(parameters);
  simulation.Run();

  const std::vector<double>& timeseries{simulation.GetTimeSeries()};
  const auto& loripes_densities_with_unit = simulation.GetLoripesDensities();
  const auto& seagrass_densities_with_unit = simulation.GetSeagrassDensities();
  const auto& sulfide_concentrations_with_unit = simulation.GetSulfideConcentrations();
  const std::vector<double>& organic_matter_densities{simulation.GetOrganicMatterDensities()};

  std::vector<double> loripes_densities;
  std::transform(
    std::begin(loripes_densities_with_unit),
    std::end(loripes_densities_with_unit),
    std::back_inserter(loripes_densities),
    [](const auto& d){ return d.value(); }
  );
  std::vector<double> seagrass_densities;
  std::transform(
    std::begin(seagrass_densities_with_unit),
    std::end(seagrass_densities_with_unit),
    std::back_inserter(seagrass_densities),
    [](const auto& d){ return d.value(); }
  );

  std::vector<double> sulfide_concentrations;
  std::transform(
    std::begin(sulfide_concentrations_with_unit),
    std::end(sulfide_concentrations_with_unit),
    std::back_inserter(sulfide_concentrations),
    [](const auto& d){ return d.value(); }
  );

  m_curve_loripes_density->setData(
    new QwtPointArrayData(&timeseries[0],&loripes_densities[0],loripes_densities.size())
  );
  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );
  m_curve_organic_matter_density->setData(
    new QwtPointArrayData(&timeseries[0],&organic_matter_densities[0],organic_matter_densities.size())
  );

  ui->plot_loripes_density->replot();
  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
  ui->plot_organic_matter_density->replot();
}
