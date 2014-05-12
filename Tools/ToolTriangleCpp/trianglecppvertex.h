#ifndef TRIANGLECPPVERTEX_H
#define TRIANGLECPPVERTEX_H

namespace tricpp {

/* The vertex data structure.  Each vertex is actually an array of doubles.    */
/*   The number of doubles is unknown until runtime.  An integer boundary      */
/*   marker, and sometimes a pointer to a triangle, is appended after the    */
/*   doubles.                                                                  */

typedef double *Vertex;

int triunsuitable(
  const Vertex triorg,
  const Vertex tridest,
  const Vertex triapex,
  double /* area */
);

} //~namespace tricpp

#endif // TRIANGLECPPVERTEX_H
