#ifndef TRIANGLECPPBADTRIANG_H
#define TRIANGLECPPBADTRIANG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "trianglecpptriangle.h"
#include "trianglecppvertex.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* A queue used to store bad triangles.  The key is the square of the cosine */
/*   of the smallest angle of the triangle.  Each triangle's vertices are    */
/*   stored so that one can check whether a triangle is still the same.      */

struct BadTriang
{
  BadTriang();
  BadTriang(const BadTriang&) = delete;
  BadTriang& operator=(const BadTriang&) = delete;

  double m_key; ///cos^2 of smallest (apical) angle
  boost::shared_ptr<BadTriang> m_nexttriang; /// Pointer to next bad triangle
  boost::shared_ptr<Triangle> m_poortri;  /// A skinny or too-large triangle.
  Vertex m_triangorg;
  Vertex m_triangdest;
  Vertex m_triangapex; /// Its three vertices
};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPBADTRIANG_H
