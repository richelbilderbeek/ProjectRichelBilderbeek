#include "qtconceptmapwidget.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QMouseEvent>

#include "qtconceptmap.h"
#include "qteditconceptmap.h"
#include "qtdisplayconceptmap.h"
#include "qtrateconceptmap.h"
#include "conceptmapcommand.h"
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
  TRACE(e);
}

void ribi::cmap::QtConceptMapWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
  TRACE(e);
}

void ribi::cmap::QtConceptMapWidget::mouseMoveEvent(QMouseEvent * e)
{
  TRACE(e);
}

void ribi::cmap::QtConceptMapWidget::mousePressEvent(QMouseEvent * e)
{
  //Try to unselect a potentially focused node or edge
  const boost::shared_ptr<CommandLoseFocus> lose_focus {
    new CommandLoseFocus
  };
  const bool has_focus = m_widget->CanDoCommand(lose_focus);
  TRACE(has_focus);

  const QPointF pos = QGraphicsView::mapToScene(e->x(),e->y());

  const boost::shared_ptr<CommandSetFocus> set_focus {
    new CommandSetFocus(pos.x(),pos.y())
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
