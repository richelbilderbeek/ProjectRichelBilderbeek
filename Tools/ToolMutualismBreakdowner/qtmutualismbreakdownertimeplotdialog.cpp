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

#include "mutualismbreakdownertimesimulation.h"
#include "ui_qtmutualismbreakdownertimeplotdialog.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

ribi::mb::QtMutualismBreakdownerTimePlotDialog::QtMutualismBreakdownerTimePlotDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new ::Ui::QtMutualismBreakdownerTimePlotDialog),
  m_curve_seagrass_density(new QwtPlotCurve),
  m_curve_sulfide_concentration(new QwtPlotCurve),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  //Parameters widget
  {
    assert(this->ui->widget->layout());
    this->ui->widget->layout()->addWidget(m_parameters_widget);
  }


  ui->plot_seagrass_density->setTitle("Seagrass density");
  ui->plot_sulfide_concentration->setTitle("Sulfide concentration");

  //Add grid
  for (const auto plot:
    {
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

  ui->plot_seagrass_density->setCanvasBackground(QColor(226,255,226));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,226,226));

  m_curve_seagrass_density->attach(ui->plot_seagrass_density);
  m_curve_seagrass_density->setStyle(QwtPlotCurve::Lines);
  m_curve_seagrass_density->setPen(QPen(QColor(0,255,0)));

  m_curve_sulfide_concentration->attach(ui->plot_sulfide_concentration);
  m_curve_sulfide_concentration->setStyle(QwtPlotCurve::Lines);
  m_curve_sulfide_concentration->setPen(QPen(QColor(255,0,0)));

  on_button_run_clicked();

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(on_button_run_clicked()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

ribi::mb::QtMutualismBreakdownerTimePlotDialog::~QtMutualismBreakdownerTimePlotDialog()
{
  delete ui;
}

ribi::mb::Parameters ribi::mb::QtMutualismBreakdownerTimePlotDialog::GetParameters() const
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void ribi::mb::QtMutualismBreakdownerTimePlotDialog::SetParameters(const Parameters& parameters)
{
  try
  {
    assert(m_parameters_widget);
    m_parameters_widget->SetParameters(parameters);
  }
  catch(std::logic_error& e)
  {
    std::clog << e.what() << std::endl;
  }
}

void ribi::mb::QtMutualismBreakdownerTimePlotDialog::on_button_run_clicked()
{
  ui->plot_seagrass_density->setEnabled(false);
  ui->plot_sulfide_concentration->setEnabled(false);
  try
  {
    const auto parameters = GetParameters();
  }
  catch (std::logic_error& e)
  {
    std::clog << e.what() << std::endl;
    return;
  }
  ui->plot_seagrass_density->setEnabled(true);
  ui->plot_sulfide_concentration->setEnabled(true);

  const auto parameters = GetParameters();
  std::clog << parameters << std::endl;
  TimeSimulation simulation(parameters);
  simulation.Run();

  const std::vector<double>& timeseries{simulation.GetTimeSeries()};
  const auto& seagrass_densities_with_unit = simulation.GetSeagrassDensities();
  const auto& sulfide_concentrations_with_unit = simulation.GetSulfideConcentrations();

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

  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );

  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
}
