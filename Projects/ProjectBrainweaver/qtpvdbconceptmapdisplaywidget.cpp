#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapdisplaywidget.h"

#include <boost/lambda/lambda.hpp>

#include "pvdbedge.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbexamplesitem.h"
#include "pvdbhelper.h"
#include "pvdbconceptmap.h"
#include "pvdbconceptmapfactory.h"
#include "qtpvdbcenternodeitem.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbdisplayconceptitem.h"
#include "trace.h"

///Collect all QGraphicsItems with class T in an unorderly way
template <class T>
std::vector<T*> Collect(const QGraphicsScene* const scene)
{
  std::vector<T*> v;
  const QList<QGraphicsItem *> items = scene->items();
  std::transform(items.begin(),items.end(),std::back_inserter(v),
    [](QGraphicsItem* const item)
    {
      assert(item);
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

QtPvdbConceptMapDisplayWidget::QtPvdbConceptMapDisplayWidget(
  const boost::shared_ptr<pvdb::ConceptMap> concept_map,
  QWidget* parent)
  : QtPvdbConceptMapWidget(concept_map,parent)
{
  #ifndef NDEBUG
  Test();
  #endif
  TRACE_FUNC();
}


void QtPvdbConceptMapDisplayWidget::AddEdge(
  const boost::shared_ptr<pvdb::Edge>& edge)
{
  assert(edge);
  const boost::shared_ptr<QtPvdbConceptItem> concept(new QtPvdbDisplayConceptItem(edge->GetConcept()));
  assert(concept);
  QtPvdbNodeItem * const from = FindQtNode(edge->GetFrom());
  assert(from);
  QtPvdbNodeItem * const to   = FindQtNode(edge->GetFrom());
  assert(to);
  QtPvdbEdgeItem * const qtedge = new QtPvdbEdgeItem(
    edge,
    concept,
    from,
    to
  );
  assert(qtedge);
  //Add the EdgeConcepts to the scene
  qtedge->m_signal_item_has_updated.connect(
    boost::bind(
      &QtPvdbConceptMapWidget::OnItemRequestsUpdate,
      this,boost::lambda::_1)); //Do not forget the placeholder!
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));
  assert(this->scene());
  this->scene()->addItem(qtedge);

  assert(qtedge->pos().x() == edge->GetX());
  assert(qtedge->pos().y() == edge->GetY());
}

QtPvdbNodeItem * QtPvdbConceptMapDisplayWidget::AddNode(const boost::shared_ptr<pvdb::Node>& node)
{
  TRACE_FUNC();
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<QtPvdbConceptItem> qtconcept(new QtPvdbDisplayConceptItem(node->GetConcept()));
  assert(qtconcept);
  QtPvdbNodeItem * const qtnode = new QtPvdbNodeItem(node,qtconcept);
  assert(qtnode);

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  this->scene()->addItem(qtnode);

  assert(qtnode->pos().x() == node->GetX());
  assert(qtnode->pos().y() == node->GetY());

  return qtnode;
}

void QtPvdbConceptMapDisplayWidget::CleanMe()
{
  TRACE_FUNC();
  //Prepare clearing the scene
  assert(m_examples);
  this->m_examples = nullptr;

  //Clear the scene, invalidates all scene items copies
  assert(this->scene());
  this->scene()->clear();

  //Put stuff back in
  //Add the invisible examples item
  {
    assert(!m_examples);
    m_examples = new QtPvdbExamplesItem;
    assert(m_examples);
    m_examples->setVisible(false);
    this->scene()->addItem(m_examples);
  }
  TRACE_FUNC();
}

#ifndef NDEBUG
std::unique_ptr<QtPvdbConceptMapWidget> QtPvdbConceptMapDisplayWidget::CreateNewDerived() const
{
  TRACE_FUNC();
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtPvdbConceptMapWidget> p(new QtPvdbConceptMapDisplayWidget(concept_map));
  assert(p);
  return p;
}
#endif

void QtPvdbConceptMapDisplayWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  TRACE_FUNC();
  assert(m_examples);
  assert(item);
  assert(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  m_examples->SetBuddyItem(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  assert(this->scene());
  scene()->update();
}
