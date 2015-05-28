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
  QObject::connect(ui->box_lambda,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_mu,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_sigma,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_lambda,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_mu,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_sigma,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtOrnsteinUhlenbeckParametersWidget::~QtOrnsteinUhlenbeckParametersWidget()
{
  delete ui;
}

void QtOrnsteinUhlenbeckParametersWidget::CalcLikelihood(
  const std::vector<double>& v
) noexcept
{
  const double dt{GetTimestep()};
  const double cand_lambda{ui->box_cand_lambda->value()};
  const double cand_mu{ui->box_cand_mu->value()};
  const double cand_sigma{ui->box_cand_sigma->value()};

  if (dt <= 0.0) return;
  if (v.size() <= 2) return;
  if (cand_lambda <= 0.0) return;

  const double log_likelihood{
    ribi::OrnsteinUhlenbeck::CalcLogLikelihood(v,dt,cand_lambda,cand_mu,cand_sigma)
  };
  ui->edit_log_likelihood->setText(std::to_string(log_likelihood).c_str());
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

double QtOrnsteinUhlenbeckParametersWidget::GetLambda() const noexcept
{
  return ui->box_lambda->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetMu() const noexcept
{
  return ui->box_mu->value();
}

double QtOrnsteinUhlenbeckParametersWidget::GetSigma() const noexcept
{
  return ui->box_sigma->value();
}

int QtOrnsteinUhlenbeckParametersWidget::GetSeed() const noexcept
{
  return ui->box_seed->value();
}

void QtOrnsteinUhlenbeckParametersWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}


