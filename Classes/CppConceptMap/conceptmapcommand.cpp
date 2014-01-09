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











































