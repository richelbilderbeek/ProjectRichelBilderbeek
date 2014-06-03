#include "trianglecppedge.h"

ribi::tricpp::Edge::Edge(const VertexPtr& from_vertex, const VertexPtr& to_vertex)
  : m_from_vertex(from_vertex),
    m_to_vertex(to_vertex)
{

}

/*
ribi::tricpp::Edge::Edge()
  :
    m_subsegs{},
    m_triangles{},
    m_boundary_marker{8}
{

}
*/

/*
bool ribi::tricpp::Edge::IsDead() const noexcept
{
  //bool deadsubseg(const SubSeg& t) { return t[1] == nullptr; }
  assert(m_triangles.size() > 1);
  return m_triangles[1] == nullptr;
}

void ribi::tricpp::Edge::KillMe() noexcept
{
  //void killsubseg(const SubSeg& t) { t[1] = nullptr; t[2] = nullptr; }
  assert(m_triangles.size() > 2);
  m_triangles[1] = nullptr;
  m_triangles[2] = nullptr;
  assert(IsDead());
}
*/
void ribi::tricpp::Edge::SetBoundaryMarker(const int value)
{
  //* (int *) (m.m_dummysub + 8) = 0;
  m_boundary_marker = value;
}

/*
void ribi::tricpp::Edge::SetSubSeg(Edge * const subseg, const int index)
{
  assert(index >= 0);
  assert(index  < 6 && "But not sure yet...");
  assert(index < static_cast<int>(m_subsegs.size()));
  m_subsegs[index] = subseg;
}

void ribi::tricpp::Edge::SetTriangle(Triangle * const triangle, const int index)
{
  assert(index >= 6);
  assert(index  < 8 && "But not sure yet...");
  assert(index < static_cast<int>(m_triangles.size()));
  m_triangles[index] = triangle;
}
*/



void ribi::tricpp::ssym(const Osub& osub1, Osub& osub2)
{
  osub2.Ssym(osub1);

  //osub2.m_subseg = osub1.m_subseg;
  //osub2.m_subseg_orient = 1 - osub1.m_subseg_orient;
  /*
  #define ssym(osub1, osub2) \
    (osub2).m_subseg = (osub1).m_subseg; \
    (osub2).m_subseg_orient = 1 - (osub1).m_subseg_orient
  */
}

void ribi::tricpp::ssymself(Osub& osub1)
{
  osub1.Ssymself();
  //osub.m_subseg_orient = 1 - osub.m_subseg_orient;
  /*
  #define ssymself(osub) \
  (osub).m_subseg_orient = 1 - (osub).m_subseg_orient
  */
}

/*
void ribi::tricpp::GetDest(Osub& osub, Vertex * vertexptr)
{
  //Does not do anything yet
  vertexptr = osub.m_subseg[3 - osub.m_subseg_orient];
}
*/
/*
#define sdest(osub, vertexptr) \
  vertexptr = (Vertex) (osub).m_subseg[3 - (osub).m_subseg_orient]
*/

/*
void ribi::tricpp::SetsOrigin(Osub& osub, const SubSeg & subsegptr)
{
  osub.SetOrigin(subsegptr);
  //osub.m_subseg[2 + osub.m_subseg_orient] = subsegptr;
}
*/

/*
#define setsorg(osub, vertexptr) \
  (osub).m_subseg[2 + (osub).m_subseg_orient] = (SubSeg) vertexptr
*/

/*
void ribi::tricpp::SetDest(Osub& osub, const SubSeg & subsegptr)
{
  osub.SetDest(subsegptr);
  //osub.m_subseg[3 - (osub).m_subseg_orient] = subsegptr;
}
*/
/*
#define setsdest(osub, vertexptr) \
  (osub).m_subseg[3 - (osub).m_subseg_orient] = (SubSeg) vertexptr
*/

/*
void ribi::tricpp::GetOrg(const Osub& osub, Vertex& vertexptr)
{
  vertexptr = osub.GetOrigin();
  //vertexptr = osub.m_subseg[4 + (osub).m_subseg_orient];
}
*/
/*
#define segorg(osub, vertexptr) \
  vertexptr = (Vertex) (osub).m_subseg[4 + (osub).m_subseg_orient]
*/
/*
void ribi::tricpp::GetDest(const Osub& osub, Vertex& vertexptr)
{
  vertexptr = osub.GetDest();
  //vertexptr = osub.m_subseg[5 - (osub).m_subseg_orient];
}
*/
/*
#define segdest(osub, vertexptr) \
  vertexptr = (Vertex) (osub).m_subseg[5 - (osub).m_subseg_orient]
*/

void ribi::tricpp::setsegorg(Osub& osub, Edge * subsegptr)
{
  osub.m_subseg[4 + osub.m_subseg_orient] = subsegptr;
}

/*
#define setsegorg(osub, vertexptr) \
  (osub).m_subseg[4 + (osub).m_subseg_orient] = (SubSeg) vertexptr
*/

void ribi::tricpp::setsegdest(Osub& osub, Edge * subsegptr)
{
  osub.m_subseg[5 - osub.m_subseg_orient] = vertexptr;
}

/*
#define setsegdest(osub, vertexptr) \
  (osub).m_subseg[5 - (osub).m_subseg_orient] = (SubSeg) vertexptr
*/

void ribi::tricpp::sdissolve(const Osub& osub, Edge m_m_dummysub)
{
  osub.m_subseg[osub.m_subseg_orient] = m.m_dummysub;
}

/*
#define sdissolve(osub) \
  (osub).m_subseg[(osub).m_subseg_orient] = (SubSeg) m.m_dummysub
*/


/*
#define subsegcopy(osub1, osub2) \
  (osub2).m_subseg = (osub1).m_subseg; \
  (osub2).m_subseg_orient = (osub1).m_subseg_orient
*/

//void ribi::tricpp::subsegcopy(const SubSeg& osub1, SubSeg& osub2) { osub2 = osub1; }

//Test for equality of subsegments.

//bool ribi::tricpp::subsegequal(const SubSeg& osub1, const SubSeg& osub2) { return osub1 == osub2; }

/*
#define subsegequal(osub1, osub2) \
  (((osub1).ss == (osub2).ss) && \
   ((osub1).m_subseg_orient == (osub2).m_subseg_orient))
*/

//Check or set a subsegment's deallocation.  Its second pointer is set to
//  NULL to indicate that it is not allocated.  (Its first pointer is used
//  for the stack of dead items.)  Its third pointer (its first vertex)
//  is set to NULL in case a `badsubseg' structure points to it.

bool ribi::tricpp::deadsubseg(const Edge& t) { return t.IsDead(); }
//#define deadsubseg(sub)  ((sub)[1] == (SubSeg) NULL)

void ribi::tricpp::killsubseg(Edge& t) { t.KillMe(); }

bool ribi::tricpp::AreConnected(const Edge& lhs, const Edge& rhs) noexcept
{
  return
       lhs.GetFromVertex() == rhs.GetFromVertex()
    || lhs.GetFromVertex() == rhs.GetToVertex()
    || lhs.GetToVertex()   == rhs.GetFromVertex()
    || lhs.GetToVertex()   == rhs.GetToVertex()
  ;
}
