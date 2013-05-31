#include "qthometrainermaindialog.h"
#include "ui_qthometrainermaindialog.h"

QtHometrainerMainDialog::QtHometrainerMainDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtHometrainerMainDialog)
{
  ui->setupUi(this);
}

QtHometrainerMainDialog::~QtHometrainerMainDialog()
{
  delete ui;
}
