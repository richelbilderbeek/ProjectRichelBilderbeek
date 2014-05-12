#ifndef TRIANGLECPPBADSUBSEG_H
#define TRIANGLECPPBADSUBSEG_H

#include "trianglecppfwd.h"
#include "trianglecppsubseg.h"
#include "trianglecppvertex.h"


namespace tricpp {

/* A queue used to store encroached subsegments.  Each subsegment's vertices */
/*   are stored so that we can check whether a subsegment is still the same. */

struct BadSubSeg {
  SubSeg encsubseg;                             /* An encroached subsegment. */
  Vertex subsegorg, subsegdest;                         /* Its two vertices. */
};

} //~namespace tricpp

#endif // TRIANGLECPPBADSUBSEG_H
