//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2015 The Brainweaver Team

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
#include "qtconceptmap.h"

#include <set>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QGraphicsScene>
#include <QKeyEvent>

#include "fuzzy_equal_to.h"
#include "qtconceptmapcollect.h"
#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtarrowitem.h"
#include "qtconceptmapdisplaystrategy.h"
#include "qtconceptmapbrushfactory.h"
#include "qtconceptmapcenternode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapelement.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmapitemhighlighter.h"
#include "qtconceptmapnewarrow.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmaptoolsitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"
#include "trace.h"
#include "xml.h"
#pragma GCC diagnostic pop

/*

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

*/

///Returns a sorted vector
template <class T>
const std::vector<T> Sort(const std::vector<T>& v)
{
  std::vector<T> w(v);
  std::sort(w.begin(),w.end());
  return w;
}

template <>
const std::vector<ribi::cmap::QtNode*>
  Sort(
    const std::vector<ribi::cmap::QtNode*>& v)
{
  typedef std::vector<ribi::cmap::QtNode*>::iterator Iterator;
  std::vector<ribi::cmap::QtNode*> w(v);
  std::sort(w.begin(),w.end());
  const Iterator i = std::find_if(w.begin(),w.end(),
    [](const ribi::cmap::QtNode* const node)
    {
      return dynamic_cast<const ribi::cmap::QtCenterNode*>(node);
    }
  );
  if (i != w.end())
  {
    std::swap(*i,*w.begin());
    assert(dynamic_cast<const ribi::cmap::QtCenterNode*>(*w.begin()));
  }
  return w;
}

ribi::cmap::QtConceptMap::QtConceptMap(QWidget* parent)
  : QtKeyboardFriendlyGraphicsView(parent),
    m_signal_conceptmapitem_requests_edit{},
    m_arrow(nullptr),
    m_concept_map{},
    m_examples_item(new QtExamplesItem),
    m_highlighter{new QtItemHighlighter},
    m_tools{new QtTool}
{
  #ifndef NDEBUG
  Test();
  #endif

  this->setScene(new QGraphicsScene(this));

  assert(!m_examples_item->scene());
  scene()->addItem(m_examples_item); //Add the examples so it has a parent

  assert(Collect<QtNode>(scene()).empty());

  //Without this line, mouseMoveEvent won't be called
  this->setMouseTracking(true);

  {
    //QLinearGradient linearGradient(-500,-500,500,500);
    //linearGradient.setColorAt(0.0,QColor(214,214,214));
    //linearGradient.setColorAt(1.0,QColor(255,255,255));
    assert(this->scene());
    //this->scene()->setBackgroundBrush(linearGradient);
    this->scene()->setBackgroundBrush(QBrush(QColor(255,255,255)));
  }
}

