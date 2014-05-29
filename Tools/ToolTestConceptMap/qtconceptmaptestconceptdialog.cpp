#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmaptestconceptdialog.h"

#include <cassert>
#include <stdexcept>

#include <boost/lexical_cast.hpp>

#include <QKeyEvent>

#include "conceptmapcompetencies.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapeditstrategy.h"
#include "qtconceptmapratestrategy.h"
#include "trace.h"
#include "ui_qtconceptmaptestconceptdialog.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapTestConceptDialog::QtConceptMapTestConceptDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtConceptMapTestConceptDialog)
    //m_concept(cmap::ConceptFactory().GetTests().at(1)),
    //m_display_concept(nullptr),
    //m_edit_concept(nullptr),
    //m_rate_concept(nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  ui->box_test->setMinimum(0);
  ui->box_test->setMaximum(ConceptFactory().GetNumberOfTests() - 1);

  ui->qtconceptdialog1->setMinimumHeight(100);
  ui->qtconceptdialog2->setMinimumHeight(100);
  ui->qtconceptdialog1->setMinimumWidth(100);
  ui->qtconceptdialog2->setMinimumWidth(100);

  ui->box_test->setValue(1);
  on_button_load_clicked();

}

ribi::cmap::QtConceptMapTestConceptDialog::~QtConceptMapTestConceptDialog() noexcept
{
  delete ui;
}


void ribi::cmap::QtConceptMapTestConceptDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapTestConceptDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::cmap::QtConceptMapTestConceptDialog::Test started");
  TRACE("ribi::cmap::QtConceptMapTestConceptDialog::Test finished successfully");
}
#endif

void ribi::cmap::QtConceptMapTestConceptDialog::on_button_load_clicked()
{
  const int i = ui->box_test->value();
  assert(i >= 0);
  assert(i < ConceptFactory().GetNumberOfTests());
  const auto concept = ConceptFactory().GetTest(i);
  ui->qtconceptdialog1->SetConcept(concept);
  ui->qtconceptdialog2->SetConcept(concept);
  assert(ui->qtconceptdialog1->GetConcept() == concept);
  assert(ui->qtconceptdialog2->GetConcept() == concept);
  ui->qtconceptdialog1->repaint();
  ui->qtconceptdialog2->repaint();
}
