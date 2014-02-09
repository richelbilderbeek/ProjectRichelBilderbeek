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
#include "qtdisplayconceptmap.h"
#include "qtrateconceptmap.h"
#include "conceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommandsetfocuswithcoordinat.h"
#include "conceptmapcommandsetfocusrandom.h"
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
  m_widget->m_signal_add_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnAddNode,this,boost::lambda::_1)
  );
  m_widget->m_signal_delete_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnDeleteNode,this,boost::lambda::_1)
  );

  m_widget->m_signal_lose_focus_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnLoseFocusNode,this,boost::lambda::_1)
  );
  m_widget->m_signal_set_focus_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnSetFocusNode,this,boost::lambda::_1)
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
    TRACE("UNDO");
    this->m_widget->Undo();
  }
}

void ribi::cmap::QtConceptMapWidget::mouseDoubleClickEvent(QMouseEvent * e) noexcept
{
  TRACE(e);
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

void ribi::cmap::QtConceptMapWidget::OnAddNode(const boost::shared_ptr<Node> node) noexcept
{
  TRACE_FUNC();
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    TRACE(qtnodes_before)
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
  TRACE(m_qtconceptmap->scene()->items().count());
  m_qtconceptmap->scene()->update();
  TRACE(m_qtconceptmap->scene()->items().count());

  TRACE(m_qtconceptmap->items().count());
  m_qtconceptmap->update();
  TRACE(m_qtconceptmap->items().count());

  TRACE(scene()->items().count());
  scene()->update();
  TRACE(scene()->items().count());

}

void ribi::cmap::QtConceptMapWidget::OnDeleteNode(const boost::shared_ptr<Node> node) noexcept
{
  TRACE_FUNC();
  if (!node)
  {
    //m_qtconceptmap->clearFocus();
  }
  else
  {
    #ifndef NDEBUG
    const std::size_t qtnodes_before { m_qtconceptmap->GetQtNodes().size() };
    const std::size_t nodes_before { m_widget->GetConceptMap()->GetNodes().size() };
    TRACE(qtnodes_before)
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

void ribi::cmap::QtConceptMapWidget::OnLoseFocusNode(Node * const node) noexcept
{
  TRACE_FUNC();
  if (!node)
  {
    //Nothing
  }
  else
  {
    if (m_qtconceptmap->FindQtNode(node))
    {
      m_qtconceptmap->FindQtNode(node)->clearFocus();
    }
  }
}


void ribi::cmap::QtConceptMapWidget::OnSetFocusNode(Node * const node) noexcept
{
  TRACE_FUNC();
  if (!node)
  {
    m_qtconceptmap->clearFocus();
  }
  else
  {
    if (m_qtconceptmap->FindQtNode(node))
    {
      m_qtconceptmap->FindQtNode(node)->setFocus();
    }
  }
}

#ifndef NDEBUG
void ribi::cmap::QtConceptMapWidget::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::cmap::QtConceptMapWidget::Test()");
  //Test that a 'set random focus' results in something getting a focus
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
    w->DoCommand(cmd);
    //assert(w->focusWidget());
    TRACE("TODO");
  }
  TRACE("Finished ribi::cmap::QtConceptMapWidget::Test()");
}
#endif
