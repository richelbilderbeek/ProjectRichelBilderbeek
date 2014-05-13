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
  Triangle * triangle,
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
