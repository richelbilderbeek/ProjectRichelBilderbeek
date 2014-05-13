#ifndef TRIANGLECPPBADSUBSEG_H
#define TRIANGLECPPBADSUBSEG_H

#include "trianglecppfwd.h"
#include "trianglecppsubseg.h"
#include "trianglecppvertex.h"


namespace tricpp {

/* A queue used to store encroached subsegments.  Each subsegment's vertices */
/*   are stored so that we can check whether a subsegment is still the same. */

struct BadSubSeg
{
  BadSubSeg();
  SubSeg m_encsubseg;                             /* An encroached subsegment. */
  Vertex m_subsegdest;
  Vertex m_subsegorg;
};

} //~namespace tricpp

#endif // TRIANGLECPPBADSUBSEG_H
