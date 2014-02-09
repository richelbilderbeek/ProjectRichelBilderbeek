#include "conceptmapcommanddeleteconceptmap.h"
/*

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandDeleteConceptMap::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  assert(static_cast<bool>(m_widget) == static_cast<bool>(m_deleted_concept_map));
  //Cannot delete a concept map, when
  // - the command already has deleted one, so its internals are non-nullptr
  // - the offered widget has no concept map
  return !m_widget && widget->GetConceptMap().get();
}

void ribi::cmap::CommandDeleteConceptMap::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommandSpecific(widget));
  assert(widget->GetConceptMap().get());
  //Correct pre state
  //Before executing the command,
  //CommandDeleteConceptMap its internals (m_widget and m_conceptmap)
  //should both be nullptr
  assert(!m_widget && "Before deleting a Widget its ConceptMap,"
    "CommandDeleteConceptMap::m_widget must be nullptr");
  assert(!m_deleted_concept_map);

  m_widget = widget;
  m_deleted_concept_map = widget->GetConceptMap();
  const boost::shared_ptr<ConceptMap> m;
  widget->SetConceptMap(m);

  m_widget->m_signal_concept_map_changed();

  //Correct post state
  assert(m_widget);
  assert(m_deleted_concept_map);
  assert(!widget->GetConceptMap().get());
  assert(!m_widget->GetConceptMap().get());
}

void ribi::cmap::CommandDeleteConceptMap::Undo() noexcept
{
  //Correct pre state
  assert(m_widget);
  assert(m_deleted_concept_map);
  assert(!m_widget->GetConceptMap().get());

  m_widget->SetConceptMap(m_deleted_concept_map);
  boost::shared_ptr<ConceptMap> empty_map;
  m_deleted_concept_map = empty_map;
  m_widget->m_signal_concept_map_changed();
  m_widget = nullptr;

  //Correct post state
  assert(!m_widget);
  assert(!m_deleted_concept_map);
}

*/