ribi::cmap::QtConceptMap::~QtConceptMap()
{
  //for (auto qtnode: Collect<QtNode>(scene()))
  {
    //signal #1
    //qtnode->m_signal_request_scene_update.disconnect(
    //  boost::bind(&ribi::cmap::QtConceptMap::OnRequestSceneUpdate,this)
    //);
    //signal #2
    //qtnode->m_signal_item_has_updated.disconnect(
    //  boost::bind(&ribi::cmap::QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1)
    //);
  }

  delete m_examples_item;
  m_examples_item = nullptr;

  m_tools = nullptr;
  if (m_highlighter) m_highlighter->SetItem(nullptr); //Do this before destroying items
  m_arrow = nullptr;

}

ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::AddEdge(
  const boost::shared_ptr<Edge> edge)
{
  assert(edge);
  //Be helpful here
  if (!GetQtNode(edge->GetFrom().get())) { AddNode(edge->GetFrom()); }
  if (!GetQtNode(edge->GetTo().get()  )) { AddNode(edge->GetTo()  ); }
  {
    const auto edges = GetConceptMap()->GetEdges();
    const int cnt{std::count(std::begin(edges),std::end(edges),edge)};
    if (cnt == 0) { GetConceptMap()->AddEdge(edge); }
  }

  QtNode * const qtfrom = GetQtNode(edge->GetFrom().get());
  assert(qtfrom);
  QtNode * const qtto   = GetQtNode(edge->GetTo().get());
  assert(qtto);
  assert(qtfrom != qtto);
  QtEdge * const qtedge = new QtEdge(
    edge,
    qtfrom,
    qtto
  );

  //Edges connected to the center node do not show their concepts
  if (IsQtCenterNode(qtfrom) || IsQtCenterNode(qtto))
  {
    //assert(qtconcept == qtedge->GetDisplayStrategy());
    //qtconcept->setVisible(false);
  }

  //General: inform an Observer that this item has changed
  //Signal #6
  qtedge->m_signal_edge_changed.connect(
    boost::bind(
      &QtConceptMap::OnItemRequestsUpdate,
      this,
      boost::lambda::_1
    )
  );

  //Focus
  qtedge->m_signal_focus_in_event.connect(
    boost::bind(
      &QtConceptMap::OnItemRequestsUpdate,
      this,
      boost::lambda::_1
    )
  );

  //Signal #7
  //General: inform an Observer that a QGraphicsScene needs to be updated
  //qtedge->m_signal_request_scene_update.connect(
  //  boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));

  //Signal #8
  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_key_down_pressed.connect(
    boost::bind(
      &ribi::cmap::QtConceptMap::OnEdgeKeyDownPressed,
      this,
      boost::lambda::_1, //Do not forget the placeholder!
      boost::lambda::_2  //Do not forget the placeholder!
    )
  );

  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  qtfrom->setSelected(false);
  qtto->setSelected(false);
  qtedge->setSelected(true);
  assert(qtedge->isSelected());

  return qtedge;
}

ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::AddEdge(QtNode * const qt_from, QtNode* const qt_to)
{
  assert(qt_from);
  assert(qt_to);
  assert(qt_from != qt_to);
  assert(qt_from->GetNode() != qt_to->GetNode());
  assert(!dynamic_cast<const QtTool*>(qt_to  ) && "Cannot select a ToolsItem");
  assert(!dynamic_cast<const QtTool*>(qt_from) && "Cannot select a ToolsItem");
  //Does this edge already exists? If yes, modify it
  {
    const std::vector<QtEdge*> edges = Collect<QtEdge>(scene());
    const auto iter = std::find_if(edges.begin(),edges.end(),
      [qt_from,qt_to](const QtEdge* const other_edge)
      {
        return
            (other_edge->GetArrow()->GetFromItem() == qt_from && other_edge->GetArrow()->GetToItem() == qt_to  )
         || (other_edge->GetArrow()->GetFromItem() == qt_to   && other_edge->GetArrow()->GetToItem() == qt_from);
      }
    );
    if (iter != edges.end())
    {
      QtEdge * const qtedge = *iter;
      assert(qtedge);
      assert(qtedge->GetEdge()->GetFrom() != qtedge->GetEdge()->GetTo());
      assert(qtedge->GetArrow()->GetFromItem() != qtedge->GetArrow()->GetToItem());
      if (qtedge->GetArrow()->GetToItem()   == qt_to && !qtedge->GetArrow()->HasHead()) { qtedge->SetHasHeadArrow(true); }
      if (qtedge->GetArrow()->GetFromItem() == qt_to && !qtedge->GetArrow()->HasTail()) { qtedge->SetHasTailArrow(true); }
      this->scene()->update();
      return qtedge;
    }
  }

  //Edge does not exist yet, create a new one
  const std::vector<QtNode*> qtnodes = Collect<QtNode>(scene());
  const boost::shared_ptr<Concept> concept(ConceptFactory().Create());
  assert(concept);
  const bool head_arrow = true;
  const bool tail_arrow = false;
  const boost::shared_ptr<Node> from = qt_from->GetNode();
  assert(from);
  const boost::shared_ptr<Node> to = qt_to->GetNode();
  assert(to);
  assert(from != to);
  const boost::shared_ptr<Edge> edge(
    EdgeFactory().Create(
      NodeFactory().Create(
        concept,
        (qt_from->GetCenterPos().x() + qt_to->GetCenterPos().x()) / 2.0,
        (qt_from->GetCenterPos().y() + qt_to->GetCenterPos().y()) / 2.0
      ),
      from,
      tail_arrow,
      to,
      head_arrow
    )
  );

  //Step 1: Create an Edge concept
  //const boost::shared_ptr<QtEditStrategy> qtconcept(new QtEditStrategy(edge->GetNode()->GetConcept()));
  //assert(qtconcept);

  QtEdge * const qtedge = new QtEdge(edge,qt_from,qt_to);

  //Edges connected to the center node do not show their concepts
  if (IsQtCenterNode(qt_from) || IsQtCenterNode(qt_to))
  {
    //assert(qtconcept == qtedge->GetDisplayStrategy());
    //qtconcept->setVisible(false); //ISSUE_
  }

  //Signal #9
  //General: inform an Observer that this item has changed
  qtedge->m_signal_edge_changed.connect(
    boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1)
  );

  //Signal #10
  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_edge_changed.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this)
  );

  //Focus
  qtedge->m_signal_focus_in_event.connect(
    boost::bind(
      &QtConceptMap::OnItemRequestsUpdate,
      this,
      boost::lambda::_1
    )
  );

  //Signal #11
  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_key_down_pressed.connect(
    boost::bind(
      &ribi::cmap::QtConceptMap::OnEdgeKeyDownPressed,
      this,
      boost::lambda::_1,boost::lambda::_2 //Do not forget the placeholders!
    )
  );


  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);
  this->GetConceptMap()->AddEdge(edge);
  this->scene()->update();

  return qtedge;
}

