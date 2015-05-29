#include "qtbrownianmotionlikelihoodwidget.h"
#include "ui_qtbrownianmotionlikelihoodwidget.h"

QtBrownianMotionLikelihoodWidget::QtBrownianMotionLikelihoodWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtBrownianMotionLikelihoodWidget)
{
  ui->setupUi(this);
}

QtBrownianMotionLikelihoodWidget::~QtBrownianMotionLikelihoodWidget()
{
  delete ui;
}
