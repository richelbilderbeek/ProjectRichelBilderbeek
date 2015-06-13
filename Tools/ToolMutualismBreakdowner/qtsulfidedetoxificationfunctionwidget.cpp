#include "qtsulfidedetoxificationfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "mutualismbreakdownersulfidedetoxificationfunction.h"
#include "ui_qtsulfidedetoxificationfunctionwidget.h"

ribi::mb::QtSulfideDetoxificationFunctionWidget::QtSulfideDetoxificationFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideDetoxificationFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

ribi::mb::QtSulfideDetoxificationFunctionWidget::~QtSulfideDetoxificationFunctionWidget()
{
  delete ui;
}

std::shared_ptr<ribi::mb::SulfideDetoxificationFunction>
  ribi::mb::QtSulfideDetoxificationFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearSulfideDetoxification>(
    ui->box_a->value()
  );
}

void ribi::mb::QtSulfideDetoxificationFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::mb::QtSulfideDetoxificationFunctionWidget::SetFunction(const std::shared_ptr<SulfideDetoxificationFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearSulfideDetoxification>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
