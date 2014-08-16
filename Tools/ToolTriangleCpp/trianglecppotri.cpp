#include "trianglecppotri.h"

ribi::tricpp::Otri::Otri()
  : m_apex{},
    m_area_bound{0.0},
    m_attributes{},
    m_dest{},
    m_is_infected{false},
    m_orient{0},
    m_origin{},
    m_subsegs{},
    m_triangles{}
{

}

boost::shared_ptr<ribi::tricpp::Triangle> ribi::tricpp::Otri::operator[](const int index) noexcept
{
  assert(index >= 0);
  assert(index >= 9 && "Just a guess");
  assert(index < 12);
  assert(index < static_cast<int>(m_triangles.size()));
  return m_triangles[index];
}

void ribi::tricpp::Otri::Dissolve(boost::shared_ptr<Triangle> m_m_dummytri)
{
  m_triangles[m_orient] = m.m_dummytri;
}

void ribi::tricpp::Otri::Dnext(const Otri& other)
{
  *this = CreateSym(other);
  //sym(otri1, otri2);

  Lprevself();
  //lprevself(otri2);
}

void ribi::tricpp::Otri::Dnextself()
{
  Symself();
  //symself(otri);

  Lprevself();
  //lprevself(otri);
}

void ribi::tricpp::Otri::Dprev(const Otri& other)
{
  SetLnext(other);
  //lnext(otri1, otri2);
  Symself();
  //symself(otri2);
}


void ribi::tricpp::Otri::SetLnext(const Otri& other)
{
  m_triangles = other.m_triangles;
  m_orient = other.m_orient + 1 % 3;
}

void ribi::tricpp::Otri::LnextSelf()
{
  m_orient = m_orient + 1 % 3;
}

void ribi::tricpp::Otri::Lprev(const Otri& other) const
{
  m_triangles = other.m_triangles;
  m_orient = other.m_orient + 2 % 3;
}

void ribi::tricpp::Otri::Lprevself()
{
  m_orient = m_orient + 2 % 3;
}

void ribi::tricpp::Otri::Onext(Otri& other)
{
  Lprev(other);
  //lprev(otri1, otri2);

  Symself();
  //symself(otri2);
}

void ribi::tricpp::Otri::Onextself(Otri& otri)
{
  Lprevself();
  //lprevself(otri);

  Symself();
  //symself(otri);
}

void ribi::tricpp::Otri::Oprev(Otri& other)
{
  *this = CreateSym(other);
  //sym(otri1, otri2);

  Lnextself();
  //lnextself(otri2);
}

void ribi::tricpp::Otri::Oprevself()
{
  Symself();
  //symself(otri);

  Lnextself();
  //lnextself(otri);
}


void ribi::tricpp::Otri::SetOrient(const int orient) noexcept
{
  assert(orient >= 0);
  assert(orient  < 3);
  m_orient = orient;
}

boost::shared_ptr<ribi::tricpp::Otri> ribi::tricpp::Otri::CreateSym(const Otri& other)
{
  return other.m_triangles[other.m_orient];
  //*this = other.m_triangles[other.m_orient];
  //otri2 = otri1.m_triangles[(otri1).m_orient];
  /*
  ptr = (otri1).m_tri[(otri1).m_orient];  \
  decode(ptr, otri2);
  */
}


void ribi::tricpp::Otri::Sym(const Otri& other)
{
  *this = other.m_triangles[other.m_orient];
  //otri2 = otri1.m_triangles[(otri1).m_orient];
  /*
  ptr = (otri1).m_tri[(otri1).m_orient];  \
  decode(ptr, otri2);
  */
}

void ribi::tricpp::Otri::Symself() noexcept
{
  //???
  *this = m_triangles[m_orient];
}

void ribi::tricpp::Otri::SetTriangle(const boost::shared_ptr<Triangle>& triangle, const int index) noexcept
{
  assert(index >= 0);
  assert(index >= 9 && "Just a guess");
  assert(index < 12);
  assert(index < static_cast<int>(m_triangles.size()));
  return m_triangles[index] = triangle;
}

boost::shared_ptr<ribi::tricpp::Osub> ribi::tricpp::Otri::CreateTspivot()
{
  boost::shared_ptr<Osub> osub = m_tri[6 + m_orient];
  return osub;
}

