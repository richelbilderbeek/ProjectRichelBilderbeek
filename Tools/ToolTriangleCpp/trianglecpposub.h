#ifndef TRIANGLECPPOSUB_H
#define TRIANGLECPPOSUB_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppsubseg.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* An oriented subsegment:  includes a pointer to a subsegment and an        */
/*   orientation.  The orientation denotes a side of the edge.  Hence, there */
/*   are two possible orientations.  By convention, the edge is always       */
/*   directed so that the "side" denoted is the right side of the edge.      */

struct Osub
{
  Osub();
  SubSeg& GetSubSeg(const int i);
  Triangle& GetTriangle(const int i);
  void SetSubSeg(SubSeg& subseg, const int i);
  void SetTriangle(Triangle& triangle, const int i);

  const SubSeg& GetDest() const noexcept;
  const SubSeg& GetOrigin() const noexcept;

  int GetMark() const noexcept { return m_mark; }
  void SetMark(const int value) noexcept { m_mark = value; }
  void SetOrient(const int orient) noexcept;

  void SetDest(const SubSeg subseg) noexcept;
  void SetOrigin(const SubSeg subseg) noexcept;

  void SetSubsegOrient(const int subseg_orient) noexcept;
  std::vector<SubSeg> m_subseg;
  std::vector<Triangle> m_triangles;
  private:
  int morient;
  /// Ranges from 0 to 1
  int m_subseg_orient;
  int m_mark;
};


//These primitives read or set a boundary marker.  Boundary markers are
//  used to hold user-defined tags for setting boundary conditions in
//  finite element solvers.

//int mark(const Osub& osub);
//void setmark(const Osub& osub, const int value);

///Bond two subsegments together.
void sbond(Osub& osub1, Osub& osub2);
void GetOrigin(const Osub& osub, Vertex& vertexptr);
void GetDest(const Osub& osub, Vertex& vertexptr);
///spivot() finds the other subsegment (from the same segment) that shares
///  the same origin.
void spivot(Osub& osub1, Osub& osub2, SubSeg& sptr);
void spivotself(Osub& osub1, SubSeg& sptr);
void snext(Osub& osub1, Osub& osub2, SubSeg& sptr);
void snextself(Osub& osub, SubSeg& sptr);

//tspivot() finds a subsegment abutting a triangle.
void tspivot(Otri& otri, Osub& osub);
void stpivot(Osub& osub, Otri& otri);
void tsbond(Otri& otri, Osub& osub);
void tsdissolve(Otri& otri, SubSeg& m_m_dummysub);
void stdissolve(Osub& osub, Triangle& m_m_dummytri);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPOSUB_H
