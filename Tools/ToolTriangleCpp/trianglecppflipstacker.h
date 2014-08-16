#ifndef TRIANGLECPPFLIPSTACKER_H
#define TRIANGLECPPFLIPSTACKER_H

#ifdef TRIANGLECPP_USE_FLIPSTACKER

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecpptriangle.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* A stack of triangles flipped during the most recent vertex insertion.     */
/*   The stack is used to undo the vertex insertion if the vertex encroaches */
/*   upon a subsegment.                                                      */

struct FlipStacker
{
  FlipStacker();
  FlipStacker(const FlipStacker&) = delete;
  FlipStacker& operator=(const FlipStacker&) = delete;

  Triangle m_flippedtri;                       /* A recently flipped triangle. */
  FlipStacker *m_prevflip;               /* Previous flip in the stack. */
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPP_USE_FLIPSTACKER

#endif // TRIANGLECPPFLIPSTACKER_H
