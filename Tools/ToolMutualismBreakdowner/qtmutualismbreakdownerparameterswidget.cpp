#include "qtmutualismbreakdownerparameterswidget.h"

#include <cassert>
#include <fstream>
#include <QFileDialog>

#include "loripesconsumptionfunction.h"
#include "qtloripesconsumptionfunctionwidget.h"
#include "qtpoisoningfunctionwidget.h"
#include "qtseagrassgrowthfunctionwidget.h"
#include "ui_qtmutualismbreakdownerparameterswidget.h"

QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtMutualismBreakdownerParametersWidget),
  //m_qtconsumptionwidget{new QtLoripesConsumptionFunctionWidget},
  m_qtpoisoningwidget{new QtPoisoningFunctionWidget},
  m_qtseagrassgrowthwidget{new QtSeagrassGrowthFunctionWidget}
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);
  /*
  {
    QLayout * const my_layout{ui->box_consumption_by_loripes->layout()};
    assert(my_layout);
    my_layout->addWidget(m_qtconsumptionwidget);
  }
  */
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
      dynamic_cast<Layout*>(ui->page_seagrass_growth->layout())
    };
    assert(my_layout);
    my_layout->addWidget(m_qtseagrassgrowthwidget);
  }


  QObject::connect(ui->box_delta_t,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_detoxification_max_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_detoxification_min,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_detoxification_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_initial_loripes_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_initial_organic_matter_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_initial_seagrass_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_mutualism_breakdown_max,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_mutualism_breakdown_r0,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_mutualism_breakdown_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_timesteps,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_addition,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_breakdown,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_capture,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_to_sulfide_factor,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_to_sulfide_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_recruitment_max,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_recruitment_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_seagrass_to_organic_matter_factor,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_sulfide_diffusion_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(ui->box_organic_matter_to_sulfide_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  //QObject::connect(m_qtconsumptionwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));

  QObject::connect(m_qtpoisoningwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
  QObject::connect(m_qtseagrassgrowthwidget,SIGNAL(signal_parameters_changed()),this,SLOT(OnAnyChange()));
}

QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

Parameters QtMutualismBreakdownerParametersWidget::GetParameters() const noexcept
{
  using boost::units::si::species_per_square_meter;
  using boost::units::si::mole;
  using boost::units::si::cubic_meter;
  Parameters p(
    ui->box_delta_t->value(),
    0.0, //ui->box_detoxification_max_rate->value(),
    0.0, //ui->box_detoxification_min->value(),
    0.0, //ui->box_detoxification_rate->value(),
    0.0 * boost::units::si::species_per_square_meter, //ui->box_initial_loripes_density->value(),
    0.0, //ui->box_initial_organic_matter_density->value(),
    0.0 * boost::units::si::species_per_square_meter, //ui->box_initial_seagrass_density->value(),
    0.0 * mole / cubic_meter, //ui->box_initial_sulfide_concentration->value(),
    std::make_shared<InvertedExponentialConsumption>(), //m_qtconsumptionwidget->GetFunction(),
    0.0, //ui->box_mutualism_breakdown_max->value(),
    0.0, //ui->box_mutualism_breakdown_r0->value(),
    0.0, //ui->box_mutualism_breakdown_rate->value(),
    0.0, //ui->box_organic_matter_addition->value(),
    0.0, //ui->box_organic_matter_breakdown->value(),
    0.0, //ui->box_organic_matter_capture->value(),
    0.0, //ui->box_organic_matter_to_sulfide_factor->value(),
    0.0, //ui->box_organic_matter_to_sulfide_rate->value(),
    m_qtpoisoningwidget->GetFunction(),
    0.0, //ui->box_recruitment_max->value(),
    0.0, //ui->box_recruitment_rate->value(),
    m_qtseagrassgrowthwidget->GetFunction(),
    0.0 * boost::units::si::species_per_square_meter, //ui->box_seagrass_carrying_capacity->value()
    0.0, //ui->box_seagrass_growth_rate->value(),
    0.0, //ui->box_seagrass_to_organic_matter_factor->value(),
    ui->box_sulfide_diffusion_rate->value(),
    ui->box_n_timesteps->value()
  );

  return p;
}

void QtMutualismBreakdownerParametersWidget::SetParameters(const Parameters& parameters) noexcept
{
  ui->box_delta_t->setValue(parameters.GetDeltaT());
  //ui->box_detoxification_max_rate->setValue(parameters.GetDetoxicationMaxRate());
  //ui->box_detoxification_min->setValue(parameters.GetDetoxicationMinimum());
  //ui->box_detoxification_rate->setValue(parameters.GetDetoxicationRate());
  //ui->box_initial_loripes_density->setValue(parameters.GetInitialLoripesDensity().value());
  //ui->box_initial_organic_matter_density->setValue(parameters.GetInitialOrganicMatterDensity());
  //ui->box_initial_seagrass_density->setValue(parameters.GetInitialSeagrassDensity().value());
  //ui->box_initial_sulfide_concentration->setValue(parameters.GetInitialSulfideConcentration().value());
  //ui->box_mutualism_breakdown_max->setValue(parameters.GetMutualismBreakdownMax());
  //ui->box_mutualism_breakdown_r0->setValue(parameters.GetMutualismBreakdownR0());
  //ui->box_mutualism_breakdown_rate->setValue(parameters.GetMutualismBreakdownRate());
  //ui->box_organic_matter_addition->setValue(parameters.GetOrganicMatterAddition());
  //ui->box_organic_matter_breakdown->setValue(parameters.GetOrganicMatterBreakdown());
  //ui->box_organic_matter_capture->setValue(parameters.GetOrganicMatterCapture());
  //ui->box_organic_matter_to_sulfide_factor->setValue(parameters.GetOrganicMatterToSulfideFactor());
  //ui->box_organic_matter_to_sulfide_rate->setValue(parameters.GetOrganicMatterToSulfideRate());
  //ui->box_recruitment_max->setValue(parameters.GetRecruitmentMax());
  //ui->box_recruitment_rate->setValue(parameters.GetRecruitmentRate());
  //ui->box_seagrass_carrying_capacity->setValue(parameters.GetSeagrassCarryingCapacity().value());
  //ui->box_seagrass_growth_rate->setValue(parameters.GetSeagrassGrowthRate());
  //ui->box_seagrass_to_organic_matter_factor->setValue(parameters.GetSeagrassToOrganicMatterFactor());
  ui->box_sulfide_diffusion_rate->setValue(parameters.GetSulfdeDiffusionRate());
  ui->box_n_timesteps->setValue(parameters.GetNumberOfTimesteps());
  //this->m_qtconsumptionwidget->SetFunction(parameters.GetLoripesConsumptionFunction());
  this->m_qtpoisoningwidget->SetFunction(parameters.GetPoisoningFunction());
  this->m_qtseagrassgrowthwidget->SetFunction(parameters.GetSeagrassGrowthFunction());
}

void QtMutualismBreakdownerParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtMutualismBreakdownerParametersWidget::on_button_set_random_values_clicked()
{
  auto p = Parameters::GetTest(0);
  this->SetParameters(p);
}


void QtMutualismBreakdownerParametersWidget::on_button_save_clicked()
{
  const std::string filename{
    QFileDialog::getSaveFileName().toStdString()
  };
  if (filename.empty()) return;
  std::ofstream f(filename);
  f << GetParameters();
}

void QtMutualismBreakdownerParametersWidget::on_button_load_clicked()
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
