#include "trianglecppvertex.h"

#include "trianglecppmesh.h"
#include "trianglecppvertextype.h"

ribi::tricpp::Vertex::Vertex(const double x, const double y, const int vertexmarker)
  : m_is_dead{false},
    m_type{VertexType::INPUTVERTEX},
    m_vertexmark{vertexmarker},
    m_x{x},
    m_y{y}
{

}

/*
int ribi::tricpp::GetVertexType(const Vertex& vx) noexcept
{
  return static_cast<int>(vx[Mesh::m_vertexmarkindex + 1]);
}

bool ribi::tricpp::IsDeadVertexType(const Vertex& vx) noexcept
{
  return GetVertexType(vx) == VertexType::DEADVERTEX;
}
*/

bool ribi::tricpp::IsTriangleUnsuitable(
  const boost::shared_ptr<Vertex>& triorg,
  const boost::shared_ptr<Vertex>& tridest,
  const boost::shared_ptr<Vertex>& triapex
) noexcept
{
  const double dxoa = triorg->GetX() - triapex->GetX();
  const double dyoa = triorg->GetY() - triapex->GetY();
  const double dxda = tridest->GetX() - triapex->GetX();
  const double dyda = tridest->GetY() - triapex->GetY();
  const double dxod = triorg->GetX() - tridest->GetX();
  const double dyod = triorg->GetY() - tridest->GetY();
  /* Find the squares of the lengths of the triangle's three edges. */
  const double oalen = dxoa * dxoa + dyoa * dyoa;
  const double dalen = dxda * dxda + dyda * dyda;
  const double odlen = dxod * dxod + dyod * dyod;
  /* Find the square of the length of the longest edge. */
  double maxlen = (dalen > oalen) ? dalen : oalen;
  maxlen = (odlen > maxlen) ? odlen : maxlen;

  return maxlen > 0.05 * (triorg->GetX() * triorg->GetX() + triorg->GetY() * triorg->GetY()) + 0.02;
}

/*
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

//#define setvertextype(vx, value) \
//  ((int *) (vx))[m.m_vertexmarkindex + 1] = value


int ribi::tricpp::vertexmark(const Vertex& vx)
{
  return vx.GetVertexMark();
}
*/

/*
#define vertexmark(vx)  ((int *) (vx))[m.m_vertexmarkindex]
*/
/*
void ribi::tricpp::setvertexmark(Vertex& vx, const int value)
{
  vx.SetMark(value);
}
*/
/*
#define setvertexmark(vx, value)                                        \
  ((int *) (vx))[m.m_vertexmarkindex] = value
*/
