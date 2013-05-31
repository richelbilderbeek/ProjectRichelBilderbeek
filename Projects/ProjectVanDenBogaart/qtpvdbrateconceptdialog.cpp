#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbrateconceptdialog.h"

#include <QFileDialog>
#include <QKeyEvent>
#include "qtpvdbconceptmapratewidget.h"
#include "pvdbfile.h"
#include "pvdbnode.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptfactory.h"
#include "pvdbnodefactory.h"
#include "trace.h"
#include "pvdbexamplesfactory.h"
#include "pvdbconceptmap.h"
#include "ui_qtpvdbrateconceptdialog.h"

QtPvdbRateConceptDialog::QtPvdbRateConceptDialog(
  const boost::shared_ptr<pvdb::ConceptMap> sub_concept_map,
  QWidget* parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtPvdbRateConceptDialog),
    m_concept(sub_concept_map->GetNodes().at(0)->GetConcept())
{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif

  assert(sub_concept_map);
  assert(!sub_concept_map->GetNodes().empty());
  assert(sub_concept_map->GetNodes()[0]);

  ui->widget->ReadFromConceptMap(sub_concept_map);

  assert(m_concept);

  ui->box_complexity->setCurrentIndex(m_concept->GetRatingComplexity());
  ui->box_concreteness->setCurrentIndex(m_concept->GetRatingConcreteness());
  ui->box_specificity->setCurrentIndex(m_concept->GetRatingSpecificity());

  ui->box_complexity->setFocus();
}

QtPvdbRateConceptDialog::~QtPvdbRateConceptDialog()
{
  delete ui;
}

void QtPvdbRateConceptDialog::keyPressEvent(QKeyEvent* e)
{
  if (e->key()  == Qt::Key_Escape) { close(); return; }
  QDialog::keyPressEvent(e);
}

void QtPvdbRateConceptDialog::on_button_ok_clicked()
{
  //Change concept
  assert(m_concept);
  assert(ui->box_complexity->currentIndex() >= -1);
  assert(ui->box_complexity->currentIndex() <=  2);

  m_concept->SetRatingComplexity(ui->box_complexity->currentIndex());
  m_concept->SetRatingConcreteness(ui->box_concreteness->currentIndex());
  m_concept->SetRatingSpecificity(ui->box_specificity->currentIndex());
  close();
}

void QtPvdbRateConceptDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    const boost::shared_ptr<pvdb::Concept> concept = concept_map->GetNodes().at(0)->GetConcept();
    assert(concept);
    const boost::shared_ptr<pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
    assert(old_concept);
    assert(concept == old_concept);
    QtPvdbRateConceptDialog d(concept_map);
    assert(concept->GetRatingComplexity() == d.ui->box_complexity->currentIndex());
    assert(concept->GetRatingConcreteness() == d.ui->box_concreteness->currentIndex());
    assert(concept->GetRatingSpecificity() == d.ui->box_specificity->currentIndex());
    //Change a box
    d.ui->box_complexity->setCurrentIndex( (d.ui->box_complexity->currentIndex() + 1) % 3);
    //But do not click OK
    assert(concept == old_concept && "Without clicking OK, QtPvdbRateConceptDialog must not change the concept");
  }
  {
    const boost::shared_ptr<pvdb::ConceptMap> concept_map
      = pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15);
    assert(concept_map);
    const boost::shared_ptr<pvdb::Concept> concept = concept_map->GetNodes().at(0)->GetConcept();
    assert(concept);
    const boost::shared_ptr<const pvdb::Concept> old_concept = pvdb::ConceptFactory::DeepCopy(concept);
    assert(old_concept);
    assert(concept == old_concept);
    QtPvdbRateConceptDialog d(concept_map);
    assert(concept->GetRatingComplexity()   == d.ui->box_complexity->currentIndex());
    assert(concept->GetRatingConcreteness() == d.ui->box_concreteness->currentIndex());
    assert(concept->GetRatingSpecificity()  == d.ui->box_specificity->currentIndex());
    //Change a box
    d.ui->box_complexity->setCurrentIndex( (d.ui->box_complexity->currentIndex() + 1) % 3);
    d.ui->button_ok->click();
    assert(concept != old_concept && "QtPvdbRateConceptDialog must change the concept when clicked OK");
  }
}
