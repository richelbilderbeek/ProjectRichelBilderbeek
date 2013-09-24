#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsecretmessageextractdialog.h"
#include "ui_qtsecretmessageextractdialog.h"
#pragma GCC diagnostic pop

ribi::QtSecretMessageExtractDialog::QtSecretMessageExtractDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSecretMessageExtractDialog)
{
    ui->setupUi(this);
}

ribi::QtSecretMessageExtractDialog::~QtSecretMessageExtractDialog() noexcept
{
    delete ui;
}
