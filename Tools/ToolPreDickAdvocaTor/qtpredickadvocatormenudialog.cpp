#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpredickadvocatormenudialog.h"

#include "qtaboutdialog.h"
#include "predickadvocatormenudialog.h"
#include "qtpredickadvocatormaindialog.h"
#include "ui_qtpredickadvocatormenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtPreDickAdvocaTorMenuDialog::QtPreDickAdvocaTorMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtPreDickAdvocaTorMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtPreDickAdvocaTorMenuDialog::~QtPreDickAdvocaTorMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtPreDickAdvocaTorMenuDialog::on_button_start_clicked()
{
  const int seed = 123;
  QtPreDickAdvocaTorMainDialog d(seed);
  this->ShowChild(&d);
}

void ribi::QtPreDickAdvocaTorMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(PreDickAdvocaTorMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtPreDickAdvocaTorMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtPreDickAdvocaTorMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtPreDickAdvocaTorMenuDialog::Test");
  QtPreDickAdvocaTorMainDialog();
  TRACE("Finished ribi::QtPreDickAdvocaTorMenuDialog::Test successfully");
}
#endif