void ribi::tricpp::Otri::Tspivot(Osub& osub)
{
  osub = m_tri[6 + m_orient];
}




//Vertex * GetOrg(const Otri& otri)
//{
//  return otri.m_tri[0][((otri.m_orient + 1) % 3) + 3];
//}
/*
void ribi::tricpp::GetOrigin(const Otri& otri, Vertex& vertexptr)
{
  vertexptr = otri.GetOrigin();
  //otri.m_tri[plus1mod3_cpp[(otri).m_orient] + 3];
}
*/
/*
#define org(otri, vertexptr)                                                  \
  vertexptr = (Vertex) (otri).m_tri[plus1mod3_cpp[(otri).m_orient] + 3]
*/

//Vertex GetDest(const Otri& otri) { return otri.m_tri[0][((otri.m_orient - 1 + 3) % 3) + 3]; }

/*
void ribi::tricpp::GetDest(const Otri& otri, Vertex& vertexptr)
{
  vertexptr = otri.GetDest();
  //vertexptr = otri.m_tri[minus1mod3_cpp[(otri).m_orient] + 3];
}
*/

/*
#define dest(otri, vertexptr)                                                 \
  vertexptr = (Vertex) (otri).m_tri[minus1mod3_cpp[(otri).m_orient] + 3]
*/

/*
void ribi::tricpp::GetApex(const Otri& otri, Vertex& vertexptr)
{
  vertexptr = otri.GetApex();
  //vertexptr = otri.m_tri[(otri).m_orient + 3];
}
*/

/*
#define apex(otri, vertexptr)                                                 \
  vertexptr = (Vertex) (otri).m_tri[(otri).m_orient + 3]
*/


/*
void ribi::tricpp::SetOrigin(Otri& otri, const Vertex& vertexptr)
{
  otri.SetOrg(vertexptr);
  //otri.m_tri[plus1mod3_cpp[otri.m_orient] + 3] = vertexptr;
}
*/

/*
#define setorg(otri, vertexptr)                                               \
  (otri).m_tri[plus1mod3_cpp[(otri).m_orient] + 3] = (Triangle) vertexptr
*/

/*
void ribi::tricpp::SetDest(Otri& otri, const Vertex& vertexptr)
{
  otri.setDest(vertexptr);
  //otri.m_tri[minus1mod3_cpp[otri.m_orient] + 3] = vertexptr;
}
*/
/*
#define setdest(otri, vertexptr)                                              \
  (otri).m_tri[minus1mod3_cpp[(otri).m_orient] + 3] = (Triangle) vertexptr
*/

/*
void ribi::tricpp::SetApex(Otri& otri, const Vertex& vertexptr)
{
  otri.SetApex(vertexptr);
  //(otri).m_tri[(otri).m_orient + 3] = (Triangle) vertexptr;
}
*/
/*
#define setapex(otri, vertexptr)                                              \
  (otri).m_tri[(otri).m_orient + 3] = (Triangle) vertexptr
*/

/* Bond two triangles together.                                              */

void ribi::tricpp::Bond(boost::shared_ptr<Otri>& otri1, boost::shared_ptr<Otri>& otri2)
{
  otri1->m_triangles[otri1->m_orient] = otri2->m_tri[otri2->m_orient];
  otri2->m_triangles[otri2->m_orient] = otri1->m_tri[otri2->m_orient];


  //(otri1).m_triangles[otri1.m_orient] = encode(otri2);
  //(otri2).m_triangles[otri2.m_orient] = encode(otri1);
}

/*
#define bond(otri1, otri2)                                                    \
  (otri1).m_tri[(otri1).m_orient] = encode(otri2);                                \
  (otri2).m_tri[(otri2).m_orient] = encode(otri1)
*/

/* Dissolve a bond (from one side).  Note that the other triangle will still */
/*   think it's connected to this triangle.  Usually, however, the other     */
/*   triangle is being deleted entirely, or bonded to another triangle, so   */
/*   it doesn't matter.                                                      */

/*
void ribi::tricpp::dissolve(Otri& otri, Triangle * m_m_dummytri)
{
  (otri).m_triangles[(otri).m_orient] = m.m_dummytri;
}
*/
/*
#define dissolve(otri)                                                        \
  (otri).m_tri[(otri).m_orient] = (Triangle) m.m_dummytri
*/

