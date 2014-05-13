#ifndef TRIANGLECPPBADTRIANG_H
#define TRIANGLECPPBADTRIANG_H

#include "trianglecpptriangle.h"
#include "trianglecppvertex.h"

namespace tricpp {

/* A queue used to store bad triangles.  The key is the square of the cosine */
/*   of the smallest angle of the triangle.  Each triangle's vertices are    */
/*   stored so that one can check whether a triangle is still the same.      */

struct BadTriang
{
  BadTriang();

  double m_key; ///cos^2 of smallest (apical) angle
  BadTriang * m_nexttriang; /// Pointer to next bad triangle
  Triangle m_poortri;  /// A skinny or too-large triangle.
  Vertex m_triangorg;
  Vertex m_triangdest;
  Vertex m_triangapex;           /// Its three vertices
};

} //~namespace tricpp

#endif // TRIANGLECPPBADTRIANG_H
