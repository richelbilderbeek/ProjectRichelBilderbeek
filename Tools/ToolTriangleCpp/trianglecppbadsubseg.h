#ifndef TRIANGLECPPBADSUBSEG_H
#define TRIANGLECPPBADSUBSEG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppfwd.h"
#include "trianglecppsubseg.h"
#include "trianglecppvertex.h"
#pragma GCC diagnostic pop


namespace ribi {
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
} //~namespace ribi

#endif // TRIANGLECPPBADSUBSEG_H
