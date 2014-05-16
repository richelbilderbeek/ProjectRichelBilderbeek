#ifndef TRIANGLECPPSUBSEG_H
#define TRIANGLECPPSUBSEG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include "trianglecppfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* The subsegment data structure.  Each subsegment contains two pointers to  */
/*   adjoining subsegments, plus four pointers to vertices, plus two         */
/*   pointers to adjoining triangles, plus one boundary marker, plus one     */
/*   segment number.                                                         */

//typedef double **SubSeg; /* Really:  typedef subseg *subseg   */
struct SubSeg
{
  SubSeg();
  bool IsDead() const noexcept;
  void KillMe() noexcept;
  void SetBoundaryMarker(const int value) noexcept;
  void SetSubSeg(SubSeg * const subseg, const int index);
  void SetTriangle(Triangle * const triangle, const int index);
  std::vector<SubSeg> m_subsegs;
  std::vector<Triangle> m_triangles;

  private:
  int m_boundary_marker;
};

bool operator==(const SubSeg& lhs, const SubSeg& rhs) noexcept;

//sdecode() converts a pointer to an oriented subsegment.  The orientation
//  is extracted from the least significant bit of the pointer.  The two
//  least significant bits (one for orientation, one for viral infection)
//  are masked out to produce the real pointer.
/*
#define sdecode(sptr, osub) \
  (osub).m_subseg_orient = (int) ((unsigned long) (sptr) & (unsigned long) 1l); \
  (osub).m_subseg = (SubSeg *) \
              ((unsigned long) (sptr) & ~ (unsigned long) 3l)
*/

//sencode() compresses an oriented subsegment into a single pointer.  It
//  relies on the assumption that all subsegments are aligned to two-byte
//  boundaries, so the least significant bit of (osub).m_subseg is zero.
/*
#define sencode(osub) \
  (SubSeg) ((unsigned long) (osub).m_subseg | (unsigned long) (osub).m_subseg_orient)
*/

///ssym() toggles the orientation of a subsegment.
void ssym(const Osub& osub1, Osub& osub2);
void ssymself(Osub& osub1);
//void SetsOrigin(Osub& osub, const SubSeg& subsegptr);
//void SetDest(Osub& osub, const SubSeg& subsegptr);
//void GetOrg(const Osub& osub, Vertex& vertexptr);
//void GetDest(const Osub& osub, Vertex& vertexptr);
void setsegorg(Osub& osub, SubSeg * subsegptr);
void setsegdest(Osub& osub, SubSeg * subsegptr);

///Dissolve a subsegment bond (from one side).  Note that the other
///  subsegment will still think it's connected to this subsegment.
void sdissolve(const Osub& osub, SubSeg m_m_dummysub);
//void subsegcopy(const SubSeg& osub1, SubSeg& osub2) { osub2 = osub1; }
//bool subsegequal(const SubSeg& osub1, const SubSeg& osub2);
bool deadsubseg(const SubSeg& t);
void killsubseg(SubSeg& t);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPSUBSEG_H
