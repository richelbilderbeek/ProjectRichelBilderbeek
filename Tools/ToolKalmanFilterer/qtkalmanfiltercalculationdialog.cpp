//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtkalmanfiltercalculationdialog.h"

#include <boost/lexical_cast.hpp>

#pragma GCC diagnostic pop

#include "ui_qtkalmanfiltercalculationdialog.h"

QtKalmanFilterCalculationDialog::QtKalmanFilterCalculationDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtKalmanFilterCalculationDialog)
{
  ui->setupUi(this);
}

QtKalmanFilterCalculationDialog::~QtKalmanFilterCalculationDialog()
{
  delete ui;
}

