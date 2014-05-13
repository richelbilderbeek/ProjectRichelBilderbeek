#ifndef TRIANGLECPPSUBSEG_H
#define TRIANGLECPPSUBSEG_H

#include <vector>
#include "trianglecppfwd.h"

namespace ribi {
namespace tricpp {

/* The subsegment data structure.  Each subsegment contains two pointers to  */
/*   adjoining subsegments, plus four pointers to vertices, plus two         */
/*   pointers to adjoining triangles, plus one boundary marker, plus one     */
/*   segment number.                                                         */

//typedef double **SubSeg; /* Really:  typedef subseg *subseg   */
struct SubSeg
{
  bool IsDead() const noexcept;
  void KillMe() noexcept;
  void SetSubSeg(SubSeg * const subseg, const int index);
  void SetTriangle(Triangle * const triangle, const int index);

  private:
  std::vector<SubSeg*> m_subsegs;
  std::vector<Triangle*> m_triangles;
};

bool operator==(const SubSeg& lhs, const SubSeg& rhs) noexcept;

//sdecode() converts a pointer to an oriented subsegment.  The orientation
//  is extracted from the least significant bit of the pointer.  The two
//  least significant bits (one for orientation, one for viral infection)
//  are masked out to produce the real pointer.
/*
#define sdecode(sptr, osub)                                                   \
  (osub).m_subseg_orient = (int) ((unsigned long) (sptr) & (unsigned long) 1l);      \
  (osub).m_subseg = (SubSeg *)                                                      \
              ((unsigned long) (sptr) & ~ (unsigned long) 3l)
*/

//sencode() compresses an oriented subsegment into a single pointer.  It
//  relies on the assumption that all subsegments are aligned to two-byte
//  boundaries, so the least significant bit of (osub).m_subseg is zero.
/*
#define sencode(osub)                                                         \
  (SubSeg) ((unsigned long) (osub).m_subseg | (unsigned long) (osub).m_subseg_orient)
*/

///ssym() toggles the orientation of a subsegment.
void ssym(const SubSeg& osub1, SubSeg& osub2);

void ssymself(const SubSeg& osub1);

//spivot() finds the other subsegment (from the same segment) that shares
//  the same origin.

#define spivot(osub1, osub2)                                                  \
  sptr = (osub1).m_subseg[(osub1).m_subseg_orient];                                        \
  sdecode(sptr, osub2)

#define spivotself(osub)                                                      \
  sptr = (osub).m_subseg[(osub).m_subseg_orient];                                          \
  sdecode(sptr, osub)

//snext() finds the next subsegment (from the same segment) in sequence;
//  one whose origin is the input subsegment's destination.

#define snext(osub1, osub2)                                                   \
  sptr = (osub1).ss[1 - (osub1).m_subseg_orient];                                    \
  sdecode(sptr, osub2)

#define snextself(osub)                                                       \
  sptr = (osub).m_subseg[1 - (osub).m_subseg_orient];                                      \
  sdecode(sptr, osub)

//These primitives determine or set the origin or destination of a
//  subsegment or the segment that includes it.

#define sorg(osub, vertexptr)                                                 \
  vertexptr = (Vertex) (osub).m_subseg[2 + (osub).m_subseg_orient]

#define sdest(osub, vertexptr)                                                \
  vertexptr = (Vertex) (osub).m_subseg[3 - (osub).m_subseg_orient]

#define setsorg(osub, vertexptr)                                              \
  (osub).m_subseg[2 + (osub).m_subseg_orient] = (SubSeg) vertexptr

#define setsdest(osub, vertexptr)                                             \
  (osub).m_subseg[3 - (osub).m_subseg_orient] = (SubSeg) vertexptr

#define segorg(osub, vertexptr)                                               \
  vertexptr = (Vertex) (osub).m_subseg[4 + (osub).m_subseg_orient]

#define segdest(osub, vertexptr)                                              \
  vertexptr = (Vertex) (osub).m_subseg[5 - (osub).m_subseg_orient]

#define setsegorg(osub, vertexptr)                                            \
  (osub).m_subseg[4 + (osub).m_subseg_orient] = (SubSeg) vertexptr

#define setsegdest(osub, vertexptr)                                           \
  (osub).m_subseg[5 - (osub).m_subseg_orient] = (SubSeg) vertexptr

//These primitives read or set a boundary marker.  Boundary markers are
//  used to hold user-defined tags for setting boundary conditions in
//  finite element solvers.

#define mark(osub)  (* (int *) ((osub).m_subseg + 8))

#define setmark(osub, value)                                                  \
  * (int *) ((osub).m_subseg + 8) = value

//Bond two subsegments together.

#define sbond(osub1, osub2)                                                   \
  (osub1).m_subseg[(osub1).m_subseg_orient] = sencode(osub2);                              \
  (osub2).m_subseg[(osub2).m_subseg_orient] = sencode(osub1)

//Dissolve a subsegment bond (from one side).  Note that the other
//  subsegment will still think it's connected to this subsegment.

#define sdissolve(osub)                                                       \
  (osub).m_subseg[(osub).m_subseg_orient] = (SubSeg) m.m_dummysub

//Copy a subsegment.

/*
#define subsegcopy(osub1, osub2)                                              \
  (osub2).m_subseg = (osub1).m_subseg;                                                    \
  (osub2).m_subseg_orient = (osub1).m_subseg_orient
*/

void subsegcopy(const SubSeg& osub1, SubSeg& osub2) { osub2 = osub1; }

//Test for equality of subsegments.

bool subsegequal(const SubSeg& osub1, const SubSeg& osub2) { return osub1 == osub2; }

/*
#define subsegequal(osub1, osub2)                                             \
  (((osub1).ss == (osub2).ss) &&                                              \
   ((osub1).m_subseg_orient == (osub2).m_subseg_orient))
*/

//Check or set a subsegment's deallocation.  Its second pointer is set to
//  NULL to indicate that it is not allocated.  (Its first pointer is used
//  for the stack of dead items.)  Its third pointer (its first vertex)
//  is set to NULL in case a `badsubseg' structure points to it.

//#define deadsubseg(sub)  ((sub)[1] == (SubSeg) NULL)
bool deadsubseg(const SubSeg& t) { return t.IsDead(); }

void killsubseg(SubSeg& t) { t.KillMe(); }




} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPSUBSEG_H