ribi::cmap::QtNode * ribi::cmap::QtConceptMap::AddNode(const boost::shared_ptr<Node> node)
{
  assert(node);

  //Add Node to ConceptMap if this has not been done yet
  {
    assert(GetConceptMap());
    const auto nodes = GetConceptMap()->GetNodes();
    const int cnt{std::count(std::begin(nodes),std::end(nodes),node)};
    assert(cnt == 0 || cnt == 1);
    if (cnt == 0)
    {
      this->GetConceptMap()->AddNode(node);
    }
  }

  QtNode * const qtnode = new QtNode(node);
  assert(qtnode);
  assert(qtnode->GetCenterX() == node->GetX());
  assert(qtnode->GetCenterY() == node->GetY());
  assert(IsCenterNode(qtnode->GetNode()) == IsQtCenterNode(qtnode)
    && "Should be equivalent");

  //Signal #1
  //General: inform an Observer that this item has changed
  qtnode->m_signal_node_changed.connect(
    boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1))
  ;
  //qtnode->m_signal_item_has_updated.connect(
  // boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1));

  //Signal #2
  //General: inform an Observer that a QGraphicsScene needs to be updated

  qtnode->m_signal_focus_in_event.connect(
    boost::bind(&QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1))
  ;

  qtnode->m_signal_focus_pen_changed.connect(
    boost::bind(&QtConceptMap::OnRequestSceneUpdate,this)
  );
  //qtnode->m_signal_request_scene_update.connect(
  //  boost::bind(&QtConceptMap::OnRequestSceneUpdate,this));

  //Signal #3
  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtnode->m_signal_key_down_pressed.connect(
    boost::bind(
      &ribi::cmap::QtConceptMap::OnNodeKeyDownPressed,
      this, boost::lambda::_1, boost::lambda::_2)
  ); //Do not forget these placeholders!


  assert(!qtnode->scene());
  this->scene()->addItem(qtnode); //Adding qtnode to scene() twice gives a warning
  qtnode->setSelected(true);
  return qtnode;
}

void ribi::cmap::QtConceptMap::CleanMe()
{
  //Prepare cleaning the scene
  assert(GetExamplesItem());
  SetExamplesItem(nullptr);

  assert(m_tools);
  this->m_tools = nullptr;
  assert(!m_tools);
  if (m_highlighter) m_highlighter->SetItem(nullptr); //Do this before destroying items

  this->m_arrow = nullptr;

  assert(!m_tools);

  //Clear the scene, invalidates all scene items copies
  assert(this->scene());
  this->scene()->clear();

  //Put stuff back in
  assert(!m_tools);

  //Add the invisible examples item
  {
    assert(!GetExamplesItem());
    QtExamplesItem * const item = new QtExamplesItem;
    assert(item);
    assert(!m_tools);
    SetExamplesItem(item);
    assert(!m_tools);
    //Signal #4
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &ribi::cmap::QtConceptMap::OnRequestSceneUpdate,this));
    item->setVisible(false);
    assert(!item->scene());
    this->scene()->addItem(item);
  }

  //Add the tools item
  {
    assert(!m_tools);
    m_tools = new QtTool;
    //Signal #5
    m_tools->m_signal_clicked.connect(
      boost::bind(
        &ribi::cmap::QtConceptMap::OnToolsClicked,
        this));
    assert(!m_tools->scene());
    this->scene()->addItem(m_tools);
  }
}

void ribi::cmap::QtConceptMap::DeleteEdge(QtEdge * const qtedge)
{
  #ifndef NDEBUG
  const int n_items_before = this->scene()->items().count();
  #endif

  assert(scene()->items().contains(qtedge));
  //Remove non-GUI edges
  GetConceptMap()->DeleteEdge(qtedge->GetEdge());
  //Remove GUI edge
  this->scene()->removeItem(qtedge);
  //No left-overs when deleting an edge
  //DeleteLeftovers();

  #ifndef NDEBUG
  const int n_items_after = this->scene()->items().count();
  assert(n_items_after + 1 == n_items_before);
  //Cannot do the check below: in DeleteNode multiple edges are deleted
  //assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
  //  && "GUI and non-GUI concept map must match");
  #endif
}

void ribi::cmap::QtConceptMap::DeleteNode(const QtNode * const qtnode)
{
  //Delete the edges connected to this node
  {
    const std::vector<QtEdge *> qtedges = GetQtEdges();
    const std::size_t sz = qtedges.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      QtEdge * const qtedge = qtedges[i];
      assert(qtedge);
      if (*qtedge->GetFrom() == *qtnode || *qtedge->GetTo() == *qtnode)
      {
        DeleteEdge(qtedge);
      }
    }
  }

  //Remove node from model
  GetConceptMap()->DeleteNode(qtnode->GetNode());
  //Remove node from view
  this->scene()->removeItem(const_cast<QtNode*>(qtnode));
}

const ribi::cmap::QtNode * ribi::cmap::QtConceptMap::GetCenterNode() const noexcept
{

  assert(scene());
  assert(!scene()->items().isEmpty());
  assert(scene()->items()[0]);
  QList<QGraphicsItem *> v = scene()->items();
  assert(std::count_if(v.begin(),v.end(),
    [this](const QGraphicsItem * const item) { return this->IsQtCenterNode(item); }
    ) < 2 && "There is at most one center node (zero for most sub-concept maps, one for a complete concept map");
  const auto iter = std::find_if(v.begin(),v.end(),
    [this](const QGraphicsItem * const item) { return this->IsQtCenterNode(item); } );
  assert(iter != v.end());
  const QtNode * const center_node = dynamic_cast<QtNode*>(*iter);
  assert(center_node);
  assert(IsQtCenterNode(center_node));
  return center_node;
}

ribi::cmap::QtNode * ribi::cmap::QtConceptMap::GetCenterNode() noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  QtNode * const qtnode(
    const_cast<QtNode *>(
      dynamic_cast<const QtConceptMap*>(this)->GetCenterNode()
    )
  );
  return qtnode;
}

const ribi::cmap::QtExamplesItem * ribi::cmap::QtConceptMap::GetExamplesItem() const
{
  assert(m_examples_item || !m_examples_item);
  return m_examples_item;
}

