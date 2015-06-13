#include "qtmutualismbreakdownerspatialplotdialog.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include <QDesktopWidget>
#include <QGridLayout>
#include <QTimer>

#include "mutualismbreakdownertimesimulation.h"
#include "qtmutualismbreakdownerparameterswidget.h"
#include "qtmutualismbreakdownerspatialwidget.h"
#include "ui_qtmutualismbreakdownerspatialplotdialog.h"
#include "mutualismbreakdownerspatialsimulation.h"
#include "mutualismbreakdownerseagrassgrowthfunction.h"

ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::QtMutualismBreakdownerSpatialPlotDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtMutualismBreakdownerSpatialPlotDialog),
  m_parameters_widget{new QtMutualismBreakdownerParametersWidget},
  m_seagrass_widget{new QtMutualismBreakdownerSpatialWidget(10,10)},
  m_sulfide_widget{new QtMutualismBreakdownerSpatialWidget(10,10)},
  m_timer{new QTimer(this)},
  m_simulation{nullptr}
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
  QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(NextTimestep()));

  {
    //Put the dialog in the screen center
    const QRect screen = QApplication::desktop()->screenGeometry();
    this->setGeometry(0,0,screen.width() * 9 / 10,screen.height() * 9 / 10);
    this->move( screen.center() - this->rect().center() );
  }
  StartRun();
}

ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::~QtMutualismBreakdownerSpatialPlotDialog()
{
  delete ui;
}

void ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::DisplayGrid()
{
  const auto parameters = GetParameters();
  const auto seagrass_growth_function
    = std::dynamic_pointer_cast<SeagrassStressedLogisticGrowth>(
      parameters.GetSeagrassGrowthFunction()
    );
  assert(seagrass_growth_function);
  const auto k = seagrass_growth_function->GetCarryingCapacity();
  const auto max_s = 1.0 * boost::units::si::mole_per_cubic_meter;

  assert(m_simulation);
  const auto grid = m_simulation->GetGrid();
  const int height{static_cast<int>(grid.size())};
  const int width{static_cast<int>(grid[0].size())};
  for (int y=0; y!=height; ++y)
  {
    const auto& line = grid[y];
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
  m_seagrass_widget->update();
  m_sulfide_widget->update();
}

ribi::mb::Parameters ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::GetParameters() const
{
  assert(m_parameters_widget);
  return m_parameters_widget->GetParameters();
}

void ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::NextTimestep()
{
  const auto parameters = GetParameters();
  const auto dt = parameters.GetSpatialDeltaT();
  assert(m_simulation);
  m_simulation->Change(dt);

  //Kill some random patch
  {
    const int w = parameters.GetSpatialWidth();
    const int h = parameters.GetSpatialHeight();
    m_simulation->KillSeagrass(
      std::rand() % w,
      std::rand() % h
    );
  }

  DisplayGrid();
}

void ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::SetParameters(const Parameters& parameters)
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

void ribi::mb::QtMutualismBreakdownerSpatialPlotDialog::StartRun()
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

  const auto parameters = GetParameters();
  {
    const int w{parameters.GetSpatialWidth()};
    const int h{parameters.GetSpatialHeight()};
    this->m_seagrass_widget->SetResolution(w,h);
    this->m_sulfide_widget->SetResolution(w,h);
  }
  this->m_seagrass_widget->setEnabled(true);
  this->m_sulfide_widget->setEnabled(true);

  m_simulation = std::make_unique<Simulation>(parameters);

  DisplayGrid();

  m_timer->setInterval(1);
  m_timer->start();

}
