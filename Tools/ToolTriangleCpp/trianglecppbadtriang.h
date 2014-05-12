#ifndef TRIANGLECPPBADTRIANG_H
#define TRIANGLECPPBADTRIANG_H

#include "trianglecpptriangle.h"
#include "trianglecppvertex.h"

namespace tricpp {

/* A queue used to store bad triangles.  The key is the square of the cosine */
/*   of the smallest angle of the triangle.  Each triangle's vertices are    */
/*   stored so that one can check whether a triangle is still the same.      */

struct BadTriang {
  Triangle poortri;                       /* A skinny or too-large triangle. */
  double key;                             /* cos^2 of smallest (apical) angle. */
  Vertex triangorg, triangdest, triangapex;           /* Its three vertices. */
  BadTriang *nexttriang;             /* Pointer to next bad triangle. */
};

} //~namespace tricpp

#endif // TRIANGLECPPBADTRIANG_H