ribi::cmap::QtExamplesItem * ribi::cmap::QtConceptMap::GetExamplesItem()
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  return const_cast<QtExamplesItem*>(
    const_cast<const QtConceptMap*>(this)->GetExamplesItem());
}

ribi::cmap::QtNode* ribi::cmap::QtConceptMap::GetItemBelowCursor(const QPointF& pos) const
{
  #if (QT_VERSION >= QT_VERSION_CHECK(5,0,0))
  const QList<QGraphicsItem*> v = this->scene()->items(pos.x(),pos.y(),2.0,2.0,Qt::IntersectsItemShape,Qt::AscendingOrder);
  #else
  const QList<QGraphicsItem*> v = this->scene()->items(pos.x(),pos.y(),2.0,2.0);
  #endif
  std::vector<QtNode*> qtnodes;
  std::for_each(v.begin(),v.end(),
    [&qtnodes](QGraphicsItem* const item)
    {
      if (QtNode * const qtnode = dynamic_cast<QtNode*>(item))
      {
        assert(!dynamic_cast<QtTool*>(item) && "Cannot draw arrow to ToolsItem");
        qtnodes.push_back(qtnode);
      }
    }
  );
  if (!qtnodes.empty())
  {
    return qtnodes[0];
  }
  return nullptr;
}

const ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::GetQtEdgeConst(
  const boost::shared_ptr<const Edge> edge) const noexcept
{
  const auto v(GetQtEdges());
  for (const auto e:v)
  {
    if (e->GetEdge() == edge) return e;
  }
  return nullptr;
}

ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::GetQtEdge(
  const boost::shared_ptr<Edge> edge) noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  QtEdge * const qtedge(
    const_cast<QtEdge *>(
      dynamic_cast<const QtConceptMap*>(this)->GetQtEdgeConst(edge)
    )
  );
  return qtedge;
}

ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::GetQtEdge(
  const QtEdge* const edge) noexcept
{
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  QtEdge * const qtedge(
    const_cast<QtEdge *>(
      dynamic_cast<const QtConceptMap*>(this)->GetQtEdgeConst(edge)
    )
  );
  return qtedge;
}

const ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::GetQtEdgeConst(
  const QtEdge* const edge) const noexcept
{
  //return FindQtEdgeConst(edge->GetFrom().get(),edge->GetTo().get());
  return GetQtEdgeConst(edge->GetFrom(),edge->GetTo());
}

const ribi::cmap::QtEdge * ribi::cmap::QtConceptMap::GetQtEdgeConst(
  const QtNode* const from,
  const QtNode* const to) const noexcept
{

  assert(from);
  assert(to);
  assert(from != to);
  const std::vector<QtEdge*> edge_concepts = Collect<QtEdge>(scene());
  const auto iter = std::find_if(edge_concepts.begin(),edge_concepts.end(),
    [from,to](const QtEdge* const edge)
    {
      return
        (*edge->GetFrom() == *from && *edge->GetTo() == *to)
     || (*edge->GetFrom() == *to && *edge->GetTo() == *from);
    }
  );
  if (iter == edge_concepts.end()) return nullptr;
  return * iter;
}

std::vector<ribi::cmap::QtEdge*> ribi::cmap::QtConceptMap::GetQtEdges(
  const QtNode* const from) const noexcept
{
  assert(from);
  const std::vector<QtEdge*> v = Collect<QtEdge>(scene());
  std::vector<QtEdge*> w;
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [from](const QtEdge* const edge)
    {
      return *edge->GetFrom() == *from || *edge->GetTo() == *from;
    }
  );
  return w;
}

std::vector<const ribi::cmap::QtEdge *> ribi::cmap::QtConceptMap::GetQtEdges() const
{
  return Collect<const QtEdge>(this->scene());
}

std::vector<ribi::cmap::QtEdge *> ribi::cmap::QtConceptMap::GetQtEdges()
{
  return Collect<QtEdge>(this->scene());
}


/*
ribi::cmap::QtNode * ribi::cmap::QtConceptMap::GetQtNode(Node * const node) noexcept
{
  return const_cast<QtNode *>(GetQtNodeConst(node));
}


*/

ribi::cmap::QtNode * ribi::cmap::QtConceptMap::GetQtNode(
  ribi::cmap::Node * const node) noexcept
{
  assert(node);
  //Calls the const version of this member function
  //To avoid duplication in const and non-const member functions [1]
  //[1] Scott Meyers. Effective C++ (3rd edition). ISBN: 0-321-33487-6.
  //    Item 3, paragraph 'Avoid duplication in const and non-const member functions'
  QtNode * const qtnode(
    const_cast<QtNode *>(
      dynamic_cast<const QtConceptMap*>(this)->GetQtNodeConst(node)
    )
  );
  return qtnode;
}

const ribi::cmap::QtNode * ribi::cmap::QtConceptMap::GetQtNodeConst(
  const ribi::cmap::Node * const node) const noexcept
{
  assert(node);
  const std::vector<QtNode *> qtnodes = Collect<QtNode>(scene());
  for (QtNode * qtnode: qtnodes)
  {
    if (qtnode->GetNode().get() == node) return qtnode;
  }
  return nullptr;
}

std::vector<const ribi::cmap::QtNode *> ribi::cmap::QtConceptMap::GetQtNodes() const
{
  return Collect<const QtNode>(this->scene());
}

