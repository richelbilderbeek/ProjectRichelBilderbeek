#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "dialog.h"
#include "ui_dialog.h"
#pragma GCC diagnostic pop

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
}

Dialog::~Dialog()
{
  delete ui;
}

void Dialog::on_pushButton_clicked()
{
  ui->pushButton->setText("Hello World");
}
