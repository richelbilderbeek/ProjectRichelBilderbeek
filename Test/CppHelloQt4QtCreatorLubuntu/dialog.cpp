#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
  this->setWindowTitle(QApplication::applicationName());
}

Dialog::~Dialog()
{
  delete ui;
}
