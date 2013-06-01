#include "qtpvdbtestcreatesubconceptmapdialog.h"

#ifdef SUPPORT_TEST_CONCEPT_MAP_DIALOGS_86543723642

#include <cassert>
#include <boost/numeric/conversion/cast.hpp>
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "ui_qtpvdbtestcreatesubconceptmapdialog.h"

QtPvdbTestCreateSubConceptMapDialog::QtPvdbTestCreateSubConceptMapDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestCreateSubConceptMapDialog)
{
  ui->setupUi(this);
  const int n_tests = boost::numeric_cast<int>(pvdb::ConceptMapFactory::GetAllTests().size());
  ui->box_index->setMaximum(n_tests - 1); //-1: 0-based counting

  QObject::connect(ui->box_index,SIGNAL(valueChanged(int)),this,SLOT(OnConceptMapChanged()));
  QObject::connect(ui->box_index_sub,SIGNAL(valueChanged(int)),this,SLOT(OnSubConceptMapChanged()));

  OnConceptMapChanged();
}

QtPvdbTestCreateSubConceptMapDialog::~QtPvdbTestCreateSubConceptMapDialog()
{
  delete ui;
}

void QtPvdbTestCreateSubConceptMapDialog::OnConceptMapChanged()
{
  const int i = ui->box_index->value();
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetAllTests();
  assert(i < boost::numeric_cast<int>(v.size()));
  const boost::shared_ptr<pvdb::ConceptMap> concept_map = v[i];
  ui->concept_map->ReadFromConceptMap(concept_map);

  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > subs = concept_map->CreateSubs();
  const int n_subs = boost::numeric_cast<int>(subs.size());
  assert(n_subs != 0);
  ui->box_index_sub->setMaximum(n_subs - 1); //-1: 0-based counting
  ui->box_index_sub->setValue(0);
}

void QtPvdbTestCreateSubConceptMapDialog::OnSubConceptMapChanged()
{
  const int i = ui->box_index->value();
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > v = pvdb::ConceptMapFactory::GetAllTests();
  assert(i < boost::numeric_cast<int>(v.size()));
  const boost::shared_ptr<pvdb::ConceptMap> concept_map = v[i];
  const std::vector<boost::shared_ptr<pvdb::ConceptMap> > subs = concept_map->CreateSubs();
  const int j = ui->box_index_sub->value();
  assert(j < boost::numeric_cast<int>(subs.size()));
  const boost::shared_ptr<pvdb::ConceptMap> sub = subs[j];
  ui->sub_concept_map->ReadFromConceptMap(sub);

}

#endif
