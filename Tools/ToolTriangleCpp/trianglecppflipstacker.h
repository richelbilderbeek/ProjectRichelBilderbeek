#ifndef TRIANGLECPPFLIPSTACKER_H
#define TRIANGLECPPFLIPSTACKER_H

#include "trianglecpptriangle.h"

namespace tricpp {

/* A stack of triangles flipped during the most recent vertex insertion.     */
/*   The stack is used to undo the vertex insertion if the vertex encroaches */
/*   upon a subsegment.                                                      */

struct FlipStacker
{
  FlipStacker();
  Triangle m_flippedtri;                       /* A recently flipped triangle. */
  FlipStacker *m_prevflip;               /* Previous flip in the stack. */
};

} //~namespace tricpp

#endif // TRIANGLECPPFLIPSTACKER_H
