#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtconceptmapeditwidget.h"

#include <boost/lambda/lambda.hpp>

#include <QGraphicsItem>
#include <QKeyEvent>

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
#include "qtconceptmapcenternodeitem.h"
#include "qtconceptmapconcepteditdialog.h"
#include "qtconceptmapitem.h"
#include "qtconceptmapedge.h"
#include "qtconceptmapexamplesitem.h"
#include "qtconceptmapitemhighlighter.h"
#include "qtconceptmapnewarrow.h"
#include "qtconceptmapnode.h"
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

ribi::cmap::QtConceptMapEditWidget::QtConceptMapEditWidget(
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map,
  QWidget* parent)
  : QtConceptMapWidget(concept_map,parent),
    m_signal_conceptmapitem_requests_edit{},
    m_arrow(nullptr),
    m_highlighter(new QtItemHighlighter(0)),
    m_tools(new QtTool)
{
  #ifndef NDEBUG
  Test();
  #endif
  if (!concept_map) return;


  assert(concept_map  && "Only an existing concept map can be edited");
  BuildQtConceptMap();

  assert(scene());

  assert(m_tools->scene() && "m_tools is added at CleanMe at BuildQtConceptMap");
  //scene()->addItem(m_tools); //Give m_tools a parent

  #ifndef NDEBUG
  assert(m_highlighter && "m_highlighter does not need to be reset in ClearMe");
  assert(concept_map->IsValid());
  const auto nodes = concept_map->GetNodes();
  const auto items = Collect<QtNode>(this->scene());
  const std::size_t n_items = items.size();
  const std::size_t n_nodes = nodes.size();
  assert(n_items == n_nodes && "GUI and non-GUI concept map must match");
  #endif
}

ribi::cmap::QtConceptMapEditWidget::~QtConceptMapEditWidget() noexcept
{
  m_tools = nullptr;
  assert(m_highlighter);
  m_highlighter->SetItem(nullptr); //Do this before destroying items
  m_arrow = nullptr;
}

void ribi::cmap::QtConceptMapEditWidget::AddEdge(
  const boost::shared_ptr<ribi::cmap::Edge> edge)
{
  const boost::shared_ptr<QtConceptMapEditConceptItem> qtconcept(new QtConceptMapEditConceptItem(edge->GetConcept()));
  assert(qtconcept);
  QtNode * const from = FindQtNode(edge->GetFrom());
  assert(from);
  QtNode * const to   = FindQtNode(edge->GetTo());
  assert(to);
  assert(from != to);
  QtEdge * const qtedge = new QtEdge(
    edge,
    qtconcept,
    from,
    to
  );

  //Edges connected to the center node do not show their concepts
  if (IsCenterNode(from) || IsCenterNode(to))
  {
    assert(qtconcept == qtedge->GetConceptItem());
    qtconcept->setVisible(false);
  }

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &ribi::cmap::QtConceptMapEditWidget::OnConceptMapItemRequestsEdit,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  assert(std::count(
    this->GetConceptMap()->GetEdges().begin(),
    this->GetConceptMap()->GetEdges().end(),
    edge) == 1 && "Assume edge is already in the concept map");
  //this->GetConceptMap()->AddEdge(edge);

  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
  #ifndef NDEBUG
  const double epsilon = 0.000001;
  #endif
  assert(std::abs(qtedge->pos().x() - edge->GetX()) < epsilon);
  assert(std::abs(qtedge->pos().y() - edge->GetY()) < epsilon);
}

void ribi::cmap::QtConceptMapEditWidget::AddEdge(QtNode * const qt_from, QtNode* const qt_to)
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
      return;
    }
  }

  //Edge does not exist yet, create a new one
  const std::vector<QtNode*> qtnodes = Collect<QtNode>(scene());
  const boost::shared_ptr<ribi::cmap::Concept> concept(cmap::ConceptFactory::Create());
  assert(concept);
  const bool head_arrow = true;
  const bool tail_arrow = false;
  const boost::shared_ptr<ribi::cmap::Node> from = qt_from->GetNode();
  assert(from);
  const boost::shared_ptr<ribi::cmap::Node> to = qt_to->GetNode();
  assert(to);
  assert(from != to);
  const boost::shared_ptr<ribi::cmap::Edge> edge(
    cmap::EdgeFactory::Create(
      concept,
      (qt_from->pos().x() + qt_to->pos().x()) / 2.0,
      (qt_from->pos().y() + qt_to->pos().y()) / 2.0,
      from,
      tail_arrow,
      to,
      head_arrow));

  //Step 1: Create an Edge concept
  const boost::shared_ptr<QtConceptMapEditConceptItem> qtconcept(new QtConceptMapEditConceptItem(edge->GetConcept()));
  assert(qtconcept);

  QtEdge * const qtedge = new QtEdge(edge,qtconcept,qt_from,qt_to);

  //Edges connected to the center node do not show their concepts
  if (IsCenterNode(qt_from) || IsCenterNode(qt_to))
  {
    assert(qtconcept == qtedge->GetConceptItem());
    qtconcept->setVisible(false);
  }

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &ribi::cmap::QtConceptMapEditWidget::OnConceptMapItemRequestsEdit,
      this, boost::lambda::_1)); //Do not forget the placeholder!


  assert(!qtedge->scene());
  this->scene()->addItem(qtedge);

  this->GetConceptMap()->AddEdge(edge);

  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");

  this->scene()->update();
}

