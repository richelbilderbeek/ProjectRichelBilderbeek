#ifndef TRIANGLECPPOTRI_H
#define TRIANGLECPPOTRI_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <string>
#include <boost/shared_ptr.hpp>
#include "trianglecpptriangle.h"
#include "trianglecppfwd.h"
#include "trianglecppvertex.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/* An oriented triangle:  includes a pointer to a triangle and orientation.  */
/*   The orientation denotes an edge of the triangle.  Hence, there are      */
/*   three possible orientations.  By convention, each edge always points    */
/*   counterclockwise about the corresponding triangle.                      */
struct Otri
{
  Otri();
  //Triangle * operator[](const int index) noexcept;
  const Vertex& GetApex() const noexcept;
  double GetAreaBound() const noexcept { return m_area_bound; }
  const Vertex& GetDest() const noexcept;
  double GetElemAttrib(const int index);
  const Vertex& GetOrigin() const noexcept;
  void GetDest(const Vertex& GetDest) noexcept;
  void GetOrigin(const Vertex& origin) noexcept;

  void SetApex(const Vertex& apex) noexcept { m_apex = apex; }
  void SetAreaBound(const double area_bound) noexcept { m_area_bound = area_bound; }
  void SetDest(const Vertex& dest) noexcept { m_dest = dest; }
  void SetElemAttrib(const double value, const int index);
  void SetOrigin(const Vertex& origin) noexcept { m_origin = origin; }
  void SetSubSeg(const boost::shared_ptr<SubSeg>& subseg, const int index) noexcept;
  void SetTriangle(const boost::shared_ptr<Triangle>& triangle, const int index) noexcept;
  //operator[](const int index) const noexcept;
  int GetOrient() const noexcept { return m_orient; }
  void SetOrient(const int orient) noexcept;

  Vertex m_apex;
  double m_area_bound;
  std::vector<double> m_attributes;
  Vertex m_dest;
  int m_orient; /// Ranges from 0 to 2
  Vertex m_origin;
  std::vector<boost::shared_ptr<SubSeg>> m_subsegs;
  std::vector<boost::shared_ptr<Triangle>> m_triangles; //Must be std::vector
};


void GetOrigin(const Otri& otri, Vertex& vertexptr);
void GetDest(const Otri& otri, Vertex& vertexptr);
//void GetApex(const Otri& otri, Vertex& vertexptr);
//void SetOrigin(Otri& otri, const Vertex& vertexptr);
void SetDest(Otri& otri, const Vertex& vertexptr);
void SetApex(Otri& otri, const Vertex& vertexptr);
// Bond two triangles together
void bond(Otri& otri1, Otri& otri2);
// Dissolve a bond (from one side).  Note that the other triangle will still
//   think it's connected to this triangle.  Usually, however, the other
//   triangle is being deleted entirely, or bonded to another triangle, so
//   it doesn't matter.
void dissolve(Otri& otri, Triangle * m_m_dummytri);
//void otricopy(const Otri& otri1, Otri& otri2);
//bool otriequal(const Otri& otri1, const Otri& otri2);
void infect(Otri& otri);
void uninfect(Otri& otri);
bool infected(Otri& otri);
double elemattribute(Otri& otri, int attnum);
void setelemattribute(Otri& otri, const int attnum, const double value);
double areabound(Otri& otri);
void setareabound(Otri& otri, const double value);
bool operator==(const Otri& lhs, const Otri& rhs) noexcept;
bool operator!=(const Otri& lhs, const Otri& rhs) noexcept;
void decode(const std::string& s, Otri& otri);
std::string encode(const Otri& /*otri*/);
void sym(const Otri& otri1, Otri& otri2);
void symself(Otri& otri);
void lnext(Otri& otri1, Otri& otri2);
void lnextself(Otri& otri);
void lprev(Otri& otri1, Otri& otri2);
void lprevself(Otri& otri);
void onext(Otri& otri1, Otri& otri2);
void onextself(Otri& otri);
void oprev(Otri& otri1, Otri& otri2);
void oprevself(Otri& otri);
void dnext(Otri& otri1, Otri& otri2);
void dnextself(Otri& otri);
void dprev(Otri& otri1, Otri& otri2);
void dprevself(Otri& otri);
void rnext(Otri& otri1, Otri& otri2);
void rnextself(Otri& otri);
void rprev(Otri& otri1, Otri& otri2);
void rprevself(Otri& otri);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPOTRI_H
