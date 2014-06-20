#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testledmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qtled.h"
#include "qtleddialog.h"
#include "qtledwidget.h"
#include "qttestledcomparedialog.h"
#include "qttestledmodifydialog.h"
#include "qttestledmenudialog.h"
#include "ui_qttestledmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedMenuDialog::QtTestLedMenuDialog(QWidget *parent) noexcept
 : QtHideAndShowDialog(parent),
   ui(new Ui::QtTestLedMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestLedMenuDialog::~QtTestLedMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestLedMenuDialog::on_button_led_compare_clicked() noexcept
{
  QtTestLedCompareDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestLedMenuDialog::on_button_led_modify_clicked() noexcept
{
  QtTestLedModifyDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestLedMenuDialog::on_button_about_clicked() noexcept
{
  About a = TestLedMenuDialog().GetAbout();
  a.AddLibrary("QtLed version: " + QtLed::GetVersion());
  a.AddLibrary("QtLedDialog version: " + QtLedDialog::GetVersion());
  a.AddLibrary("QtLedWidget version: " + QtLedWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestLedMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtTestLedMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  QtTestLedCompareDialog();
  QtTestLedModifyDialog();
}
#endif
