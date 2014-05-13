#ifndef TRIANGLECPPTRIANGLE_H
#define TRIANGLECPPTRIANGLE_H

#include <vector>
#include "trianglecppfwd.h"

namespace ribi {
namespace tricpp {

/* The triangle data structure.  Each triangle contains three pointers to    */
/*   adjoining triangles, plus three pointers to vertices, plus three        */
/*   pointers to subsegments (declared below; these pointers are usually     */
/*   `dummysub').  It may or may not also contain user-defined attributes    */
/*   and/or a floating-point "area constraint."  It may also contain extra   */
/*   pointers for nodes, when the user asks for high-order elements.         */
/*   Because the size and structure of a `triangle' is not decided until     */
/*   runtime, I haven't simply declared the type `triangle' as a struct.     */

//typedef double **Triangle;
struct Triangle
{
  void SetTriangle(Triangle * triangle, const int index); //If the lvalue of operator[] needed to be used
  void SetSubSeg(SubSeg * subseg, const int index); //If the lvalue of operator[] needed to be used
  Triangle * operator[](const int i);
  const Triangle * operator[](const int i) const;
  Vertex GetOrg();
  bool IsDead() const noexcept;
  void KillMe() const noexcept;

  std::vector<Triangle *> m_triangles;
  std::vector<SubSeg *> m_subsegs;
};

//These primitives determine or set the origin, destination, or apex of a
//triangle.


//Check or set a triangle's deallocation.  Its second pointer is set to
//  NULL to indicate that it is not allocated.  (Its first pointer is used
//  for the stack of dead items.)  Its fourth pointer (its first vertex)
//  is set to NULL in case a `badtriang' structure points to it.

//#define deadtri(tria)  ((tria)[1] == (Triangle) NULL)
//bool deadtri(const Triangle& t) { return t[1] == nullptr; }

//void killtri(const Triangle& t) { t[1] = nullptr; t[3] = nullptr; }

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPTRIANGLE_H
