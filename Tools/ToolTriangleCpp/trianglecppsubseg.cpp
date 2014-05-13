#include "trianglecppsubseg.h"

bool ribi::tricpp::SubSeg::IsDead() const noexcept
{
  //bool deadsubseg(const SubSeg& t) { return t[1] == nullptr; }
  assert(m_triangles.size() > 1);
  return m_triangles[1] == nullptr;
}

void ribi::tricpp::SubSeg::KillMe() noexcept
{
  //void killsubseg(const SubSeg& t) { t[1] = nullptr; t[2] = nullptr; }
  assert(m_triangles.size() > 2);
  m_triangles[1] = nullptr;
  m_triangles[2] = nullptr;
  assert(IsDead());
}

void ribi::tricpp::SubSeg::SetSubSeg(SubSeg * const subseg, const int index)
{
  assert(index >= 0);
  assert(index  < 6 && "But not sure yet...");
  assert(index < static_cast<int>(m_subsegs.size()));
  m_subsegs[index] = subseg;
}

void ribi::tricpp::SubSeg::SetTriangle(Triangle * const triangle, const int index)
{
  assert(index >= 6);
  assert(index  < 8 && "But not sure yet...");
  assert(index < static_cast<int>(m_triangles.size()));
  m_triangles[index] = triangle;
}

void ribi::tricpp::SubSeg::ssym(const SubSeg& osub1, SubSeg& osub2)
{
  osub2.m_subseg = osub1.m_subseg;
  osub2.m_subseg_orient = 1 - osub1.m_subseg_orient;
  /*
  #define ssym(osub1, osub2) \
    (osub2).m_subseg = (osub1).m_subseg; \
    (osub2).m_subseg_orient = 1 - (osub1).m_subseg_orient
  */
}

void ribi::tricpp::SubSeg::ssymself(const SubSeg& osub1)
{
  osub.m_subseg_orient = 1 - osub.m_subseg_orient;
  /*
  #define ssymself(osub) \
  (osub).m_subseg_orient = 1 - (osub).m_subseg_orient
  */
}

