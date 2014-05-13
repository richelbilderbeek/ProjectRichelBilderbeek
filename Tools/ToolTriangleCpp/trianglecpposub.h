#ifndef TRIANGLECPPOSUB_H
#define TRIANGLECPPOSUB_H

#include "trianglecppsubseg.h"

namespace ribi {
namespace tricpp {

/* An oriented subsegment:  includes a pointer to a subsegment and an        */
/*   orientation.  The orientation denotes a side of the edge.  Hence, there */
/*   are two possible orientations.  By convention, the edge is always       */
/*   directed so that the "side" denoted is the right side of the edge.      */

struct Osub
{
  Osub();
  SubSeg *m_subseg;
  int m_subseg_orient; /* Ranges from 0 to 1. */
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPOSUB_H
