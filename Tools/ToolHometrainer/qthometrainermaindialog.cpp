#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qthometrainermaindialog.h"
#include "ui_qthometrainermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtHometrainerMainDialog::QtHometrainerMainDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtHometrainerMainDialog)
{
  ui->setupUi(this);
}

ribi::QtHometrainerMainDialog::~QtHometrainerMainDialog() noexcept
{
  delete ui;
}
