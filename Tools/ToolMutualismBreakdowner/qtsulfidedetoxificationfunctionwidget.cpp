#include "qtsulfidedetoxificationfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "sulfidedetoxificationfunction.h"
#include "ui_qtsulfidedetoxificationfunctionwidget.h"

QtSulfideDetoxificationFunctionWidget::QtSulfideDetoxificationFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideDetoxificationFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtSulfideDetoxificationFunctionWidget::~QtSulfideDetoxificationFunctionWidget()
{
  delete ui;
}

std::shared_ptr<SulfideDetoxificationFunction> QtSulfideDetoxificationFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearSulfideDetoxification>(
    ui->box_a->value()
  );
}

void QtSulfideDetoxificationFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtSulfideDetoxificationFunctionWidget::SetFunction(const std::shared_ptr<SulfideDetoxificationFunction>& f) noexcept
{
  #ifndef NDEBUG
  if (!f)
  {
    std::cerr << "BREAK";
  }
  #endif
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearSulfideDetoxification>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
