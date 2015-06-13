#include "qtseagrassgrowthfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "mutualismbreakdownerseagrassgrowthfunction.h"
#include "ui_qtseagrassgrowthfunctionwidget.h"

ribi::mb::QtSeagrassGrowthFunctionWidget::QtSeagrassGrowthFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSeagrassGrowthFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_seagrass_carrying_capacity,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_stress_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

ribi::mb::QtSeagrassGrowthFunctionWidget::~QtSeagrassGrowthFunctionWidget()
{
  delete ui;
}

std::shared_ptr<ribi::mb::SeagrassGrowthFunction>
  ribi::mb::QtSeagrassGrowthFunctionWidget::GetFunction() const
{
  return std::make_shared<SeagrassStressedLogisticGrowth>(
    ui->box_seagrass_carrying_capacity->value() * boost::units::si::species_per_square_meter,
    ui->box_seagrass_growth_rate->value() * boost::units::si::per_second,
    ui->box_seagrass_stress_rate->value() * boost::units::si::per_second
  );
}

void ribi::mb::QtSeagrassGrowthFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::mb::QtSeagrassGrowthFunctionWidget::SetFunction(
  const std::shared_ptr<SeagrassGrowthFunction>& f
)
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<SeagrassStressedLogisticGrowth>(f);
  assert(iec);
  ui->box_seagrass_growth_rate->setValue(
    iec->GetGrowthRate().value()
  );
  ui->box_seagrass_carrying_capacity->setValue(
    iec->GetCarryingCapacity().value()
  );
  ui->box_seagrass_stress_rate->setValue(
    iec->GetStressRate().value()
  );
}
