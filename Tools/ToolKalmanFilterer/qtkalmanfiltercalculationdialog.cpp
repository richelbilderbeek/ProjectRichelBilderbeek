

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtkalmanfiltercalculationdialog.h"

#include <boost/lexical_cast.hpp>

#pragma GCC diagnostic pop

#include "ui_qtkalmanfiltercalculationdialog.h"

ribi::QtKalmanFilterCalculationDialog::QtKalmanFilterCalculationDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtKalmanFilterCalculationDialog)
{
  ui->setupUi(this);
}

ribi::QtKalmanFilterCalculationDialog::~QtKalmanFilterCalculationDialog()
{
  delete ui;
}

