#include "qtconceptmapwidget.h"

#include <cassert>
#include "qtconceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapwidget.h"
#include "trace.h"

ribi::cmap::QtConceptMapWidget::QtConceptMapWidget(
  const boost::shared_ptr<QtConceptMap> qtconceptmap)
  : m_qtconceptmap(qtconceptmap),
    m_widget(new Widget(qtconceptmap->GetConceptMap()))
{
  #ifndef NDEBUG
  Test();
  #endif
  this->setScene(m_qtconceptmap->GetScene());
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
