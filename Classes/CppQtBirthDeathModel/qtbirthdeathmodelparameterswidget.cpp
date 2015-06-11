#include "qtbirthdeathmodelparameterswidget.h"

#include "birthdeathmodelparameters.h"

#include "ui_qtbirthdeathmodelparameterswidget.h"

QtBirthDeathModelParametersWidget::QtBirthDeathModelParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBirthDeathModelParametersWidget)
{
  ui->setupUi(this);

  QObject::connect(this->ui->box_birth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_death_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_n_taxa,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(this->ui->box_rng_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
}

QtBirthDeathModelParametersWidget::~QtBirthDeathModelParametersWidget()
{
  delete ui;
}

ribi::bdm::Parameters QtBirthDeathModelParametersWidget::GetParameters() const noexcept
{
  const int n_taxa{ui->box_n_taxa->value()};
  const auto birth_rate = ui->box_birth_rate->value() / boost::units::si::second;
  const auto death_rate = ui->box_death_rate->value() / boost::units::si::second;
  const int rng_seed{ui->box_rng_seed->value()};

  const ribi::bdm::Parameters parameters(
    birth_rate,death_rate,n_taxa,rng_seed
  );
  return parameters;
}

void QtBirthDeathModelParametersWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}
