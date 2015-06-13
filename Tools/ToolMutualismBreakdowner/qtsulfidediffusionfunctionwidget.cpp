#include "qtsulfidediffusionfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "mutualismbreakdownersulfidediffusionfunction.h"
#include "ui_qtsulfidediffusionfunctionwidget.h"

ribi::mb::QtSulfideDiffusionFunctionWidget::QtSulfideDiffusionFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSulfideDiffusionFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

ribi::mb::QtSulfideDiffusionFunctionWidget::~QtSulfideDiffusionFunctionWidget()
{
  delete ui;
}

std::shared_ptr<ribi::mb::SulfideDiffusionFunction>
  ribi::mb::QtSulfideDiffusionFunctionWidget::GetFunction() const noexcept
{
  return std::make_shared<LinearSulfideDiffusion>(
    ui->box_a->value()
  );
}

void ribi::mb::QtSulfideDiffusionFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void ribi::mb::QtSulfideDiffusionFunctionWidget::SetFunction(
  const std::shared_ptr<ribi::mb::SulfideDiffusionFunction>& f
) noexcept
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<LinearSulfideDiffusion>(f);
  assert(iec);
  ui->box_a->setValue(iec->m_a);
}
