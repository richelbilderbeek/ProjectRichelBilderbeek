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

  m_widget = widget;
  m_nodes = m_widget->GetFocus();
  assert(m_widget->GetFocus().size() == 2);
  m_widget->CreateNewEdge(

  cmap::EdgeFactory().C

  assert(m_widget);
  assert(m_node);
}

void ribi::cmap::CommandCreateNewEdge::Undo() noexcept
{
  assert(m_widget);
  assert(m_widget->GetConceptMap().get());

  m_widget->DeleteEdge(m_node);

  m_widget = nullptr;
  m_node = boost::shared_ptr<Edge>();

}
