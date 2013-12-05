#include "qtbrainspinnermaindialog.h"
#include "ui_qtbrainspinnermaindialog.h"

QtBrainSpinnerMainDialog::QtBrainSpinnerMainDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtBrainSpinnerMainDialog)
{
  ui->setupUi(this);
}

QtBrainSpinnerMainDialog::~QtBrainSpinnerMainDialog()
{
  delete ui;
}
