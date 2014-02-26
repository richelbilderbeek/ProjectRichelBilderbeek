#include "conceptmapcommanddeletefocusnode.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandDeleteFocusNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get()
    && !widget->GetFocus().empty();
}

void ribi::cmap::CommandDeleteFocusNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(widget);
  assert(widget->GetConceptMap().get());
  assert(CanDoCommand(widget));

  m_widget = widget;
  m_old_focus = m_widget->GetFocus();
  for (const auto node: m_old_focus)
  {
    assert(node);
    m_widget->DeleteNode(node);
  }
  assert(m_widget);
}

void ribi::cmap::CommandDeleteFocusNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  for (const auto node: m_old_focus)
  {
    m_widget->AddNode(node);
  }

  m_widget = nullptr;
  m_old_focus.clear();

}
