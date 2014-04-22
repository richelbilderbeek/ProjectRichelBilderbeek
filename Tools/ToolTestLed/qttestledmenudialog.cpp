#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testledmenudialog.h"

#include "about.h"
#include "qtaboutdialog.h"
#include "qtledwidget.h"
#include "qttestledmaindialog.h"
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

void ribi::QtTestLedMenuDialog::on_button_start_clicked() noexcept
{
  QtTestLedMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestLedMenuDialog::on_button_about_clicked() noexcept
{
  About a = TestLedMenuDialog().GetAbout();
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
  {
    QtTestLedMainDialog d;
  }
}
#endif