ribi::cmap::QtNode * ribi::cmap::QtConceptMapEditWidget::AddNode(const boost::shared_ptr<ribi::cmap::Node> node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<QtConceptMapEditConceptItem> qtconcept(new QtConceptMapEditConceptItem(node->GetConcept()));
  assert(node);
  QtNode * const qtnode = new QtNode(node,qtconcept);

  assert(qtnode->pos().x() == node->GetX());
  assert(qtnode->pos().y() == node->GetY());

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtnode->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &ribi::cmap::QtConceptMapEditWidget::OnConceptMapItemRequestsEdit,
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
  //Cannot check this: during construction the concept map has multiple nodes, that can only be
  //added one by one
  //assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
  //  && "GUI and non-GUI concept map must match");

  return qtnode;
}

void ribi::cmap::QtConceptMapEditWidget::CleanMe()
{
  //Prepare cleaning the scene
  assert(GetExamplesItem());
  SetExamplesItem(nullptr);
  assert(m_tools);
  this->m_tools = nullptr;
  assert(m_highlighter);
  m_highlighter->SetItem(nullptr); //Do this before destroying items
  //assert(m_arrow); //Not necessarily true: m_arrow is null when not active
  this->m_arrow = nullptr;

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
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &ribi::cmap::QtConceptMapEditWidget::OnRequestSceneUpdate,this));
    item->setVisible(false);
    assert(!item->scene());
    this->scene()->addItem(item);
  }

  //Add the tools item
  {
    assert(!m_tools);
    m_tools = new QtTool;
    m_tools->m_signal_clicked.connect(
      boost::bind(
        &ribi::cmap::QtConceptMapEditWidget::OnToolsClicked,
        this));
    assert(!m_tools->scene());
    this->scene()->addItem(m_tools);
  }
}

#ifndef NDEBUG
std::unique_ptr<ribi::cmap::QtConceptMapWidget> ribi::cmap::QtConceptMapEditWidget::CreateNewDerived() const
{
  const boost::shared_ptr<ribi::cmap::ConceptMap> concept_map
    = ribi::cmap::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtConceptMapWidget> p(new This_t(concept_map));
  return p;
}
#endif

void ribi::cmap::QtConceptMapEditWidget::DeleteEdge(QtEdge * const qtedge)
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

#ifdef BELIEF_THIS_IS_A_GOOD_MEMBER_FUNCTION_20130629_723648723687
void ribi::cmap::QtConceptMapEditWidget::DeleteLeftovers()
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

void ribi::cmap::QtConceptMapEditWidget::DeleteNode(QtNode * const qtnode)
{
  #ifndef NDEBUG
  const int n_items_before = this->scene()->items().count();
  #endif

  //Delete the edges connected to this node
  {
    const std::vector<QtEdge *> qtedges = this->GetQtEdges();
    const std::size_t sz = qtedges.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      QtEdge * const qtedge = qtedges[i];
      assert(qtedge);
      if (qtedge->GetFrom() == qtnode || qtedge->GetTo() == qtnode)
      {
        DeleteEdge(qtedge);
      }
    }
  }

  //Remove node from GUI
  this->scene()->removeItem(qtnode);
  //Remove from non-GUI, which removes the left-overs
  GetConceptMap()->DeleteNode(qtnode->GetNode());

  #ifndef NDEBUG
  const int n_items_after = this->scene()->items().count();
  assert(n_items_before - n_items_after >= 1 && "At least one item is deleted: one node and x edges");
  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
  #endif
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapEditWidget::DoRandomStuff()
{
  //this->mouseDoubleClickEvent(0); //CAUSES ACCESS VIOLATION

  const boost::shared_ptr<ribi::cmap::Concept> concept1(cmap::ConceptFactory::Create("...", { {} } ) );
  const boost::shared_ptr<ribi::cmap::Node> node1(cmap::NodeFactory::Create(concept1));
  this->GetConceptMap()->AddNode(node1);
  QtNode * const qtnode1 = AddNode(node1);

  const boost::shared_ptr<ribi::cmap::Concept> concept2(cmap::ConceptFactory::Create("...", { {} } ) );
  const boost::shared_ptr<ribi::cmap::Node> node2(cmap::NodeFactory::Create(concept2));
  this->GetConceptMap()->AddNode(node2);
  QtNode * const qtnode2 = AddNode(node2);

  assert(qtnode1->GetNode() != qtnode2->GetNode());
  this->AddEdge(qtnode1,qtnode2);

  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}
