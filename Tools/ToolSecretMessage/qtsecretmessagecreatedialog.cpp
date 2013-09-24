#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <QFileDialog>
#include "qtsecretmessagecreatedialog.h"
#include "ui_qtsecretmessagecreatedialog.h"
#pragma GCC diagnostic pop

ribi::QtSecretMessageCreateDialog::QtSecretMessageCreateDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSecretMessageCreateDialog)
{
    ui->setupUi(this);
}

ribi::QtSecretMessageCreateDialog::~QtSecretMessageCreateDialog() noexcept
{
  delete ui;
}

void ribi::QtSecretMessageCreateDialog::on_button_load_original_clicked()
{
  QFileDialog::getOpenFileName(0,"Please select an image to hide a message in",QString(),"*.png,*.bmp,*.jpg,*.jpeg");
}