std::vector<ribi::cmap::QtNode *> ribi::cmap::QtConceptMap::GetQtNodes()
{
  return Collect<QtNode>(this->scene());
}


QGraphicsScene* ribi::cmap::QtConceptMap::GetScene() const noexcept
{

  return scene();
}

std::string ribi::cmap::QtConceptMap::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::cmap::QtConceptMap::GetVersionHistory() noexcept
{
  return {
    "2012-xx-xx: version 1.0: initial version"
    "2013-12-03: version 1.1: start of versioning"
    "2015-08-12: version 2.0: merge with QtConceptMap"
  };
}


bool ribi::cmap::QtConceptMap::IsQtCenterNode(const QGraphicsItem* const item)
{
  const QtCenterNode * const qtnode = dynamic_cast<const QtCenterNode*>(item);
  assert(!qtnode || IsCenterNode(qtnode->GetNode()));
  return qtnode;
}

void ribi::cmap::QtConceptMap::keyPressEvent(QKeyEvent *event) noexcept
{
  switch (event->key())
  {
    case Qt::Key_Delete:
      {
        QList<QGraphicsItem *> v = this->scene()->selectedItems();
        if (std::count(v.begin(),v.end(),scene()->focusItem()) == 0)
        {
          v.push_back(scene()->focusItem());
        }
        std::for_each(v.begin(),v.end(),
          [this](QGraphicsItem* const item)
          {
            //Delete a Node Concept
            if (QtNode * const qtnode = dynamic_cast<QtNode *>(item))
            {
              if (!IsQtCenterNode(qtnode)) //Cannot delete center node
              {
                const std::vector<QtNode*> node_concepts = Collect<QtNode>(scene());
                assert(std::count(node_concepts.begin(),node_concepts.end(),qtnode) == 1);
                DeleteNode(qtnode);
              }
            }
            //Delete an Edge Concept
            if (QtEdge* const edge = dynamic_cast<QtEdge*>(item))
            {
              const std::vector<QtEdge*> edge_concepts = Collect<QtEdge>(scene());
              assert(std::count(edge_concepts.begin(),edge_concepts.end(),edge) == 1);
              assert(scene()->items().contains(edge));
              DeleteEdge(edge);
            }
          }
        );
        if (!v.empty())
        {
          //DeleteLeftovers();
          GetExamplesItem()->hide();
          this->OnItemRequestsUpdate(0);
        }
        this->scene()->update();
      }
      break;
    case Qt::Key_Escape:
    {
      //Only remove the 'new arrow' if present
      //Otherwise let the ESC be handled by the class this one derives from
      if (m_arrow)
      {
        this->scene()->removeItem(m_arrow);
        m_arrow = nullptr;
      }
    }
    break;
    case Qt::Key_Equal:
      this->scale(1.1,1.1);
      break;
    case Qt::Key_Minus:
      this->scale(0.9,0.9);
      break;
  }

  QtKeyboardFriendlyGraphicsView::keyPressEvent(event);
  scene()->update();
}

bool ribi::cmap::QtConceptMap::MustReposition(const std::vector<boost::shared_ptr<const cmap::Node> >& nodes) const
{
  //If all are at the origin, the nodes must be (re)positioned
  return std::count_if(nodes.begin(),nodes.end(),
    [](const boost::shared_ptr<const cmap::Node>& node)
    {
      return node->GetX() == 0.0 && node->GetY() == 0.0;
    }
  ) == static_cast<int>(nodes.size());
}

void ribi::cmap::QtConceptMap::OnItemRequestsUpdate(const QGraphicsItem* const item)
{
  OnItemRequestUpdateImpl(item);
}

void ribi::cmap::QtConceptMap::OnRequestSceneUpdate()
{
  scene()->update();
}


