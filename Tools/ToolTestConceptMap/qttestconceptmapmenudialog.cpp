#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include "qtaboutdialog.h"
#include "testconceptmapmenudialog.h"
#include "qttestconceptmapconceptdialog.h"
#include "qttestconceptmapedgedialog.h"
#include "qttestconceptmapexampledialog.h"
#include "qttestconceptmapexamplesdialog.h"
#include "qttestconceptmapnodedialog.h"
#include "qttestconceptmapqtedgedialog.h"
#include "qttestconceptmapqtnodedialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapwidgetdialog.h"
#include "qttestdisplayconceptmapdialog.h"
#include "qttesteditconceptmapdialog.h"
#include "qttestrateconceptmapdialog.h"
#include "ui_qttestconceptmapmenudialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestMenuDialog::QtTestMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestMenuDialog)
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

ribi::cmap::QtTestMenuDialog::~QtTestMenuDialog() noexcept
{
  delete ui;
}

void ribi::cmap::QtTestMenuDialog::on_button_about_clicked()
{
  QtAboutDialog d(TestConceptMapMenuDialog().GetAbout());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_quit_clicked()
{
  close();
}

#ifndef NDEBUG
void ribi::cmap::QtTestMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtTestMenuDialog::Test");
  TestConceptMapMenuDialog().GetAbout();
  //Tests I am most interested in
  if (sm_test_qtedge) { QtTestQtEdgeDialog(); }

  //Tests in order from small elements to bigger
  if (sm_test_example) { QtTestExampleDialog(); }
  if (sm_test_examples) { QtTestExamplesDialog(); };
  if (sm_test_concept) { QtTestConceptDialog(); }
  if (sm_test_node) { QtTestNodeDialog(); }
  if (sm_test_edge) { QtTestEdgeDialog(); }
  if (sm_test_qtnode) { QtTestQtNodeDialog(); }
  if (sm_test_qtedge) { QtTestQtEdgeDialog(); }
  //if (sm_test_qtdisplayconceptmap) { QtTestDisplayConceptMapDialog(); }
  //if (sm_test_qteditconceptmap) { QtTestEditConceptMapDialog(); }
  //QtTestRateConceptMapDialog();
  //QtConceptMapViewTestsDialog();
  //QtTestWidgetDialog();
  TRACE("Finished ribi::cmap::QtTestMenuDialog::Test successfully");
}
#endif

/*
void ribi::cmap::QtTestMenuDialog::on_button_readonly_conceptmap_clicked()
{
  QtTestDisplayConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_rate_conceptmap_clicked()
{
  QtTestRateConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/

void ribi::cmap::QtTestMenuDialog::on_button_concept_clicked()
{
  QtTestConceptDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}


void ribi::cmap::QtTestMenuDialog::on_button_node_clicked()
{
  QtTestNodeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_edge_clicked()
{
  QtTestEdgeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

/*

void ribi::cmap::QtTestMenuDialog::on_button_view_concept_maps_clicked()
{
  QtConceptMapViewTestsDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_conceptmapwidget_clicked()
{
  QtTestWidgetDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/

void ribi::cmap::QtTestMenuDialog::on_button_example_clicked()
{
  QtTestExampleDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_examples_clicked()
{
  QtTestExamplesDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_qtnode_clicked()
{
  QtTestQtNodeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_qtedge_clicked()
{
  QtTestQtEdgeDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
