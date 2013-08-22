#include "qtarrowswidget.h"
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
  ui->setupUi(this);
  ui->layout->addWidget(new QtArrowsWidget);
}

Dialog::~Dialog()
{
  delete ui;
}
