#include "qtdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "ui_qtdialog.h"
#pragma GCC diagnostic pop

QtDialog::QtDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtDialog)
{
  ui->setupUi(this);
}

QtDialog::~QtDialog()
{
  delete ui;
}

void QtDialog::on_pushButton_1_clicked()
{
  ui->label->setText("1");
}

void QtDialog::on_pushButton_2_clicked()
{
  ui->label->setText("2");
}

void QtDialog::on_pushButton_3_clicked()
{
  ui->label->setText("3");
}
