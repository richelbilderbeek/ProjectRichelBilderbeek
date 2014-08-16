#ifndef TRIANGLECPPTRIANGLE_H
#define TRIANGLECPPTRIANGLE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "trianglecppfwd.h"
#include "trianglecpptriangle.h"
#include "trianglecppedge.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

// The triangle data structure.  Each triangle contains three pointers to
//   adjoining triangles, plus three pointers to vertices, plus three
//   pointers to subsegments (declared below; these pointers are usually
//   `dummysub').  It may or may not also contain user-defined attributes
//   and/or a floating-point "area constraint."  It may also contain extra
//   pointers for nodes, when the user asks for high-order elements.
//   Because the size and structure of a `triangle' is not decided until
//   runtime, I haven't simply declared the type `triangle' as a struct.

//typedef double **Triangle;
struct Triangle
{
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef std::array<boost::shared_ptr<Edge>,3> Edges;
  //Triangle(const EdgePtr& a, const EdgePtr& b, const EdgePtr& c);
  Triangle(const Edges& edges);


  //void SetTriangle(const Triangle& triangle, const int index); //If the lvalue of operator[] needed to be used
  //void SetSubSeg(const Edge& subseg, const int index); //If the lvalue of operator[] needed to be used
  //Triangle& operator[](const int i) noexcept;
  //const Triangle& operator[](const int i) const noexcept;
  //Vertex GetOrg();
  //bool IsDead() const noexcept;
  //void KillMe() noexcept;

  //bool m_is_dead;
  private:
  const Edges m_edges;
  //Triangle(const EdgePtr& a, const EdgePtr& b, const EdgePtr& c);

  //std::vector<boost::shared_ptr<Edge>> m_subsegs;
  //std::vector<boost::shared_ptr<Triangle>> m_triangles;
};

bool operator==(const Triangle& lhs, const Triangle& rhs) noexcept;
bool operator!=(const Triangle& lhs, const Triangle& rhs) noexcept;

//These primitives determine or set the origin, destination, or apex of a
//triangle.


//Check or set a triangle's deallocation.  Its second pointer is set to
//  NULL to indicate that it is not allocated.  (Its first pointer is used
//  for the stack of dead items.)  Its fourth pointer (its first vertex)
//  is set to NULL in case a `badtriang' structure points to it.

//#define deadtri(tria)  ((tria)[1] == (Triangle) NULL)
//bool deadtri(const Triangle& t) { return t[1] == nullptr; }

//void killtri(const Triangle& t) { t[1] = nullptr; t[3] = nullptr; }

//boost::shared_ptr<Triangle> vertex2tri(Vertex& vx);
//Triangle vertex2tri(Vertex& vx);

//void setvertex2tri(Vertex& vx, const Triangle& value);
//void setvertex2tri(Vertex& vx, const boost::shared_ptr<Triangle>& value);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPTRIANGLE_H
