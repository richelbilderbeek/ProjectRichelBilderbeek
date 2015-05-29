#include "qtbrownianmotionparameterswidget.h"

#include "brownianmotion.h"

#include "ui_qtbrownianmotionparameterswidget.h"

QtBrownianMotionParametersWidget::QtBrownianMotionParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBrownianMotionParametersWidget)
{
  ui->setupUi(this);

  QObject::connect(ui->box_init_x,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_t_end,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_volatility,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_seed,SIGNAL(valueChanged(int)),this,SLOT(OnAnyChange()));
  QObject::connect(ui->box_cand_volatility,SIGNAL(valueChanged(double)),this,SLOT(OnAnyChange()));
}

QtBrownianMotionParametersWidget::~QtBrownianMotionParametersWidget()
{
  delete ui;
}

void QtBrownianMotionParametersWidget::CalcLikelihood(
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

double QtBrownianMotionParametersWidget::GetInitValue() const noexcept
{
  return ui->box_init_x->value();
}

int QtBrownianMotionParametersWidget::GetEndTime() const noexcept
{
  return ui->box_t_end->value();
}

double QtBrownianMotionParametersWidget::GetVolatility() const noexcept
{
  return ui->box_volatility->value();
}

int QtBrownianMotionParametersWidget::GetSeed() const noexcept
{
  return ui->box_seed->value();
}

void QtBrownianMotionParametersWidget::OnAnyChange() noexcept
{
  emit signal_parameters_changed();
}
