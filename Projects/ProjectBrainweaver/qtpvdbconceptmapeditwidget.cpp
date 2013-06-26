#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtpvdbconceptmapeditwidget.h"

#include <QGraphicsItem>
#include <QKeyEvent>
#include <boost/lambda/lambda.hpp>

#include "pvdbconceptfactory.h"
#include "pvdbconcept.h"
#include "pvdbconceptmapfactory.h"
#include "pvdbconceptmap.h"
#include "pvdbedgefactory.h"
#include "pvdbedge.h"
#include "pvdbexample.h"
#include "pvdbexamples.h"
#include "pvdbhelper.h"
#include "pvdbnodefactory.h"
#include "pvdbnode.h"
#include "qtpvdbcenternodeitem.h"
#include "qtpvdbconcepteditdialog.h"
#include "qtpvdbconceptmapitem.h"
#include "qtpvdbedgeitem.h"
#include "qtpvdbexamplesitem.h"
#include "qtpvdbitemhighlighter.h"
#include "qtpvdbnewarrow.h"
#include "qtpvdbnodeitem.h"
#include "qtpvdbtoolsitem.h"
#include "qtquadbezierarrowitem.h"
#include "qtscopeddisable.h"
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

QtPvdbConceptMapEditWidget::QtPvdbConceptMapEditWidget(
  const boost::shared_ptr<pvdb::ConceptMap> concept_map,
  QWidget* parent)
  : QtPvdbConceptMapWidget(concept_map,parent),
    m_arrow(nullptr),
    m_highlighter(new QtPvdbItemHighlighter(0)),
    m_tools(new QtPvdbToolsItem)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(scene());
  scene()->addItem(m_tools); //Give m_tools a parent

  assert(concept_map  && "Only an existing concept map can be edited");
  BuildQtConceptMap();

  #ifndef NDEBUG
  assert(m_highlighter && "m_highlighter does not need to be reset in ClearMe");
  assert(concept_map->IsValid());
  const auto nodes = concept_map->GetNodes();
  const auto items = Collect<QtPvdbNodeItem>(this->scene());
  const std::size_t n_items = items.size();
  const std::size_t n_nodes = nodes.size();
  assert(n_items == n_nodes && "GUI and non-GUI concept map must match");
  #endif
}

QtPvdbConceptMapEditWidget::~QtPvdbConceptMapEditWidget()
{
  m_tools = nullptr;
  assert(m_highlighter);
  m_highlighter->SetItem(nullptr); //Do this before destroying items
  m_arrow = nullptr;
}

void QtPvdbConceptMapEditWidget::AddEdge(
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

  //Edges connected to the center node do not show their concepts
  if (IsCenterNode(from) || IsCenterNode(to))
  {
    assert(qtconcept == qtedge->GetConceptItem());
    qtconcept->setVisible(false);
  }

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &QtPvdbConceptMapEditWidget::OnConceptMapItemRequestsEdit,
      this, boost::lambda::_1)); //Do not forget the placeholder!

  this->scene()->addItem(qtedge);

  assert(std::count(
    this->GetConceptMap()->GetEdges().begin(),
    this->GetConceptMap()->GetEdges().end(),
    edge) == 1 && "Assume edge is already in the concept map");
  //this->GetConceptMap()->AddEdge(edge);

  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
  assert(qtedge->pos().x() == edge->GetX());
  assert(qtedge->pos().y() == edge->GetY());
}

