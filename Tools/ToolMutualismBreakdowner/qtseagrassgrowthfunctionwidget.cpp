#include "qtseagrassgrowthfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "seagrassgrowthfunction.h"
#include "ui_qtseagrassgrowthfunctionwidget.h"

QtSeagrassGrowthFunctionWidget::QtSeagrassGrowthFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSeagrassGrowthFunctionWidget)
{
  #ifndef NDEBUG
  //Test();
  #endif
  ui->setupUi(this);

  QObject::connect(ui->box_seagrass_carrying_capacity,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seagrass_growth_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtSeagrassGrowthFunctionWidget::~QtSeagrassGrowthFunctionWidget()
{
  delete ui;
}

std::shared_ptr<SeagrassGrowthFunction> QtSeagrassGrowthFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<SeagrassLogisticGrowth>(
    ui->box_seagrass_carrying_capacity->value() * boost::units::si::species_per_square_meter,
    ui->box_seagrass_growth_rate->value() * boost::units::si::per_second
  );
}

void QtSeagrassGrowthFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtSeagrassGrowthFunctionWidget::SetFunction(const std::shared_ptr<SeagrassGrowthFunction>& f) noexcept
{
  #ifndef NDEBUG
  if (!f)
  {
    std::cerr << "BREAK";
  }
  #endif
  assert(f);
  const auto iec = std::dynamic_pointer_cast<SeagrassLogisticGrowth>(f);
  assert(iec);
  ui->box_seagrass_growth_rate->setValue(
    iec->GetGrowthRate().value()
  );
  ui->box_seagrass_carrying_capacity->setValue(
    iec->GetCarryingCapacity().value()
  );
}
