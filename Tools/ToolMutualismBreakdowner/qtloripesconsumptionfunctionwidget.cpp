#include "qtloripesconsumptionfunctionwidget.h"

#include <cassert>

#include "loripesconsumptionfunction.h"
#include "ui_qtloripesconsumptionfunctionwidget.h"

QtLoripesConsumptionFunctionWidget::QtLoripesConsumptionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtLoripesConsumptionFunctionWidget)
{
  ui->setupUi(this);
}

QtLoripesConsumptionFunctionWidget::~QtLoripesConsumptionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<LoripesConsumptionFunction> QtLoripesConsumptionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<InvertedExponentialConsumption>(
    ui->box_ie_r->value()
  );
}

void QtLoripesConsumptionFunctionWidget::SetFunction(const std::shared_ptr<LoripesConsumptionFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<InvertedExponentialConsumption>(f);
  assert(iec);
  ui->box_ie_r->setValue(iec->m_r);
}
