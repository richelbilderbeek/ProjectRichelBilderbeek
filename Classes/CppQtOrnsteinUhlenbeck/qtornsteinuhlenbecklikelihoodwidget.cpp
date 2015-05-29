#include "qtornsteinuhlenbecklikelihoodwidget.h"

#include "ornsteinuhlenbeck.h"

#include "ui_qtornsteinuhlenbecklikelihoodwidget.h"


QtOrnsteinUhlenbeckLikelihoodWidget::QtOrnsteinUhlenbeckLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtOrnsteinUhlenbeckLikelihoodWidget)
{
  ui->setupUi(this);
  QObject::connect(ui->box_cand_mean_reversion_rate,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_target_mean,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_volatility,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtOrnsteinUhlenbeckLikelihoodWidget::~QtOrnsteinUhlenbeckLikelihoodWidget()
{
  delete ui;
}

void QtOrnsteinUhlenbeckLikelihoodWidget::CalcLikelihood(
  const std::vector<double>& v,
  const double dt
) noexcept
{
  const double cand_mean_reversion_rate{ui->box_cand_mean_reversion_rate->value()};
  const double cand_target_mean{ui->box_cand_target_mean->value()};
  const double cand_volatility{ui->box_cand_volatility->value()};

  if (dt <= 0.0) return;
  if (v.size() <= 2) return;
  if (cand_mean_reversion_rate <= 0.0) return;

  const double log_likelihood{
    ribi::OrnsteinUhlenbeck::CalcLogLikelihood(
      v,
      dt,
      cand_mean_reversion_rate,
      cand_target_mean,
      cand_volatility
    )
  };
  ui->edit_log_likelihood->setText(std::to_string(log_likelihood).c_str());
}

void QtOrnsteinUhlenbeckLikelihoodWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}
