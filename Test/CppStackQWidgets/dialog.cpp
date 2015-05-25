#include "dialog.h"

#include <QGroupBox>

#include "mywidget.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Dialog)
{
  ui->setupUi(this);

  //Create a QGroupBox to stack the MyWidgets
  QGroupBox * const b = new QGroupBox(this);

  //A fresh QGroupBox does not have a layout yet
  b->setLayout(new QVBoxLayout);

  //Stack the MyWidgets
  for (int i=0; i!=10; ++i)
  {
    b->layout()->addWidget(new MyWidget(this));
  }

  //Use setWidget
  ui->scrollArea->setWidget(b);
}

Dialog::~Dialog()
{
  delete ui;
}
