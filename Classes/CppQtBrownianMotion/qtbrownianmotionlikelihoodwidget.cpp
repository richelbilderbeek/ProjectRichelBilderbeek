#include "qtbrownianmotionlikelihoodwidget.h"

#include "brownianmotion.h"

#include "ui_qtbrownianmotionlikelihoodwidget.h"

QtBrownianMotionLikelihoodWidget::QtBrownianMotionLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBrownianMotionLikelihoodWidget)
{
  ui->setupUi(this);
  QObject::connect(ui->box_cand_volatility,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtBrownianMotionLikelihoodWidget::~QtBrownianMotionLikelihoodWidget()
{
  delete ui;
}

void QtBrownianMotionLikelihoodWidget::CalcLikelihood(
  const std::vector<double>& v
) noexcept
{
  const double cand_volatility{ui->box_cand_volatility->value()};

  if (v.size() <= 2) return;

  const double log_likelihood{
    ribi::BrownianMotion::CalcLogLikelihood(
      v,
      cand_volatility
    )
  };
  ui->edit_log_likelihood->setText(std::to_string(log_likelihood).c_str());
}

void QtBrownianMotionLikelihoodWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}
