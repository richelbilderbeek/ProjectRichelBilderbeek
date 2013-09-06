#include "qthometrainermaindialog.h"
#include "ui_qthometrainermaindialog.h"

ribi::QtHometrainerMainDialog::QtHometrainerMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtHometrainerMainDialog)
{
  ui->setupUi(this);
}

ribi::QtHometrainerMainDialog::~QtHometrainerMainDialog()
{
  delete ui;
}
