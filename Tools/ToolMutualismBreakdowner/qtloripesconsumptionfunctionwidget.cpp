#include "qtloripesconsumptionfunctionwidget.h"

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
