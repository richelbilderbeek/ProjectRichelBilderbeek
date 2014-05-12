#ifndef TRIANGLECPPOSUB_H
#define TRIANGLECPPOSUB_H

#include "trianglecppsubseg.h"

namespace tricpp {

/* An oriented subsegment:  includes a pointer to a subsegment and an        */
/*   orientation.  The orientation denotes a side of the edge.  Hence, there */
/*   are two possible orientations.  By convention, the edge is always       */
/*   directed so that the "side" denoted is the right side of the edge.      */

struct Osub {
  SubSeg *ss;
  int ssorient;                                       /* Ranges from 0 to 1. */
};

} //~namespace tricpp

#endif // TRIANGLECPPOSUB_H
