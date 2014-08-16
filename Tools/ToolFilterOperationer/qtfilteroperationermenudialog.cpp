#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtfilteroperationermenudialog.h"

#include "qtaboutdialog.h"
#include "filteroperationermenudialog.h"
#include "qtfilteroperationermaindialog.h"
#include "ui_qtfilteroperationermenudialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtFilterOperationerMenuDialog::QtFilterOperationerMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtFilterOperationerMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtFilterOperationerMenuDialog::~QtFilterOperationerMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtFilterOperationerMenuDialog::on_button_start_clicked()
{
  QtFilterOperationerMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtFilterOperationerMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(FilterOperationerMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtFilterOperationerMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtFilterOperationerMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  QtFilterOperationerMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
