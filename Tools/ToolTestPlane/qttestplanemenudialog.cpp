#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestplanemenudialog.h"

#include <cassert>

#include "qtaboutdialog.h"
#include "qtsurfaceplotwidget.h"
#include "qttestplaneconstructplanedialog.h"
#include "qttestplaneinvestigateaccuracyqwtdialog.h"
#include "qttestplaneinvestigateaccuracyribidialog.h"
#include "testplanemenudialog.h"
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
  QtTestPlaneConstructPlaneDialog d;
  ShowChild(&d);
}

void ribi::QtTestPlaneMenuDialog::on_button_about_clicked()
{
  About a(TestPlaneMenuDialog().GetAbout());
  //a.AddLibrary("QtSurfacePlotWidget version: " + QtSurfacePlotWidget::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
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
  {
    const QtTestPlaneMenuDialog d;
    assert(!d.GetVersion().empty());
  }
  {
    const TestPlaneMenuDialog d;
    assert(!d.GetVersion().empty());
  }
  {
    const QtTestPlaneConstructPlaneDialog d;
    assert(!d.GetVersion().empty());
  }
  {
    const QtTestPlaneInvestigateAccuracyQwtDialog d;
    assert(!d.GetVersion().empty());
  }
  {
    const QtTestPlaneInvestigateAccuracyRibiDialog d;
    assert(!d.GetVersion().empty());
  }
  TRACE("Finished ribi::QtTestPlaneMenuDialog::Test successfully");
  exit(0); //For profiling
}
#endif

void ribi::QtTestPlaneMenuDialog::on_button_investigate_accuracy_qwt_clicked()
{
  QtTestPlaneInvestigateAccuracyQwtDialog d;
  d.setStyleSheet(this->styleSheet());
  ShowChild(&d);
}

void ribi::QtTestPlaneMenuDialog::on_button_investigate_accuracy_ribi_clicked()
{
  QtTestPlaneInvestigateAccuracyRibiDialog d;
  ShowChild(&d);
  d.setStyleSheet(this->styleSheet());
}
