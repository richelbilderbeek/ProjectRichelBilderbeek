#include "trianglecpptriangle.h"

void ribi::tricpp::Triangle::IsDead()
{
  //Follows:
  //#define deadtri(tria)  ((tria)[1] == (Triangle) NULL)
  return operator[](1) == nullptr;
}

void ribi::tricpp::Triangle::KillMe()
{
  //Follows:
  //void killtri(const Triangle& t) { t[1] = nullptr; t[3] = nullptr; }
  SetTriangle(nullptr,1);
  SetTriangle(nullptr,3);
  assert(IsDead());
}

void ribi::tricpp::Triangle::SetTriangle(
  Triangle& triangle,
  const int i
)
{
  assert(i >= 0);
  assert(i < 6 && "But not sure if 6 is the limit indeed");
  assert(i < static_cast<int>(m_subsegs.size()));
  assert(triangle || !triangle); //Also allow unsetting a triangle
  m_triangles[index] = triangle;
}

void ribi::tricpp::Triangle::SetSubSeg(
  SubSeg * subseg,
  const int i
)
{
  assert(i >= 6 && "But not sure if this is the limit indeed");
  assert(i  < 9 && "But not sure if this is the limit indeed");
  assert(i < static_cast<int>(m_subsegs.size()));
  assert(triangle || !triangle); //Also allow unsetting a triangle
  m_triangles[index] = triangle;
}

ribi::tricpp::Triangle * ribi::tricpp::Triangle::operator[](const int i)
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_triangles.size()));
  return m_triangles[i];
}

const ribi::tricpp::Triangle * ribi::tricpp::Triangle::operator[](const int i) const
{
  assert(i >= 0);
  assert(i < static_cast<int>(m_triangles.size()));
  return m_triangles[i];
}


Triangle& ribi::tricpp::vertex2tri(Vertex& vx)
{
  return vx.GetTriangle();
}

/*
#define vertex2tri(vx)  ((Triangle *) (vx))[m.m_vertex2triindex]
*/

void ribi::tricpp::setvertex2tri(Vertex& vx, const Triangle& value)
{
  vx.SetTriangle(value);
}

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

