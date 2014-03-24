#include "qtconceptmapwidget.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/lambda/lambda.hpp>
#include <QMouseEvent>

#include "qtconceptmap.h"
#include "qtconceptmapnode.h"
#include "qteditconceptmap.h"
#include "qtconceptmapedge.h"
#include "qtdisplayconceptmap.h"
#include "qtrateconceptmap.h"
#include "conceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapcommanddeletenode.h"
#include "conceptmapcommanddeletefocusnode.h"
#include "conceptmapcommandcreatenewnode.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommandsetfocuswithcoordinat.h"
#include "conceptmapcommandsetfocusrandom.h"
#include "conceptmapnodefactory.h"
#include "qtconceptmapnode.h"
#include "conceptmapwidget.h"
#include "qtconceptmapdisplaystrategy.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::cmap::QtConceptMapWidget::QtConceptMapWidget(
  const boost::shared_ptr<QtConceptMap> qtconceptmap)
  : m_qtconceptmap(qtconceptmap),
    m_widget(new Widget(qtconceptmap->GetConceptMap()))
{
  #ifndef NDEBUG
  Test();
  #endif
  this->setScene(m_qtconceptmap->GetScene());

  //Without this line, mouseMoveEvent won't be called
  this->setMouseTracking(true);

  m_widget->m_signal_concept_map_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnConceptMapChanged,this)
  );
  m_widget->m_signal_add_edge.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnAddEdge,this,boost::lambda::_1)
  );
  m_widget->m_signal_add_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnAddNode,this,boost::lambda::_1)
  );
  m_widget->m_signal_delete_edge.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnDeleteEdge,this,boost::lambda::_1)
  );
  m_widget->m_signal_delete_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnDeleteNode,this,boost::lambda::_1)
  );

  m_widget->m_signal_lose_focus_nodes.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnLoseFocusNodes,this,boost::lambda::_1)
  );
  m_widget->m_signal_set_selected_nodes.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnSetFocusNodes,this,boost::lambda::_1)
  );
}


bool ribi::cmap::QtConceptMapWidget::CanDoCommand(
  const boost::shared_ptr<const Command> command) const noexcept
{
  assert(command);
  assert(m_widget.get());
  return command->CanDoCommand(m_widget.get());
}

void ribi::cmap::QtConceptMapWidget::DoCommand(
  const boost::shared_ptr<Command> command) noexcept
{
  assert(CanDoCommand(command));
  command->DoCommand(m_widget.get());
}

void ribi::cmap::QtConceptMapWidget::keyPressEvent(QKeyEvent * e) noexcept
{
  if (e->key() == Qt::Key_Z && e->modifiers() & Qt::ControlModifier)
  {
    //TRACE("UNDO");
    this->m_widget->Undo();
  }
}

void ribi::cmap::QtConceptMapWidget::mouseDoubleClickEvent(QMouseEvent * e) noexcept
{
  //TRACE(e);
  if (!e) throw std::exception(); //To satisfy the compiler
}

void ribi::cmap::QtConceptMapWidget::mouseMoveEvent(QMouseEvent * e) noexcept
{
  this->setCursor(QCursor(Qt::ArrowCursor));
  //Can focus be set here?
  {
    const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());
    const boost::shared_ptr<const CommandSetFocusWithCoordinat> cmd {
      new CommandSetFocusWithCoordinat(pos.x(),pos.y())
    };
    if (cmd->CanDoCommand(m_widget))
    {
      this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
      //Nothing
    }
  }
}


void ribi::cmap::QtConceptMapWidget::mousePressEvent(QMouseEvent * e) noexcept
{
  {
    const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());
    const boost::shared_ptr<CommandSetFocusWithCoordinat> cmd {
      new CommandSetFocusWithCoordinat(pos.x(),pos.y())
    };
    if (cmd->CanDoCommand(m_widget))
    {
      cmd->DoCommand(m_widget);
    }
  }
}

