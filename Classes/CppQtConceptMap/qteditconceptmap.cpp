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
#include "qteditconceptmap.h"

#include <boost/lambda/lambda.hpp>

#include <QGraphicsItem>
#include <QKeyEvent>

#include "conceptmapcenternode.h"
#include "conceptmapconceptfactory.h"
#include "conceptmapconcept.h"
#include "conceptmapfactory.h"
#include "conceptmap.h"
#include "conceptmapedgefactory.h"
#include "conceptmapedge.h"
#include "conceptmapexample.h"
#include "conceptmapexamples.h"
#include "conceptmaphelper.h"
#include "conceptmapnodefactory.h"
#include "conceptmapnode.h"
#include "qtconceptmapcenternode.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapelement.h"
#include "qtconceptmapqtedge.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmapitemhighlighter.h"
#include "qtconceptmapnewarrow.h"
#include "qtconceptmapqtnode.h"
#include "qtconceptmaptoolsitem.h"
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

ribi::cmap::QtEditConceptMap::QtEditConceptMap(
  const Mode mode,
  QWidget* parent
)
  : QtConceptMap(parent),
    m_signal_conceptmapitem_requests_edit{},
    m_arrow(nullptr),
    m_highlighter(mode == Mode::classic ? new QtItemHighlighter(0) : nullptr),
    m_mode(mode),
    m_tools(m_mode == Mode::classic ? new QtTool : nullptr)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(scene());
}

ribi::cmap::QtEditConceptMap::~QtEditConceptMap() noexcept
{
  if (m_mode == Mode::classic)
  {
    m_tools = nullptr;
    assert(m_highlighter);
    m_highlighter->SetItem(nullptr); //Do this before destroying items
    m_arrow = nullptr;
  }
}

ribi::cmap::QtEdge * ribi::cmap::QtEditConceptMap::AddEdge(
  const boost::shared_ptr<Edge> edge)
{
  assert(edge);
  //Be helpful here
  if (!FindQtNode(edge->GetFrom().get())) { AddNode(edge->GetFrom()); }
  if (!FindQtNode(edge->GetTo().get()  )) { AddNode(edge->GetTo()  ); }
  {
    const auto edges = GetConceptMap()->GetEdges();
    const int cnt{std::count(std::begin(edges),std::end(edges),edge)};
    if (cnt == 0) { GetConceptMap()->AddEdge(edge); }
  }

  QtNode * const qtfrom = FindQtNode(edge->GetFrom().get());
  assert(qtfrom);
  QtNode * const qtto   = FindQtNode(edge->GetTo().get());
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
      &ribi::cmap::QtEditConceptMap::OnEdgeKeyDownPressed,
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

ribi::cmap::QtEdge * ribi::cmap::QtEditConceptMap::AddEdge(QtNode * const qt_from, QtNode* const qt_to)
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
      &ribi::cmap::QtEditConceptMap::OnEdgeKeyDownPressed,
      this,
      boost::lambda::_1,boost::lambda::_2 //Do not forget the placeholders!
    )
  );


  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  this->GetConceptMap()->AddEdge(edge);

  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");

  this->scene()->update();

  return qtedge;
}

ribi::cmap::QtNode * ribi::cmap::QtEditConceptMap::AddNode(const boost::shared_ptr<Node> node)
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
      &ribi::cmap::QtEditConceptMap::OnNodeKeyDownPressed,
      this, boost::lambda::_1, boost::lambda::_2)
  ); //Do not forget these placeholders!


  assert(!qtnode->scene());
  this->scene()->addItem(qtnode); //Adding qtnode to scene() twice gives a warning
  qtnode->setSelected(true);
  return qtnode;
}

void ribi::cmap::QtEditConceptMap::CleanMe()
{
  //Prepare cleaning the scene
  assert(GetExamplesItem());
  SetExamplesItem(nullptr);
  if (m_mode == Mode::classic)
  {
    assert(m_tools);
    this->m_tools = nullptr;
    assert(!m_tools);
    assert(m_highlighter || m_mode != Mode::classic);
    m_highlighter->SetItem(nullptr); //Do this before destroying items
    //assert(m_arrow); //Not necessarily true: m_arrow is null when not active
    this->m_arrow = nullptr;
  }

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
        &ribi::cmap::QtEditConceptMap::OnRequestSceneUpdate,this));
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
        &ribi::cmap::QtEditConceptMap::OnToolsClicked,
        this));
    assert(!m_tools->scene());
    this->scene()->addItem(m_tools);
  }
}

#ifndef NDEBUG
std::unique_ptr<ribi::cmap::QtConceptMap> ribi::cmap::QtEditConceptMap::CreateNewDerived() const
{
  const boost::shared_ptr<ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory().DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtConceptMap> p(new This_t(this->m_mode));
  p->SetConceptMap(concept_map);
  return p;
}
#endif


