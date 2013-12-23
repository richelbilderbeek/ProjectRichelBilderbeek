#include "conceptmapcommand.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic pop

#include "conceptmapwidget.h"

bool ribi::cmap::Command::CanDoCommand(const Widget * const widget) const noexcept
{
  assert(widget);
  return CanDoCommandSpecific(widget);
}

void ribi::cmap::Command::DoCommand(Widget * const widget) const noexcept
{
  assert(widget);
  assert(CanDoCommand(widget));
  DoCommandSpecific(widget);
}

bool ribi::cmap::CommandDeleteConceptMap::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return widget->GetConceptMap();
}

void ribi::cmap::CommandDeleteConceptMap::DoCommandSpecific(Widget * const widget) const noexcept
{
  assert(widget);
  const boost::shared_ptr<ConceptMap> m;
  assert(!m);
  widget->SetConceptMap(m);
}

bool ribi::cmap::CommandStartConceptMap::CanDoCommandSpecific(const Widget * const widget) const noexcept
{
  assert(widget);
  return !widget->GetConceptMap();
}

void ribi::cmap::CommandStartConceptMap::DoCommandSpecific(Widget * const widget) const noexcept
{
  assert(widget);
  const boost::shared_ptr<ConceptMap> m {
    ConceptMapFactory::Create("...")
  };
  assert(m);
  widget->SetConceptMap(m);
}
