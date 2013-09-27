#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "somedialog.h"
#include "ui_somedialog.h"
#pragma GCC diagnostic pop

SomeDialog::SomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SomeDialog)
{
    ui->setupUi(this);
}

SomeDialog::~SomeDialog()
{
    delete ui;
}
