#include "qtsulfideconsumptionfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "mutualismbreakdownersulfideconsumptionfunction.h"
#include "ui_qtsulfideconsumptionfunctionwidget.h"

ribi::mb::QtSulfideConsumptionFunctionWidget::QtSulfideConsumptionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideConsumptionFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

ribi::mb::QtSulfideConsumptionFunctionWidget::~QtSulfideConsumptionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<ribi::mb::SulfideConsumptionFunction>
  ribi::mb::QtSulfideConsumptionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearConsumption>(
    ui->box_a->value()
  );
}

void ribi::mb::QtSulfideConsumptionFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::mb::QtSulfideConsumptionFunctionWidget::SetFunction(const std::shared_ptr<SulfideConsumptionFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearConsumption>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
