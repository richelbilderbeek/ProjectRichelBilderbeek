#include "conceptmapcommandcreatenewconceptmap.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandCreateNewConceptMap::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return !widget->GetConceptMap();
}

void ribi::cmap::CommandCreateNewConceptMap::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);

  assert(widget);
  assert(!widget->GetConceptMap().get());

  m_widget = widget;

  const boost::shared_ptr<ConceptMap> new_map {
    ConceptMapFactory::Create("...")
  };
  assert(new_map);
  m_widget->SetConceptMap(new_map);

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(m_widget->GetConceptMap().get());
}

void ribi::cmap::CommandCreateNewConceptMap::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  boost::shared_ptr<ConceptMap> empty_map;
  m_widget->SetConceptMap(empty_map);

  m_widget->m_signal_concept_map_changed();

  m_widget = nullptr;

}
