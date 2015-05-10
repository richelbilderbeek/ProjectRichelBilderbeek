#include "qtpoisoningfunctionwidget.h"

#include <cassert>

#include "poisoningfunction.h"
#include "ui_qtpoisoningfunctionwidget.h"

QtPoisoningFunctionWidget::QtPoisoningFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtPoisoningFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_ie_r,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtPoisoningFunctionWidget::~QtPoisoningFunctionWidget()
{
  delete ui;
}

std::shared_ptr<PoisoningFunction> QtPoisoningFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<InvertedExponentialPoisoning>(
    ui->box_ie_r->value()
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
  ui->box_ie_r->setValue(iec->m_r);
  ui->box_ie_max->setValue(iec->m_max);
}
