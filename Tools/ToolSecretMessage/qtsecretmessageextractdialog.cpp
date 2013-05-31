#include "qtsecretmessageextractdialog.h"
#include "ui_qtsecretmessageextractdialog.h"

QtSecretMessageExtractDialog::QtSecretMessageExtractDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSecretMessageExtractDialog)
{
    ui->setupUi(this);
}

QtSecretMessageExtractDialog::~QtSecretMessageExtractDialog()
{
    delete ui;
}
