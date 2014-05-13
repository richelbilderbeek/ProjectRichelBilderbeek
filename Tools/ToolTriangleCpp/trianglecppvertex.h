#ifndef TRIANGLECPPVERTEX_H
#define TRIANGLECPPVERTEX_H

namespace tricpp {

/* The vertex data structure.  Each vertex is actually an array of doubles.    */
/*   The number of doubles is unknown until runtime.  An integer boundary      */
/*   marker, and sometimes a pointer to a triangle, is appended after the    */
/*   doubles.                                                                  */

typedef double *Vertex;

#ifdef TODO_ISSUE_206_IMPROVE_VERTEX
struct Vertex
{
  double& operator[](const int index) noexcept;
  const double& operator[](const int index) const noexcept;
};
#endif //#ifdef TODO_ISSUE_206_IMPROVE_VERTEX


bool triunsuitable(
  const Vertex& triorg,
  const Vertex& tridest,
  const Vertex& triapex
);

} //~namespace tricpp

#endif // TRIANGLECPPVERTEX_H
