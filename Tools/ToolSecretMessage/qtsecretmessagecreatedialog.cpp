#include <QFileDialog>
#include "qtsecretmessagecreatedialog.h"
#include "ui_qtsecretmessagecreatedialog.h"

QtSecretMessageCreateDialog::QtSecretMessageCreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtSecretMessageCreateDialog)
{
    ui->setupUi(this);
}

QtSecretMessageCreateDialog::~QtSecretMessageCreateDialog()
{
    delete ui;
}

void QtSecretMessageCreateDialog::on_button_load_original_clicked()
{
  QFileDialog::getOpenFileName(0,"Please select an image to hide a message in",QString(),"*.png,*.bmp,*.jpg,*.jpeg");
}
