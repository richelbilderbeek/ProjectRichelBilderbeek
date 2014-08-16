#ifndef TRIANGLECPPSUBSEG_H
#define TRIANGLECPPSUBSEG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "trianglecppfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

// The subsegment data structure.  Each subsegment contains
//  two pointers to adjoining subsegments,
//WHY ONLY TWO? BOTH THE HEAD AND TAIL OF THE EDGE CAN BE CONNECTED TO MULTIPLE EDGES
//  plus four pointers to vertices,
//WHY FOUR VERTICES? AN EDGE IS A CONNECTION BETWEEN TWO POINTS
//  plus two pointers to adjoining triangles,
//  plus one boundary marker,
//  plus one segment number.

//typedef double **SubSeg; /* Really:  typedef subseg *subseg   */
struct Edge
{
  typedef boost::shared_ptr<Vertex> VertexPtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef std::vector<EdgePtr> Edges;

  Edge(const VertexPtr& from_vertex, const VertexPtr& to_vertex);

  Edges GetFromEdges();
  Edges GetToEdges();

  //double GetX() const noexcept;
  //double GetY() const noexcept;
  //bool IsDead() const noexcept;
  //void KillMe() noexcept;
  void SetBoundaryMarker(const int value) noexcept;
  //void SetSubSeg(const boost::shared_ptr<Edge>& subseg, const int index);
  //void SetTriangle(const boost::shared_ptr<Triangle>& triangle, const int index);
  //std::vector<boost::shared_ptr<Edge>> m_subsegs;
  //std::vector<boost::shared_ptr<Triangle>> m_triangles;

  private:
  Edges m_from_edges;
  const boost::shared_ptr<Vertex> m_from_vertex;
  Edges m_to_edges;
  const boost::shared_ptr<Vertex> m_to_vertex;
  int m_boundary_marker;
};

bool AreConnected(const Edge& lhs, const Edge& rhs) noexcept;

bool operator==(const Edge& lhs, const Edge& rhs) noexcept;

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

/*
///ssym() toggles the orientation of a subsegment.
void ssym(const Osub& osub1, Osub& osub2);
void ssymself(Osub& osub1);
//void SetsOrigin(Osub& osub, const SubSeg& subsegptr);
//void SetDest(Osub& osub, const SubSeg& subsegptr);
//void GetOrg(const Osub& osub, Vertex& vertexptr);
//void GetDest(const Osub& osub, Vertex& vertexptr);
void setsegorg(Osub& osub, Edge * subsegptr);
void setsegdest(Osub& osub, Edge * subsegptr);

///Dissolve a subsegment bond (from one side).  Note that the other
///  subsegment will still think it's connected to this subsegment.
void sdissolve(const Osub& osub, Edge m_m_dummysub);
//void subsegcopy(const SubSeg& osub1, SubSeg& osub2) { osub2 = osub1; }
//bool subsegequal(const SubSeg& osub1, const SubSeg& osub2);
bool deadsubseg(const Edge& t);
void killsubseg(Edge& t);
*/

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPSUBSEG_H
