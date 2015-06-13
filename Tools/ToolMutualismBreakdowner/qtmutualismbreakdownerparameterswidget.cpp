#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "qtpoisoningfunctionwidget.h"
#include "qtseagrasscolonisationfunctionwidget.h"
#include "qtseagrassgrowthfunctionwidget.h"
#include "qtsulfideconsumptionfunctionwidget.h"
#include "qtsulfidedetoxificationfunctionwidget.h"
#include "qtsulfidediffusionfunctionwidget.h"
#include "qtsulfideproductionfunctionwidget.h"
#include "ui_qtmutualismbreakdownerparameterswidget.h"

ribi::mb::QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtMutualismBreakdownerParametersWidget),
  m_qtpoisoningwidget{new QtPoisoningFunctionWidget},
  m_qtseagrasscolonisationwidget{new QtSeagrassColonisationFunctionWidget},
  m_qtseagrassgrowthwidget{new QtSeagrassGrowthFunctionWidget},
  m_qtsulfideconsumptionwidget{new QtSulfideConsumptionFunctionWidget},
  m_qtsulfidedetoxificationwidget{new QtSulfideDetoxificationFunctionWidget},
  m_qtsulfidediffusionwidget{new QtSulfideDiffusionFunctionWidget},
  m_qtsulfideproductionwidget{new QtSulfideProductionFunctionWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_poisoning->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_qtpoisoningwidget);
  }
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_seagrass_colonisation->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_qtseagrasscolonisationwidget);
  }
  {
    using Layout = QGridLayout;
    Layout * const my_layout{
      dynamic_cast<Layout*>(ui->page_seagrass_growth->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_qtseagrassgrowthwidget);
  }
  {
    QLayout * const my_layout{ui->page_sulfide_consumption->layout()};
    assert(my_layout);
    my_layout->addWidget(m_qtsulfideconsumptionwidget);
  }
  {
    QLayout * const my_layout{ui->page_sulfide_detoxification->layout()};
    assert(my_layout);
    my_layout->addWidget(m_qtsulfidedetoxificationwidget);
  }
  {
    QLayout * const my_layout{ui->page_sulfide_diffusion->layout()};
    assert(my_layout);
    my_layout->addWidget(m_qtsulfidediffusionwidget);
  }
  {
    QLayout * const my_layout{ui->page_sulfide_production->layout()};
    assert(my_layout);
    my_layout->addWidget(m_qtsulfideproductionwidget);
  }



  QObject::connect(ui->box_spatial_delta_t,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_height,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_spatial_width,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_timeplot_delta_t,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_timesteps,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_loripes_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_seagrass_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtpoisoningwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtseagrasscolonisationwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtseagrassgrowthwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtsulfideconsumptionwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtsulfidedetoxificationwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtsulfidediffusionwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtsulfideproductionwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
}

ribi::mb::QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

ribi::mb::Parameters ribi::mb::QtMutualismBreakdownerParametersWidget::GetParameters() const
{
  using boost::units::si::species_per_square_meter;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  using boost::units::si::seconds;
  const Parameters p(
    ui->box_spatial_delta_t->value() * seconds,
    ui->box_spatial_height->value(),
    ui->box_spatial_width->value(),
    ui->box_timeplot_delta_t->value() * seconds,
    ui->box_initial_loripes_density->value() * boost::units::si::species_per_square_meter,
    ui->box_initial_seagrass_density->value() * boost::units::si::species_per_square_meter,
    ui->box_initial_sulfide_concentration->value() * mole / cubic_meter,
    m_qtpoisoningwidget->GetFunction(),
    m_qtseagrasscolonisationwidget->GetFunction(),
    m_qtseagrassgrowthwidget->GetFunction(),
    m_qtsulfideconsumptionwidget->GetFunction(),
    m_qtsulfidedetoxificationwidget->GetFunction(),
    m_qtsulfidediffusionwidget->GetFunction(),
    m_qtsulfideproductionwidget->GetFunction(),
    ui->box_n_timesteps->value()
  );

  return p;
}

void ribi::mb::QtMutualismBreakdownerParametersWidget::SetParameters(const Parameters& parameters)
{
  ui->box_spatial_delta_t->setValue(parameters.GetSpatialDeltaT().value());
  ui->box_spatial_height->setValue(parameters.GetSpatialHeight());
  ui->box_spatial_width->setValue(parameters.GetSpatialWidth());
  ui->box_timeplot_delta_t->setValue(parameters.GetTimeplotDeltaT().value());
  ui->box_n_timesteps->setValue(parameters.GetNumberOfTimesteps());
  ui->box_initial_loripes_density->setValue(parameters.GetInitialLoripesDensity().value());
  ui->box_initial_seagrass_density->setValue(parameters.GetInitialSeagrassDensity().value());
  ui->box_initial_sulfide_concentration->setValue(parameters.GetInitialSulfideConcentration().value());
  this->m_qtpoisoningwidget->SetFunction(parameters.GetPoisoningFunction());
  this->m_qtseagrasscolonisationwidget->SetFunction(parameters.GetSeagrassColonisationFunction());
  this->m_qtseagrassgrowthwidget->SetFunction(parameters.GetSeagrassGrowthFunction());
  this->m_qtsulfideconsumptionwidget->SetFunction(parameters.GetSulfideConsumptionFunction());
  this->m_qtsulfidedetoxificationwidget->SetFunction(parameters.GetSulfideDetoxificationFunction());
  this->m_qtsulfidediffusionwidget->SetFunction(parameters.GetSulfideDiffusionFunction());
  this->m_qtsulfideproductionwidget->SetFunction(parameters.GetSulfideProductionFunction());
}

void ribi::mb::QtMutualismBreakdownerParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}



void ribi::mb::QtMutualismBreakdownerParametersWidget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << GetParameters();
}

void ribi::mb::QtMutualismBreakdownerParametersWidget::on_button_load_clicked()
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
