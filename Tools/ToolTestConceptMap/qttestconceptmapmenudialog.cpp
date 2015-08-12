#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include <cassert>

#include "qtaboutdialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapconceptdialog.h"
#include "qttestconceptmapedgedialog.h"
#include "qttestconceptmapexampledialog.h"
#include "qttestconceptmapexamplesdialog.h"
#include "qttestconceptmapnodedialog.h"
#include "qttestconceptmapqtedgedialog.h"
#include "qttestconceptmapqtnodedialog.h"
#include "qttestconceptmapwidgetdialog.h"

#include "qttesteditconceptmapdialog.h"

#include "testconceptmapmenudialog.h"
#include "qttestconceptmapwidgetdialog.h"
#include "testtimer.h"
#include "trace.h"
#include "ui_qttestconceptmapmenudialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtTestMenuDialog::QtTestMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestMenuDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);
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
  TestConceptMapMenuDialog().GetAbout();
  //Tests I am most interested in
  //if (sm_test_qtnode) { QtTestQtNodeDialog(); }

  //Tests in order from small elements to bigger
  QtTestExampleDialog();
  QtTestExamplesDialog();
  QtTestConceptDialog();
  QtTestNodeDialog();
  QtTestEdgeDialog();
  QtTestQtNodeDialog();
  QtTestQtEdgeDialog();
  //QtTestDisplayConceptMapDialog();
  QtTestEditConceptMapDialog();
  //QtTestRateConceptMapDialog();
  QtConceptMapViewTestsDialog();
  QtTestConceptMapWidgetDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //No tests...
}
#endif


/*
void ribi::cmap::QtTestMenuDialog::on_button_readonly_conceptmap_clicked()
{
  QtTestDisplayConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}
*/

void ribi::cmap::QtTestMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

/*
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

void ribi::cmap::QtTestMenuDialog::on_button_view_concept_maps_clicked()
{
  QtConceptMapViewTestsDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

void ribi::cmap::QtTestMenuDialog::on_button_conceptmapwidget_clicked()
{
  QtTestConceptMapWidgetDialog d;
  d.setStyleSheet(this->styleSheet());
  this->ShowChild(&d);
}

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
