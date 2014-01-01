#include "qtconceptmapwidget.h"

#include <cassert>
#include "qtconceptmap.h"
#include "qteditconceptmap.h"
#include "qtdisplayconceptmap.h"
#include "qtrateconceptmap.h"
#include "conceptmapcommand.h"
#include "conceptmapwidget.h"
#include "qtconceptmapdisplaystrategy.h"
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

void ribi::cmap::QtConceptMapWidget::OnConceptMapChanged() noexcept
{
  if (boost::dynamic_pointer_cast<QtDisplayConceptMap>(m_qtconceptmap))
  {
    m_qtconceptmap.reset(new QtDisplayConceptMap(this->m_widget->GetConceptMap()));
  }
  else if (boost::dynamic_pointer_cast<QtEditConceptMap>(m_qtconceptmap))
  {
    m_qtconceptmap.reset(new QtEditConceptMap(this->m_widget->GetConceptMap()));
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
