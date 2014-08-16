#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstateobservermenudialog.h"

#include "qtaboutdialog.h"
#include "qtstateobservermaindialog.h"
#include "qthideandshowdialog.h"
#include "stateobservermenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtstateobservermenudialog.h"

#pragma GCC diagnostic pop

ribi::QtStateObserverMenuDialog::QtStateObserverMenuDialog(QWidget *parent) noexcept :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtStateObserverMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtStateObserverMenuDialog::~QtStateObserverMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtStateObserverMenuDialog::on_button_start_clicked() noexcept
{
  QtStateObserverMainDialog d;
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStateObserverMenuDialog::on_button_about_clicked() noexcept
{
  About a = StateObserverMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->ShowChild(&d);
}

void ribi::QtStateObserverMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

#ifndef NDEBUG
void ribi::QtStateObserverMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
