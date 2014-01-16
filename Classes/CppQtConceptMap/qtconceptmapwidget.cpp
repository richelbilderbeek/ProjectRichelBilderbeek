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
#include "conceptmapcommand.h"
#include "conceptmapcommandlosefocus.h"
#include "conceptmapcommandsetfocuswithcoordinat.h"
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
  m_widget->m_signal_concept_map_changed.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnConceptMapChanged,this)
  );
  m_widget->m_signal_set_focus_node.connect(
    boost::bind(&ribi::cmap::QtConceptMapWidget::OnSetFocusNode,this,boost::lambda::_1)
  );
}


bool ribi::cmap::QtConceptMapWidget::CanDoCommand(
  const boost::shared_ptr<const Command> command) const noexcept
{
  return command->CanDoCommand(m_widget.get());
}

void ribi::cmap::QtConceptMapWidget::DoCommand(
  const boost::shared_ptr<Command> command) noexcept
{
  assert(command);
  assert(m_widget.get());
  command->DoCommand(m_widget.get());
}

void ribi::cmap::QtConceptMapWidget::keyPressEvent(QKeyEvent * e) noexcept
{
  if (e->key()  == Qt::Key_Z && e->modifiers() & Qt::ControlModifier)
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
      TRACE("YES");
      this->setCursor(QCursor(Qt::PointingHandCursor));
    }
    else
    {
      TRACE("NO");
    }
  }
}


void ribi::cmap::QtConceptMapWidget::mousePressEvent(QMouseEvent * e) noexcept
{
  //Try to unselect a potentially focused node or edge
  const boost::shared_ptr<CommandLoseFocus> lose_focus {
    new CommandLoseFocus
  };
  const bool has_focus = m_widget->CanDoCommand(lose_focus);
  TRACE(has_focus);

  const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());

  const boost::shared_ptr<CommandSetFocusWithCoordinat> set_focus {
    new CommandSetFocusWithCoordinat(pos.x(),pos.y())
  };
  const bool can_set_focus = m_widget->CanDoCommand(set_focus);
  TRACE(can_set_focus);
  if (has_focus)
  {
    if (can_set_focus)
    {
      //Focus transferred
      m_widget->DoCommand(lose_focus);
      assert(m_widget->CanDoCommand(set_focus));
      m_widget->DoCommand(set_focus);
    }
    else
    {
      //Lose focus
      assert(!can_set_focus);
      m_widget->DoCommand(lose_focus);
    }
  }
  else
  {
    assert(!has_focus);
    if (can_set_focus)
    {
      //No focus yet, next will be
      m_widget->DoCommand(set_focus);
    }
    else
    {
      assert(!can_set_focus);
      //Done: currently no focus, next
    }
  }
}

void ribi::cmap::QtConceptMapWidget::OnConceptMapChanged() noexcept
{
  m_qtconceptmap->scene()->update();
  m_qtconceptmap->update();
  /*
  if (boost::dynamic_pointer_cast<QtDisplayConceptMap>(m_qtconceptmap))
  {
    m_qtconceptmap.reset(new QtDisplayConceptMap(this->m_widget->GetConceptMap()));
  }
  else if (boost::dynamic_pointer_cast<QtEditConceptMap>(m_qtconceptmap))
  {
    m_qtconceptmap.reset(new QtEditConceptMap(this->m_widget->GetConceptMap(),QtEditConceptMap::Mode::simple));
  }
  else if (boost::dynamic_pointer_cast<QtRateConceptMap>(m_qtconceptmap))
  {
    m_qtconceptmap.reset(new QtRateConceptMap(this->m_widget->GetConceptMap()));
  }
  else
  {
    assert(!"Should not get here: unknown QtConceptMap derived class");
  }
  */
}

void ribi::cmap::QtConceptMapWidget::OnSetFocusNode(Node * const node) noexcept
{
  m_qtconceptmap->FindQtNode(node)->setFocus();
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

  TRACE("Finished ribi::cmap::QtConceptMapWidget::Test()");
}
#endif
