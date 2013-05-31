#include "qtfilteroperationermaindialog.h"
#include "ui_qtfilteroperationermaindialog.h"

QtFilterOperationerMainDialog::QtFilterOperationerMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtFilterOperationerMainDialog)
{
    ui->setupUi(this);
}

QtFilterOperationerMainDialog::~QtFilterOperationerMainDialog()
{
    delete ui;
}
