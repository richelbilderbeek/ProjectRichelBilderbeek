#include "qtornsteinuhlenbecklikelihoodwidget.h"

#include "ornsteinuhlenbeckhelper.h"

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
  const Time dt
) noexcept
{
  const auto cand_mean_reversion_rate
    = ui->box_cand_mean_reversion_rate->value() / boost::units::si::second;
  const double cand_target_mean{ui->box_cand_target_mean->value()};
  const auto cand_volatility
    = ui->box_cand_volatility->value() / boost::units::si::second;

  if (dt <= 0.0 * boost::units::si::second) return;
  if (v.size() <= 2) return;
  if (cand_mean_reversion_rate <= 0.0 / boost::units::si::second) return;

  const double log_likelihood{
    ribi::ou::Helper().CalcLogLikelihood(
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
