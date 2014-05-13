#ifndef TRIANGLECPPVERTEX_H
#define TRIANGLECPPVERTEX_H

#include "trianglecppvertextype.h"
namespace ribi {
namespace tricpp {

/* The vertex data structure.  Each vertex is actually an array of doubles.    */
/*   The number of doubles is unknown until runtime.  An integer boundary      */
/*   marker, and sometimes a pointer to a triangle, is appended after the    */
/*   doubles.                                                                  */

/* The vertex types.   A DEADVERTEX has been deleted entirely.  An           */
/*   UNDEADVERTEX is not part of the mesh, but is written to the output      */
/*   .node file and affects the node indexing in the other output files.     */



#define TODO_ISSUE_206_IMPROVE_VERTEX
#ifdef TODO_ISSUE_206_IMPROVE_VERTEX
struct Vertex
{
  Vertex();
  Vertex(double * begin);
  double& operator[](const int index) noexcept;
  const double& operator[](const int index) const noexcept;
  void Clear() noexcept; //Set size to zero
  bool IsEmpty() const noexcept;

  VertexType GetVertexType() const noexcept { return m_type; }
  void SetVertexType(const VertexType type) noexcept { m_type = type; }

  private:
  VertexType m_type;
};
#else
typedef double *Vertex;
#endif //#ifdef TODO_ISSUE_206_IMPROVE_VERTEX

int GetVertexType(const Vertex& vx) noexcept;
bool IsDeadVertexType(const Vertex& vx) noexcept;

bool IsTriangleUnsuitable(
  const Vertex& triorg,
  const Vertex& tridest,
  const Vertex& triapex
) noexcept;

int vertextype(const Vertex& vertex) noexcept;
void setvertextype(Vertex& vertex, const int value);

bool operator==(const Vertex& lhs,const Vertex& rhs) noexcept;
bool operator!=(const Vertex& lhs,const Vertex& rhs) noexcept;

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPVERTEX_H