/* Copy an oriented triangle.                                                */

/*
void ribi::tricpp::otricopy(const Otri& otri1, Otri& otri2)
{
  otri2 = otri1;
}
*/
/*
#define otricopy(otri1, otri2)                                                \
  (otri2).m_tri = (otri1).m_tri;                                                  \
  (otri2).m_orient = (otri1).m_orient
*/

/* Test for equality of oriented triangles.                                  */

/*
bool ribi::tricpp::otriequal(const Otri& otri1, const Otri& otri2)
{
  return otri1 == otri2;
}
*/

/*
#define otriequal(otri1, otri2)                                               \
  (((otri1).m_tri == (otri2).m_tri) &&                                            \
   ((otri1).m_orient == (otri2).m_orient))
*/

/* Primitives to infect or cure a triangle with the virus.  These rely on    */
/*   the assumption that all subsegments are aligned to four-byte boundaries.*/

/*
void ribi::tricpp::infect(Otri& otri)
{
  otri.SetInfected(true);

  //(otri).m_triangles[6] = (otri).m_triangles[6] | 2l;

}
*/
/*
#define infect(otri)                                                          \
  (otri).m_tri[6] = (Triangle)                                                  \
                    ((unsigned long) (otri).m_tri[6] | (unsigned long) 2l)

*/

/*
void ribi::tricpp::uninfect(Otri& otri)
{
  (otri).m_triangles[6] = otri.m_triangles[6] & ~ 2l;
}
*/
/*
#define uninfect(otri)                                                        \
  (otri).m_tri[6] = (Triangle)                                                  \
                    ((unsigned long) (otri).m_tri[6] & ~ (unsigned long) 2l)
*/

/* Test a triangle for viral infection.                                      */

/*
bool ribi::tricpp::infected(Otri& otri)
{
  return otri.GetInfected();
  //return ((otri.m_triangles[6] & (unsigned long) 2l) != 0l)
}
*/
/*
#define infected(otri)                                                        \
  (((unsigned long) (otri).m_tri[6] & (unsigned long) 2l) != 0l)
*/

/* Check or set a triangle's attributes.                                     */

///Returns the attnum-th attribute, the double at m.m_elemattribindex + attnum
/*
double ribi::tricpp::elemattribute(Otri& otri, int attnum)
{
  return otri.GetElemAttrib(attnum);
  //return otri.m_tri[m.m_elemattribindex + attnum];
}
*/
/*
#define elemattribute(otri, attnum)                                           \
  ((double *) (otri).m_tri)[m.m_elemattribindex + (attnum)]
*/
/*
void ribi::tricpp::setelemattribute(Otri& otri, const int attnum, const double value)
{
  otri.SetElemAttrib(value,attnum);
  //((double *) (otri).m_tri)[m.m_elemattribindex + (attnum)] = value
}
*/
///Set the attnum-th attribute with a value
/*
#define setelemattribute(otri, attnum, value)                                 \
  ((double *) (otri).m_tri)[m.m_elemattribindex + (attnum)] = value
*/

/* Check or set a triangle's maximum area bound.                             */

/*
double ribi::tricpp::areabound(Otri& otri)
{
  return otri.GetAreaBound();
  //  ((double *) (otri).m_tri)[m.m_areaboundindex]
}
*/

/*
#define areabound(otri)  ((double *) (otri).m_tri)[m.m_areaboundindex]
*/
/*
void ribi::tricpp::setareabound(Otri& otri, const double value)
{
  otri.SetAreaBound(value);
  //((double *) (otri).m_tri)[m.m_areaboundindex] = value
}
*/
/*
#define setareabound(otri, value)                                             \
  ((double *) (otri).m_tri)[m.m_areaboundindex] = value
*/































//decode() converts a pointer to an oriented triangle.  The orientation is
//  extracted from the two least significant bits of the pointer.
/*
void ribi::tricpp::decode(const std::string& s, Otri& otri)
{
  otri.m_orient = (int) ((unsigned long) (ptr) & (unsigned long) 3l); \
  otri.m_tri = (Triangle *) ((unsigned long) (ptr) ^ (unsigned long) (otri).m_orient)
}
*/

/*
#define decode(ptr, otri) \
  (otri).m_orient = (int) ((unsigned long) (ptr) & (unsigned long) 3l); \
  (otri).m_tri = (Triangle *) \
                  ((unsigned long) (ptr) ^ (unsigned long) (otri).m_orient)
*/

