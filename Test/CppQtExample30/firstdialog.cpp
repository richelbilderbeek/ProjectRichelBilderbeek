#include "firstdialog.h"
#include "ui_firstdialog.h"

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
