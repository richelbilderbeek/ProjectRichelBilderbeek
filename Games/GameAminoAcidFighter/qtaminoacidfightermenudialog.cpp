#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtaminoacidfightermenudialog.h"

#include "qtaboutdialog.h"
#include "aafmenudialog.h"
#include "qtaminoacidfightermaindialog.h"
#include "ui_qtaminoacidfightermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::aaf::QtAafMenuDialog::QtAafMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtAafMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::aaf::QtAafMenuDialog::~QtAafMenuDialog() noexcept
{
  delete ui;
}

void ribi::aaf::QtAafMenuDialog::on_button_start_clicked()
{
  QtAafMainDialog d;
  this->ShowChild(&d);
}

void ribi::aaf::QtAafMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(aaf::MenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::aaf::QtAafMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::aaf::QtAafMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::aaf::QtAafMenuDialog::Test");
  QtAafMainDialog();
  aaf::MenuDialog();
  TRACE("Finished ribi::aaf::QtAafMenuDialog::Test successfully");
}
#endif
