#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtaboutdialog.h"
#include "qtsurfaceplotwidget.h"
#include "testplanemenudialog.h"
#include "qttestplanemaindialog.h"
#include "qttestplanemenudialog.h"
#include "trace.h"
#include "ui_qttestplanemenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestPlaneMenuDialog::QtTestPlaneMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestPlaneMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestPlaneMenuDialog::~QtTestPlaneMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestPlaneMenuDialog::on_button_start_clicked()
{
  QtTestPlaneMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestPlaneMenuDialog::on_button_about_clicked()
{
  About a(TestPlaneMenuDialog().GetAbout());
  //a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestPlaneMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestPlaneMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestPlaneMenuDialog::Test");
  TRACE("Finished ribi::QtTestPlaneMenuDialog::Test successfully");
}
#endif
