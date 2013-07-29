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
#include "pvdbedge.h"
#include "pvdbconceptfactory.h"
#include "pvdbedgefactory.h"
#include "pvdbconceptmap.h"
#include "pvdbnodefactory.h"
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
  assert( (concept_map || !concept_map)
    && "Also an empty concept map can be displayed");
  #endif
  if (concept_map) BuildQtConceptMap();

  //assert(m_tools->scene() && "m_tools is added at CleanMe at BuildQtConceptMap");
  //scene()->addItem(m_tools); //Give m_tools a parent
}


void QtPvdbConceptMapDisplayWidget::AddEdge(
  const boost::shared_ptr<pvdb::Edge> edge)
{
  assert(edge);
  const boost::shared_ptr<QtPvdbConceptItem> concept(new QtPvdbDisplayConceptItem(edge->GetConcept()));
  assert(concept);
  QtPvdbNodeItem * const from = FindQtNode(edge->GetFrom());
  assert(from);
  QtPvdbNodeItem * const to   = FindQtNode(edge->GetTo());
  assert(to);
  assert(from != to);
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


  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  assert(std::count(
    this->GetConceptMap()->GetEdges().begin(),
    this->GetConceptMap()->GetEdges().end(),
    edge) == 1 && "Assume edge is already in the concept map");
  //this->GetConceptMap()->AddEdge(edge);

  assert(qtedge->pos().x() == edge->GetX());
  assert(qtedge->pos().y() == edge->GetY());
}

QtPvdbNodeItem * QtPvdbConceptMapDisplayWidget::AddNode(const boost::shared_ptr<pvdb::Node> node)
{
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

  assert(!qtnode->scene());
  this->scene()->addItem(qtnode);

  assert(std::count(
    GetConceptMap()->GetNodes().begin(),
    GetConceptMap()->GetNodes().end(),
    node) == 1 && "Assume Node is already in the concept map");
  //this->GetConceptMap()->AddNode(node);

  assert(qtnode->pos().x() == node->GetX());
  assert(qtnode->pos().y() == node->GetY());

  //Cannot test this: during construction, the nodes will be put in one-by-one
  //assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size());

  return qtnode;
}

void QtPvdbConceptMapDisplayWidget::CleanMe()
{
  //Prepare clearing the scene
  assert(GetExamplesItem());
  SetExamplesItem(nullptr);
  assert(!GetExamplesItem());

  //Clear the scene, invalidates all scene items copies
  assert(this->scene());
  this->scene()->clear();

  //Put stuff back in
  //Add the invisible examples item
  {
    assert(!GetExamplesItem());
    QtPvdbExamplesItem * const item = new QtPvdbExamplesItem;
    assert(item);
    SetExamplesItem(item);
    assert(GetExamplesItem());
    GetExamplesItem()->setVisible(false);
    assert(!GetExamplesItem()->scene());
    this->scene()->addItem(GetExamplesItem());
  }
}

#ifndef NDEBUG
std::unique_ptr<QtPvdbConceptMapWidget> QtPvdbConceptMapDisplayWidget::CreateNewDerived() const
{
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtPvdbConceptMapWidget> p(new QtPvdbConceptMapDisplayWidget(concept_map));
  assert(p);
  return p;
}
#endif

#ifndef NDEBUG
void QtPvdbConceptMapDisplayWidget::DoRandomStuff()
{
  assert(this->GetConceptMap());
  const int n_edges_before = boost::numeric_cast<int>(GetConceptMap()->GetEdges().size());
  const int n_nodes_before = boost::numeric_cast<int>(GetConceptMap()->GetNodes().size());
  assert(!"Do something here");
  const auto node_from = pvdb::NodeFactory::GetTests().at(0);
  const auto node_to   = pvdb::NodeFactory::GetTests().at(1);
  assert(node_from != node_to);
  this->AddNode(node_from);
  this->AddNode(node_to  );
  const auto edge_concept = pvdb::ConceptFactory::GetTests().at(0);
  const double node_x = 12.34; //Just some coordinat
  const double node_y = 45.67; //Just some coordinat
  const boost::shared_ptr<pvdb::Edge> edge = pvdb::EdgeFactory::Create(
    edge_concept,node_x,node_y,node_from,true,node_to,true);
  this->AddEdge(edge);
  const int n_edges_after = boost::numeric_cast<int>(GetConceptMap()->GetEdges().size());
  const int n_nodes_after = boost::numeric_cast<int>(GetConceptMap()->GetNodes().size());
  assert(n_edges_after > n_edges_before);
  assert(n_nodes_after > n_nodes_before);
}
#endif

void QtPvdbConceptMapDisplayWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  assert(GetExamplesItem());
  assert(item);
  assert(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  if (GetExamplesItem()->GetBuddyItem() != item)
  {
    GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtPvdbConceptMapItem*>(item));
    assert(this->scene());
    scene()->update();
  }
}