void ribi::cmap::QtConceptMap::RepositionItems()
{

  {
    //The ray of the upcoming circle of nodes, is the larger of
    //(1) half of the diagonal of the focal question (e.g. for short concepts)
    //(2) calculated from the circumference by adding the nodes' length
    const std::vector<QtNode *> qtnode_concepts_unsorted = Collect<QtNode>(scene());

    if (qtnode_concepts_unsorted.empty()) return;

    const std::vector<QtNode *> qtnode_concepts = Sort(qtnode_concepts_unsorted);
    assert(!qtnode_concepts.empty());
    assert(!qtnode_concepts.empty());
    assert(qtnode_concepts[0]);
    const QtNode * const qtcenter_node
      = dynamic_cast<const QtNode *>(qtnode_concepts[0]);
    assert(qtcenter_node);
    //assert(qtcenter_node->GetOuterRect(). GetOuterX() > -0.5);
    //assert(qtcenter_node->GetOuterX() <  0.5);
    //assert(qtcenter_node->GetOuterY() > -0.5);
    //assert(qtcenter_node->GetOuterY() <  0.5);

    const double r1
      = 0.5 * ribi::cmap::GetDistance(
        qtcenter_node->boundingRect().width(),
        qtcenter_node->boundingRect().height());
    const double r3 = 50.0;
    const double r = std::max(r1,r3);
    assert(r > 10.0);
    const int n_nodes = qtnode_concepts.size();
    for (int i = 1; i!=n_nodes; ++i) //+1 to skip center node
    {
      //Added +0 (instead of -1) to n_nodes, to prevent, in a setup with two concepts and
      //one edge, the edge to overlap the central question
      const double pi = boost::math::constants::pi<double>();
      const double angle
        = 2.0 * pi * boost::numeric_cast<double>(i)
        / boost::numeric_cast<double>(n_nodes - 1);
      const double x =  std::cos(angle) * r;
      const double y = -std::sin(angle) * r;
      QtNode * const qtnode = qtnode_concepts[i];
      qtnode->GetNode()->SetPos(x,y);
      //qtnode->setPos(x,y);
      #ifndef NDEBUG
      //const double epsilon = 0.000001;
      #endif
      //assert(std::abs(x - qtnode->GetOuterX()) < epsilon);
      //assert(std::abs(x - qtnode->GetNode()->GetX()) < epsilon);
      //assert(std::abs(y - qtnode->GetOuterY()) < epsilon);
      //assert(std::abs(y - qtnode->GetNode()->GetY()) < epsilon);

    }
  }

  #define NOT_NOW_20141111
  #ifdef NOT_NOW_20141111
  {
    //Put the edge concepts in the middle of the nodes
    const std::vector<QtEdge *> qtedge_concepts = Collect<QtEdge>(scene());
    std::for_each(qtedge_concepts.begin(), qtedge_concepts.end(),
      [](QtEdge * const qtedge)
      {
        const QPointF p((qtedge->GetFrom()->GetCenterPos() + qtedge->GetTo()->GetCenterPos()) / 2.0);
        const double new_x = p.x();
        const double new_y = p.y();
        qtedge->GetEdge()->GetNode()->SetX(new_x);
        qtedge->GetEdge()->GetNode()->SetY(new_y);
      }
    );
  }
  #endif // NOT_NOW_20141111

  //Put the nodes around the focal question in their improved position
  //If there is no focal node, the non-focal nodes are put around an empty spot
  for (int i=0; i!=10; ++i) //TODO: replace by while (1)
  {
    bool done = true;
    const std::vector<QtNode *> qtnodes = Sort(Collect<QtNode>(scene()));
    assert(!qtnodes.empty());
    assert(qtnodes[0]);
    //assert(IsCenterNode(qtnodes[0]));
    const std::vector<QtEdge* > qtedges = Collect<QtEdge>(scene());

    //First node
    //const bool is_first_node_center_node {
    //  boost::dynamic_pointer_cast<QtCenterNode>(qtnodes[0])
    //};
    const QtNode * const first_node { qtnodes[0] };
    assert(first_node);

    std::vector<QGraphicsItem*> nodes_and_edges;
    std::copy(qtnodes.begin(),qtnodes.end(),std::back_inserter(nodes_and_edges));
    std::copy(qtedges.begin(),qtedges.end(),std::back_inserter(nodes_and_edges));

    //Move the nodes away from the center
    std::for_each(
      nodes_and_edges.begin() + 1, //+1 to skip the center node at [0]
      nodes_and_edges.end(),
      [first_node,&done](QGraphicsItem* const node_or_edge)
      {
        if (first_node->boundingRect().intersects(
          node_or_edge->boundingRect().translated(-node_or_edge->pos())))
        {
          const double cur_x = node_or_edge->x();
          const double cur_y = node_or_edge->y();
          const double new_x = cur_x + (node_or_edge->x() < first_node->x() ? -1.0 : 1.0);
          const double new_y = cur_y + (node_or_edge->y() < first_node->y() ? -1.0 : 1.0);
          if (QtNode * const qtnode = dynamic_cast<QtNode *>(node_or_edge))
          {
            qtnode->GetNode()->SetX(new_x);
            qtnode->GetNode()->SetY(new_y);
          }
          else
          {
            QtEdge * const qtedge = dynamic_cast<QtEdge *>(node_or_edge);
            assert(qtedge && "Every item is either a Qt node or Qt edge");
            qtedge->GetEdge()->GetNode()->SetX(new_x);
            qtedge->GetEdge()->GetNode()->SetY(new_y);
            //node->setPos(QPointF(new_x,new_y));
          }
          done = false;
        }
      }
    );

    if (done) break;
  }
}

