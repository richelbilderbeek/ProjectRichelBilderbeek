#include "qtmutualismbreakdownerparameterswidget.h"

#include <fstream>
#include <QFileDialog>

#include "ui_qtmutualismbreakdownerparameterswidget.h"

QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtMutualismBreakdownerParametersWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_delta_t,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_desiccation_stress,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_organic_matter_density  ,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_seagrass_density,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_initial_sulfide_concentration,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_n_timesteps,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_organic_matter_to_sulfide_factor,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_carrying_capacity,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_to_organic_matter_factor,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_sulfide_consumption_by_loripes,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_sulfide_diffusion_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_organic_matter_to_sulfide_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}

Parameters QtMutualismBreakdownerParametersWidget::GetParameters() const noexcept
{
  Parameters p(
    ui->box_delta_t->value(),
    ui->box_desiccation_stress->value(),
    ui->box_initial_organic_matter_density->value(),
    ui->box_initial_seagrass_density->value(),
    ui->box_initial_sulfide_concentration->value(),
    ui->box_organic_matter_to_sulfide_factor->value(),
    ui->box_organic_matter_to_sulfide_rate->value(),
    ui->box_seagrass_carrying_capacity->value(),
    ui->box_seagrass_growth_rate->value(),
    ui->box_seagrass_to_organic_matter_factor->value(),
    ui->box_sulfide_consumption_by_loripes->value(),
    ui->box_sulfide_diffusion_rate->value(),
    ui->box_n_timesteps->value()
  );

  return p;
}

void QtMutualismBreakdownerParametersWidget::SetParameters(const Parameters& parameters) noexcept
{
  ui->box_delta_t->setValue(parameters.delta_t);
  ui->box_desiccation_stress->setValue(parameters.desiccation_stress);
  ui->box_initial_organic_matter_density->setValue(parameters.initial_organic_matter_density);
  ui->box_initial_seagrass_density->setValue(parameters.initial_seagrass_density);
  ui->box_initial_sulfide_concentration->setValue(parameters.initial_sulfide_concentration);
  ui->box_organic_matter_to_sulfide_factor->setValue(parameters.organic_matter_to_sulfide_factor);
  ui->box_organic_matter_to_sulfide_rate->setValue(parameters.organic_matter_to_sulfide_rate);
  ui->box_seagrass_carrying_capacity->setValue(parameters.seagrass_carrying_capacity);
  ui->box_seagrass_growth_rate->setValue(parameters.seagrass_growth_rate);
  ui->box_seagrass_to_organic_matter_factor->setValue(parameters.seagrass_to_organic_matter_factor);
  ui->box_sulfide_consumption_by_loripes->setValue(parameters.sulfide_consumption_by_loripes_rate);
  ui->box_sulfide_diffusion_rate->setValue(parameters.sulfide_diffusion_rate);
  ui->box_n_timesteps->setValue(parameters.n_timesteps);
}

void QtMutualismBreakdownerParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtMutualismBreakdownerParametersWidget::on_button_set_random_values_clicked()
{
  auto p = GetParameters();
  p.SetRandom();
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
