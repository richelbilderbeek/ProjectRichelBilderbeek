#ifndef TRIANGLECPPOTRI_H
#define TRIANGLECPPOTRI_H

#include "trianglecpptriangle.h"

namespace tricpp {

/* An oriented triangle:  includes a pointer to a triangle and orientation.  */
/*   The orientation denotes an edge of the triangle.  Hence, there are      */
/*   three possible orientations.  By convention, each edge always points    */
/*   counterclockwise about the corresponding triangle.                      */

struct Otri {
  Triangle *tri;
  int orient;                                         /* Ranges from 0 to 2. */
};

} //~namespace tricpp

#endif // TRIANGLECPPOTRI_H