void ribi::cmap::QtConceptMap::SetConceptMap(const boost::shared_ptr<ConceptMap> concept_map)
{
  CleanMe();
  m_concept_map = concept_map;
  if (!m_concept_map) return;

  assert(m_concept_map);
  assert(m_concept_map->IsValid());
  assert(this->scene());

  //This std::vector keeps the QtNodes in the same order as the nodes in the concept map
  //You cannot rely on Collect<QtConceptMapNodeConcept*>(scene), as this shuffles the order
  std::vector<QtNode*> qtnodes;

  assert(Collect<QtNode>(scene()).empty());

  //Add the nodes to the scene, if there are any
  if (!m_concept_map->GetNodes().empty())
  {
    //Add the main question as the first node
    const boost::shared_ptr<Node> node = m_concept_map->GetFocalNode();

    QtNode * qtnode = nullptr;
    if (IsCenterNode(node))
    {
      const boost::shared_ptr<CenterNode> centernode
        = boost::dynamic_pointer_cast<CenterNode>(node);
      qtnode = new QtCenterNode(centernode);
    }
    else
    {
      qtnode = new QtNode(node);
    }
    assert(qtnode);
    //Let the center node respond to mouse clicks
    //signal #1
    //qtnode->m_signal_request_scene_update.connect(
    //  boost::bind(&ribi::cmap::QtConceptMap::OnRequestSceneUpdate,this)
    //);
    //signal #2
    //qtnode->m_signal_item_has_updated.connect(
    //  boost::bind(&ribi::cmap::QtConceptMap::OnItemRequestsUpdate,this,boost::lambda::_1)
    //);
    //Add the center node to scene
    assert(!qtnode->scene());
    this->scene()->addItem(qtnode);
    qtnodes.push_back(qtnode);
    assert(Collect<QtNode>(scene()).size() == 1);

    //Add the regular nodes to the scene
    const std::vector<boost::shared_ptr<Node>> nodes = m_concept_map->GetNodes();
    const std::size_t n_nodes = nodes.size();
    assert(n_nodes >= 1);
    for (std::size_t i=1; i!=n_nodes; ++i) //+1 to skip focal node
    {
      assert(Collect<QtNode>(scene()).size() == i && "Node not yet added to scene");
      assert(i < nodes.size());
      boost::shared_ptr<Node> node = nodes[i];
      assert(node);
      assert( (IsCenterNode(node) || !IsCenterNode(node))
        && "focal node != center node");
      QtNode * const qtnode = AddNode(node); //NEVER CALL VIRTUAL FUNCTIONS IN BASE CLASS CONSTRUCTORS!
      qtnodes.push_back(qtnode);
      assert(Collect<QtNode>(scene()).size() == i + 1 && "Node is added to scene");
    }
  }
  //Add the Concepts on the Edges
  {
    const std::vector<boost::shared_ptr<ribi::cmap::Edge> > edges = m_concept_map->GetEdges();
    std::for_each(edges.begin(),edges.end(),
      [this,qtnodes](const boost::shared_ptr<Edge> edge)
      {
        assert(edge->GetFrom());
        assert(edge->GetTo());
        assert(edge->GetFrom() != edge->GetTo());
        this->AddEdge(edge); //NEVER CALL VIRTUAL FUNCTIONS IN BASE CLASS CONSTRUCTORS!
      }
    );
  }

  //Put the nodes around the focal question in an initial position
  if (MustReposition(AddConst(m_concept_map->GetNodes())))
  {
    RepositionItems();
  }

  #ifndef NDEBUG
  TestMe(m_concept_map);
  #endif

  assert(GetConceptMap() == concept_map);
  assert( (!concept_map || concept_map->IsValid())
    && "Expect no or a valid concept map");

}

void ribi::cmap::QtConceptMap::SetExamplesItem(QtExamplesItem * const item)
{
  assert((item || !item) && "Can be both");
  m_examples_item = item;
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMap::Shuffle() noexcept
{
  const std::vector<QtNode*> nodes = Collect<QtNode>(scene());
  std::for_each(nodes.begin(),nodes.end(),
    [this](QtNode* qtnode)
    {
      if (!IsQtCenterNode(qtnode))
      {
        #ifdef NOT_NOW_20141111
        double x = qtnode->GetCenterX();
        double y = qtnode->GetCenterY();
        const int i = (std::rand() >> 4) % 4;
        switch(i)
        {
          case 0: x+= 1.0; break;
          case 1: y+= 1.0; break;
          case 2: x+=-1.0; break;
          case 3: y+=-1.0; break;
          default: assert(!"Should not get here");
        }
        assert(QPointF(x,y) != qtnode->GetCenterPos());
        qtnode->GetNode()->SetPos(x,y);
        #endif // NOT_NOW_20141111
      }
    }
  );
  scene()->update();
}
#endif

#ifndef NDEBUG
void ribi::cmap::QtConceptMap::TestMe(const boost::shared_ptr<const ribi::cmap::ConceptMap> map) const
{
  {
    std::set<const cmap::Node*> w;
    const std::vector<boost::shared_ptr<const cmap::Node> > v = map->GetNodes();
    std::transform(v.begin(),v.end(),std::inserter(w,w.begin()),
      [](const boost::shared_ptr<const cmap::Node>  ptr)
      {
        return ptr.get();
      }
    );
    assert(v.size() == w.size() && "All nodes must be unique");
  }
  {
    std::set<const cmap::Edge*> w;
    const std::vector<boost::shared_ptr<const cmap::Edge> > v = map->GetEdges();
    std::transform(v.begin(),v.end(),std::inserter(w,w.begin()),
      [](const boost::shared_ptr<const cmap::Edge>  ptr)
      {
        return ptr.get();
      }
    );
    assert(v.size() == w.size() && "All edges must be unique");
  }
  {
    std::set<QGraphicsItem*> v;
    const std::vector<QtNode*> node_concepts = Collect<QtNode>(scene());
    std::copy(node_concepts.begin(),node_concepts.end(),std::inserter(v,v.begin()));
    const std::vector<QtEdge*> edge_concepts = Collect<QtEdge>(scene());
    std::copy(edge_concepts.begin(),edge_concepts.end(),std::inserter(v,v.begin()));
    assert(v.size() == (node_concepts.size() + edge_concepts.size()) && "All Qt nodes must be unique");
  }
  {
    ///Note that the ConceptMap read out again differs from the original,
    ///because the Nodes are placed
    if (!cmap::ConceptMap::HasSameContent(*GetConceptMap(),*map))
    {
      //OH OH, AN ERROR! HELP ME OUT AND GIMME LOTS OF DEBUG INFO!
      {
        const std::vector<std::string> v
          = xml::XmlToPretty(cmap::ConceptMap::ToXml(map));
        std::clog << "original map:\n";
        std::clog << "\n";
        std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::clog,"\n"));
        std::clog << "\n";
      }
      {
        const std::vector<std::string> v
          = xml::XmlToPretty(cmap::ConceptMap::ToXml(GetConceptMap()));
        std::clog << "GetConceptMap():\n";
        std::clog << "\n";
        std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(std::clog,"\n"));
        std::clog << "\n";
      }

      TRACE(cmap::ConceptMap::ToXml(GetConceptMap()));
      TRACE(cmap::ConceptMap::ToXml(map));
    }
  }
  assert(cmap::ConceptMap::HasSameContent(*GetConceptMap(),*map)
    && "The concept map supplied must be homomorphous to the one created in the widget");

}
#endif










