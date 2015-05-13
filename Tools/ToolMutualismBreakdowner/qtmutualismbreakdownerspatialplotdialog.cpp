#include "qtmutualismbreakdownerspatialplotdialog.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include <QDesktopWidget>
#include <QGridLayout>
#include <QTimer>

#include "timesimulation.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#include "qtmutualismbreakdownerspatialwidget.h"
#include "ui_qtmutualismbreakdownerspatialplotdialog.h"
//#include "ui_qtmutualismbreakdownerparameterswidget.h"
#include "seagrassgrowthfunction.h"

QtMutualismBreakdownerSpatialPlotDialog::QtMutualismBreakdownerSpatialPlotDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerSpatialPlotDialog),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget},
  m_seagrass_widget{new QtMutualismBreakdownerSpatialWidget(10,10)},
  m_sulfide_widget{new QtMutualismBreakdownerSpatialWidget(10,10)},
  m_timer{new QTimer(this)},
  m_grid{}
{
  ui->setupUi(this);

  {
    const auto my_layout = ui->widget_left->layout();
    assert(my_layout);
    my_layout->addWidget(m_parameters_widget);
    //m_parameters_widget->HideTimeplot();
  }
  {
    const auto my_layout = ui->widget_mid->layout();
    assert(my_layout);
    my_layout->addWidget(m_seagrass_widget);
  }
  {
    const auto my_layout = ui->widget_right->layout();
    assert(my_layout);
    my_layout->addWidget(m_sulfide_widget);
  }

  QObject::connect(m_parameters_widget,SIGNAL(signal_parameters_changed()),this,SLOT(StartRun()));
  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
  StartRun();
}

QtMutualismBreakdownerSpatialPlotDialog::~QtMutualismBreakdownerSpatialPlotDialog()
{
  delete ui;
}

void QtMutualismBreakdownerSpatialPlotDialog::DisplayGrid()
{
  const auto parameters = GetParameters();
  const auto seagrass_growth_function
    = std::dynamic_pointer_cast<SeagrassStressedLogisticGrowth>(
      parameters.GetSeagrassGrowthFunction()
    );
  assert(seagrass_growth_function);
  const auto k = seagrass_growth_function->GetCarryingCapacity();
  const auto max_s = 10.0 * boost::units::si::mole_per_cubic_meter;

  assert(!m_grid.empty());
  const int height{static_cast<int>(m_grid.size())};
  const int width{static_cast<int>(m_grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    const auto& line = m_grid[y];
    for (int x=0; x!=width; ++x)
    {
      const auto& cell = line[x];
      //Seagrass
      {
        const auto n = cell.GetSeagrassDensity();
        int g = static_cast<int>(255.0 * n / k);
        if (g < 0) g = 0;
        else if (g > 255) g = 255;
        m_seagrass_widget->SetPixel(x,y,qRgb(0,g,0));
      }
      //Sulfide
      {
        const auto s = cell.GetSulfideConcentration();
        int r = static_cast<int>(255.0 * s / max_s);
        if (r < 0) r = 0;
        else if (r > 255) r = 255;
        m_sulfide_widget->SetPixel(x,y,qRgb(r,0,0));
      }
    }
  }
}

Parameters QtMutualismBreakdownerSpatialPlotDialog::GetParameters() const
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void QtMutualismBreakdownerSpatialPlotDialog::NextTimestep()
{
  const auto parameters = GetParameters();
  const auto dt = parameters.GetSpatialDeltaT();

  for (auto& line: m_grid)
  {
    for (auto& system: line)
    {
      system.Change(dt);
    }
  }
}

void QtMutualismBreakdownerSpatialPlotDialog::SetParameters(const Parameters& parameters)
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

void QtMutualismBreakdownerSpatialPlotDialog::StartRun()
{
  m_timer->stop();
  m_seagrass_widget->setEnabled(false);
  m_sulfide_widget->setEnabled(false);
  try
  {
    const auto parameters = GetParameters();
  }
  catch (std::logic_error& e)
  {
    std::clog << e.what() << std::endl;
    return;
  }
  this->m_seagrass_widget->setEnabled(true);
  this->m_sulfide_widget->setEnabled(true);

  const auto parameters = GetParameters();
  const int width = 10;
  const int height = 10;

  m_grid = Grid(height,std::vector<System>(width,System(parameters)));
  DisplayGrid();

  //SpatialSimulation simulation(parameters,width,height);
  //simulation.Run();
  m_timer->start();

}
