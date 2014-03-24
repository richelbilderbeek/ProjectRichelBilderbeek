#include "conceptmapcommanddeletefocusnode.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandDeleteFocusNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get() && widget->GetFocus();
}

void ribi::cmap::CommandDeleteFocusNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(widget);
  assert(widget->GetConceptMap().get());
  assert(CanDoCommand(widget));

  m_widget = widget;
  m_old_focus = m_widget->GetFocus();
  assert(m_old_focus);
  m_widget->DeleteNode(m_old_focus);
  assert(m_widget);
}

void ribi::cmap::CommandDeleteFocusNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->AddNode(m_old_focus);

  m_widget = nullptr;
  m_old_focus = nullptr;

}