void QtPvdbConceptMapEditWidget::AddEdge(QtPvdbNodeItem * const qt_from, QtPvdbNodeItem* const qt_to)
{
  assert(qt_from);
  assert(qt_to);
  assert(qt_from != qt_to);
  assert(qt_from->GetNode() != qt_to->GetNode());
  assert(!dynamic_cast<const QtPvdbToolsItem*>(qt_to  ) && "Cannot select a ToolsItem");
  assert(!dynamic_cast<const QtPvdbToolsItem*>(qt_from) && "Cannot select a ToolsItem");
  //Does this edge already exists? If yes, modify it
  {
    const std::vector<QtPvdbEdgeItem*> edges = Collect<QtPvdbEdgeItem>(scene());
    const auto iter = std::find_if(edges.begin(),edges.end(),
      [qt_from,qt_to](const QtPvdbEdgeItem* const other_edge)
      {
        return
            (other_edge->GetArrow()->GetFromItem() == qt_from && other_edge->GetArrow()->GetToItem() == qt_to  )
         || (other_edge->GetArrow()->GetFromItem() == qt_to   && other_edge->GetArrow()->GetToItem() == qt_from);
      }
    );
    if (iter != edges.end())
    {
      QtPvdbEdgeItem * const qtedge = *iter;
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
  const std::vector<QtPvdbNodeItem*> qtnodes = Collect<QtPvdbNodeItem>(scene());
  const boost::shared_ptr<pvdb::Concept> concept(pvdb::ConceptFactory::Create());
  assert(concept);
  const bool head_arrow = true;
  const bool tail_arrow = false;
  const boost::shared_ptr<pvdb::Node> from = qt_from->GetNode();
  assert(from);
  const boost::shared_ptr<pvdb::Node> to = qt_to->GetNode();
  assert(to);
  assert(from != to);
  const boost::shared_ptr<pvdb::Edge> edge(
    pvdb::EdgeFactory::Create(
      concept,
      (qt_from->pos().x() + qt_to->pos().x()) / 2.0,
      (qt_from->pos().y() + qt_to->pos().y()) / 2.0,
      from,
      tail_arrow,
      to,
      head_arrow));

  //Step 1: Create an Edge concept
  const boost::shared_ptr<QtPvdbEditConceptItem> qtconcept(new QtPvdbEditConceptItem(edge->GetConcept()));
  assert(qtconcept);

  QtPvdbEdgeItem * const qtedge = new QtPvdbEdgeItem(edge,qtconcept,qt_from,qt_to);

  //Edges connected to the center node do not show their concepts
  if (IsCenterNode(qt_from) || IsCenterNode(qt_to))
  {
    assert(qtconcept == qtedge->GetConceptItem());
    qtconcept->setVisible(false);
  }

  //General: inform an Observer that this item has changed
  qtedge->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtedge->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtedge->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &QtPvdbConceptMapEditWidget::OnConceptMapItemRequestsEdit,
      this, boost::lambda::_1)); //Do not forget the placeholder!


  this->scene()->addItem(qtedge);
  this->GetConceptMap()->AddEdge(edge);

  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");

  this->scene()->update();
}

QtPvdbNodeItem * QtPvdbConceptMapEditWidget::AddNode(const boost::shared_ptr<pvdb::Node> node)
{
  assert(node);
  assert(node->GetConcept());
  const boost::shared_ptr<QtPvdbEditConceptItem> qtconcept(new QtPvdbEditConceptItem(node->GetConcept()));
  assert(node);
  QtPvdbNodeItem * const qtnode = new QtPvdbNodeItem(node,qtconcept);

  assert(qtnode->pos().x() == node->GetX());
  assert(qtnode->pos().y() == node->GetY());

  //General: inform an Observer that this item has changed
  qtnode->m_signal_item_has_updated.connect(
   boost::bind(&QtPvdbConceptMapWidget::OnItemRequestsUpdate,this,boost::lambda::_1));

  //General: inform an Observer that a QGraphicsScene needs to be updated
  qtnode->m_signal_request_scene_update.connect(
    boost::bind(&QtPvdbConceptMapWidget::OnRequestSceneUpdate,this));

  //Specific for Edit widget: inform an Observer of a request for a text edit
  qtnode->m_signal_conceptmapitem_requests_edit.connect(
    boost::bind(
      &QtPvdbConceptMapEditWidget::OnConceptMapItemRequestsEdit,
      this, boost::lambda::_1)); //Do not forget the placeholder!

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
  //assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
  //  && "GUI and non-GUI concept map must match");

  return qtnode;
}

void QtPvdbConceptMapEditWidget::CleanMe()
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
    QtPvdbExamplesItem * const item = new QtPvdbExamplesItem;
    assert(item);
    SetExamplesItem(item);
    item->m_signal_request_scene_update.connect(
      boost::bind(
        &QtPvdbConceptMapEditWidget::OnRequestSceneUpdate,this));
    item->setVisible(false);
    this->scene()->addItem(item);
  }

  //Add the tools item
  {
    assert(!m_tools);
    m_tools = new QtPvdbToolsItem;
    m_tools->m_signal_clicked.connect(
      boost::bind(
        &QtPvdbConceptMapEditWidget::OnToolsClicked,
        this));
    this->scene()->addItem(m_tools);
  }
}

