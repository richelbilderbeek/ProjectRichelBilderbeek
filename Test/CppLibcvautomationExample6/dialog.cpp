#include "dialog.h"

#include <stdexcept>

#include "ui_dialog.h"

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

void Dialog::on_pushButton_1_clicked()
{
  ui->pushButton_1->setText("OK");
}

void Dialog::on_pushButton_2_clicked()
{
  throw std::runtime_error("DON'T PRESS ME");
}

void Dialog::on_pushButton_3_clicked()
{
  ui->pushButton_3->setText("OK");
}