#ifdef BELIEF_THIS_IS_A_GOOD_MEMBER_FUNCTION_20130629_723648723687
void ribi::cmap::QtEditConceptMap::DeleteLeftovers()
{
  //assert(m_edge_concepts.size() == m_arrows.size());
  bool done = true;
  while (1)
  {
    done = true;
    //Delete edges without to/from nodes
    {
      const std::vector<QtEdge*> qtedge = Collect<QtEdge>(scene());
      for (int i = 0; i!=static_cast<int>(qtedge.size()); ++i)
      {
        assert(i >= 0 && i < static_cast<int>(qtedge.size()));
        //An edge can be deleted if its 'to' or 'from' is absent
        QtEdge * const edge = qtedge[i];
        assert(edge->GetFrom());
        assert(edge->GetTo());
        assert(edge->GetFrom() != edge->GetTo());
        const std::vector<QtNode*> qtnodes = Collect<QtNode>(scene());
        if (std::count_if(qtnodes.begin(),qtnodes.end(),
          [edge](const QtNode * node)
          {
            return edge->GetArrow()->GetToItem() == node || edge->GetArrow()->GetFromItem() == node;
          }
        ) < 2)
        {
          assert(scene()->items().contains(edge));
          DeleteEdge(edge);
          done = false;
        }
      }
    }
    if (done) break;
  }

  assert(Collect<QtNode>(this->scene()) == this->GetQtNodes());
  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}
#endif

#ifndef NDEBUG
void ribi::cmap::QtEditConceptMap::DoRandomStuff()
{
  //this->mouseDoubleClickEvent(0); //CAUSES ACCESS VIOLATION

  const boost::shared_ptr<Concept> concept1(ConceptFactory().Create("...", { {} } ) );
  const boost::shared_ptr<Node> node1(NodeFactory().Create(concept1));
  this->GetConceptMap()->AddNode(node1);
  QtNode * const qtnode1 = AddNode(node1);

  const boost::shared_ptr<Concept> concept2(ConceptFactory().Create("...", { {} } ) );
  const boost::shared_ptr<Node> node2(NodeFactory().Create(concept2));
  this->GetConceptMap()->AddNode(node2);
  QtNode * const qtnode2 = AddNode(node2);

  assert(qtnode1->GetNode() != qtnode2->GetNode());
}
#endif


std::vector<ribi::cmap::QtNode *> ribi::cmap::QtEditConceptMap::GetQtNodes()
{
  const std::vector<QtNode *> qtnodes = Collect<QtNode>(this->scene());
  return qtnodes;
}

void ribi::cmap::QtEditConceptMap::keyPressEvent(QKeyEvent* event) noexcept
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
      if (m_mode == Mode::classic)
      {
        //Only remove the 'new arrow' if present
        //Otherwise let the ESC be handled by the class this one derives from
        if (m_arrow)
        {
          this->scene()->removeItem(m_arrow);
          m_arrow = nullptr;
        }
      }
    }
    break;
  }
  QtConceptMap::keyPressEvent(event);
}

void ribi::cmap::QtEditConceptMap::mouseDoubleClickEvent(QMouseEvent *event)
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

  {
    //TODO: Move this to a test
    const int n_nodes_in_scene{static_cast<int>(Collect<QtNode>(this->scene()).size())};
    const int n_nodes_in_conceptmap{static_cast<int>(this->GetConceptMap()->GetNodes().size())};
    if (n_nodes_in_scene != n_nodes_in_conceptmap)
    {
      std::stringstream msg;
      msg << "Warning: #nodes in scene (" << n_nodes_in_scene
        << ") does not match #nodes in concept map (" << n_nodes_in_conceptmap << ")";
      TRACE(msg.str());
    }
  }
}

void ribi::cmap::QtEditConceptMap::mouseMoveEvent(QMouseEvent * event)
{
  if (m_mode == Mode::classic)
  {

    if (m_arrow)
    {
      const QPointF pos = mapToScene(event->pos());
      m_arrow->SetHeadPos(pos.x(),pos.y());

      //Move the item under the arrow
      QtNode* const item_below = GetItemBelowCursor(mapToScene(event->pos()));

      m_highlighter->SetItem(item_below); //item_below is allowed to be nullptr
    }
    else
    {
      m_highlighter->SetItem(nullptr); //item_below is allowed to be nullptr
    }
  }
  QtConceptMap::mouseMoveEvent(event);
}

void ribi::cmap::QtEditConceptMap::mousePressEvent(QMouseEvent *event)
{
  if (m_mode == Mode::classic)
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
  }

  QtConceptMap::mousePressEvent(event);

  //If nothing is selected, hide the Examples
  if (!GetScene()->focusItem() && !this->GetScene()->selectedItems().count())
  {
    //Let any node (in this case the central node) emit an update for the Examples
    //to hide.
    this->GetCenterNode()->m_signal_node_changed(GetCenterNode());
  }
}

void ribi::cmap::QtEditConceptMap::OnEdgeKeyDownPressed(QtEdge* const edge, const int key)
{
  assert(edge);
  if (!edge) throw std::logic_error("ribi::cmap::QtEditConceptMap::OnEdgeKeyDownPressed: edge must be non-nullptr");
  if (key != Qt::Key_F2) return;
}

void ribi::cmap::QtEditConceptMap::OnNodeKeyDownPressed(QtNode* const item, const int key)
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

void ribi::cmap::QtEditConceptMap::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  if (m_mode == Mode::classic)
  {
    m_tools->SetBuddyItem(dynamic_cast<const QtNode*>(item));
  }
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapElement*>(item));
  scene()->update();
}

void ribi::cmap::QtEditConceptMap::OnToolsClicked()
{
  if (m_mode == Mode::classic)
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
}
