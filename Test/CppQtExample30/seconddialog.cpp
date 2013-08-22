#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "commander.h"

SecondDialog::SecondDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondDialog)
{
    ui->setupUi(this);
}

SecondDialog::~SecondDialog()
{
    delete ui;
}

void SecondDialog::on_pushButton_clicked()
{
  Commander::GetInstance()->Quit();
  this->close();
}
