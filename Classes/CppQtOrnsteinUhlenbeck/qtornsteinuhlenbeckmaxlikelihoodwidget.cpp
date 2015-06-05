#include "qtornsteinuhlenbeckmaxlikelihoodwidget.h"

#include "ornsteinuhlenbeckhelper.h"

#include "ui_qtornsteinuhlenbeckmaxlikelihoodwidget.h"

QtOrnsteinUhlenbeckMaxLikelihoodWidget::QtOrnsteinUhlenbeckMaxLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtOrnsteinUhlenbeckMaxLikelihoodWidget),
  m_max_log_likelihood{0.0}
{
  ui->setupUi(this);
}

QtOrnsteinUhlenbeckMaxLikelihoodWidget::~QtOrnsteinUhlenbeckMaxLikelihoodWidget()
{
  delete ui;
}

void QtOrnsteinUhlenbeckMaxLikelihoodWidget::SetData(
  const std::vector<double>& v,
  const Time dt
)
{
  auto mean_reversion_rate_hat = 0.0 / boost::units::si::second;
  double target_mean_hat = 0.0;
  auto volatility_hat = 0.0 / boost::units::si::second;
  ribi::ou::Helper().CalcMaxLikelihood(v,dt,mean_reversion_rate_hat,target_mean_hat,volatility_hat);
  ui->edit_lambda_hat->setText(std::to_string(mean_reversion_rate_hat.value()).c_str());
  ui->edit_mu_hat->setText(std::to_string(target_mean_hat).c_str());
  ui->edit_sigma_hat->setText(std::to_string(volatility_hat.value()).c_str());
  m_max_log_likelihood
    = ribi::ou::Helper().CalcLogLikelihood(
      v,dt,mean_reversion_rate_hat,target_mean_hat,volatility_hat
    );
  ui->edit_max_log_likelihood->setText(std::to_string(m_max_log_likelihood).c_str());
}
