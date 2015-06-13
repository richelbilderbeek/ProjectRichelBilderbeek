#include "qtsulfideproductionfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "mutualismbreakdownersulfideproductionfunction.h"
#include "ui_qtsulfideproductionfunctionwidget.h"

ribi::mb::QtSulfideProductionFunctionWidget::QtSulfideProductionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideProductionFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

ribi::mb::QtSulfideProductionFunctionWidget::~QtSulfideProductionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<ribi::mb::SulfideProductionFunction>
  ribi::mb::QtSulfideProductionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearSulfideProduction>(
    ui->box_a->value()
  );
}

void ribi::mb::QtSulfideProductionFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::mb::QtSulfideProductionFunctionWidget::SetFunction(const std::shared_ptr<SulfideProductionFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearSulfideProduction>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
