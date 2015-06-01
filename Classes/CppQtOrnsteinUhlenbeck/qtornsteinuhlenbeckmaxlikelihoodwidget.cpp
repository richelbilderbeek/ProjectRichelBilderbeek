#include "qtornsteinuhlenbeckmaxlikelihoodwidget.h"

#include "ornsteinuhlenbeck.h"

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
  const double dt
)
{
  double lambda_hat = 0.0;
  double mu_hat = 0.0;
  double sigma_hat = 0.0;
  ribi::OrnsteinUhlenbeck::CalcMaxLikelihood(v,dt,lambda_hat,mu_hat,sigma_hat);
  ui->edit_lambda_hat->setText(std::to_string(lambda_hat).c_str());
  ui->edit_mu_hat->setText(std::to_string(mu_hat).c_str());
  ui->edit_sigma_hat->setText(std::to_string(sigma_hat).c_str());
  m_max_log_likelihood
    = ribi::OrnsteinUhlenbeck::CalcLogLikelihood(
      v,dt,lambda_hat,mu_hat,sigma_hat
    );
  ui->edit_max_log_likelihood->setText(std::to_string(m_max_log_likelihood).c_str());
}
