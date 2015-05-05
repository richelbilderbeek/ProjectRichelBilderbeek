#include "qtmutualismbreakdownermaindialog.h"

#include <fstream>
#include <QDesktopWidget>
#include <QFileDialog>

#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

#include "simulation.h"
#include "ui_qtmutualismbreakdownermaindialog.h"

#if QWT_VERSION >= 0x060100 || !WIN32
#include "qwt_point_data.h"
#endif

QtMutualismBreakdownerMainDialog::QtMutualismBreakdownerMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerMainDialog),
  m_curve_seagrass_density(new QwtPlotCurve),
  m_curve_sulfide_concentration(new QwtPlotCurve),
  m_curve_organic_matter_density(new QwtPlotCurve)
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

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

  QObject::connect(ui->box_delta_t,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_desiccation_stress,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_initial_organic_matter_density  ,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_initial_seagrass_density,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_loripes_density,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_n_timesteps,SIGNAL(valueChanged(int)),this,SLOT(Run()));
  QObject::connect(ui->box_organic_matter_to_sulfide_factor,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_seagrass_carrying_capacity,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_seagrass_to_organic_matter_factor,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_sulfide_consumption_by_loripes,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_sulfide_diffusion_rate,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_organic_matter_to_sulfide_rate,SIGNAL(valueChanged(double)),this,SLOT(Run()));
  QObject::connect(ui->box_sulfide_toxicity,SIGNAL(valueChanged(double)),this,SLOT(Run()));

  Run();

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 8 / 10,screen.height() * 8 / 10);
    this->move( screen.center() - this->rect().center() );
  }
}

QtMutualismBreakdownerMainDialog::~QtMutualismBreakdownerMainDialog()
{
  delete ui;
}

void QtMutualismBreakdownerMainDialog::FixZoom()
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

Parameters QtMutualismBreakdownerMainDialog::GetParameters() const noexcept
{
  Parameters p(
    ui->box_delta_t->value(),
    ui->box_desiccation_stress->value(),
    ui->box_initial_organic_matter_density->value(),
    ui->box_initial_seagrass_density->value(),
    ui->box_initial_sulfide_concentration->value(),
    ui->box_loripes_density->value(),
    ui->box_organic_matter_to_sulfide_factor->value(),
    ui->box_organic_matter_to_sulfide_rate->value(),
    ui->box_seagrass_carrying_capacity->value(),
    ui->box_seagrass_growth_rate->value(),
    ui->box_seagrass_to_organic_matter_factor->value(),
    ui->box_sulfide_consumption_by_loripes->value(),
    ui->box_sulfide_diffusion_rate->value(),
    ui->box_sulfide_toxicity->value(),
    ui->box_n_timesteps->value()
  );

  return p;
}

void QtMutualismBreakdownerMainDialog::SetParameters(const Parameters& parameters) noexcept
{
  ui->box_delta_t->setValue(parameters.delta_t);
  ui->box_desiccation_stress->setValue(parameters.desiccation_stress);
  ui->box_initial_organic_matter_density->setValue(parameters.initial_organic_matter_density);
  ui->box_initial_seagrass_density->setValue(parameters.initial_seagrass_density);
  ui->box_initial_sulfide_concentration->setValue(parameters.initial_sulfide_concentration);
  ui->box_loripes_density->setValue(parameters.loripes_density);
  ui->box_organic_matter_to_sulfide_factor->setValue(parameters.organic_matter_to_sulfide_factor);
  ui->box_organic_matter_to_sulfide_rate->setValue(parameters.organic_matter_to_sulfide_rate);
  ui->box_seagrass_carrying_capacity->setValue(parameters.seagrass_carrying_capacity);
  ui->box_seagrass_growth_rate->setValue(parameters.seagrass_growth_rate);
  ui->box_seagrass_to_organic_matter_factor->setValue(parameters.seagrass_to_organic_matter_factor);
  ui->box_sulfide_consumption_by_loripes->setValue(parameters.sulfide_consumption_by_loripes_rate);
  ui->box_sulfide_diffusion_rate->setValue(parameters.sulfide_diffusion_rate);
  ui->box_sulfide_toxicity->setValue(parameters.sulfide_toxicity);
  ui->box_n_timesteps->setValue(parameters.n_timesteps);
}

double QtMutualismBreakdownerMainDialog::GetRandom() const noexcept
{
  switch (std::rand() % 8)
  {
    case 0: return 10.0;
    case 1: return  5.0;
    case 2: return  1.0;
    case 3: return  0.1;
    case 4: return  0.5;
    case 5: return  0.01;
    case 6: return  0.005;
    case 7: return  0.001;
  }
  return 0.0;
}

void QtMutualismBreakdownerMainDialog::Run()
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

void QtMutualismBreakdownerMainDialog::on_button_fix_zoom_clicked()
{
  FixZoom();
}

void QtMutualismBreakdownerMainDialog::on_button_set_random_values_clicked()
{
  ui->box_desiccation_stress->setValue(GetRandom());
  ui->box_initial_organic_matter_density->setValue(GetRandom());
  ui->box_initial_seagrass_density->setValue(GetRandom());
  ui->box_initial_sulfide_concentration->setValue(GetRandom());
  ui->box_loripes_density->setValue(GetRandom());
  ui->box_organic_matter_to_sulfide_factor->setValue(GetRandom());
  ui->box_organic_matter_to_sulfide_rate->setValue(GetRandom());
  ui->box_seagrass_carrying_capacity->setValue(GetRandom());
  ui->box_seagrass_growth_rate->setValue(GetRandom());
  ui->box_seagrass_to_organic_matter_factor->setValue(GetRandom());
  ui->box_sulfide_consumption_by_loripes->setValue(GetRandom());
  ui->box_sulfide_toxicity->setValue(GetRandom());
}

void QtMutualismBreakdownerMainDialog::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << GetParameters();
}

void QtMutualismBreakdownerMainDialog::on_button_load_clicked()
{
  const std::string filename{
    QFileDialog::getOpenFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ifstream f(filename);
  Parameters parameters;
  f >> parameters;
  SetParameters(parameters);
}
