#include "qtloripesconsumptionfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "loripesconsumptionfunction.h"
#include "ui_qtloripesconsumptionfunctionwidget.h"

QtLoripesConsumptionFunctionWidget::QtLoripesConsumptionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtLoripesConsumptionFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtLoripesConsumptionFunctionWidget::~QtLoripesConsumptionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<LoripesConsumptionFunction> QtLoripesConsumptionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearConsumption>(
    ui->box_a->value()
  );
}

void QtLoripesConsumptionFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtLoripesConsumptionFunctionWidget::SetFunction(const std::shared_ptr<LoripesConsumptionFunction>& f) noexcept
{
  #ifndef NDEBUG
  if (!f)
  {
    std::cerr << "BREAK";
  }
  #endif
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearConsumption>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
