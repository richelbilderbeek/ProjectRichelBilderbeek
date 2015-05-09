#include "qtmutualismbreakdownerparameterswidget.h"
#include "ui_qtmutualismbreakdownerparameterswidget.h"

QtMutualismBreakdownerParametersWidget::QtMutualismBreakdownerParametersWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::QtMutualismBreakdownerParametersWidget)
{
  ui->setupUi(this);
}

QtMutualismBreakdownerParametersWidget::~QtMutualismBreakdownerParametersWidget()
{
  delete ui;
}