void ribi::cmap::QtConceptMap::mouseDoubleClickEvent(QMouseEvent *event)
{
  const boost::shared_ptr<Concept> concept(
    ribi::cmap::ConceptFactory().Create("..."));
  const boost::shared_ptr<Node> node(NodeFactory().Create(concept));
  assert(node);
  assert(GetConceptMap());
  GetConceptMap()->AddNode(node);

  QtNode * const qtnode = AddNode(node); //AddNode creates, connects and adds the node to scene

  assert(qtnode);
  const QPointF new_point = mapToScene(event->pos());
  qtnode->GetNode()->SetPos(new_point.x(),new_point.y());
}

void ribi::cmap::QtConceptMap::mouseMoveEvent(QMouseEvent * event)
{

  if (m_arrow)
  {
    const QPointF pos = mapToScene(event->pos());
    m_arrow->SetHeadPos(pos.x(),pos.y());

    //Move the item under the arrow
    QtNode* const item_below = GetItemBelowCursor(mapToScene(event->pos()));

    assert(m_highlighter);
    m_highlighter->SetItem(item_below); //item_below is allowed to be nullptr
  }
  else
  {
    assert(m_highlighter);
    m_highlighter->SetItem(nullptr); //item_below is allowed to be nullptr
  }
  QtKeyboardFriendlyGraphicsView::mouseMoveEvent(event);
}

void ribi::cmap::QtConceptMap::mousePressEvent(QMouseEvent *event)
{
  assert(m_highlighter);
  if (m_arrow) //&& m_highlighter->GetItem())
  {
    if (m_highlighter->GetItem() && m_arrow->GetFrom() != m_highlighter->GetItem())
    {
      assert(!dynamic_cast<QtTool*>(m_highlighter->GetItem()) && "Cannot select a ToolsItem");
      AddEdge( m_arrow->GetFrom(),m_highlighter->GetItem());
    }
    this->scene()->removeItem(m_arrow);
    m_arrow = nullptr;
    assert(m_highlighter);
    m_highlighter->SetItem(nullptr);
  }

  QtKeyboardFriendlyGraphicsView::mousePressEvent(event);

  //If nothing is selected, hide the Examples
  if (!GetScene()->focusItem() && !this->GetScene()->selectedItems().count())
  {
    //Let any node (in this case the central node) emit an update for the Examples
    //to hide.
    this->GetCenterNode()->m_signal_node_changed(GetCenterNode());
  }
}

void ribi::cmap::QtConceptMap::OnEdgeKeyDownPressed(QtEdge* const edge, const int key)
{
  assert(edge);
  if (!edge) throw std::logic_error("ribi::cmap::QtConceptMap::OnEdgeKeyDownPressed: edge must be non-nullptr");
  if (key != Qt::Key_F2) return;
}

void ribi::cmap::QtConceptMap::OnNodeKeyDownPressed(QtNode* const item, const int key)
{
  if (key != Qt::Key_F2) return;
  //assert(item->GetConcept());
  //const boost::shared_ptr<Concept> new_concept = ConceptFactory().DeepCopy(item->GetConcept());
  //assert(new_concept);

  assert(this);
  assert(item);
  //TRACE("Try edit from EditWidget");
  //m_signal_conceptmapitem_requests_edit(item);

  #ifdef NOT_NOW_20141111
  {
    QtScopedDisable<QtConceptMap> disable(this);
    QtConceptMapConceptEditDialog d(item->GetNode()->GetConcept());
    d.exec();
  }
  #endif // NOT_NOW_20141111
  this->show();
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  item->m_signal_node_changed(item);
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}

void ribi::cmap::QtConceptMap::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  m_tools->SetBuddyItem(dynamic_cast<const QtNode*>(item));
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapElement*>(item));
  scene()->update();
}

void ribi::cmap::QtConceptMap::OnToolsClicked()
{
  const QPointF cursor_pos_approx(
    m_tools->GetBuddyItem()->GetCenterX(),
    m_tools->GetBuddyItem()->GetCenterY() - 32.0
    - m_tools->GetBuddyItem()->GetRadiusY()
    //TODO_COEN ISSUE_101 the QGraphicsItem needs to emit that it is clicked,
    //with itself as the argument, so that the QtTool knows the height the of the square to be above
  );
  m_arrow = new QtNewArrow(
    m_tools->GetBuddyItem(),cursor_pos_approx
  );
  assert(!m_arrow->scene());
  this->scene()->addItem(m_arrow);
  m_arrow->update();
  this->scene()->update();
}
