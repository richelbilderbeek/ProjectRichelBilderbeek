#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtdisplayconceptmap.h"

#include <boost/lambda/lambda.hpp>

#include "conceptmapcenternode.h"
#include "conceptmapedge.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapexamplesitem.h"
#include "conceptmaphelper.h"
#include "conceptmapedge.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapedgefactory.h"
#include "conceptmap.h"
#include "conceptmapnodefactory.h"
#include "conceptmapfactory.h"
#include "qtconceptmapcenternode.h"
#include "qtconceptmapnode.h"
#include "qtconceptmapdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

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

ribi::cmap::QtDisplayConceptMap::QtDisplayConceptMap(
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map,
  QWidget* parent)
  : QtConceptMap(concept_map,parent)
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


void ribi::cmap::QtDisplayConceptMap::AddEdge(
  const boost::shared_ptr<ribi::cmap::Edge> edge)
{
  assert(edge);
  const boost::shared_ptr<QtDisplayStrategy> qtconcept(new QtDisplayStrategy(edge->GetConcept()));
  assert(qtconcept);
  QtNode * const from = FindQtNode(edge->GetFrom().get());
  assert(from);
  QtNode * const to   = FindQtNode(edge->GetTo().get());
  assert(to);
  assert(from != to);
  QtEdge * const qtedge = new QtEdge(
    edge,
    qtconcept,
    from,
    to
  );
  assert(qtedge);

  //Edges connected to the center node do not show their concepts
  if (IsQtCenterNode(from) || IsQtCenterNode(to))
  {
    qtedge->GetDisplayStrategy()->setVisible(false);
  }

  //Add the EdgeConcepts to the scene
  qtedge->m_signal_item_has_updated.connect(
    boost::bind(
      &QtConceptMap::OnItemRequestsUpdate,
      this,boost::lambda::_1)); //Do not forget the placeholder!
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));
  assert(this->scene());


  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  assert(std::count(
    this->GetConceptMap()->GetEdges().begin(),
    this->GetConceptMap()->GetEdges().end(),
    edge) == 1 && "Assume edge is already in the concept map");
  //this->GetConceptMap()->AddEdge(edge);

  #ifndef NDEBUG
  if(qtedge->pos().x() != edge->GetX())
  {
    TRACE(qtedge->pos().x());
    TRACE(edge->GetX());
  }
  assert(qtedge->pos().x() == edge->GetX());
  if(qtedge->pos().y() != edge->GetY())
  {
    TRACE(qtedge->pos().y());
    TRACE(edge->GetY());
  }
  assert(qtedge->pos().y() == edge->GetY());
  #endif
}

ribi::cmap::QtNode * ribi::cmap::QtDisplayConceptMap::AddNode(const boost::shared_ptr<ribi::cmap::Node> node)
{
  assert(node);
  assert(node->GetConcept());
  //const boost::shared_ptr<QtDisplayStrategy> display_strategy(new QtDisplayStrategy(node->GetConcept()));
  //assert(display_strategy);
  //QtNode * const qtnode = new QtNode(node,display_strategy);
  QtNode * const qtnode {
    IsCenterNode(node)
    ? new QtCenterNode(boost::dynamic_pointer_cast<CenterNode>(node))
    : new QtNode(node,GetDisplayStrategy(node->GetConcept()))
  };
  assert(qtnode);
  assert(IsCenterNode(qtnode->GetNode()) == IsQtCenterNode(qtnode)
    && "Should be equivalent");

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));

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
  //assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size());

  return qtnode;
}

void ribi::cmap::QtDisplayConceptMap::CleanMe()
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
    QtExamplesItem * const item = new QtExamplesItem;
    assert(item);
    SetExamplesItem(item);
    assert(GetExamplesItem());
    GetExamplesItem()->setVisible(false);
    assert(!GetExamplesItem()->scene());
    this->scene()->addItem(GetExamplesItem());
  }
}

#ifndef NDEBUG
std::unique_ptr<ribi::cmap::QtConceptMap> ribi::cmap::QtDisplayConceptMap::CreateNewDerived() const
{
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtConceptMap> p(new QtDisplayConceptMap(concept_map));
  assert(p);
  return p;
}
#endif

#ifndef NDEBUG
void ribi::cmap::QtDisplayConceptMap::DoRandomStuff()
{
  assert(this->GetConceptMap());
  const int n_edges_before = boost::numeric_cast<int>(GetConceptMap()->GetEdges().size());
  const int n_nodes_before = boost::numeric_cast<int>(GetConceptMap()->GetNodes().size());
  assert(!"Do something here");
  const auto node_from = cmap::NodeFactory::GetTests().at(0);
  const auto node_to   = cmap::NodeFactory::GetTests().at(1);
  assert(node_from != node_to);
  this->AddNode(node_from);
  this->AddNode(node_to  );
  const int index = 0;
  assert(index < static_cast<int>(ConceptFactory::GetTests().size()));
  const auto edge_concept = ribi::cmap::ConceptFactory::GetTests().at(index);
  const double node_x = 12.34; //Just some coordinat
  const double node_y = 45.67; //Just some coordinat
  const boost::shared_ptr<ribi::cmap::Edge> edge = cmap::EdgeFactory::Create(
    edge_concept,node_x,node_y,node_from,true,node_to,true);
  this->AddEdge(edge);
  const int n_edges_after = boost::numeric_cast<int>(GetConceptMap()->GetEdges().size());
  const int n_nodes_after = boost::numeric_cast<int>(GetConceptMap()->GetNodes().size());
  assert(n_edges_after > n_edges_before);
  assert(n_nodes_after > n_nodes_before);
}
#endif

const boost::shared_ptr<ribi::cmap::QtItemDisplayStrategy> ribi::cmap::QtDisplayConceptMap::GetDisplayStrategy(
  const boost::shared_ptr<ribi::cmap::Concept> concept) const noexcept
{
  assert(concept);
  const boost::shared_ptr<QtItemDisplayStrategy> display_strategy {
    new QtDisplayStrategy(concept)
  };
  assert(display_strategy);
  return display_strategy;
}

void ribi::cmap::QtDisplayConceptMap::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  assert(GetExamplesItem());
  assert(item);
  assert(dynamic_cast<const QtConceptMapElement*>(item));
  if (GetExamplesItem()->GetBuddyItem() != item)
  {
    GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapElement*>(item));
    assert(this->scene());
    scene()->update();
  }
}
