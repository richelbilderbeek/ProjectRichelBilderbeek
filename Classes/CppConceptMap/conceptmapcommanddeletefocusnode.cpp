#include "conceptmapcommanddeletefocusnode.h"

#include <cassert>

#include "conceptmapwidget.h"

bool ribi::cmap::CommandDeleteFocusNode::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get()
    && widget->GetFocus();
}

void ribi::cmap::CommandDeleteFocusNode::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  assert(!m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());
  assert(CanDoCommand(widget));

  m_widget = widget;
  m_node = m_widget->GetFocus();
  m_widget->DeleteNode(m_node);

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandDeleteFocusNode::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());
  assert(m_node);

  m_widget->AddNode(m_node);

  m_widget = nullptr;
  m_node = boost::shared_ptr<Node>();

}
