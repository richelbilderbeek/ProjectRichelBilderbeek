#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include "qtaboutdialog.h"
#include "testconceptmapmenudialog.h"
#include "qtconceptmaptestconceptdialog.h"
#include "qtconceptmaptestedgedialog.h"
#include "qtconceptmaptestexampledialog.h"
#include "qtconceptmaptestexamplesdialog.h"
#include "qtconceptmaptestnodedialog.h"
#include "qtconceptmaptestqtedgedialog.h"
#include "qtconceptmaptestqtnodedialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapwidgetdialog.h"
#include "qttestdisplayconceptmapdialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestrateconceptmapdialog.h"
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
  ui->button_example->setEnabled(sm_test_example);
  ui->button_examples->setEnabled(sm_test_examples);
  ui->button_concept->setEnabled(sm_test_concept);
  ui->button_node->setEnabled(sm_test_node);
  ui->button_edge->setEnabled(sm_test_edge);
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
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtTestConceptMapMenuDialog::Test");
  TestConceptMapMenuDialog().GetAbout();
  if (sm_test_example) { QtConceptMapTestExampleDialog(); }
  if (sm_test_examples) { QtConceptMapTestExamplesDialog(); };
  if (sm_test_concept) { QtConceptMapTestConceptDialog(); }
  if (sm_test_node) { QtConceptMapTestNodeDialog(); }
  if (sm_test_edge) { QtConceptMapTestEdgeDialog(); }
  if (sm_test_qtnode) { QtConceptMapTestQtNodeDialog(); }
  //QtTestDisplayConceptMapDialog();
  //QtTestEditConceptMapDialog();
  //QtTestRateConceptMapDialog();
  //QtConceptMapViewTestsDialog();
  //QtTestConceptMapWidgetDialog();
  TRACE("Finished ribi::cmap::QtTestConceptMapMenuDialog::Test successfully");
}
#endif

/*
void ribi::cmap::QtTestConceptMapMenuDialog::on_button_readonly_conceptmap_clicked()
{
  QtTestDisplayConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_rate_conceptmap_clicked()
{
  QtTestRateConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_concept_clicked()
{
  QtConceptMapTestConceptDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}


void ribi::cmap::QtTestConceptMapMenuDialog::on_button_node_clicked()
{
  QtConceptMapTestNodeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_edge_clicked()
{
  QtConceptMapTestEdgeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

/*

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_view_concept_maps_clicked()
{
  QtConceptMapViewTestsDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_conceptmapwidget_clicked()
{
  QtTestConceptMapWidgetDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_example_clicked()
{
  QtConceptMapTestExampleDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_examples_clicked()
{
  QtConceptMapTestExamplesDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestConceptMapMenuDialog::on_button_qtnode_clicked()
{
  QtConceptMapTestQtNodeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

/*
void ribi::cmap::QtTestConceptMapMenuDialog::on_button_qtedge_clicked()
{
  QtConceptMapTestQtEdgeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/
