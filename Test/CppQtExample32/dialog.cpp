#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtarrowswidget.h"
#include "dialog.h"
#include "ui_dialog.h"
#pragma GCC diagnostic pop

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
