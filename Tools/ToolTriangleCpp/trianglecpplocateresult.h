#ifndef TRIANGLECPPLOCATERESULT_H
#define TRIANGLECPPLOCATERESULT_H

namespace tricpp {

/* Labels that signify the result of point location.  The result of a        */
/*   search indicates that the point falls in the interior of a triangle, on */
/*   an edge, on a vertex, or outside the mesh.                              */

enum LocateResult {INTRIANGLE, ONEDGE, ONVERTEX, OUTSIDE};

} //~namespace tricpp

#endif // TRIANGLECPPLOCATERESULT_H
