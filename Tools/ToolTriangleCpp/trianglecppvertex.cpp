#include "trianglecppvertex.h"

#include "trianglecppmesh.h"
#include "trianglecppvertextype.h"

int ribi::tricpp::GetVertexType(const Vertex& vx) noexcept
{
  return static_cast<int>(vx[Mesh::m_vertexmarkindex + 1]);
}

bool ribi::tricpp::IsDeadVertexType(const Vertex& vx) noexcept
{
  return GetVertexType(vx) == VertexType::DEADVERTEX;
}

bool ribi::tricpp::IsTriangleUnsuitable(
  const Vertex& triorg,
  const Vertex& tridest,
  const Vertex& triapex
) noexcept
{
  const double dxoa = triorg[0] - triapex[0];
  const double dyoa = triorg[1] - triapex[1];
  const double dxda = tridest[0] - triapex[0];
  const double dyda = tridest[1] - triapex[1];
  const double dxod = triorg[0] - tridest[0];
  const double dyod = triorg[1] - tridest[1];
  /* Find the squares of the lengths of the triangle's three edges. */
  const double oalen = dxoa * dxoa + dyoa * dyoa;
  const double dalen = dxda * dxda + dyda * dyda;
  const double odlen = dxod * dxod + dyod * dyod;
  /* Find the square of the length of the longest edge. */
  double maxlen = (dalen > oalen) ? dalen : oalen;
  maxlen = (odlen > maxlen) ? odlen : maxlen;

  return maxlen > 0.05 * (triorg[0] * triorg[0] + triorg[1] * triorg[1]) + 0.02;
}

int ribi::tricpp::vertextype(const Vertex& vertex) noexcept
{
  return static_cast<int*>(vertex)[m.m_vertexmarkindex + 1];
}

//#define vertextype(vx)  ((int *) (vx))[m.m_vertexmarkindex + 1]

void ribi::tricpp::setvertextype(Vertex& vertex, const int value) noexcept
{
  static_cast<int*>(vertex)[m.m_vertexmarkindex + 1] = value;
  assert(vertextype(vertex) == value);
}

//#define setvertextype(vx, value)                                              \
//  ((int *) (vx))[m.m_vertexmarkindex + 1] = value

