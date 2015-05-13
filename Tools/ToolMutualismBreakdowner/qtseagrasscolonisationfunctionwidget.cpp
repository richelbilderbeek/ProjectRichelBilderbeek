#include "qtseagrasscolonisationfunctionwidget.h"

#include <cassert>
#include <iostream>

#include "seagrasscolonisationfunction.h"
#include "ui_qtseagrasscolonisationfunctionwidget.h"

QtSeagrassColonisationFunctionWidget::QtSeagrassColonisationFunctionWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtSeagrassColonisationFunctionWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_r,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_a,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtSeagrassColonisationFunctionWidget::~QtSeagrassColonisationFunctionWidget()
{
  delete ui;
}

std::shared_ptr<SeagrassColonisationFunction> QtSeagrassColonisationFunctionWidget::GetFunction() const
{
  return std::make_shared<SeagrassInvertedExponential>(
    ui->box_a->value(),
    ui->box_r->value() * boost::units::si::per_second
  );
}

void QtSeagrassColonisationFunctionWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}

void QtSeagrassColonisationFunctionWidget::SetFunction(const std::shared_ptr<SeagrassColonisationFunction>& f)
{
  assert(f);
  const auto iec = std::dynamic_pointer_cast<SeagrassInvertedExponential>(f);
  assert(iec);
  ui->box_a->setValue(
    iec->GetAlpha()
  );
  ui->box_r->setValue(
    iec->GetGrowthRate().value()
  );
}
