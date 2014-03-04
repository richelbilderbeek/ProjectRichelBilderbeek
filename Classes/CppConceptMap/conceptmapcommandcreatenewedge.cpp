#include "conceptmapcommandcreatenewedge.h"

#include <cassert>

#include "conceptmapwidget.h"
#include "conceptmapedgefactory.h"

bool ribi::cmap::CommandCreateNewEdge::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap().get()
   && widget->GetFocus().size() == 2;
}

void ribi::cmap::CommandCreateNewEdge::DoCommandSpecific(Widget * const widget) noexcept
{
  assert(!m_widget);
  //assert(!m_node);
  assert(widget);
  assert(widget->GetConceptMap().get());
  assert(CanDoCommand(widget));

  m_widget = widget;
  m_nodes = m_widget->GetFocus();
  assert(m_nodes.size() == 2);
  m_edge = m_widget->CreateNewEdge();

  assert(m_widget);
  assert(m_edge);
}

void ribi::cmap::CommandCreateNewEdge::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->DeleteEdge(m_edge);

  m_widget = nullptr;
  m_nodes.clear();
  m_edge = boost::shared_ptr<Edge>();

}
