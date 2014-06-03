#ifndef TRIANGLECPPVERTEX_H
#define TRIANGLECPPVERTEX_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include "trianglecppvertextype.h"
#include "trianglecppfwd.h"
#include "trianglecpptypedefs.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* The vertex data structure.  Each vertex is actually an array of doubles.    */
/*   The number of doubles is unknown until runtime.  An integer boundary      */
/*   marker, and sometimes a pointer to a triangle, is appended after the    */
/*   doubles.                                                                  */

/* The vertex types.   A DEADVERTEX has been deleted entirely.  An           */
/*   UNDEADVERTEX is not part of the mesh, but is written to the output      */
/*   .node file and affects the node indexing in the other output files.     */
struct Vertex
{
  Vertex(const Length x, const Length y, const int vertexmarker);
  Length GetX() const noexcept { return m_x; }
  Length GetY() const noexcept { return m_y; }
  //double& operator[](const int index) noexcept;
  //const double& operator[](const int index) const noexcept;
  //void Clear() noexcept; //Set size to zero
  //bool IsDead() { return m_is_dead; }
  //bool IsEmpty() const noexcept;

  int GetMark() const noexcept { return m_vertexmark; }
  //boost::shared_ptr<Triangle> GetTriangle() const noexcept;
  VertexType GetVertexType() const noexcept { return m_type; }
  void SetMark(const int mark) noexcept { m_vertexmark = mark; }
  //void SetTriangle(const boost::shared_ptr<Triangle>& triangle) noexcept;
  void SetVertexType(const VertexType type) noexcept { m_type = type; }
  void SetX(const Length x) noexcept { m_x = x; }
  void SetY(const Length y) noexcept { m_y = y; }

  private:
  Length m_x;
  Length m_y;
  //bool m_is_dead;
  int m_vertexmark;
  VertexType m_type;
};

//int GetVertexType(const Vertex& vx) noexcept;
//bool IsDeadVertexType(const Vertex& vx) noexcept;

bool IsTriangleUnsuitable(
  const boost::shared_ptr<Vertex>& triorg,
  const boost::shared_ptr<Vertex>& tridest,
  const boost::shared_ptr<Vertex>& triapex
) noexcept;

//int vertextype(const Vertex& vertex) noexcept;
//void setvertextype(Vertex& vertex, const int value);

bool operator==(const Vertex& lhs,const Vertex& rhs) noexcept;
bool operator!=(const Vertex& lhs,const Vertex& rhs) noexcept;

//int vertexmark(const Vertex& vx);
//void setvertexmark(Vertex& vx, const int value);



} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPVERTEX_H
