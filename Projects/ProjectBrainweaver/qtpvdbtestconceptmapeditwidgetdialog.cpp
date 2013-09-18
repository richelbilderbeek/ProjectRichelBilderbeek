#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtpvdbtestconceptmapeditwidgetdialog.h"

#include <cassert>

#include <boost/lexical_cast.hpp>
#include <QKeyEvent>
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbexample.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtpvdbbrushfactory.h"
#include "qtpvdbconceptmapitem.h"
#include "pvdbexamplesfactory.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbeditconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbrateconceptitem.h"
#include "qtpvdbconceptmapeditwidget.h"
#include "trace.h"
#include "ui_qtpvdbtestconceptmapeditwidgetdialog.h"
#pragma GCC diagnostic pop


ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::QtPvdbTestConceptMapEditWidgetDialog(QWidget *parent) :
  QtHideAndShowDialog(parent),
  ui(new Ui::QtPvdbTestConceptMapEditWidgetDialog),
  m_concept_map(
    new QtPvdbConceptMapEditWidget(
      ribi::pvdb::ConceptMapFactory::GetHeteromorphousTestConceptMaps().at(15)
    )
  )

{
  ui->setupUi(this);
  #ifndef NDEBUG
  Test();
  #endif
  assert(ui->widget->layout());
  ui->widget->layout()->addWidget(m_concept_map.get());
}

ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::~QtPvdbTestConceptMapEditWidgetDialog() noexcept
{
  delete ui;
}

void ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
  if (event->key() == Qt::Key_1
     && event->modifiers() & Qt::AltModifier)
  {
    DoSomethingRandom();
  }
}

void ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::Test started");
  QtPvdbTestConceptMapEditWidgetDialog d;
  d.DoSomethingRandom();
  TRACE("TODO");
  /*
  assert(d.m_concept_map.get() == d.m_display_node->GetNode().get());
  assert(d.m_concept_map.get() == d.m_edit_node->GetNode().get());
  assert(d.m_concept_map.get() == d.m_rate_node->GetNode().get());
  assert(d.m_concept_map->GetConcept().get() == d.m_display_node->GetNode()->GetConcept().get());
  assert(d.m_concept_map->GetConcept().get() == d.m_edit_node->GetNode()->GetConcept().get());
  assert(d.m_concept_map->GetConcept().get() == d.m_rate_node->GetNode()->GetConcept().get());
  */
  //Test resizing due to text being changed
  {
    TRACE("TODO");
    /*
    const std::string s = d.m_concept_map->GetConcept()->GetName();
    assert(d.m_display_node->boundingRect().width() == d.m_edit_node->boundingRect().width());
    assert(d.m_display_node->boundingRect().width() == d.m_rate_node->boundingRect().width());
    const double w = d.m_display_node->boundingRect().width();
    d.m_concept_map->GetConcept()->SetName(s + "*");
    assert(d.m_display_node->boundingRect().width() > w);
    assert(d.m_edit_node->boundingRect().width() > w);
    assert(d.m_rate_node->boundingRect().width() > w);
    */
  }
  //Test resizing due to shorter text being set
  {
    TRACE("TODO");
    /*
    d.m_concept_map->GetConcept()->SetName("1234567890");
    const double w = d.m_display_node->boundingRect().width();
    d.m_concept_map->GetConcept()->SetName("123456789");
    assert(d.m_display_node->boundingRect().width() < w);
    */
  }
  //Test brushes being changed when ratings are given
  {
    TRACE("TODO");
    /*
    const boost::shared_ptr<ribi::pvdb::Concept> concept = d.m_concept_map->GetConcept();
    concept->SetRatingComplexity(-1);
    concept->SetRatingConcreteness(-1);
    concept->SetRatingSpecificity(-1);
    QtPvdbRateConceptItem item(concept);
    assert(d.m_edit_node->brush()    == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_node->brush() == QtPvdbBrushFactory::CreateRedGradientBrush());
    assert(d.m_rate_node->brush()    == QtPvdbBrushFactory::CreateRedGradientBrush());

    concept->SetRatingComplexity(0);
    concept->SetRatingConcreteness(1);

    assert(d.m_edit_node->brush()     == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_node->brush()  == QtPvdbBrushFactory::CreateYellowGradientBrush());
    assert(d.m_rate_node->brush()     == QtPvdbBrushFactory::CreateYellowGradientBrush());

    concept->SetRatingSpecificity(2);

    assert(d.m_edit_node->brush()    == QtPvdbBrushFactory::CreateGrayGradientBrush());
    assert(d.m_display_node->brush() == QtPvdbBrushFactory::CreateGreenGradientBrush());
    assert(d.m_rate_node->brush()    == QtPvdbBrushFactory::CreateGreenGradientBrush());
    */
  }
  TRACE("ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::Test finished successfully");
}

void ribi::pvdb::QtPvdbTestConceptMapEditWidgetDialog::DoSomethingRandom()
{

  const QList<QGraphicsItem *> v = m_concept_map->GetScene()->items();
  std::for_each(v.begin(),v.end(),
    [](QGraphicsItem * const item)
    {
      if (QtPvdbNodeItem* const qtitem = dynamic_cast<QtPvdbNodeItem*>(item))
      {
        assert(qtitem->GetConcept());
        assert(!qtitem->GetConcept()->GetName().empty());
        assert(qtitem->GetConcept()->GetExamples());
        qtitem->SetName(qtitem->GetConcept()->GetName() + "N");
        const std::vector<boost::shared_ptr<ribi::pvdb::Examples> > v = pvdb::ExamplesFactory::GetTests();
        qtitem->GetConcept()->SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
      if (QtPvdbEdgeItem* const qtitem = dynamic_cast<QtPvdbEdgeItem*>(item))
      {
        assert(qtitem->GetConcept());
        assert(!qtitem->GetConcept()->GetName().empty());
        assert(qtitem->GetConcept()->GetExamples());
        qtitem->SetName(qtitem->GetConcept()->GetName() + "E");
        const std::vector<boost::shared_ptr<ribi::pvdb::Examples> > v = pvdb::ExamplesFactory::GetTests();
        qtitem->GetConcept()->SetExamples(v [ std::rand() % v.size() ] );
        qtitem->update();
      }
    }
  );
  m_concept_map->GetScene()->update();
}
