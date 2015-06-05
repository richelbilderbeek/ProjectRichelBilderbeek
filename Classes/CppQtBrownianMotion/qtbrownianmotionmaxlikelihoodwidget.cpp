#include "qtbrownianmotionmaxlikelihoodwidget.h"

#include "brownianmotionhelper.h"

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
  auto volatility_hat = 0.0 / boost::units::si::second;
  ribi::bm::Helper().CalcMaxLikelihood(v,volatility_hat);
  ui->edit_sigma_hat->setText(std::to_string(volatility_hat.value()).c_str());
  m_max_log_likelihood
    = ribi::bm::Helper().CalcLogLikelihood(v,volatility_hat * volatility_hat)
  ;
  ui->edit_max_log_likelihood->setText(std::to_string(m_max_log_likelihood).c_str());
}
