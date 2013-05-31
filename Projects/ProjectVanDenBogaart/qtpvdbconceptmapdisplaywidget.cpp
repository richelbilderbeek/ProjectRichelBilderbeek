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
#include "pvdbhints.h"
#include "pvdbhelper.h"
#include "pvdbconceptmap.h"
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
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

QtPvdbConceptMapDisplayWidget::QtPvdbConceptMapDisplayWidget(QWidget* parent)
  : QtPvdbConceptMapWidget(parent)
{
  #ifndef NDEBUG
  Test();
  #endif
}


void QtPvdbConceptMapDisplayWidget::AddEdge(
  const boost::shared_ptr<pvdb::Edge>& edge,
  const std::vector<QtPvdbNodeItem*>& qtnodes)
{
  //ERROR IN THIS LINE: THE NODE CONCEPTS HAVE GOTTEN A DIFFERENT ORDER!
  //SOLUTION: MAKE NODE_CONCEPTS LOCAL AND IN THE SAME ORDER
  //const std::vector<QtPvdbRateConcept*> node_concepts = Collect<QtPvdbRateConcept>(scene());
  assert(edge->GetFrom() < static_cast<int>(qtnodes.size()));
  assert(edge->GetTo()   < static_cast<int>(qtnodes.size()));
  const boost::shared_ptr<QtPvdbConceptItem> concept(new QtPvdbDisplayConceptItem(edge->GetConcept()));
  assert(concept);
  QtPvdbEdgeItem * const qtedge = new QtPvdbEdgeItem(
    edge,
    concept,
    qtnodes[edge->GetFrom()],
    qtnodes[edge->GetTo()]
  );
  //Add the EdgeConcepts to the scene
  qtedge->m_signal_item_has_updated.connect(
    boost::bind(
      &QtPvdbConceptMapWidget::OnItemRequestsUpdate,
      this,boost::lambda::_1)); //Do not forget the placeholder!
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));
  this->scene()->addItem(qtedge);

  assert(qtedge->pos().x() == edge->GetX());
  assert(qtedge->pos().y() == edge->GetY());
}

QtPvdbNodeItem * QtPvdbConceptMapDisplayWidget::AddNode(const boost::shared_ptr<pvdb::Node>& node)
{
  const boost::shared_ptr<QtPvdbConceptItem> qtconcept(new QtPvdbDisplayConceptItem(node->GetConcept()));
  QtPvdbNodeItem * const qtnode = new QtPvdbNodeItem(node,qtconcept);

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
    m_examples->setVisible(false);
    this->scene()->addItem(m_examples);
  }
}

std::unique_ptr<QtPvdbConceptMapWidget> QtPvdbConceptMapDisplayWidget::CreateNewDerived() const
{
  std::unique_ptr<QtPvdbConceptMapWidget> p(new This_t);
  return p;
}

void QtPvdbConceptMapDisplayWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  m_examples->SetBuddyItem(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  scene()->update();
}