//encode() compresses an oriented triangle into a single pointer.  It
//  relies on the assumption that all triangles are aligned to four-byte
//  boundaries, so the two least significant bits of (otri).m_tri are zero.
/*
std::string ribi::tricpp::encode(const Otri& otri)
{
  assert(!"Get rid of this");
  return "";
  //returns the Triangle otri.m_tri[otri.m_orient]
}
*/
/*
#define encode(otri)  \
  (Triangle) ((unsigned long) (otri).m_tri | (unsigned long) (otri).m_orient)
*/

//The following handle manipulation primitives are all described by Guibas
//  and Stolfi.  However, Guibas and Stolfi use an edge-based data
//  structure, whereas I use a triangle-based data structure.

//sym() finds the abutting triangle, on the same edge.  Note that the edge
//  direction is necessarily reversed, because the handle specified by an
//  oriented triangle is directed counterclockwise around the triangle.
/*
void ribi::tricpp::sym(const Otri& otri1, Otri& otri2)
{
  otri2.Sym(otri1);
  //otri2 = otri1.m_triangles[(otri1).m_orient];

  ptr = (otri1).m_tri[(otri1).m_orient]; \
  decode(ptr, otri2);

}
*/
/*
#define sym(otri1, otri2) \
  ptr = (otri1).m_tri[(otri1).m_orient];  \
  decode(ptr, otri2);
*/

/*
void ribi::tricpp::symself(Otri& otri)
{
  otri.Symself();
  //otri = otri.m_triangles[(otri).m_orient];

  //ptr = (otri).m_tri[(otri).m_orient];
  //decode(ptr, otri);

}
*/
/*
#define symself(otri) \
  ptr = (otri).m_tri[(otri).m_orient];  \
  decode(ptr, otri);
*/

//lnext() finds the next edge (counterclockwise) of a triangle.

/*
void ribi::tricpp::lnext(const Otri& otri1, Otri& otri2)
{
  otri2.lnext(otri1);
  //otri2.m_triangles = otri1.m_triangles;
  //otri2.m_orient = otri1.m_orient + 1 % 3;
}
*/

/*
#define lnext(otri1, otri2) \
  (otri2).m_tri = (otri1).m_tri;  \
  (otri2).m_orient = plus1mod3_cpp[(otri1).m_orient]
*/
/*
void ribi::tricpp::lnextself(Otri& otri)
{
  otri.Lnextself();

  //otri.m_orient = otri.m_orient + 1 % 3;
  //(otri).m_orient = plus1mod3_cpp[(otri).m_orient]
}
*/
/*
#define lnextself(otri) \
  (otri).m_orient = plus1mod3_cpp[(otri).m_orient]
*/

//lprev() finds the previous edge (clockwise) of a triangle.

/*
void ribi::tricpp::lprev(Otri& otri1, Otri& otri2)
{
  otri2.Lprev(otri1);
  //(otri2).m_triangles = otri1.m_triangles;
  //(otri2).m_orient = otri1.m_orient + 2 % 3;
}
*/

/*
#define lprev(otri1, otri2) \
  (otri2).m_tri = (otri1).m_tri;  \
  (otri2).m_orient = minus1mod3_cpp[(otri1).m_orient]
*/

/*
void ribi::tricpp::lprevself(Otri& otri)
{
  otri.Lprevself();
  //otri.m_orient = otri.m_orient + 2 % 3;
}
*/
/*
#define lprevself(otri) \
  (otri).m_orient = minus1mod3_cpp[(otri).m_orient]
*/

//onext() spins counterclockwise around a vertex; that is, it finds the
//  next edge with the same origin in the counterclockwise direction.  This
//  edge is part of a different triangle.

/*
void ribi::tricpp::onext(Otri& otri1, Otri& otri2)
{
  otri2.Onext(otri1);

  //otri2.Lprev(otri1);
  //lprev(otri1, otri2);

  //otri2.Symself();
  //symself(otri2);
}
*/
/*
#define onext(otri1, otri2) \
  lprev(otri1, otri2);  \
  symself(otri2);
*/

/*
void ribi::tricpp::onextself(Otri& otri)
{
  otri.Lprevself();
  //lprevself(otri);

  otri.Symself();
  //symself(otri);
}
*/
/*
#define onextself(otri) \
  lprevself(otri);  \
  symself(otri);
*/

