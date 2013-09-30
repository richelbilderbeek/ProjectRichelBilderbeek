#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "toolgraycodermaindialog.h"
#include "qttoolgraycodermaindialog.h"
#include "ui_qttoolgraycodermaindialog.h"
#pragma GCC diagnostic pop

ribi::QtGrayCoderMainDialog::QtGrayCoderMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtGrayCoderMainDialog)
{
  ui->setupUi(this);
  ui->box_int->setValue(1);
  ui->box_int->setValue(0);
}

ribi::QtGrayCoderMainDialog::~QtGrayCoderMainDialog() noexcept
{
  delete ui;
}

void ribi::QtGrayCoderMainDialog::on_box_int_valueChanged(int arg1) noexcept
{
  GrayCoderMainDialog d(arg1);
  ui->box_gray->setValue(d.GetGrayInt());
  ui->value_gray_binary->setText(d.GetGrayIntAsBitStr().c_str());
  ui->value_int_binary->setText(d.GetNormalIntAsBitStr().c_str());

}

void ribi::QtGrayCoderMainDialog::on_box_gray_valueChanged(int arg1) noexcept
{
  GrayCoderMainDialog d(0);
  d.SetGrayInt(arg1);
  ui->box_int->setValue(d.GetNormalInt());
  ui->value_gray_binary->setText(d.GetGrayIntAsBitStr().c_str());
  ui->value_int_binary->setText(d.GetNormalIntAsBitStr().c_str());
}
