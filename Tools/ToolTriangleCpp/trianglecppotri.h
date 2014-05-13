#ifndef TRIANGLECPPOTRI_H
#define TRIANGLECPPOTRI_H

#include "trianglecpptriangle.h"
#include "trianglecppfwd.h"

namespace ribi {
namespace tricpp {

/* An oriented triangle:  includes a pointer to a triangle and orientation.  */
/*   The orientation denotes an edge of the triangle.  Hence, there are      */
/*   three possible orientations.  By convention, each edge always points    */
/*   counterclockwise about the corresponding triangle.                      */

struct Otri
{
  Otri();
  Triangle * m_tri;
  int m_orient; /* Ranges from 0 to 2. */
};

//Vertex * GetOrg(const Otri& otri)
//{
//  return otri.m_tri[0][((otri.m_orient + 1) % 3) + 3];
//}

/*
#define org(otri, vertexptr)                                                  \
  vertexptr = (Vertex) (otri).m_tri[plus1mod3_cpp[(otri).m_orient] + 3]
*/

//Vertex GetDest(const Otri& otri) { return otri.m_tri[0][((otri.m_orient - 1 + 3) % 3) + 3]; }

#define dest(otri, vertexptr)                                                 \
  vertexptr = (Vertex) (otri).m_tri[minus1mod3_cpp[(otri).m_orient] + 3]

#define apex(otri, vertexptr)                                                 \
  vertexptr = (Vertex) (otri).m_tri[(otri).m_orient + 3]

#define setorg(otri, vertexptr)                                               \
  (otri).m_tri[plus1mod3_cpp[(otri).m_orient] + 3] = (Triangle) vertexptr

#define setdest(otri, vertexptr)                                              \
  (otri).m_tri[minus1mod3_cpp[(otri).m_orient] + 3] = (Triangle) vertexptr

#define setapex(otri, vertexptr)                                              \
  (otri).m_tri[(otri).m_orient + 3] = (Triangle) vertexptr

/* Bond two triangles together.                                              */

#define bond(otri1, otri2)                                                    \
  (otri1).m_tri[(otri1).m_orient] = encode(otri2);                                \
  (otri2).m_tri[(otri2).m_orient] = encode(otri1)

/* Dissolve a bond (from one side).  Note that the other triangle will still */
/*   think it's connected to this triangle.  Usually, however, the other     */
/*   triangle is being deleted entirely, or bonded to another triangle, so   */
/*   it doesn't matter.                                                      */

#define dissolve(otri)                                                        \
  (otri).m_tri[(otri).m_orient] = (Triangle) m.m_dummytri

/* Copy an oriented triangle.                                                */

#define otricopy(otri1, otri2)                                                \
  (otri2).m_tri = (otri1).m_tri;                                                  \
  (otri2).m_orient = (otri1).m_orient

/* Test for equality of oriented triangles.                                  */

#define otriequal(otri1, otri2)                                               \
  (((otri1).m_tri == (otri2).m_tri) &&                                            \
   ((otri1).m_orient == (otri2).m_orient))

/* Primitives to infect or cure a triangle with the virus.  These rely on    */
/*   the assumption that all subsegments are aligned to four-byte boundaries.*/

#define infect(otri)                                                          \
  (otri).m_tri[6] = (Triangle)                                                  \
                    ((unsigned long) (otri).m_tri[6] | (unsigned long) 2l)

#define uninfect(otri)                                                        \
  (otri).m_tri[6] = (Triangle)                                                  \
                    ((unsigned long) (otri).m_tri[6] & ~ (unsigned long) 2l)

/* Test a triangle for viral infection.                                      */

#define infected(otri)                                                        \
  (((unsigned long) (otri).m_tri[6] & (unsigned long) 2l) != 0l)

/* Check or set a triangle's attributes.                                     */

///Returns the attnum-th attribute, the double at m.m_elemattribindex + attnum
#define elemattribute(otri, attnum)                                           \
  ((double *) (otri).m_tri)[m.m_elemattribindex + (attnum)]

///Set the attnum-th attribute with a value
#define setelemattribute(otri, attnum, value)                                 \
  ((double *) (otri).m_tri)[m.m_elemattribindex + (attnum)] = value

/* Check or set a triangle's maximum area bound.                             */

#define areabound(otri)  ((double *) (otri).m_tri)[m.m_areaboundindex]

#define setareabound(otri, value)                                             \
  ((double *) (otri).m_tri)[m.m_areaboundindex] = value


} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPOTRI_H
