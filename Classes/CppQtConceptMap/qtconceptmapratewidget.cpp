#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapratewidget.h"

#include <boost/lambda/lambda.hpp>

#include "conceptmapconceptfactory.h"
#include "conceptmap.h"
#include "conceptmapedge.h"
#include "conceptmaphelper.h"
#include "conceptmapconcept.h"
#include "conceptmapexamples.h"
#include "qtconceptmapdisplayconceptitem.h"
#include "qtconceptmapnodeitem.h"
#include "conceptmapedgefactory.h"
#include "conceptmapfactory.h"
#include "conceptmapnode.h"
#include "conceptmapnodefactory.h"
#include "qtconceptmapcenternodeitem.h"
#include "qtconceptmapedgeitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtconceptmaprateexamplesdialog.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmaprateconceptitem.h"
#include "qtscopeddisable.h"
#include "qtconceptmaprateconceptdialog.h"
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
      return dynamic_cast<T*>(item);
    }
  );
  v.erase(std::remove(v.begin(),v.end(),nullptr),v.end());
  assert(std::count(v.begin(),v.end(),nullptr)==0);
  return v;
}

ribi::cmap::QtConceptMapRateWidget::QtConceptMapRateWidget(
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map,
  QWidget* parent)
  : QtConceptMapWidget(concept_map,parent),
    m_signal_request_rate_concept_dialog{}
{
  #ifndef NDEBUG
  Test();

  assert( (concept_map || !concept_map )
    && "Only an existing concept map can be rated,"
       "an empty one displays nothing");
  #endif
  if (concept_map) BuildQtConceptMap();

  //assert(m_tools->scene() && "m_tools is added at CleanMe at BuildQtConceptMap");
  //scene()->addItem(m_tools); //Give m_tools a parent
}

void ribi::cmap::QtConceptMapRateWidget::AddEdge(
  const boost::shared_ptr<ribi::cmap::Edge> edge)
{
  const boost::shared_ptr<QtConceptMapEditConceptItem> qtconcept(new QtConceptMapEditConceptItem(edge->GetConcept()));
  assert(qtconcept);
  QtConceptMapNodeItem * const from = FindQtNode(edge->GetFrom());
  assert(from);
  QtConceptMapNodeItem * const to   = FindQtNode(edge->GetTo());
  assert(to);
  assert(from != to);
  QtConceptMapEdgeItem * const qtedge = new QtConceptMapEdgeItem(
    edge,
    qtconcept,
    from,
    to
  );
  assert(qtedge);

  //Edges connected to the center node do not show their concepts
  if (IsCenterNode(from) || IsCenterNode(to))
  {
    assert(qtconcept == qtedge->GetConceptItem());
    qtconcept->setVisible(false);
  }


  //General
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific: disable changing arrow heads
  qtedge->GetArrow()->setEnabled(false);

  //Do not connect m_signal_rate, because Edges will never be rated


  //Add the EdgeConcepts to the scene
  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  assert(std::count(
    this->GetConceptMap()->GetEdges().begin(),
    this->GetConceptMap()->GetEdges().end(),
    edge) == 1 && "Assume edge is already in the concept map");

  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  assert(std::abs(qtedge->pos().x() - edge->GetX()) < epsilon);
  assert(std::abs(qtedge->pos().y() - edge->GetY()) < epsilon);
}

