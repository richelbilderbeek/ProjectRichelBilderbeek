#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecpptriangle.h"

#include <cassert>

#include "trianglecppvertex.h"
#pragma GCC diagnostic pop

/*
ribi::tricpp::Triangle::Triangle()
  : m_is_dead{false},
    m_subsegs{},
    m_triangles{}
{

}


bool ribi::tricpp::Triangle::IsDead() const noexcept
{
  //Follows:
  //#define deadtri(tria)  ((tria)[1] == (Triangle) NULL)
  //return operator[](1) == nullptr;
  return m_is_dead;
}

void ribi::tricpp::Triangle::KillMe() noexcept
{
  //Follows:
  //void killtri(const Triangle& t) { t[1] = nullptr; t[3] = nullptr; }
  //SetTriangle(nullptr,1);
  //SetTriangle(nullptr,3);
  m_is_dead = true;
  assert(IsDead());
}

void ribi::tricpp::Triangle::SetTriangle(
  const Triangle& triangle,
  const int i
)
{
  assert(i >= 0);
  assert(i < 6 && "But not sure if 6 is the limit indeed");
  assert(i < static_cast<int>(m_triangles.size()));
  m_triangles[i] = triangle;
}

void ribi::tricpp::Triangle::SetSubSeg(
  const Edge& subseg,
  const int i
)
{
  assert(i >= 6 && "But not sure if this is the limit indeed");
  assert(i  < 9 && "But not sure if this is the limit indeed");
  assert(i < static_cast<int>(m_subsegs.size()));
  m_subsegs[i] = subseg;
}

ribi::tricpp::Triangle& ribi::tricpp::Triangle::operator[](const int i) noexcept
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_triangles.size()));
  return m_triangles[i];
}

const ribi::tricpp::Triangle& ribi::tricpp::Triangle::operator[](const int i) const noexcept
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_triangles.size()));
  return m_triangles[i];
}


boost::shared_ptr<ribi::tricpp::Triangle> ribi::tricpp::vertex2tri(Vertex& vx)
{
  return vx.GetTriangle();
}
*/

/*
#define vertex2tri(vx)  ((Triangle *) (vx))[m.m_vertex2triindex]
*/
/*
void ribi::tricpp::setvertex2tri(Vertex& vx, const boost::shared_ptr<Triangle>& triangle)
{
  vx.SetTriangle(triangle);
}
*/
/*
#define setvertex2tri(vx, value)                                        \
  ((Triangle *) (vx))[m.m_vertex2triindex] = value
*/

/*****************************************************************************/
//
// triunsuitable()   Determine if a triangle is unsuitable, and thus must
//                   be further refined.
//
// You may write your own procedure that decides whether or not a selected
// triangle is too big (and needs to be refined).  There are two ways to do
// this.
//
// (1)  Modify the procedure `triunsuitable' below, then recompile
// Triangle.
//
// (2)  Define the symbol EXTERNAL_TEST (either by adding the definition
// to this file, or by using the appropriate compiler switch).  This way,
// you can compile triangle.c separately from your test.  Write your own
// `triunsuitable' procedure in a separate C file (using the same prototype
// as below).  Compile it and link the object code with triangle.o.
//
// This procedure returns 1 if the triangle is too large and should be
// refined; 0 otherwise.
//
/*****************************************************************************/

