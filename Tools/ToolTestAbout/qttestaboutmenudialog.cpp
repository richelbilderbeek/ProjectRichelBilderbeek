#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestaboutmenudialog.h"

#include <cassert>

#include "testaboutmenudialog.h"
#include "qtaboutdialog.h"
#include "trace.h"
#include "ui_qttestaboutmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestAboutMenuDialog::QtTestAboutMenuDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtTestAboutMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestAboutMenuDialog::~QtTestAboutMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestAboutMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestAboutMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtTestAboutMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestAboutMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestAboutMenuDialog::Test");
  QtAboutDialog d(TestAboutMenuDialog().GetAbout());
  TRACE("Successfully finished ribi::QtTestAboutMenuDialog::Test");
}
#endif
