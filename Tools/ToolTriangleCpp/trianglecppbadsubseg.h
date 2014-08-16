#ifndef TRIANGLECPPBADSUBSEG_H
#define TRIANGLECPPBADSUBSEG_H

#ifdef TRIANGLECPP_USE_BADSUBSEG

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppfwd.h"
#include "trianglecppedge.h"
#include "trianglecppvertex.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace tricpp {

/// A queue used to store encroached subsegments.  Each subsegment's vertices
///   are stored so that we can check whether a subsegment is still the same.
struct BadSubSeg
{
  BadSubSeg();
  ///An encroached subsegment
  boost::shared_ptr<Edge> m_encsubseg;
  boost::shared_ptr<Vertex> m_subsegdest;
  boost::shared_ptr<Vertex> m_subsegorg;
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPP_USE_BADSUBSEG

#endif // TRIANGLECPPBADSUBSEG_H
