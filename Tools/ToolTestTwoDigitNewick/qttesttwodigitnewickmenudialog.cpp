#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttesttwodigitnewickmenudialog.h"

#include <cassert>

#include "testtwodigitnewickmenudialog.h"
#include "qtaboutdialog.h"
#include "qttesttwodigitnewickmaindialog.h"
#include "trace.h"
#include "ui_qttesttwodigitnewickmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTwoDigitNewickMenuDialog::QtTestTwoDigitNewickMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestTwoDigitNewickMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestTwoDigitNewickMenuDialog::~QtTestTwoDigitNewickMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTwoDigitNewickMenuDialog::on_button_start_clicked()
{
  QtTestTwoDigitNewickMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestTwoDigitNewickMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestTwoDigitNewickMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtTestTwoDigitNewickMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestTwoDigitNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTwoDigitNewickMenuDialog::Test");
  QtTestTwoDigitNewickMainDialog();
  TRACE("Successfully finished ribi::QtTestTwoDigitNewickMenuDialog::Test");
}
#endif
