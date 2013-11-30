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

ribi::QtTestConceptMapMenuDialog::QtTestConceptMapMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestConceptMapMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::QtTestConceptMapMenuDialog::~QtTestConceptMapMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtTestConceptMapMenuDialog::on_button_start_clicked()
{
  QtTestConceptMapMainDialog d;
  this->ShowChild(&d);
}

void ribi::QtTestConceptMapMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestConceptMapMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::QtTestConceptMapMenuDialog::on_button_quit_clicked()
{
  this->close();
}

#ifndef NDEBUG
void ribi::QtTestConceptMapMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::QtTestConceptMapMenuDialog::Test");
  QtTestConceptMapMainDialog();
  TRACE("Finished ribi::QtTestConceptMapMenuDialog::Test successfully");
}
#endif
