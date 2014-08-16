#include "qtdialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <string>

#include <boost/lexical_cast.hpp>

#include "ui_qtdialog.h"
#pragma GCC diagnostic pop

QtDialog::QtDialog(QWidget *parent)
  : QDialog(parent),
    ui(new Ui::QtDialog)
{
  ui->setupUi(this);
}

QtDialog::~QtDialog()
{
  delete ui;
}


void QtDialog::on_button_1_clicked()
{
  ui->toolBox->setItemText(0,"Clicked");
}

void QtDialog::on_button_2_clicked()
{
  ui->toolBox->setItemText(1,"Clicked");
}

void QtDialog::on_button_3_clicked()
{
  ui->toolBox->setItemText(2,"Clicked");
}
