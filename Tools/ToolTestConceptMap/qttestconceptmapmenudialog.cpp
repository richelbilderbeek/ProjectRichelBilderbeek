#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qttestconceptmapmenudialog.h"

#include <cassert>

#include <QTimer>

#include "qtaboutdialog.h"
#include "qtconceptmapviewtestsdialog.h"
#include "qttestconceptmapconceptdialog.h"
#include "qttestconceptmapedgedialog.h"
#include "conceptmapconceptfactory.h"
#include "qttestconceptmapexampledialog.h"
#include "qttestconceptmapexamplesdialog.h"
#include "qttestconceptmapnodedialog.h"
#include "qttestconceptmapqtedgedialog.h"
#include "qttestconceptmapqtnodedialog.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qttesteditconceptmapdialog.h"

#include "testconceptmapmenudialog.h"

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

  //Show current screen I am most interested in
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  QTimer::singleShot(100,Qt::CoarseTimer,this,SLOT(on_button_edit_conceptmap_clicked()));
  #else
  QTimer::singleShot(100,this,SLOT(on_button_edit_conceptmap_clicked()));
  #endif
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
  {
    auto concept = ConceptFactory().GetTest(0);
    QtConceptMapConceptEditDialog dialog(concept);
  }

  //Tests in order from small elements to bigger
  QtTestExampleDialog();
  QtTestExamplesDialog();
  QtTestConceptDialog();
  QtTestNodeDialog();
  QtTestEdgeDialog();
  QtTestQtNodeDialog();
  QtTestQtEdgeDialog();
  QtTestEditConceptMapDialog();
  QtConceptMapViewTestsDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //No tests...
}
#endif

void ribi::cmap::QtTestMenuDialog::on_button_edit_conceptmap_clicked()
{
  QtTestEditConceptMapDialog d;
  d.setStyleSheet(this->styleSheet());
  //d.setWindowState(Qt::WindowFullScreen);
  this->ShowChild(&d);
}

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

void ribi::cmap::QtTestMenuDialog::on_button_view_conceptmaps_clicked()
{
  QtConceptMapViewTestsDialog d;
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
