#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "commander.h"
#pragma GCC diagnostic pop

SecondDialog::SecondDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::SecondDialog)
{
    ui->setupUi(this);
}

SecondDialog::~SecondDialog() noexcept
{
  delete ui;
}

void SecondDialog::on_pushButton_clicked()
{
  Commander::GetInstance()->Quit();
  this->close();
}