//oprev() spins clockwise around a vertex; that is, it finds the next edge
//  with the same origin in the clockwise direction.  This edge is part of
//  a different triangle.
/*
void ribi::tricpp::oprev(Otri& otri1, Otri& otri2)
{
  otri2.Sym(otri1);
  //sym(otri1, otri2);

  otri2.Lnextself();
  //lnextself(otri2);
}
*/
/*
#define oprev(otri1, otri2) \
  sym(otri1, otri2);  \
  lnextself(otri2);
*/

/*
void ribi::tricpp::oprevself(Otri& otri)
{
  otri.Symself();
  //symself(otri);

  otri.Lnextself();
  //lnextself(otri);
}
*/
/*
#define oprevself(otri) \
  symself(otri);  \
  lnextself(otri);
*/

//dnext() spins counterclockwise around a vertex; that is, it finds the
//  next edge with the same destination in the counterclockwise direction.
//  This edge is part of a different triangle.
/*
void ribi::tricpp::dnext(Otri& otri1, Otri& otri2)
{
  otri2.Sym(otri1);
  //sym(otri1, otri2);

  otri2.Lprevself();
  //lprevself(otri2);
}
*/
/*
#define dnext(otri1, otri2) \
  sym(otri1, otri2);  \
  lprevself(otri2);
*/

/*
void ribi::tricpp::dnextself(Otri& otri)
{
  otri.Symself();
  //symself(otri);

  otri.Lprevself();
  //lprevself(otri);
}
*/

/*
#define dnextself(otri) \
  symself(otri);  \
  lprevself(otri);
*/

//dprev() spins clockwise around a vertex; that is, it finds the next edge
//  with the same destination in the clockwise direction.  This edge is
//  part of a different triangle.
/*
void ribi::tricpp::dprev(Otri& otri1, Otri& otri2)
{
  otri2.Lnext(otri1);
  //lnext(otri1, otri2);
  otri2.Symself();
  //symself(otri2);
}
*/
/*
#define dprev(otri1, otri2) \
  lnext(otri1, otri2);  \
  symself(otri2);
*/

/*
void ribi::tricpp::dprevself(Otri& otri)
{
  otri.Lnextself();
  //lnextself(otri);

  otri.Symself();
  //symself(otri);
}
*/
/*
#define dprevself(otri) \
  lnextself(otri);  \
  symself(otri);
*/

//rnext() moves one edge counterclockwise about the adjacent triangle.
//  (It's best understood by reading Guibas and Stolfi.  It involves
//  changing triangles twice.)

/*
void ribi::tricpp::rnext(Otri& otri1, Otri& otri2)
{
  sym(otri1, otri2);

  otri2.Lnextself();
  //lnextself(otri2);

  otri2.Symself();
  //symself(otri2);
}
*/
/*
#define rnext(otri1, otri2) \
  sym(otri1, otri2);  \
  lnextself(otri2); \
  symself(otri2);
*/

/*
void ribi::tricpp::rnextself(Otri& otri)
{
  otri.Symself();
  //symself(otri);

  otri.Lnextself();
  //lnextself(otri);

  otri.Symself();
  //symself(otri);
}
*/
/*
#define rnextself(otri) \
  symself(otri);  \
  lnextself(otri);  \
  symself(otri);
*/

//rprev() moves one edge clockwise about the adjacent triangle.
//  (It's best understood by reading Guibas and Stolfi.  It involves
//  changing triangles twice.)

/*
void ribi::tricpp::rprev(Otri& otri1, Otri& otri2)
{
  sym(otri1, otri2);

  otri2.Lprevself();
  //lprevself(otri2);

  otri2.Symself();
  //symself(otri2);
}
*/
/*
#define rprev(otri1, otri2) \
  sym(otri1, otri2);  \
  lprevself(otri2); \
  symself(otri2);
*/

/*
void ribi::tricpp::rprevself(Otri& otri)
{
  otri.Symself();
  //symself(otri);

  otri.Lprevself();
  //lprevself(otri);

  otri.Symself();
  //symself(otri);
}
*/
/*
#define rprevself(otri) \
  symself(otri);  \
  lprevself(otri);  \
  symself(otri);
*/
