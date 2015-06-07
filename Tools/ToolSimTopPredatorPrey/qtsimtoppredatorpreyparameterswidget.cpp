#include "qtsimtoppredatorpreyparameterswidget.h"
#include "ui_qtsimtoppredatorpreyparameterswidget.h"

QtSimTopPredatorPreyParametersWidget::QtSimTopPredatorPreyParametersWidget(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtSimTopPredatorPreyParametersWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_diffusion_pred,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_diffusion_prey,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_diffusion_top,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_f_pred,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_f_prey,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_f_top,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_conv_pred_to_top,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_conv_prey_to_pred,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_hunt_eff_pred,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_hunt_eff_top,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtSimTopPredatorPreyParametersWidget::~QtSimTopPredatorPreyParametersWidget()
{
  delete ui;
}

double QtSimTopPredatorPreyParametersWidget::GetConvPredToTop() const noexcept
{
  return ui->box_conv_pred_to_top->value();
}

double QtSimTopPredatorPreyParametersWidget::GetConvPreyToPred() const noexcept
{
  return ui->box_conv_prey_to_pred->value();

}

double QtSimTopPredatorPreyParametersWidget::GetDiffusionPred() const noexcept
{
  return ui->box_diffusion_pred->value();
}

double QtSimTopPredatorPreyParametersWidget::GetDiffusionPrey() const noexcept
{
  return ui->box_diffusion_prey->value();
}

double QtSimTopPredatorPreyParametersWidget::GetDiffusionTop() const noexcept
{
  return ui->box_diffusion_top->value();
}


double QtSimTopPredatorPreyParametersWidget::GetFractionPred() const noexcept
{
  return ui->box_f_pred->value();
}

double QtSimTopPredatorPreyParametersWidget::GetFractionPrey() const noexcept
{
  return ui->box_f_prey->value();
}

double QtSimTopPredatorPreyParametersWidget::GetFractionTop() const noexcept
{
  return ui->box_f_top->value();
}


double QtSimTopPredatorPreyParametersWidget::GetHuntEffPred() const noexcept
{
  return ui->box_hunt_eff_pred->value();
}

double QtSimTopPredatorPreyParametersWidget::GetHuntEffTop() const noexcept
{
  return ui->box_hunt_eff_top->value();
}

void QtSimTopPredatorPreyParametersWidget::HideTopPredator()
{
  ui->toolBox->setCurrentIndex(0);
  ui->toolBox->removeItem(2);
  delete ui->page_top; //Otherwise it won't be, well, deleted :-)
}

void QtSimTopPredatorPreyParametersWidget::OnAnyChange()
{
  emit signal_parameters_changed();
}
