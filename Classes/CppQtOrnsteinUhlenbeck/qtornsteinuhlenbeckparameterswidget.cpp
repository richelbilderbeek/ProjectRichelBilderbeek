#include "qtornsteinuhlenbeckparameterswidget.h"

#include "ornsteinuhlenbeck.h"

#include "ui_qtornsteinuhlenbeckparameterswidget.h"

QtOrnsteinUhlenbeckParametersWidget::QtOrnsteinUhlenbeckParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtOrnsteinUhlenbeckParametersWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_dt,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_init_x,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_t_end,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_mean_reversion_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_target_mean,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_volatility,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
}

QtOrnsteinUhlenbeckParametersWidget::~QtOrnsteinUhlenbeckParametersWidget()
{
  delete ui;
}

double QtOrnsteinUhlenbeckParametersWidget::GetInitValue() const noexcept
{
  return ui->box_init_x->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetTimestep() const noexcept
{
  return ui->box_dt->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetEndTime() const noexcept
{
  return ui->box_t_end->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetMeanReversionRate() const noexcept
{
  return ui->box_mean_reversion_rate->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetTargetMean() const noexcept
{
  return ui->box_target_mean->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetVolatility() const noexcept
{
  return ui->box_volatility->value();
}

int QtOrnsteinUhlenbeckParametersWidget::GetSeed() const noexcept
{
  return ui->box_seed->value();
}

void QtOrnsteinUhlenbeckParametersWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}


