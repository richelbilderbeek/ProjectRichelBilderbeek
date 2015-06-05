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

QtOrnsteinUhlenbeckParametersWidget::Time
  QtOrnsteinUhlenbeckParametersWidget::GetTimestep() const noexcept
{
  return ui->box_dt->value() * boost::units::si::second;
}

QtOrnsteinUhlenbeckParametersWidget::Time
  QtOrnsteinUhlenbeckParametersWidget::GetEndTime() const noexcept
{
  return ui->box_t_end->value() * boost::units::si::second;
}

QtOrnsteinUhlenbeckParametersWidget::Rate
  QtOrnsteinUhlenbeckParametersWidget::GetMeanReversionRate() const noexcept
{
  return ui->box_mean_reversion_rate->value() / boost::units::si::second;
}

double QtOrnsteinUhlenbeckParametersWidget::GetTargetMean() const noexcept
{
  return ui->box_target_mean->value();
}

QtOrnsteinUhlenbeckParametersWidget::Rate
  QtOrnsteinUhlenbeckParametersWidget::GetVolatility() const noexcept
{
  return ui->box_volatility->value() / boost::units::si::second;
}

int QtOrnsteinUhlenbeckParametersWidget::GetSeed() const noexcept
{
  return ui->box_seed->value();
}

void QtOrnsteinUhlenbeckParametersWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}


