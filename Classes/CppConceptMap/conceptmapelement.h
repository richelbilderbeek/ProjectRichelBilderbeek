#ifndef CONCEPTMAPELEMENT_H
#define CONCEPTMAPELEMENT_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "conceptmapfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///A focusable element of a concept map, which is either a Node or an Edge
struct Element
{
  Element() {}
  virtual ~Element() noexcept {}
};

} //~namespace cmap
} //~namespace ribi

#endif // CONCEPTMAPELEMENT_H
