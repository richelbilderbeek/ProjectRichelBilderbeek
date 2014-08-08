#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtstylesheetsettermenudialog.h"

#include "qtaboutdialog.h"
#include "stylesheetsettermenudialog.h"
#include "qtstylesheetsettermaindialog.h"
#include "testtimer.h"
#include "ui_qtstylesheetsettermenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtStyleSheetSetterMenuDialog::QtStyleSheetSetterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtStyleSheetSetterMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtStyleSheetSetterMenuDialog::~QtStyleSheetSetterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtStyleSheetSetterMenuDialog::on_button_start_clicked()
{
  QtStyleSheetSetterMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtStyleSheetSetterMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(StyleSheetSetterMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtStyleSheetSetterMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtStyleSheetSetterMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtStyleSheetSetterMainDialog();
}
#endif
