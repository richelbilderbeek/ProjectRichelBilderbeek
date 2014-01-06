#include "conceptmapcommand.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic pop

//Don't include ConceptMap, use Widget its mostly-private-except-for-Command interface only
#include "conceptmapwidget.h"
#include "trace.h"

bool ribi::cmap::Command::CanDoCommand(const Widget * const widget) const noexcept
{
  assert(widget);
  return CanDoCommandSpecific(widget);
}

void ribi::cmap::Command::DoCommand(Widget * const widget) noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));
  DoCommandSpecific(widget);
  #ifndef NDEBUG
  for (int i=0; i!=2; ++i)
  {
    Undo();
    DoCommandSpecific(widget);
  }
  #endif
}




bool ribi::cmap::CommandCreateNewNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get();
}

void ribi::cmap::CommandCreateNewNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(!m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());

  m_widget = widget;
  m_node = m_widget->CreateNewNode();

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandCreateNewNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->DeleteNode(m_node);

  m_widget->m_signal_concept_map_changed();

  m_widget = nullptr;
  m_node = boost::shared_ptr<Node>();

}





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











bool ribi::cmap::CommandLoseFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetFocus();
}

void ribi::cmap::CommandLoseFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(!m_old_focus);
  assert(widget);
  assert(widget->m_focus);

  //Transfer focus to this command
  m_widget = widget;
  m_old_focus = widget->m_focus;
  m_widget->m_signal_concept_map_changed();
  m_widget->m_focus = nullptr;


  assert(m_widget);
  assert(m_old_focus);
  assert(!widget->m_focus);
}

void ribi::cmap::CommandLoseFocus::Undo() noexcept
{
  assert(m_widget);
  assert(m_old_focus);
  assert(!m_widget->m_focus);

  //Transfer focus to this command
  m_widget->m_focus = m_old_focus;
  m_old_focus = nullptr;
  m_widget->m_signal_concept_map_changed();
  m_widget = nullptr;


  assert(!m_widget);
  assert(!m_old_focus);
}


















bool ribi::cmap::CommandSetFocus::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->FindNodeAt(m_x,m_y).get();
}

void ribi::cmap::CommandSetFocus::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(widget);
  assert(!widget->m_focus);

  //Transfer focus to this Node
  m_widget = widget;
  m_widget->m_focus = widget->FindNodeAt(m_x,m_y).get();

  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(widget);
  assert(widget->m_focus);
}

void ribi::cmap::CommandSetFocus::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->m_focus);

  //Lose focus to this Node
  m_widget->m_focus = nullptr;
  m_widget->m_signal_concept_map_changed();

  assert(m_widget);
  assert(!m_widget->m_focus);

}