void ribi::cmap::QtConceptMapWidget::OnAddEdge(const boost::shared_ptr<Edge> edge) noexcept
{
  //TRACE_FUNC();
  assert(edge);
  if (!edge)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtedge_before { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_before { m_widget->GetConceptMap()->GetEdges().size() };
    #endif
    QtEdge * const qtedge { m_qtconceptmap->AddEdge(edge) };
    assert(m_qtconceptmap->FindQtEdge(qtedge));
    m_qtconceptmap->FindQtEdge(qtedge)->setFocus();

    #ifndef NDEBUG
    const std::size_t qtedges_after { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_after { m_widget->GetConceptMap()->GetEdges().size() };
    assert(qtedges_after > qtedge_before);
    assert(edges_after == edges_before && "These edges are already added to the Widget");
    if(m_qtconceptmap->GetQtEdges().size() != m_widget->GetConceptMap()->GetEdges().size())
    {
      TRACE(qtedge_before);
      TRACE(edges_before);
      TRACE(qtedges_after);
      TRACE(edges_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtEdges().size() == m_widget->GetConceptMap()->GetEdges().size());
    #endif
  }
}

void ribi::cmap::QtConceptMapWidget::OnAddNode(const boost::shared_ptr<Node> node) noexcept
{
  //TRACE_FUNC();
  assert(node);
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    #endif
    m_qtconceptmap->AddNode(node);
    assert(m_qtconceptmap->FindQtNode(node.get()));
    m_qtconceptmap->FindQtNode(node.get())->setFocus();

    #ifndef NDEBUG
    const std::size_t qtnodes_after { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_after { m_widget->GetConceptMap()->GetNodes().size() };
    assert(qtnodes_after > qtnodes_before);
    assert(nodes_after == nodes_before && "These nodes are already added to the Widget");
    if(m_qtconceptmap->GetQtNodes().size() != m_widget->GetConceptMap()->GetNodes().size())
    {
      TRACE(qtnodes_before);
      TRACE(nodes_before);
      TRACE(qtnodes_after);
      TRACE(nodes_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtNodes().size() == m_widget->GetConceptMap()->GetNodes().size());
    #endif
  }
}

void ribi::cmap::QtConceptMapWidget::OnConceptMapChanged() noexcept
{
  m_qtconceptmap->scene()->update();
  m_qtconceptmap->update();
  scene()->update();
}

void ribi::cmap::QtConceptMapWidget::OnDeleteEdge(const boost::shared_ptr<Edge> edge) noexcept
{
  if (!edge)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtedges_before { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_before { m_widget->GetConceptMap()->GetEdges().size() };
    #endif
    assert(m_qtconceptmap->FindQtEdge(edge));
    m_qtconceptmap->DeleteEdge(m_qtconceptmap->FindQtEdge(edge));
    assert(!m_qtconceptmap->FindQtEdge(edge));
    //m_qtconceptmap->FindQtEdge(node.get())->setFocus();
    m_qtconceptmap->clearFocus();

    #ifndef NDEBUG
    const std::size_t qtedges_after { m_qtconceptmap->GetQtEdges().size() };
    const std::size_t edges_after { m_widget->GetConceptMap()->GetEdges().size() };
    assert(qtedges_after < qtedges_before);
    assert(edges_after == edges_before && "These nodes are already added to the Widget");
    if(m_qtconceptmap->GetQtEdges().size() != m_widget->GetConceptMap()->GetEdges().size())
    {
      TRACE(qtedges_before);
      TRACE(edges_before);
      TRACE(qtedges_after);
      TRACE(edges_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtEdges().size() == m_widget->GetConceptMap()->GetEdges().size());
    #endif

  }
}

void ribi::cmap::QtConceptMapWidget::OnDeleteNode(const boost::shared_ptr<Node> node) noexcept
{
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    #endif
    assert(m_qtconceptmap->FindQtNode(node.get()));
    m_qtconceptmap->DeleteNode(m_qtconceptmap->FindQtNode(node.get()));
    assert(!m_qtconceptmap->FindQtNode(node.get()));
    //m_qtconceptmap->FindQtNode(node.get())->setFocus();
    m_qtconceptmap->clearFocus();

    #ifndef NDEBUG
    const std::size_t qtnodes_after { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_after { m_widget->GetConceptMap()->GetNodes().size() };
    assert(qtnodes_after < qtnodes_before);
    assert(nodes_after == nodes_before && "These nodes are already added to the Widget");
    if(m_qtconceptmap->GetQtNodes().size() != m_widget->GetConceptMap()->GetNodes().size())
    {
      TRACE(qtnodes_before);
      TRACE(nodes_before);
      TRACE(qtnodes_after);
      TRACE(nodes_after);
      TRACE("BREAK");
    }
    assert(m_qtconceptmap->GetQtNodes().size() == m_widget->GetConceptMap()->GetNodes().size());
    #endif

  }
}

void ribi::cmap::QtConceptMapWidget::OnLoseFocusNodes(const std::vector<boost::shared_ptr<Node>> nodes) noexcept
{
  for (const auto node: nodes) { OnLoseFocusNode(node); }
}

void ribi::cmap::QtConceptMapWidget::OnLoseFocusNode(const boost::shared_ptr<Node> node) noexcept
{
  if (m_qtconceptmap->FindQtNode(node.get()))
  {
    m_qtconceptmap->FindQtNode(node.get())->clearFocus();
  }
}

void ribi::cmap::QtConceptMapWidget::OnSetFocusNodes(const std::vector<boost::shared_ptr<Node>>& nodes) noexcept
{
  for (const auto node: nodes) { OnSetFocusNode(node); }
}

void ribi::cmap::QtConceptMapWidget::OnSetFocusNode(const boost::shared_ptr<Node> node) noexcept
{
  //TRACE_FUNC();
  assert(node);
  assert(m_qtconceptmap->FindQtNode(node.get()));
  //if(m_qtconceptmap->FindQtNode(node))
  {
    assert(m_qtconceptmap->FindQtNode(node.get())->flags() & QGraphicsItem::GraphicsItemFlag::ItemIsFocusable);
    m_qtconceptmap->FindQtNode(node.get())->setFocus();
  }
  assert( (m_qtconceptmap->isVisible() || !m_qtconceptmap->isVisible())
    && "m_qtconceptmap->isVisible() == true if the widget is visible"
  );
  assert( (m_qtconceptmap->FindQtNode(node.get())->isVisible() || !m_qtconceptmap->FindQtNode(node.get())->isVisible())
    && "m_qtconceptmap->FindQtNode(node)->isVisible() == true if the widget is visible"
  );
  assert(dynamic_cast<QtNode*>(scene()->focusItem()));
  assert((m_qtconceptmap->FindQtNode(node.get())->hasFocus()
      || !m_qtconceptmap->FindQtNode(node.get())->hasFocus())
    && "Could not find out how to enforce the node getting focus"
  );
}

/*
void ribi::cmap::QtConceptMapWidget::showEvent(QShowEvent*) noexcept
{
  assert(this->isVisible());
  m_qtconceptmap->show();
  assert(this->m_qtconceptmap->isVisible());
}
*/

#ifndef NDEBUG
void ribi::cmap::QtConceptMapWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtConceptMapWidget::Test()");
  //AddNode: Test creation of node from empty concept map
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::Create() };
    assert(m);
    assert(m->GetNodes().empty() && "An empty concept map must not have nodes");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m,QtEditConceptMap::Mode::simple));
    assert(c);
    assert(c->GetQtNodes().empty() && "An empty QtConceptMap must not have nodes");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    const boost::shared_ptr<CommandCreateNewNode> cmd(
      new CommandCreateNewNode
    );

    assert(m->GetNodes().empty() && "Tthe concept map must be empty");
    assert(c->GetQtNodes().empty() && "The QtConceptMap must be empty");
    w->DoCommand(cmd);
    assert(!m->GetNodes().empty() && "After creation a new node, the previously empty concept map must have a node");
    assert(!c->GetQtNodes().empty() && "After creation a new node, the previously empty QtConceptMap must have a node");
    cmd->Undo();
    assert(m->GetNodes().empty() && "After undoing the creation of a new node, the concept map must be empty again");
    assert(c->GetQtNodes().empty() && "After undoing the creation of a new node, the QtConceptMap must be empty again");
  }
  //SetFocusRandom: that a 'set random focus' results in something getting a focus
  {
    const int concept_map_index = 17;
    assert(concept_map_index < static_cast<int>(ConceptMapFactory::GetHeteromorphousTestConceptMaps().size()));
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::GetHeteromorphousTestConceptMaps()[concept_map_index] };
    assert(m);
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m,QtEditConceptMap::Mode::simple));
    assert(c);
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    assert(!w->focusWidget());
    const boost::shared_ptr<CommandSetFocusRandom> cmd(
      new CommandSetFocusRandom
    );
    //w->show();
    //assert(w->isVisible());
    //assert(c->isVisible());
    w->DoCommand(cmd);
    assert(dynamic_cast<QtNode*>(w->scene()->focusItem()));
  }
  //DeleteNode: Test deletion of node from concept map
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::Create() };
    assert(m);
    assert(m->GetNodes().empty() && "An empty concept map must not have nodes");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m,QtEditConceptMap::Mode::simple));
    assert(c);
    assert(c->GetQtNodes().empty() && "An empty QtConceptMap must not have nodes");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );
    const boost::shared_ptr<CommandCreateNewNode> cmd_add_node(
      new CommandCreateNewNode
    );

    assert(m->GetNodes().empty() && "Tthe concept map must be empty");
    assert(c->GetQtNodes().empty() && "The QtConceptMap must be empty");
    w->DoCommand(cmd_add_node);
    assert(m->GetNodes().size()   == 1 && "After creation a new node, the previously empty concept map must have a node");
    assert(c->GetQtNodes().size() == 1 && "After creation a new node, the previously empty QtConceptMap must have a node");

    const boost::shared_ptr<CommandDeleteNode> cmd_delete_node(
      new CommandDeleteNode(m->GetNodes()[0])
    );
    w->DoCommand(cmd_delete_node);
    assert(m->GetNodes().size()   == 0 && "After deleting the new node, the concept map must be empty");
    assert(c->GetQtNodes().size() == 0 && "After deleting the new node, the QtConceptMap must be empty");
    cmd_delete_node->Undo();
    assert(m->GetNodes().size()   == 1 && "After undoing the deletion of the only node, the previously empty concept map must have a node");
    assert(c->GetQtNodes().size() == 1 && "After undoing the deletion of the only node, the previously empty QtConceptMap must have a node");
  }
  //DeleteNodeFocus: Test deletion of node with focus from concept map
  {
    const boost::shared_ptr<ConceptMap> m { ConceptMapFactory::GetHeteromorphousTestConceptMap(19) };
    assert(m);
    assert(!m->GetNodes().empty() && "Concept map must have nodes to delete");
    const boost::shared_ptr<QtConceptMap> c(new QtEditConceptMap(m,QtEditConceptMap::Mode::simple));
    assert(c);
    assert(!c->GetQtNodes().empty() && "QtConceptMap must have nodes to delete");
    const boost::shared_ptr<QtConceptMapWidget> w(
      new QtConceptMapWidget(c)
    );

    {
      assert(!w->focusWidget());
      const boost::shared_ptr<CommandSetFocusRandom> cmd(
        new CommandSetFocusRandom
      );

      //w->show();
      //assert(w->isVisible());
      //assert(c->isVisible());
      w->DoCommand(cmd);
      assert(dynamic_cast<QtNode*>(w->scene()->focusItem()));
    }
    {
      const int n_nodes_before = static_cast<int>(m->GetNodes().size());
      const int n_qtnodes_before = static_cast<int>(c->GetQtNodes().size());
      const boost::shared_ptr<CommandDeleteFocusNode> cmd(
        new CommandDeleteFocusNode
      );
      w->DoCommand(cmd);
      const int n_deleted = cmd->CountDeleted();
      assert(static_cast<int>(m->GetNodes().size()) + n_deleted == n_nodes_before);
      assert(static_cast<int>(c->GetQtNodes().size()) + n_deleted == n_qtnodes_before);

      cmd->Undo();

      assert(static_cast<int>(m->GetNodes().size()) == n_nodes_before);
      assert(static_cast<int>(c->GetQtNodes().size()) == n_qtnodes_before);
    }
  }
  TRACE("Finished ribi::cmap::QtConceptMapWidget::Test()");
}
#endif
