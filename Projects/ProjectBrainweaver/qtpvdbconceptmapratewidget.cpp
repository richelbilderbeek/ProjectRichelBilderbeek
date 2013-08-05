#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapratewidget.h"

#include <boost/lambda/lambda.hpp>

#include "pvdbconceptfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbedge.h"
#include "pvdbhelper.h"
#include "pvdbconcept.h"
#include "pvdbexamples.h"
#include "qtpvdbdisplayconceptitem.h"
#include "qtpvdbnodeitem.h"
#include "pvdbedgefactory.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbnode.h"
#include "pvdbnodefactory.h"
#include "qtpvdbcenternodeitem.h"
#include "qtpvdbedgeitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtpvdbrateexamplesdialog.h"
#include "qtpvdbexamplesitem.h"
#include "qtpvdbrateconceptitem.h"
#include "qtscopeddisable.h"
#include "qtpvdbrateconceptdialog.h"
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

QtPvdbConceptMapRateWidget::QtPvdbConceptMapRateWidget(
  const boost::shared_ptr<pvdb::ConceptMap> concept_map,
  QWidget* parent)
  : QtPvdbConceptMapWidget(concept_map,parent)
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

void QtPvdbConceptMapRateWidget::AddEdge(
  const boost::shared_ptr<pvdb::Edge> edge)
{
  const boost::shared_ptr<QtPvdbEditConceptItem> qtconcept(new QtPvdbEditConceptItem(edge->GetConcept()));
  assert(qtconcept);
  QtPvdbNodeItem * const from = FindQtNode(edge->GetFrom());
  assert(from);
  QtPvdbNodeItem * const to   = FindQtNode(edge->GetTo());
  assert(to);
  assert(from != to);
  QtPvdbEdgeItem * const qtedge = new QtPvdbEdgeItem(
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
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

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

QtPvdbNodeItem * QtPvdbConceptMapRateWidget::AddNode(const boost::shared_ptr<pvdb::Node> node)
{
  const boost::shared_ptr<QtPvdbRateConceptItem> qtconcept(new QtPvdbRateConceptItem(node->GetConcept()));
  assert(qtconcept);
  QtPvdbNodeItem * const qtnode = new QtPvdbNodeItem(node,qtconcept);
  assert(qtnode);

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific: inform an Observer that the Node requests its Concept being rated
  qtnode->m_signal_node_requests_rate_concept.connect(
    boost::bind(
      &QtPvdbConceptMapRateWidget::OnNodeRequestsRateConcept,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  //Specific: inform an Observer that the Node requests its Examples being rated
  qtnode->m_signal_node_requests_rate_examples.connect(
    boost::bind(
      &QtPvdbConceptMapRateWidget::OnNodeRequestsRateExamples,
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
  //assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size());

  return qtnode;
}

void QtPvdbConceptMapRateWidget::CleanMe()
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
    QtPvdbExamplesItem * const item = new QtPvdbExamplesItem;
    SetExamplesItem(item);
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &QtPvdbConceptMapRateWidget::OnRequestSceneUpdate,this));
    item->setVisible(false);
    assert(!item->scene());
    this->scene()->addItem(item);
  }

}

#ifndef NDEBUG
std::unique_ptr<QtPvdbConceptMapWidget> QtPvdbConceptMapRateWidget::CreateNewDerived() const
{
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtPvdbConceptMapWidget> p(new This_t(concept_map));
  return p;
}
#endif

const boost::shared_ptr<pvdb::ConceptMap> QtPvdbConceptMapRateWidget::CreateSubConceptMap(QtPvdbNodeItem * const item)
{
  assert(item);
  //Collect all nodes first
  const std::vector<QtPvdbEdgeItem*> qtedges = FindEdges(item);
  std::vector<boost::shared_ptr<pvdb::Node> > nodes;
  //assert(focal_concept);
  const boost::shared_ptr<pvdb::Node> focal_node = item->GetNode(); //FIX?
  assert(focal_node);
  nodes.push_back(focal_node);

  assert(nodes[0]->GetConcept() == item->GetNode()->GetConcept());

  std::vector<boost::shared_ptr<pvdb::Edge> > edges;

  const int sz = static_cast<int>(qtedges.size());
  for (int i=0; i!=sz; ++i)
  {
    QtPvdbEdgeItem* const qtedge = qtedges[i];
    assert(qtedge);
    assert(qtedge->GetFrom());
    assert(qtedge->GetTo());
    assert(qtedge->GetArrow());
    assert(qtedge->GetArrow()->GetFromItem());
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetFromItem()));
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetFromItem())->GetNode());
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetFromItem())->GetNode()->GetConcept());
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetToItem()));
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetToItem())->GetNode());
    assert(dynamic_cast<const QtPvdbNodeItem*>(qtedge->GetArrow()->GetToItem())->GetNode()->GetConcept());
    const boost::shared_ptr<pvdb::Node> other_node
      = qtedge->GetFrom()->GetNode() == focal_node
      ? qtedge->GetTo()->GetNode()
      : qtedge->GetFrom()->GetNode();
    assert(other_node);
    assert(other_node != focal_node);
    nodes.push_back(other_node);
    assert(qtedge);
    assert(qtedge->GetEdge());
    const boost::shared_ptr<pvdb::Edge> edge(pvdb::EdgeFactory::Create(
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
  const boost::shared_ptr<pvdb::ConceptMap> concept_map(pvdb::ConceptMapFactory::Create(nodes,edges));
  assert(concept_map);
  assert(focal_node == concept_map->GetNodes().at(0));

  assert(concept_map->GetNodes().at(0));
  assert(concept_map->GetNodes().at(0)->GetConcept());
  assert(concept_map->GetNodes().at(0)->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  return concept_map;
}

#ifndef NDEBUG
void QtPvdbConceptMapRateWidget::DoRandomStuff()
{
  assert(!"TODO");
}
#endif


void QtPvdbConceptMapRateWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  scene()->update();
}

void QtPvdbConceptMapRateWidget::OnNodeRequestsRateConcept(QtPvdbNodeItem * const item)
{
  assert(item);
  assert(item->GetNode()->GetConcept());
  //Concept map must be edited, so item changes with it
  const boost::shared_ptr<pvdb::ConceptMap> sub_concept_map = CreateSubConceptMap(item);
  assert(sub_concept_map);
  assert(sub_concept_map->GetNodes().at(0));
  assert(sub_concept_map->GetNodes().at(0)->GetConcept());
  assert(sub_concept_map->GetNodes().at(0)->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  m_signal_request_rate_concept_dialog(sub_concept_map);


  //PUT RATING HERE
  //item->GetNode()->GetConcept()->GetExamples().
  TRACE("CALCULATE RATING HERE");

  //QtPvdbRateConceptDialog d(sub_concept_map); //Item may be changed
  //d.exec();
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}

void QtPvdbConceptMapRateWidget::OnNodeRequestsRateExamples(QtPvdbNodeItem * const item)
{
  assert(item);
  if (item->GetConcept()->GetExamples()->Get().empty())
  {
    return;
  }
  //Start edit
  {
    QtScopedDisable<QtPvdbConceptMapRateWidget> disable(this);
    const boost::shared_ptr<pvdb::Concept> concept = item->GetConcept();
    assert(concept);
    assert(item->GetConcept().get() == concept.get());
    assert(item->GetConcept() == concept);

    QtPvdbRateExamplesDialog d(concept); //FYI: Might change the concept (as suggested by the ctor prototype)
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
