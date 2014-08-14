#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtvalentinecarddecryptermenudialog.h"

#include "qtaboutdialog.h"
#include "valentinecarddecryptermenudialog.h"
#include "qtvalentinecarddecryptermaindialog.h"
#include "testtimer.h"
#include "ui_qtvalentinecarddecryptermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtValentineCardDecrypterMenuDialog::QtValentineCardDecrypterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtValentineCardDecrypterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtValentineCardDecrypterMenuDialog::~QtValentineCardDecrypterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtValentineCardDecrypterMenuDialog::on_button_start_clicked()
{
  QtValentineCardDecrypterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtValentineCardDecrypterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(ValentineCardDecrypterMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtValentineCardDecrypterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtValentineCardDecrypterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtValentineCardDecrypterMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
