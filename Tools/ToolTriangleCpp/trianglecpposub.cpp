#include "trianglecpposub.h"

ribi::tricpp::Osub::Osub()
  : m_subseg{nullptr},
    m_subseg_orient{0}
{

}


void ribi::tricpp::Osub::SetSubsegOrient(const int subseg_orient) noexcept
{
  /// Ranges from 0 to 1
  assert(subseg_orient >= 0);
  assert(subseg_orient  < 2);
  m_subseg_orient = subseg_orient;
}

//These primitives read or set a boundary marker.  Boundary markers are
//  used to hold user-defined tags for setting boundary conditions in
//  finite element solvers.

//#define mark(osub)  (* (int *) ((osub).m_subseg + 8))
/*
int ribi::tricpp::mark(const Osub& osub) { return osub.GetMark(); }
*/
//#define setmark(osub, value) \
//  * (int *) ((osub).m_subseg + 8) = value
/*
void ribi::tricpp::setmark(const Osub& osub, const int value) { return osub.SetMark(value); }
*/
//Bond two subsegments together.

void ribi::tricpp::sbond(Osub& osub1, Osub& osub2)
{
  osub1.m_subseg[osub1.m_subseg_orient] = sencode(osub2);
  osub2.m_subseg[osub2.m_subseg_orient] = sencode(osub1);
}

//#define sbond(osub1, osub2) \
//  (osub1).m_subseg[(osub1).m_subseg_orient] = sencode(osub2); \
//  (osub2).m_subseg[(osub2).m_subseg_orient] = sencode(osub1)



void ribi::tricpp::GetOrigin(const Osub& osub, Vertex& vertexptr)
{
  vertexptr = osub.GetOrigin();
  //Does not do anything yet
  //vertexptr = osub.m_subseg[2 + osub.m_subseg_orient;
}

/*
#define sorg(osub, vertexptr) \
  vertexptr = (Vertex) (osub).m_subseg[2 + (osub).m_subseg_orient]
*/

void ribi::tricpp::GetDest(const Osub& osub, Vertex& vertexptr)
{
  vertexptr = osub.GetDest();
  //Does not do anything yet
  //vertexptr = osub.m_subseg[3 - osub.m_subseg_orient];
}

/*
#define sdest(osub, vertexptr) \
  vertexptr = (Vertex) (osub).m_subseg[3 - (osub).m_subseg_orient]
*/

//spivot() finds the other subsegment (from the same segment) that shares
//  the same origin.

void ribi::tricpp::spivot(Osub& osub1, Osub& osub2, SubSeg& sptr)
{
  sptr = osub1.m_subseg[osub1.m_subseg_orient];
  sdecode(sptr, osub2);
}

/*
#define spivot(osub1, osub2) \
  sptr = (osub1).m_subseg[(osub1).m_subseg_orient]; \
  sdecode(sptr, osub2)
*/

void ribi::tricpp::spivotself(Osub& osub1, SubSeg& sptr)
{
  sptr = osub.m_subseg[osub.m_subseg_orient];
  sdecode(sptr, osub);
}

/*
#define spivotself(osub) \
  sptr = (osub).m_subseg[(osub).m_subseg_orient]; \
  sdecode(sptr, osub)
*/

//snext() finds the next subsegment (from the same segment) in sequence;
//  one whose origin is the input subsegment's destination.

void ribi::tricpp::snext(Osub& osub1, Osub& osub2, SubSeg& sptr)
{
  sptr = osub1.ss[1 - osub1.m_subseg_orient];
  sdecode(sptr, osub2);
}

/*
#define snext(osub1, osub2) \
  sptr = (osub1).ss[1 - (osub1).m_subseg_orient]; \
  sdecode(sptr, osub2)
*/

void ribi::tricpp::snextself(Osub& osub, SubSeg& sptr)
{
  assert(!"Does not change the pointer");
  sptr = (osub).m_subseg[1 - (osub).m_subseg_orient];
  sdecode(sptr, osub);
}

/*
#define snextself(osub) \
  sptr = (osub).m_subseg[1 - (osub).m_subseg_orient]; \
  sdecode(sptr, osub)
*/


//tspivot() finds a subsegment abutting a triangle.
void ribi::tricpp::tspivot(Otri& otri, Osub& osub)
{
  osub = otri.m_tri[6 + otri.m_orient];
  //sptr = (SubSeg) (otri).m_tri[6 + (otri).m_orient];
  //sdecode(sptr, osub)
}

/*
#define tspivot(otri, osub)                                             \
  sptr = (SubSeg) (otri).m_tri[6 + (otri).m_orient];                        \
  sdecode(sptr, osub)
*/

//stpivot() finds a triangle abutting a subsegment.  It requires that the
//  variable `ptr' of type `triangle' be defined.

void ribi::tricpp::stpivot(Osub& osub, Otri& otri)
{
  otri = m_subseg[6 + osub.m_subseg_orient];
  //ptr = (Triangle) (osub).m_subseg[6 + (osub).m_subseg_orient];
  //decode(ptr, otri);
}

/*
#define stpivot(osub, otri)                                             \
  ptr = (Triangle) (osub).m_subseg[6 + (osub).m_subseg_orient];                      \
  decode(ptr, otri)
*/

//Bond a triangle to a subsegment.

void ribi::tricpp::tsbond(Otri& otri, Osub& osub)
{
  otri.m_tri[6 + (otri).m_orient] = (Triangle) sencode(osub);
  osub.m_subseg[6 + (osub).m_subseg_orient] = (SubSeg) encode(otri);
}

/*
#define tsbond(otri, osub)                                              \
  (otri).m_tri[6 + (otri).m_orient] = (Triangle) sencode(osub);             \
  (osub).m_subseg[6 + (osub).m_subseg_orient] = (SubSeg) encode(otri)
*/

//Dissolve a bond (from the triangle side).

void ribi::tricpp::tsdissolve(Otri& otri, SubSeg& m_m_dummysub)
{
  otri.m_tri[6 + otri.m_orient] = m_m_dummysub;
}

/*
#define tsdissolve(otri)                                                \
  (otri).m_tri[6 + (otri).m_orient] = (Triangle) m.m_dummysub
*/

//Dissolve a bond (from the subsegment side).

void ribi::tricpp::stdissolve(Osub& osub, Triangle& m_m_dummytri)
{
  osub.m_subseg[6 + osub.m_subseg_orient] = m.m_dummytri;
}

/*
#define stdissolve(osub)                                                \
  (osub).m_subseg[6 + (osub).m_subseg_orient] = (SubSeg) m.m_dummytri
*/
