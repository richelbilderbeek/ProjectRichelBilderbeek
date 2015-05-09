#include "qtmutualismbreakdownertimeplotdialog.h"

#include <cassert>
#include <fstream>
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

  ui->plot_seagrass_density->setTitle("Seagrass density");
  ui->plot_sulfide_concentration->setTitle("Sulfide concentration");
  ui->plot_organic_matter_density->setTitle("Organic matter density");

  //Add grid
  for (const auto plot:
    {
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

  ui->plot_seagrass_density->setCanvasBackground(QColor(226,255,226));
  ui->plot_sulfide_concentration->setCanvasBackground(QColor(255,226,226));
  ui->plot_organic_matter_density->setCanvasBackground(QColor(226,226,255));

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

void QtMutualismBreakdownerTimePlotDialog::FixZoom()
{
  ui->plot_seagrass_density->setAxisScale(
    QwtPlot::xBottom,0.0,
    static_cast<double>(GetParameters().n_timesteps)
  );
  ui->plot_organic_matter_density->setAxisScale(
    QwtPlot::xBottom,0.0,
    static_cast<double>(GetParameters().n_timesteps)
  );
  ui->plot_sulfide_concentration->setAxisScale(
    QwtPlot::xBottom,0.0,
    static_cast<double>(GetParameters().n_timesteps)
  );
  ui->plot_seagrass_density->setAxisScale(
    QwtPlot::yLeft,0.0,
    std::max(
      GetParameters().initial_seagrass_density,
      GetParameters().seagrass_carrying_capacity
    )
  );
  ui->plot_seagrass_density->replot();
  ui->plot_sulfide_concentration->replot();
  ui->plot_organic_matter_density->replot();

}

Parameters QtMutualismBreakdownerTimePlotDialog::GetParameters() const noexcept
{
  return m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerTimePlotDialog::SetParameters(const Parameters& parameters) noexcept
{
  m_parameters_widget->SetParameters(parameters);
}

void QtMutualismBreakdownerTimePlotDialog::on_button_fix_zoom_clicked()
{
  FixZoom();
}

void QtMutualismBreakdownerTimePlotDialog::on_button_run_clicked()
{
  Simulation simulation(GetParameters());
  simulation.Run();

  const std::vector<double>& timeseries{simulation.GetTimeSeries()};
  const std::vector<double>& seagrass_densities{simulation.GetSeagrassDensities()};
  const std::vector<double>& sulfide_concentrations{simulation.GetSulfideConcentrations()};
  const std::vector<double>& organic_matter_densities{simulation.GetOrganicMatterDensities()};

  m_curve_seagrass_density->setData(
    new QwtPointArrayData(&timeseries[0],&seagrass_densities[0],seagrass_densities.size())
  );
  m_curve_sulfide_concentration->setData(
    new QwtPointArrayData(&timeseries[0],&sulfide_concentrations[0],sulfide_concentrations.size())
  );
  m_curve_organic_matter_density->setData(
    new QwtPointArrayData(&timeseries[0],&organic_matter_densities[0],organic_matter_densities.size())
  );
  FixZoom();

}