ribi::cmap::QtConceptMapNodeItem * ribi::cmap::QtConceptMapRateWidget::AddNode(const boost::shared_ptr<ribi::cmap::Node> node)
{
  const boost::shared_ptr<QtConceptMapRateConceptItem> qtconcept(new QtConceptMapRateConceptItem(node->GetConcept()));
  assert(qtconcept);
  QtConceptMapNodeItem * const qtnode = new QtConceptMapNodeItem(node,qtconcept);
  assert(qtnode);

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific: inform an Observer that the Node requests its Concept being rated
  qtnode->m_signal_node_requests_rate_concept.connect(
    boost::bind(
      &ribi::cmap::QtConceptMapRateWidget::OnNodeRequestsRateConcept,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  //Specific: inform an Observer that the Node requests its Examples being rated
  qtnode->m_signal_node_requests_rate_examples.connect(
    boost::bind(
      &ribi::cmap::QtConceptMapRateWidget::OnNodeRequestsRateExamples,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  assert(!qtnode->scene());
  this->scene()->addItem(qtnode);

  assert(std::count(
    GetConceptMap()->GetNodes().begin(),
    GetConceptMap()->GetNodes().end(),
    node) == 1 && "Assume Node is already in the concept map");
  //this->GetConceptMap()->AddNode(node);

  assert(qtnode->pos().x() == node->GetX());
  assert(qtnode->pos().y() == node->GetY());

  //Cannot test this: during construction not all nodes are put in
  //assert(Collect<QtConceptMapNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size());

  return qtnode;
}

void ribi::cmap::QtConceptMapRateWidget::CleanMe()
{
  //Prepare cleaning the scene
  assert(GetExamplesItem());
  SetExamplesItem(nullptr);

  //Clear the scene, invalidates all scene items copies
  assert(this->scene());
  this->scene()->clear();

  //Put stuff back in

  //Add the invisible examples item
  {
    assert(!GetExamplesItem());
    QtConceptMapExamplesItem * const item = new QtConceptMapExamplesItem;
    SetExamplesItem(item);
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &ribi::cmap::QtConceptMapRateWidget::OnRequestSceneUpdate,this));
    item->setVisible(false);
    assert(!item->scene());
    this->scene()->addItem(item);
  }

}

#ifndef NDEBUG
std::unique_ptr<ribi::cmap::QtConceptMapWidget> ribi::cmap::QtConceptMapRateWidget::CreateNewDerived() const
{
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtConceptMapWidget> p(new This_t(concept_map));
  return p;
}
#endif

const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::QtConceptMapRateWidget::CreateSubConceptMap(QtConceptMapNodeItem * const item)
{
  assert(item);
  //Collect all nodes first
  const std::vector<QtConceptMapEdgeItem*> qtedges = FindEdges(item);
  std::vector<boost::shared_ptr<ribi::cmap::Node> > nodes;
  //assert(focal_concept);
  const boost::shared_ptr<ribi::cmap::Node> focal_node = item->GetNode(); //FIX?
  assert(focal_node);
  nodes.push_back(focal_node);

  assert(nodes[0]->GetConcept() == item->GetNode()->GetConcept());

  std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges;

  const int sz = static_cast<int>(qtedges.size());
  for (int i=0; i!=sz; ++i)
  {
    QtConceptMapEdgeItem* const qtedge = qtedges[i];
    assert(qtedge);
    assert(qtedge->GetFrom());
    assert(qtedge->GetTo());
    assert(qtedge->GetArrow());
    assert(qtedge->GetArrow()->GetFromItem());
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetFromItem()));
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetFromItem())->GetNode());
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetFromItem())->GetNode()->GetConcept());
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetToItem()));
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetToItem())->GetNode());
    assert(dynamic_cast<const QtConceptMapNodeItem*>(qtedge->GetArrow()->GetToItem())->GetNode()->GetConcept());
    const boost::shared_ptr<ribi::cmap::Node> other_node
      = qtedge->GetFrom()->GetNode() == focal_node
      ? qtedge->GetTo()->GetNode()
      : qtedge->GetFrom()->GetNode();
    assert(other_node);
    assert(other_node != focal_node);
    nodes.push_back(other_node);
    assert(qtedge);
    assert(qtedge->GetEdge());
    const boost::shared_ptr<ribi::cmap::Edge> edge(cmap::EdgeFactory::Create(
      qtedge->GetEdge()->GetConcept(),
      qtedge->GetEdge()->GetX(),
      qtedge->GetEdge()->GetY(),
      focal_node,
      qtedge->GetEdge()->HasTailArrow(),
      other_node,
      qtedge->GetEdge()->HasHeadArrow()
      )
    );
    assert(edge);
    edges.push_back(edge);
  }
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map(cmap::ConceptMapFactory::Create(nodes,edges));
  assert(concept_map);
  assert(focal_node == concept_map->GetNodes().at(0));

  assert(concept_map->GetNodes().at(0));
  assert(concept_map->GetNodes().at(0)->GetConcept());
  assert(concept_map->GetNodes().at(0)->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  return concept_map;
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapRateWidget::DoRandomStuff()
{
  assert(!"TODO");
}
#endif


void ribi::cmap::QtConceptMapRateWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapItem*>(item));
  scene()->update();
}

void ribi::cmap::QtConceptMapRateWidget::OnNodeRequestsRateConcept(QtConceptMapNodeItem * const item)
{
  assert(item);
  assert(item->GetNode()->GetConcept());
  //Concept map must be edited, so item changes with it
  const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map = CreateSubConceptMap(item);
  assert(sub_concept_map);
  assert(sub_concept_map->GetNodes().at(0));
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  m_signal_request_rate_concept_dialog(sub_concept_map);


  //PUT RATING HERE
  //item->GetNode()->GetConcept()->GetExamples().
  TRACE("CALCULATE RATING HERE");

  //QtConceptMapRateConceptDialog d(sub_concept_map); //Item may be changed
  //d.exec();
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}

void ribi::cmap::QtConceptMapRateWidget::OnNodeRequestsRateExamples(QtConceptMapNodeItem * const item)
{
  assert(item);
  if (item->GetConcept()->GetExamples()->Get().empty())
  {
    return;
  }
  //Start edit
  {
    QtScopedDisable<QtConceptMapRateWidget> disable(this);
    const boost::shared_ptr<ribi::cmap::Concept> concept = item->GetConcept();
    assert(concept);
    assert(item->GetConcept().get() == concept.get());
    assert(item->GetConcept() == concept);

    QtConceptMapRateExamplesDialog d(concept); //FYI: Might change the concept (as suggested by the ctor prototype)
    d.exec();

    assert(item->GetConcept().get() == concept.get());
    assert(item->GetConcept() == concept);
  }
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}
