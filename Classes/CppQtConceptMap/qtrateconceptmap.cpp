//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtrateconceptmap.h"

#include <boost/lambda/lambda.hpp>

#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexamples.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapcenternode.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmapnode.h"
#include "qtconceptmaprateconceptdialognewname.h"
#include "qtconceptmaprateexamplesdialognewname.h"
#include "qtconceptmapratestrategy.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"
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

ribi::cmap::QtRateConceptMap::QtRateConceptMap(
  const boost::shared_ptr<ConceptMap> concept_map,
  QWidget* parent)
  : QtConceptMap(concept_map,parent),
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

ribi::cmap::QtEdge * ribi::cmap::QtRateConceptMap::AddEdge(
  const boost::shared_ptr<Edge> edge)
{
  const boost::shared_ptr<QtEditStrategy> qtconcept(new QtEditStrategy(edge->GetConcept()));
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

  //Approaches should be equivalent
  #ifndef NDEBUG
  if(IsCenterNode(from->GetNode()) != IsQtCenterNode(from))
  {
    TRACE("ERROR");
    TRACE(IsCenterNode(from->GetNode()));
    TRACE(IsQtCenterNode(from));
  }
  if(IsCenterNode(to->GetNode()) != IsQtCenterNode(to))
  {
    TRACE("ERROR");
    TRACE(IsCenterNode(to->GetNode()));
    TRACE(IsQtCenterNode(to));
  }
  assert(IsCenterNode(from->GetNode()) == IsQtCenterNode(from));
  assert(IsCenterNode(to->GetNode()) == IsQtCenterNode(to));
  #endif
  if (IsQtCenterNode(from) || IsQtCenterNode(to))
  {
    assert(qtconcept == qtedge->GetDisplayStrategy());
    qtconcept->setVisible(false);
  }


  //General
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));

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
  return qtedge;
}

ribi::cmap::QtNode * ribi::cmap::QtRateConceptMap::AddNode(const boost::shared_ptr<Node> node)
{
  //const boost::shared_ptr<QtRateStrategy> display_strategy(new QtRateStrategy(node->GetConcept()));
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

  //Specific: inform an Observer that the Node requests its Concept being rated
  qtnode->m_signal_node_requests_rate_concept.connect(
    boost::bind(
      &ribi::cmap::QtRateConceptMap::OnNodeRequestsRateConcept,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  //Specific: inform an Observer that the Node requests its Examples being rated
  qtnode->m_signal_node_requests_rate_examples.connect(
    boost::bind(
      &ribi::cmap::QtRateConceptMap::OnNodeRequestsRateExamples,
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
  //assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size());

  return qtnode;
}

void ribi::cmap::QtRateConceptMap::CleanMe()
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
    QtExamplesItem * const item = new QtExamplesItem;
    SetExamplesItem(item);
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &ribi::cmap::QtRateConceptMap::OnRequestSceneUpdate,this));
    item->setVisible(false);
    assert(!item->scene());
    this->scene()->addItem(item);
  }

}

#ifndef NDEBUG
std::unique_ptr<ribi::cmap::QtConceptMap> ribi::cmap::QtRateConceptMap::CreateNewDerived() const
{
  const boost::shared_ptr<ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtConceptMap> p(new This_t(concept_map));
  return p;
}
#endif

const boost::shared_ptr<ribi::cmap::ConceptMap> ribi::cmap::QtRateConceptMap::CreateSubConceptMap(QtNode * const item)
{
  assert(item);
  //Collect all nodes first
  const std::vector<QtEdge*> qtedges = FindEdges(item);
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
    QtEdge* const qtedge = qtedges[i];
    assert(qtedge);
    assert(qtedge->GetFrom());
    assert(qtedge->GetTo());
    assert(qtedge->GetArrow());
    assert(qtedge->GetArrow()->GetFromItem());
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetFromItem()));
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetFromItem())->GetNode());
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetFromItem())->GetNode()->GetConcept());
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetToItem()));
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetToItem())->GetNode());
    assert(dynamic_cast<const QtNode*>(qtedge->GetArrow()->GetToItem())->GetNode()->GetConcept());
    const boost::shared_ptr<ribi::cmap::Node> other_node
      = qtedge->GetFrom()->GetNode() == focal_node
      ? qtedge->GetTo()->GetNode()
      : qtedge->GetFrom()->GetNode();
    assert(other_node);
    assert(other_node != focal_node);
    nodes.push_back(other_node);
    assert(qtedge);
    assert(qtedge->GetEdge());
    const boost::shared_ptr<Edge> edge(EdgeFactory().Create(
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
  assert(ConceptMap::CanConstruct(nodes,edges));
  const boost::shared_ptr<ConceptMap> concept_map(cmap::ConceptMapFactory::Create(nodes,edges));
  assert(concept_map);
  assert(focal_node == concept_map->GetFocalNode());

  assert(concept_map->GetFocalNode());
  assert(concept_map->GetFocalNode()->GetConcept());
  assert(concept_map->GetFocalNode()->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  return concept_map;
}

#ifndef NDEBUG
void ribi::cmap::QtRateConceptMap::DoRandomStuff()
{
  assert(!"TODO");
}
#endif

const boost::shared_ptr<ribi::cmap::QtItemDisplayStrategy> ribi::cmap::QtRateConceptMap::GetDisplayStrategy(
  const boost::shared_ptr<Concept> concept) const noexcept
{
  assert(concept);
  const boost::shared_ptr<QtItemDisplayStrategy> display_strategy {
    new QtRateStrategy(concept)
  };
  assert(display_strategy);
  return display_strategy;
}

void ribi::cmap::QtRateConceptMap::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  //Allow a QtConceptMapWidget to have no QtExamplesItem
  //This allows to omit showing these in the PDF versions used for printing (#205)
  if (!GetExamplesItem()) return;

  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapElement*>(item));
  scene()->update();
}

void ribi::cmap::QtRateConceptMap::OnNodeRequestsRateConcept(QtNode * const item)
{
  assert(item);
  assert(item->GetNode()->GetConcept());
  //Concept map must be edited, so item changes with it
  const boost::shared_ptr<ribi::cmap::ConceptMap> sub_concept_map = CreateSubConceptMap(item);
  assert(sub_concept_map);
  assert(sub_concept_map->GetFocalNode());
  assert(sub_concept_map->GetFocalNode()->GetConcept());
  assert(sub_concept_map->GetFocalNode()->GetConcept().get() == item->GetNode()->GetConcept().get()
    && "Should not be a deep copy, otherwise item will not be changed");

  m_signal_request_rate_concept_dialog(sub_concept_map);


  //PUT RATING HERE
  //item->GetNode()->GetConcept()->GetExamples().
  TRACE("CALCULATE RATING HERE");

  //QtRateStrategyDialog d(sub_concept_map); //Item may be changed
  //d.exec();
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}

void ribi::cmap::QtRateConceptMap::OnNodeRequestsRateExamples(QtNode * const item)
{
  assert(item);
  if (item->GetConcept()->GetExamples()->Get().empty())
  {
    return;
  }
  //Start edit
  {
    QtScopedDisable<QtRateConceptMap> disable(this);
    const boost::shared_ptr<Concept> concept = item->GetConcept();
    assert(concept);
    assert(item->GetConcept().get() == concept.get());
    assert(item->GetConcept() == concept);

    QtRateExamplesDialogNewName d(concept); //FYI: Might change the concept (as suggested by the ctor prototype)
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