#endif




const std::vector<ribi::cmap::QtEdge *> ribi::cmap::QtConceptMapEditWidget::GetQtEdges()
{
  const std::vector<QtEdge *> qtedges
    = Collect<QtEdge>(this->scene());
  //Cannot do the check below: in DeleteNode multiple edges are deleted
  //assert(qtedges.size() == GetConceptMap()->GetNodes().size()
  //    && "GUI and non-GUI must contain an equal amount of edges");
  return qtedges;
}

const std::vector<ribi::cmap::QtNode *> ribi::cmap::QtConceptMapEditWidget::GetQtNodes()
{
  const std::vector<QtNode *> qtnodes
    = Collect<QtNode>(this->scene());
  if (qtnodes.size() != GetConceptMap()->GetNodes().size())
  {
    TRACE(qtnodes.size());
    TRACE(GetConceptMap()->GetNodes().size());
    TRACE("BREAK");
  }
  assert(qtnodes.size() == GetConceptMap()->GetNodes().size()
      && "GUI and non-GUI must contain an equal amount of nodes");
  return qtnodes;
}

void ribi::cmap::QtConceptMapEditWidget::keyPressEvent(QKeyEvent* event) noexcept
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
            if (QtNode * const node = dynamic_cast<QtNode *>(item))
            {
              if (!IsCenterNode(node)) //Cannot delete center node
              {
                const std::vector<QtNode*> node_concepts = Collect<QtNode>(scene());
                assert(std::count(node_concepts.begin(),node_concepts.end(),node) == 1);
                DeleteNode(node);
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
          //DeleteLeftovers(); //2013-06-29: Really needed?
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
  }
  QtConceptMapWidget::keyPressEvent(event);
}

void ribi::cmap::QtConceptMapEditWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  const boost::shared_ptr<ribi::cmap::Concept> concept(
    ribi::cmap::ConceptFactory::Create("..."));
  const boost::shared_ptr<ribi::cmap::Node> node(cmap::NodeFactory::Create(concept));
  assert(node);
  assert(GetConceptMap());
  GetConceptMap()->AddNode(node);

  QtNode * const qtnode = AddNode(node); //AddNode creates, connects and adds the node to scene

  assert(qtnode);
  const QPointF new_point = mapToScene(event->pos());
  qtnode->SetPos(new_point.x(),new_point.y());

  assert(Collect<QtNode>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}

void ribi::cmap::QtConceptMapEditWidget::mouseMoveEvent(QMouseEvent * event)
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
  QtConceptMapWidget::mouseMoveEvent(event);
}

void ribi::cmap::QtConceptMapEditWidget::mousePressEvent(QMouseEvent *event)
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
    m_highlighter->SetItem(nullptr);
  }

  QtConceptMapWidget::mousePressEvent(event);

  //If nothing is selected, hide the Examples
  if (!GetScene()->focusItem() && !this->GetScene()->selectedItems().count())
  {
    //Let any node (in this case the central node) emit an update for the Examples
    //to hide.
    this->GetCenterNode()->m_signal_item_has_updated(0);
  }
}

void ribi::cmap::QtConceptMapEditWidget::OnConceptMapItemRequestsEdit(QtConceptMapItem* const item)
{

  //assert(item->GetConcept());
  //const boost::shared_ptr<ribi::cmap::Concept> new_concept = ribi::cmap::ConceptFactory::DeepCopy(item->GetConcept());
  //assert(new_concept);

  assert(this);
  assert(item);
  //TRACE("Try edit from EditWidget");
  //m_signal_conceptmapitem_requests_edit(item);

  {
    QtScopedDisable<QtConceptMapWidget> disable(this);
    QtConceptMapConceptEditDialog d(item->GetConcept());
    d.exec();
  }
  this->show();
  this->setFocus();
  this->scene()->setFocusItem(item);
  item->setSelected(true);
  item->m_signal_item_has_updated(item);
  item->m_signal_request_scene_update();
  this->scene()->update();
  this->OnItemRequestsUpdate(item);
}

void ribi::cmap::QtConceptMapEditWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  m_tools->SetBuddyItem(dynamic_cast<const QtNode*>(item));
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtConceptMapItem*>(item));
  scene()->update();
}

void ribi::cmap::QtConceptMapEditWidget::OnToolsClicked()
{
  const QPointF cursor_pos_approx(
    m_tools->GetBuddyItem()->pos().x(),
    m_tools->GetBuddyItem()->pos().y() - 32.0);
  m_arrow = new QtNewArrow(
    m_tools->GetBuddyItem(),cursor_pos_approx);
  assert(!m_arrow->scene());
  this->scene()->addItem(m_arrow);
  m_arrow->update();
  this->scene()->update();
}
