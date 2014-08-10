#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtimagerotatermenudialog.h"

#include "qtaboutdialog.h"
#include "imagerotatermenudialog.h"
#include "testtimer.h"
#include "qtimagerotatermaindialog.h"
#include "ui_qtimagerotatermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtImageRotaterMenuDialog::QtImageRotaterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtImageRotaterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtImageRotaterMenuDialog::~QtImageRotaterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtImageRotaterMenuDialog::on_button_start_clicked()
{
  QtImageRotaterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtImageRotaterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(ImageRotaterMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtImageRotaterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtImageRotaterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtImageRotaterMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
