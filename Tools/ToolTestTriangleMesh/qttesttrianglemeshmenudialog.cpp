#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtaboutdialog.h"
#include "qtsurfaceplotwidget.h"
#include "testtrianglemeshmenudialog.h"
#include "qttesttrianglemeshmaindialog.h"
#include "qttesttrianglemeshmenudialog.h"
#include "trace.h"
#include "ui_qttesttrianglemeshmenudialog.h"
#pragma GCC diagnostic pop

ribi::QtTestTriangleMeshMenuDialog::QtTestTriangleMeshMenuDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestTriangleMeshMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestTriangleMeshMenuDialog::~QtTestTriangleMeshMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestTriangleMeshMenuDialog::on_button_start_clicked()
{
  QtTestTriangleMeshMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestTriangleMeshMenuDialog::on_button_about_clicked()
{
  About a(TestTriangleMeshMenuDialog().GetAbout());
  //a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  this->ShowChild(&d);
}

void ribi::QtTestTriangleMeshMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestTriangleMeshMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestTriangleMeshMenuDialog::Test");
  TRACE("Finished ribi::QtTestTriangleMeshMenuDialog::Test successfully");
}
#endif
