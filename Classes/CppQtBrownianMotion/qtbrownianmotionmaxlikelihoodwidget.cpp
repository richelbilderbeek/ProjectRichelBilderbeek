#include "qtbrownianmotionmaxlikelihoodwidget.h"

#include "brownianmotion.h"

#include "ui_qtbrownianmotionmaxlikelihoodwidget.h"

QtBrownianMotionMaxLikelihoodWidget::QtBrownianMotionMaxLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBrownianMotionMaxLikelihoodWidget)
{
  ui->setupUi(this);
}

QtBrownianMotionMaxLikelihoodWidget::~QtBrownianMotionMaxLikelihoodWidget()
{
  delete ui;
}

void QtBrownianMotionMaxLikelihoodWidget::SetData(const std::vector<double>& v)
{
  double volatility_hat = 0.0;
  ribi::BrownianMotion::CalcMaxLikelihood(v,volatility_hat);
  ui->edit_sigma_hat->setText(std::to_string(volatility_hat).c_str());
  m_max_log_likelihood
    = ribi::BrownianMotion::CalcLogLikelihood(v,volatility_hat)
  ;
  ui->edit_max_log_likelihood->setText(std::to_string(m_max_log_likelihood).c_str());
}
