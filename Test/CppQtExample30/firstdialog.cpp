#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "firstdialog.h"
#include "ui_firstdialog.h"
#pragma GCC diagnostic pop

FirstDialog::FirstDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirstDialog)
{
    ui->setupUi(this);
}

FirstDialog::~FirstDialog()
{
    delete ui;
}
