#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtvirtualbastardexample1dialog.h"
#include "ui_qtvirtualbastardexample1dialog.h"
#pragma GCC diagnostic pop

QtVirtualBastardExample1Dialog::QtVirtualBastardExample1Dialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::QtVirtualBastardExample1Dialog)
{
  ui->setupUi(this);
}

QtVirtualBastardExample1Dialog::~QtVirtualBastardExample1Dialog()
{
  delete ui;
}
