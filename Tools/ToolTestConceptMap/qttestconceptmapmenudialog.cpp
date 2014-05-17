#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include "qtaboutdialog.h"
#include "testconceptmapmenudialog.h"
#include "qttestdisplayconceptmapdialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestrateconceptmapdialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qtconceptmaptestconceptitemdialog.h"
#include "qtconceptmaptestedgeitemdialog.h"
#include "qtconceptmaptestnodeitemdialog.h"
#include "qttestconceptmapwidgetdialog.h"
#include "ui_qttestconceptmapmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestConceptMapMenuDialog::QtTestConceptMapMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestConceptMapMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
}

ribi::cmap::QtTestConceptMapMenuDialog::~QtTestConceptMapMenuDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestConceptMapMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::cmap::QtTestConceptMapMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtTestConceptMapMenuDialog::Test");
  QtConceptMapTestConceptItemDialog();
  QtConceptMapTestNodeItemDialog();
  QtConceptMapTestEdgeItemDialog();
  QtTestDisplayConceptMapDialog();
  QtTestEditConceptMapDialog();
  QtTestRateConceptMapDialog();
  QtConceptMapViewTestsDialog();
  QtTestConceptMapWidgetDialog();
  TRACE("Finished ribi::cmap::QtTestConceptMapMenuDialog::Test successfully");
}
#endif

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_readonly_conceptmap_clicked()
{
  QtTestDisplayConceptMapDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_rate_conceptmap_clicked()
{
  QtTestRateConceptMapDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_concept_clicked()
{
  QtConceptMapTestConceptItemDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_node_clicked()
{
  QtConceptMapTestNodeItemDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_edge_clicked()
{
  QtConceptMapTestEdgeItemDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_view_concept_maps_clicked()
{
  QtConceptMapViewTestsDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_conceptmapwidget_clicked()
{
  QtTestConceptMapWidgetDialog d;
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_example_clicked()
{
  QtConceptMapTestExampleDialog d;
  this->ShowChild(&d);
}
