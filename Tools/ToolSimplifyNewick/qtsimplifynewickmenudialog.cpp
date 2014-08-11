#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtsimplifynewickmenudialog.h"

#include "qtaboutdialog.h"
#include "qtsimplifynewickmaindialog.h"
#include "simplifynewickmaindialog.h"
#include "simplifynewickmenudialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qtsimplifynewickmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtToolSimplifyNewickMenuDialog::QtToolSimplifyNewickMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtToolSimplifyNewickMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtToolSimplifyNewickMenuDialog::~QtToolSimplifyNewickMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtToolSimplifyNewickMenuDialog::on_button_about_clicked() noexcept
{
  QtAboutDialog d(ToolSimplifyNewickMenuDialog().GetAbout());
  d.setWindowIcon(this->windowIcon());
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtToolSimplifyNewickMenuDialog::on_button_quit_clicked() noexcept
{
  close();
}

void ribi::QtToolSimplifyNewickMenuDialog::on_button_start_clicked() noexcept
{
  QtToolSimplifyNewickMainDialog d;
  ShowChild(&d);
}

#ifndef NDEBUG
void ribi::QtToolSimplifyNewickMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtToolSimplifyNewickMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
