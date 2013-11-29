#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include "qtaboutdialog.h"
#include "testconceptmapmenudialog.h"
#include "qttestconceptmapdisplaywidgetdialog.h"
#include "qttestconceptmapeditwidgetdialog.h"
#include "qttestconceptmapratewidgetdialog.h"
#include "ui_qttestconceptmapmenudialog.h"
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
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtFilterOperationerMenuDialog::Test");
  QtFilterOperationerMainDialog();
  TRACE("Finished ribi::QtFilterOperationerMenuDialog::Test successfully");
}
#endif
