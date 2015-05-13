#include "qtsulfideproductionfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "sulfideproductionfunction.h"
#include "ui_qtsulfideproductionfunctionwidget.h"

QtSulfideProductionFunctionWidget::QtSulfideProductionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideProductionFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtSulfideProductionFunctionWidget::~QtSulfideProductionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<SulfideProductionFunction> QtSulfideProductionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearSulfideProduction>(
    ui->box_a->value()
  );
}

void QtSulfideProductionFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtSulfideProductionFunctionWidget::SetFunction(const std::shared_ptr<SulfideProductionFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearSulfideProduction>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