#ifndef NDEBUG
std::unique_ptr<QtPvdbConceptMapWidget> QtPvdbConceptMapEditWidget::CreateNewDerived() const
{
  const boost::shared_ptr<pvdb::ConceptMap> concept_map
    = pvdb::ConceptMapFactory::DeepCopy(this->GetConceptMap());
  assert(concept_map);
  std::unique_ptr<QtPvdbConceptMapWidget> p(new This_t(concept_map));
  return p;
}
#endif

void QtPvdbConceptMapEditWidget::DeleteEdge(QtPvdbEdgeItem * const qtedge)
{
  #ifndef NDEBUG
  const int n_items_before = this->scene()->items().count();
  #endif

  assert(scene()->items().contains(qtedge));
  this->scene()->removeItem(qtedge);
  DeleteLeftovers();
  GetConceptMap()->DeleteEdge(qtedge->GetEdge());

  #ifndef NDEBUG
  const int n_items_after = this->scene()->items().count();
  assert(n_items_after + 1 == n_items_before);
  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
  #endif
}

void QtPvdbConceptMapEditWidget::DeleteLeftovers()
{
  //assert(m_edge_concepts.size() == m_arrows.size());
  bool done = true;
  while (1)
  {
    done = true;
    //Delete edges without to/from nodes
    {
      const std::vector<QtPvdbEdgeItem*> qtedge = Collect<QtPvdbEdgeItem>(scene());
      for (int i = 0; i!=static_cast<int>(qtedge.size()); ++i)
      {
        assert(i >= 0 && i < static_cast<int>(qtedge.size()));
        //An edge can be deleted if its 'to' or 'from' is absent
        QtPvdbEdgeItem * const edge = qtedge[i];
        assert(edge->GetFrom());
        assert(edge->GetTo());
        assert(edge->GetFrom() != edge->GetTo());
        const std::vector<QtPvdbNodeItem*> qtnodes = Collect<QtPvdbNodeItem>(scene());
        if (std::count_if(qtnodes.begin(),qtnodes.end(),
          [edge](const QtPvdbNodeItem * node)
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
  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}

void QtPvdbConceptMapEditWidget::DeleteNode(QtPvdbNodeItem * const qtnode)
{
  #ifndef NDEBUG
  const int n_items_before = this->scene()->items().count();
  #endif

  this->scene()->removeItem(qtnode);
  DeleteLeftovers();
  GetConceptMap()->DeleteNode(qtnode->GetNode());

  #ifndef NDEBUG
  const int n_items_after = this->scene()->items().count();
  assert(n_items_after + 1 == n_items_before);
  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
  #endif
}

#ifndef NDEBUG
void QtPvdbConceptMapEditWidget::DoRandomStuff()
{
  //this->mouseDoubleClickEvent(0); //CAUSES ACCESS VIOLATION

  const boost::shared_ptr<pvdb::Concept> concept1(pvdb::ConceptFactory::Create("...", { {} } ) );
  const boost::shared_ptr<pvdb::Node> node1(pvdb::NodeFactory::Create(concept1));
  this->GetConceptMap()->AddNode(node1);
  QtPvdbNodeItem * const qtnode1 = AddNode(node1);

  const boost::shared_ptr<pvdb::Concept> concept2(pvdb::ConceptFactory::Create("...", { {} } ) );
  const boost::shared_ptr<pvdb::Node> node2(pvdb::NodeFactory::Create(concept2));
  this->GetConceptMap()->AddNode(node2);
  QtPvdbNodeItem * const qtnode2 = AddNode(node2);

  assert(qtnode1->GetNode() != qtnode2->GetNode());
  this->AddEdge(qtnode1,qtnode2);

  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}
#endif

void QtPvdbConceptMapEditWidget::keyPressEvent(QKeyEvent* event)
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
            if (QtPvdbNodeItem * const node = dynamic_cast<QtPvdbNodeItem *>(item))
            {
              if (!IsCenterNode(node)) //Cannot delete center node
              {
                const std::vector<QtPvdbNodeItem*> node_concepts = Collect<QtPvdbNodeItem>(scene());
                assert(std::count(node_concepts.begin(),node_concepts.end(),node) == 1);
                DeleteNode(node);
              }
            }
            //Delete an Edge Concept
            if (QtPvdbEdgeItem* const edge = dynamic_cast<QtPvdbEdgeItem*>(item))
            {
              const std::vector<QtPvdbEdgeItem*> edge_concepts = Collect<QtPvdbEdgeItem>(scene());
              assert(std::count(edge_concepts.begin(),edge_concepts.end(),edge) == 1);
              assert(scene()->items().contains(edge));
              DeleteEdge(edge);
            }
          }
        );
        if (!v.empty())
        {
          DeleteLeftovers();
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
  QtPvdbConceptMapWidget::keyPressEvent(event);
}

void QtPvdbConceptMapEditWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
  const boost::shared_ptr<pvdb::Concept> concept(
    pvdb::ConceptFactory::Create("..."));
  const boost::shared_ptr<pvdb::Node> node(pvdb::NodeFactory::Create(concept));
  assert(node);
  assert(GetConceptMap());
  GetConceptMap()->AddNode(node);

  QtPvdbNodeItem * const qtnode = AddNode(node); //AddNode creates, connects and adds the node to scene

  assert(qtnode);
  qtnode->setPos(mapToScene(event->pos()));

  assert(Collect<QtPvdbNodeItem>(this->scene()).size() == this->GetConceptMap()->GetNodes().size()
    && "GUI and non-GUI concept map must match");
}

void QtPvdbConceptMapEditWidget::mouseMoveEvent(QMouseEvent * event)
{
  if (m_arrow)
  {
    const QPointF pos = mapToScene(event->pos());
    m_arrow->SetHeadPos(pos.x(),pos.y());

    //Move the item under the arrow
    QtPvdbNodeItem* const item_below = GetItemBelowCursor(mapToScene(event->pos()));

    m_highlighter->SetItem(item_below); //item_below is allowed to be nullptr
  }
  else
  {
    m_highlighter->SetItem(nullptr); //item_below is allowed to be nullptr
  }
  QtPvdbConceptMapWidget::mouseMoveEvent(event);
}

void QtPvdbConceptMapEditWidget::mousePressEvent(QMouseEvent *event)
{
  assert(m_highlighter);
  if (m_arrow) //&& m_highlighter->GetItem())
  {
    if (m_highlighter->GetItem() && m_arrow->GetFrom() != m_highlighter->GetItem())
    {
      assert(!dynamic_cast<QtPvdbToolsItem*>(m_highlighter->GetItem()) && "Cannot select a ToolsItem");
      AddEdge( m_arrow->GetFrom(),m_highlighter->GetItem());
    }
    this->scene()->removeItem(m_arrow);
    m_arrow = nullptr;
    m_highlighter->SetItem(nullptr);
  }

  QtPvdbConceptMapWidget::mousePressEvent(event);

  //If nothing is selected, hide the Examples
  if (!GetScene()->focusItem() && !this->GetScene()->selectedItems().count())
  {
    //Let any node (in this case the central node) emit an update for the Examples
    //to hide.
    this->GetCenterNode()->m_signal_item_has_updated(0);
  }
}

void QtPvdbConceptMapEditWidget::OnConceptMapItemRequestsEdit(QtPvdbConceptMapItem* const item)
{

  //assert(item->GetConcept());
  //const boost::shared_ptr<pvdb::Concept> new_concept = pvdb::ConceptFactory::DeepCopy(item->GetConcept());
  //assert(new_concept);

  assert(this);
  assert(item);
  //TRACE("Try edit from EditWidget");
  //m_signal_conceptmapitem_requests_edit(item);

  {
    QtScopedDisable<QtPvdbConceptMapWidget> disable(this);
    QtPvdbConceptEditDialog d(item->GetConcept());
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

void QtPvdbConceptMapEditWidget::OnItemRequestUpdateImpl(const QGraphicsItem* const item)
{
  m_tools->SetBuddyItem(dynamic_cast<const QtPvdbNodeItem*>(item));
  GetExamplesItem()->SetBuddyItem(dynamic_cast<const QtPvdbConceptMapItem*>(item));
  scene()->update();
}

void QtPvdbConceptMapEditWidget::OnToolsClicked()
{
  const QPointF cursor_pos_approx(
    m_tools->GetBuddyItem()->pos().x(),
    m_tools->GetBuddyItem()->pos().y() - 32.0);
  m_arrow = new QtPvdbNewArrow(
    m_tools->GetBuddyItem(),cursor_pos_approx);
  this->scene()->addItem(m_arrow);
  m_arrow->update();
  this->scene()->update();
}
