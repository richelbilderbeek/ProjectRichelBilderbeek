#include "qtpoisoningfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "poisoningfunction.h"
#include "ui_qtpoisoningfunctionwidget.h"

QtPoisoningFunctionWidget::QtPoisoningFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtPoisoningFunctionWidget)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_b,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_max,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtPoisoningFunctionWidget::~QtPoisoningFunctionWidget()
{
  delete ui;
}

std::shared_ptr<PoisoningFunction> QtPoisoningFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<InvertedExponentialPoisoning>(
    ui->box_a->value(),
    ui->box_b->value(),
    ui->box_max->value()
  );
}

void QtPoisoningFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtPoisoningFunctionWidget::SetFunction(const std::shared_ptr<PoisoningFunction>& f) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<InvertedExponentialPoisoning>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
  ui->box_b->setValue(iec->m_b);
  ui->box_max->setValue(iec->m_max);
}
