#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
//#pragma GCC diagnostic ignored "-Wsign-compare"
//#pragma GCC diagnostic ignored "-Wunused-parameter"
//#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglecppmain.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <boost/math/constants/constants.hpp>
#include "fileio.h"
#include "trianglecppbadsubseg.h"
#include "trianglecppbehavior.h"
#include "trianglecppdefines.h"
#include "trianglecppevent.h"
#include "trianglecppfile.h"
#include "trianglecppglobals.h"
#include "trianglecppmesh.h"
#include "trianglecpposub.h"
#include "trianglecppotri.h"
#include "trianglecppsplaynode.h"
#include "trianglecppstring.h"
#include "trianglecppsubseg.h"
#include "trianglecpptrimalloc.h"
#include "trianglecppvertex.h"
#include "trianglecppvertextype.h"



void ribi::tricpp::dummyinit(
  Mesh& m
  //const Behavior& b,
  //const int trianglebytes,
  //const int subsegbytes
)
{
  //Set up `dummytri', the `triangle' that occupies "outer space."
  //m.m_dummytribase = (Triangle *) TriMalloc(trianglebytes +
  //                                         m.m_triangles.m_alignbytes);
  //Align `dummytri' on a `triangles.alignbytes'-byte boundary.
  //unsigned long alignptr = (unsigned long) m.m_dummytribase;
  //m.m_dummytri = (Triangle *)
  //  (alignptr + (unsigned long) m.m_triangles.m_alignbytes -
  //   (alignptr % (unsigned long) m.m_triangles.m_alignbytes));
  //Initialize the three adjoining triangles to be "outer space."  These
  //  will eventually be changed by various bonding operations, but their
  //  values don't really matter, as long as they can legally be
  //  dereferenced.
  //assert(m.m_dummytri);
  m.m_dummytri.m_triangles.push_back(Triangle());
  m.m_dummytri.m_triangles.push_back(Triangle());
  m.m_dummytri.m_triangles.push_back(Triangle());
  //SetTriangle(*m.m_dummytri,0);
  //m.m_dummytri->SetTriangle(*m.m_dummytri,1);
  //m.m_dummytri->SetTriangle(*m.m_dummytri,2);
  //Three NULL vertices.
  //m.m_dummytri->SetTriangle(nullptr,3);
  //m.m_dummytri->SetTriangle(nullptr,4);
  //m.m_dummytri->SetTriangle(nullptr,5);

  {
    //Set up `dummysub', the omnipresent subsegment pointed to by any
    //  triangle side or subsegment end that isn't attached to a real
    //  subsegment.

    //m.m_dummysubbase = (SubSeg *) TriMalloc(subsegbytes + m.m_subsegs.m_alignbytes);
    //Align `dummysub' on a `subsegs.alignbytes'-byte boundary.
    //alignptr = (unsigned long) m.m_dummysubbase;
    //m.m_dummysub = (SubSeg *)
    //  (alignptr + (unsigned long) m.m_subsegs.m_alignbytes -
    //   (alignptr % (unsigned long) m.m_subsegs.m_alignbytes));
    //Initialize the two adjoining subsegments to be the omnipresent
    //  subsegment.  These will eventually be changed by various bonding
    //  operations, but their values don't really matter, as long as they
    //  can legally be dereferenced.
    //assert(m.m_dummysub);
    m.m_dummysub.m_subsegs.push_back(SubSeg());
    m.m_dummysub.m_subsegs.push_back(SubSeg());
    //m.m_dummysub->SetSubSeg(m.m_dummysub,0);
    //m.m_dummysub->SetSubSeg(m.m_dummysub,1);
    //Four NULL vertices.
    //m.m_dummysub->SetSubSeg(nullptr,2);
    //m.m_dummysub->SetSubSeg(nullptr,3);
    //m.m_dummysub->SetSubSeg(nullptr,4);
    //m.m_dummysub->SetSubSeg(nullptr,5);
    //Initialize the two adjoining triangles to be "outer space."
    //assert(m.m_dummytri);
    m.m_dummysub.m_triangles.push_back(Triangle());
    m.m_dummysub.m_triangles.push_back(Triangle());
    //m.m_dummysub->SetTriangle(m.m_dummytri,6);
    //m.m_dummysub->SetTriangle(m.m_dummytri,7);
    //Set the boundary marker to zero.
    m.m_dummysub.SetBoundaryMarker(0);
    //* (int *) (m.m_dummysub + 8) = 0;

    //Initialize the three adjoining subsegments of `dummytri' to be
    //  the omnipresent subsegment.
    m.m_dummytri.m_subsegs.push_back(m.m_dummysub);
    m.m_dummytri.m_subsegs.push_back(m.m_dummysub);
    m.m_dummytri.m_subsegs.push_back(m.m_dummysub);
    //m.m_dummytri->SetSubSeg(m.m_dummysub,6);
    //m.m_dummytri->SetSubSeg(m.m_dummysub,7);
    //m.m_dummytri->SetSubSeg(m.m_dummysub,8);
  }
}

/*
void ribi::tricpp::initializevertexpool(
  Mesh& m,
  const Behavior& b
)
{
  static_assert(
    (m.m_mesh_dim + m.m_nextras * sizeof(double) + sizeof(int) - 1) / sizeof(int)
    == 1,"m.m_vertexmarkindex is determined here"
  );
  static_assert(
    m.m_vertexmarkindex == (m.m_mesh_dim + m.m_nextras * sizeof(double) + sizeof(int) - 1) / sizeof(int)
    ,"m.m_vertexmarkindex is determined here"
  );
  static_assert((m.m_vertexmarkindex + 2) * sizeof(int) == 12,"");
  static const int vertexsize_first = (m.m_vertexmarkindex + 2) * sizeof(int);
  static_assert(vertexsize_first  == 12,"");
  static_assert(b.m_poly,"");
  // The index within each vertex at which a triangle pointer is found.
  //   Ensure the pointer is aligned to a sizeof(triangle)-byte address.
  static_assert((vertexsize_first + sizeof(Triangle) - 1) /sizeof(Triangle) == 3,"");
  static_assert(m.m_vertex2triindex == (vertexsize_first + sizeof(Triangle) - 1) /sizeof(Triangle),"");
  static const int vertexsize = (m.m_vertex2triindex + 1) * sizeof(Triangle);
  static_assert(vertexsize == 16,"");
  // Initialize the pool of vertices.
  PoolInit(
    &m.m_vertices,
    vertexsize,
    VERTEXPERBLOCK,
    m.m_invertices > VERTEXPERBLOCK ? m.m_invertices : VERTEXPERBLOCK,
    sizeof(double)
  );

}
*/

/*
void ribi::tricpp::initializetrisubpools(
  Mesh& m,
  const Behavior& b
)
{

  //The number of bytes occupied by a triangle.
  int trisize = ((b.m_order + 1) * (b.m_order + 2) / 2 + (m.m_highorderindex - 3)) *
            sizeof(Triangle);
  //The index within each triangle at which its attributes are found,
  //  where the index is measured in doubles.
  m.m_elemattribindex = (trisize + sizeof(double) - 1) / sizeof(double);
  //The index within each triangle at which the maximum area constraint
  //  is found, where the index is measured in doubles.  Note that if the
  //  `regionattrib' flag is set, an additional attribute will be added.
  m.m_areaboundindex = m.m_elemattribindex + m.m_eextras + b.m_regionattrib;
  //If triangle attributes or an area bound are needed, increase the number
  //  of bytes occupied by a triangle.
  if (b.m_vararea) {
    trisize = (m.m_areaboundindex + 1) * sizeof(double);
  } else if (m.m_eextras + b.m_regionattrib > 0) {
    trisize = m.m_areaboundindex * sizeof(double);
  }
  //If a Voronoi diagram or triangle neighbor graph is requested, make
  //  sure there's room to store an integer index in each triangle.  This
  //  integer index can occupy the same space as the subsegment pointers
  //  or attributes or area constraint or extra nodes.
  if ((b.m_voronoi || b.m_neighbors) &&
      (trisize < 6 * static_cast<int>(sizeof(Triangle)) + static_cast<int>(sizeof(int)))) {
    trisize = 6 * sizeof(Triangle) + sizeof(int);
  }

  //Having determined the memory size of a triangle, initialize the pool.
  PoolInit(&m.m_triangles, trisize, g_triangles_per_block,
           (2 * m.m_invertices - 2) > g_triangles_per_block ? (2 * m.m_invertices - 2) :
           g_triangles_per_block, 4);

  {
    //Initialize the pool of subsegments.  Take into account all eight
    //  pointers and one boundary marker.
    PoolInit(&m.m_subsegs, 8 * sizeof(Triangle) + sizeof(int),
             SUBSEGPERBLOCK, SUBSEGPERBLOCK, 4);

    //Initialize the "outer space" triangle and omnipresent subsegment.
    dummyinit(m, b, m.m_triangles.m_itembytes, m.m_subsegs.m_itembytes);
  }
}
*/

void ribi::tricpp::triangledealloc(
  std::vector<Triangle>& m_m_triangles,
  Triangle& dyingtriangle
)
{
  //Mark the triangle as dead.  This makes it possible to detect dead
  //  triangles when traversing the list of all triangles.
  dyingtriangle.KillMe();
  //killtri(dyingtriangle);
  PoolDealloc(m_m_triangles,dyingtriangle);
}


/*
ribi::tricpp::Triangle * ribi::tricpp::triangletraverse(Mesh& m)
{
  Triangle *newtriangle = nullptr;

  do {
    newtriangle = (Triangle *) Traverse(&m.m_triangles);
    if (newtriangle == (Triangle *) NULL) {
      return (Triangle *) NULL;
    }
  } while (newtriangle->IsDead()); // Skip dead ones
  return newtriangle;
}
*/

void ribi::tricpp::subsegdealloc(
  Mesh& m,
  SubSeg& dyingsubseg
)
{
  //Mark the subsegment as dead.  This makes it possible to detect dead
  //  subsegments when traversing the list of all subsegments.
  /*
  killsubseg(dyingsubseg);
  PoolDealloc(&m.m_subsegs, (void *) dyingsubseg);
  */
  dyingsubseg.KillMe();
  m.KillSubSeg(dyingsubseg);
}

/*
ribi::tricpp::SubSeg * ribi::tricpp::subsegtraverse(
  Mesh& m
)
{
  SubSeg *newsubseg = nullptr;

  do {
    newsubseg = (SubSeg *) Traverse(&m.m_subsegs);
    if (newsubseg == nullptr)
    {
      return nullptr;
    }
  } while (newsubseg.IsDead()); //Skip dead ones.
  return newsubseg;
}
*/

void ribi::tricpp::vertexdealloc(
  std::vector<Vertex>& vertices,
  Vertex& dyingvertex
)
{
  //Mark the vertex as dead.  This makes it possible to detect dead
  //  vertices when traversing the list of all vertices.
  dyingvertex.SetVertexType(VertexType::DEADVERTEX);
  //PoolDealloc(&m.m_vertices, (void *) &dyingvertex[0]);
  PoolDealloc(vertices, dyingvertex);
}



void ribi::tricpp::badsubsegdealloc(
  //Mesh& m,
  std::vector<BadSubSeg>& m_m_badsubsegs,
  BadSubSeg& dyingseg
)
{
  //Set subsegment's origin to NULL.  This makes it possible to detect dead
  //  badsubsegs when traversing the list of all badsubsegs             .
  dyingseg.m_subsegorg.Clear();
  PoolDealloc(m_m_badsubsegs,dyingseg);
}


/*
ribi::tricpp::BadSubSeg * ribi::tricpp::badsubsegtraverse(Mesh& m)
{
  BadSubSeg *newseg = nullptr;

  do
  {
    newseg = (BadSubSeg *) Traverse(&m.m_badsubsegs);
    if (newseg == nullptr)
    {
      return nullptr;
    }
  } while (newseg->m_subsegorg.IsEmpty()); // Skip dead ones.
  return newseg;
}
*/

/*
ribi::tricpp::Vertex ribi::tricpp::getvertex(
  const std::vector<Vertex>& vertices,
  const Behavior&,
  const int index
)
{
  assert(index >= 0);
  assert(index < static_cast<int>(vertices.size()));
  return vertices[index];

  void **getblock = vertices.m_firstblock;
  int current = b.m_firstnumber;

  // Find the right block.
  if (current + vertices.m_itemsfirstblock <= number) {
    getblock = (void **) *getblock;
    current += vertices.m_itemsfirstblock;
    while (current + vertices.m_itemsperblock <= number) {
      getblock = (void **) *getblock;
      current += vertices.m_itemsperblock;
    }
  }

  // Now find the right vertex.
  const unsigned long alignptr = (unsigned long) (getblock + 1);
  const char * const foundvertex = (char *) (alignptr + (unsigned long) vertices.m_alignbytes -
                          (alignptr % (unsigned long) vertices.m_alignbytes));
  return (Vertex)(foundvertex + vertices.m_itembytes * (number - current));
}
*/

/*
void ribi::tricpp::triangledeinit(
  Mesh& m,
  const Behavior& b
)
{
  PoolDeinit(m.m_triangles);
  //delete m.m_dummytribase;
  //m.m_dummytribase = nullptr;
  {
    PoolDeinit(m.m_subsegs);
    //delete m.m_dummysubbase;
    //m.m_dummysubbase = nullptr;
  }
  PoolDeinit(m.m_vertices);
  if (b.m_quality) {
    PoolDeinit(m.m_badsubsegs);
    if ((b.m_minangle > 0.0) || b.m_vararea || b.m_fixedarea || b.m_usertest)
    {
      PoolDeinit(m.m_badtriangles);
      PoolDeinit(m.m_flipstackers);
    }
  }
}
*/

void ribi::tricpp::maketriangle(
  //Mesh& m,
  const boost::shared_ptr<Triangle>& m_m_dummytri,
  const boost::shared_ptr<SubSeg>& m_m_dummysub,
  const int m_m_eextras,
  //const Behavior& b,
  const bool b_m_vararea,
  Otri& newotri
)
{
  //newotri->m_tri = (Triangle *) PoolAlloc(&m.m_triangles);
  //Initialize the three adjoining triangles to be "outer space".
  newotri.m_tri[0] = m_m_dummytri;
  newotri.m_tri[1] = m_m_dummytri;
  newotri.m_tri[2] = m_m_dummytri;
  //Three NULL vertices.
  newotri.m_tri[3] = nullptr;
  newotri.m_tri[4] = nullptr;
  newotri.m_tri[5] = nullptr;
  //Initialize the three adjoining subsegments to be the omnipresent
  //  subsegment.
  newotri.SetSubSeg(m_m_dummysub,6);
  newotri.SetSubSeg(m_m_dummysub,7);
  newotri.SetSubSeg(m_m_dummysub,8);
  for (int i = 0; i != m_m_eextras; ++i)
  {
    newotri.SetElemAttrib(i,0.0);
  }
  if (b_m_vararea)
  {
    newotri.SetAreaBound(-1.0);
  }
  newotri.SetOrient(0);
}


void ribi::tricpp::makesubseg(
  //Mesh& m,
  Triangle& m_m_dummytri,
  SubSeg& m_m_dummysub,
  Osub& newsubseg
)
{
  //newsubseg->m_subseg = (SubSeg *) PoolAlloc(&m.m_subsegs);
  //Initialize the two adjoining subsegments to be the omnipresent
  //  subsegment.
  newsubseg.m_subseg.push_back(m_m_dummysub);
  newsubseg.m_subseg.push_back(m_m_dummysub);
  //Four NULL vertices.
  //newsubseg.m_subseg[2] = nullptr;
  //newsubseg.m_subseg[3] = nullptr;
  //newsubseg.m_subseg[4] = nullptr;
  //newsubseg.m_subseg[5] = nullptr;
  //Initialize the two adjoining triangles to be "outer space."
  newsubseg.m_triangles.push_back(m_m_dummytri);
  newsubseg.m_triangles.push_back(m_m_dummytri);
  //newsubseg.m_subseg[6] = m_m_dummytri;
  //newsubseg.m_subseg[7] = m_m_dummytri;
  //Set the boundary marker to zero.
  newsubseg.SetMark(0);
  newsubseg.SetOrient(0);
}

int ribi::tricpp::fast_expansion_sum_zeroelim(
  const int elen_original,
  const std::vector<double>& e,
  //const double * const e,
  const int flen_original,
  const std::vector<double>& f,
  //const double * const f,
  std::vector<double>& h
  //double * const h
)
{
  const int elen = static_cast<int>(e.size());
  const int flen = static_cast<int>(f.size());
  assert(elen_original == elen);
  assert(flen_original == flen);
  double Q;
  double Qnew;
  double hh;
  double enow = e[0];
  double fnow = f[0];
  int eindex = 0;
  int findex = 0;
  if ((fnow > enow) == (fnow > -enow))
  {
    Q = enow;
    enow = e[++eindex];
  }
  else
  {
    Q = fnow;
    fnow = f[++findex];
  }
  int hindex = 0;
  if (eindex < elen && findex < flen)
  {
    if ((fnow > enow) == (fnow > -enow))
    {
      Qnew = enow + Q; hh = 0.0;
      //Fast_Two_Sum(a,b,x,y) : x = a + b, y = 0.0;
      //Fast_Two_Sum(enow, Q, Qnew, hh);
      enow = e[++eindex];
    }
    else
    {
      Qnew = fnow + Q; hh = 0.0;
      //Fast_Two_Sum(a,b,x,y) : x = a + b, y = 0.0;
      //Fast_Two_Sum(fnow, Q, Qnew, hh);

      fnow = f[++findex];
    }
    Q = Qnew;
    if (hh != 0.0)
    {
      h[hindex++] = hh;
    }
    while (eindex < elen && findex < flen)
    {
      if ((fnow > enow) == (fnow > -enow))
      {
        Qnew = Q + enow;
        hh = 0.0;
        //x = a + b, y = 0.0;
        //Two_Sum(Q, enow, Qnew, hh);
        enow = e[++eindex];
      }
      else
      {
        Qnew = Q + fnow;
        hh = 0.0;
        //x = a + b, y = 0.0;
        //Two_Sum(Q, fnow, Qnew, hh);
        fnow = f[++findex];
      }
      Q = Qnew;
      if (hh != 0.0)
      {
        h[hindex++] = hh;
      }
    }
  }
  while (eindex < elen)
  {
    Qnew = Q + enow;
    hh = 0.0;
    //x = a + b, y = 0.0;
    //Two_Sum(Q, enow, Qnew, hh);
    enow = e[++eindex];
    Q = Qnew;
    if (hh != 0.0)
    {
      h[hindex++] = hh;
    }
  }
  while (findex < flen)
  {
    Qnew = Q + fnow;
    hh = 0.0;
    //x = a + b, y = 0.0;
    //Two_Sum(Q, fnow, Qnew, hh);

    fnow = f[++findex];
    Q = Qnew;
    if (hh != 0.0)
    {
      h[hindex++] = hh;
    }
  }
  if (Q != 0.0 || hindex == 0)
  {
    h[hindex++] = Q;
  }
  return hindex;
}


int ribi::tricpp::scale_expansion_zeroelim(
  const int elen_original,
  const std::vector<double>& e,
  //const double * const e,
  const double b,
  std::vector<double>& h
  //double * const h
)
{
  const int elen = static_cast<int>(e.size());
  assert(elen == elen_original);
  double Q, sum;
  double hh;
  double product1;
  double product0;
  int hindex;
  double enow;

  double bhi = b;
  double blo =0.0;
  //Split(b, bhi, blo);
  Two_Product_Presplit(e[0], b, bhi, blo, Q, hh);
  hindex = 0;
  if (hh != 0) {
    h[hindex++] = hh;
  }
  for (int eindex = 1; eindex < elen; eindex++) {
    enow = e[eindex];
    Two_Product_Presplit(enow, b, bhi, blo, product1, product0);

    sum = Q + product0;
    hh = 0.0;
    //x = a + b, y = 0.0;
    //Two_Sum(Q, product0, sum, hh);

    if (hh != 0) {
      h[hindex++] = hh;
    }

    Q = product1 + sum; hh = 0.0;
    //Fast_Two_Sum(a,b,x,y) : x = a + b, y = 0.0;
    //Fast_Two_Sum(product1, sum, Q, hh);

    if (hh != 0) {
      h[hindex++] = hh;
    }
  }
  if ((Q != 0.0) || (hindex == 0)) {
    h[hindex++] = Q;
  }
  return hindex;
}

// estimate()   Produce a one-word estimate of an expansion's value.
/*
double estimate(
  //const int elen,
  //const double * const e
  const std::vector<double>& v
)
{
  return std::accumulate(v.begin(),v.end(),0.0);

  /double Q = e[0];
  /for (int eindex = 1; eindex < elen; ++eindex)
  /{
  /  Q += e[eindex];
  /}
  /return Q;

}
*/

double ribi::tricpp::counterclockwiseadapt(
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const double detsum
)
{
  //double acxtail, acytail, bcxtail, bcytail;
  //double detleft, detright;
  const double detlefttail = 0.0;
  const double detrighttail = 0.0;
  //double det, errbound;
  std::vector<double> B(4,0.0);
  //double B[4];
  std::vector<double> C1(8,0.0);
  std::vector<double> C2(12,0.0);
  std::vector<double> D(16,0.0);
  //double C1[8], C2[12], D[16];
  //double B3;
  //int C1length, C2length, Dlength;
  std::vector<double> u(4,0.0);
  //double u[4];
  double u3;
  double s1, t1;
  const double s0 = 0.0;
  const double t0 = 0.0;

  const double acx = pa[0] - pc[0];
  const double bcx = pb[0] - pc[0];
  const double acy = pa[1] - pc[1];
  const double bcy = pb[1] - pc[1];

  const double detleft = acx * bcy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acx, bcy, detleft, detlefttail);

  const double detright = acy * bcx;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acy, bcx, detright, detrighttail);

  const double B3 = detleft + detlefttail - detright - detrighttail;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(detleft, detlefttail, detright, detrighttail,B3, B[2], B[1], B[0]);

  B[3] = B3;


  double det = std::accumulate(B.begin(),B.end(),0.0);
  //double det = estimate(B);

  double errbound = Global().m_ccwerrboundB * detsum;
  if (det >= errbound || -det >= errbound)
  {
    return det;
  }

  const double acxtail = -acx + pa[0] - pc[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[0], pc[0], acx, acxtail);

  const double bcxtail = -bcx + pb[0] - pc[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[0], pc[0], bcx, bcxtail);

  const double acytail = -acy + pa[1] - pc[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[1], pc[1], acy, acytail);

  const double bcytail = -bcy + pb[1] - pc[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[1], pc[1], bcy, bcytail);

  if (acxtail == 0.0 && acytail == 0.0 && bcxtail == 0.0 && bcytail == 0.0)
  {
    return det;
  }

  errbound = Global().m_ccwerrboundC * detsum + Global().m_resulterrbound * std::abs(det);
  det += (acx * bcytail + bcy * acxtail)
       - (acy * bcxtail + bcx * acytail);
  if ((det >= errbound) || (-det >= errbound))
  {
    return det;
  }

  s1 = acxtail * bcy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acxtail, bcy, s1, s0);

  t1 = acytail * bcx;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acytail, bcx, t1, t0);

  u3 = s1 + s0 - t1 - t0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(s1, s0, t1, t0, u3, u[2], u[1], u[0]);

  u[3] = u3;
  const int C1length = fast_expansion_sum_zeroelim(4, B, 4, u, C1);

  s1 = acx * bcytail;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acx, bcytail, s1, s0);

  t1 = acy * bcxtail;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acy, bcxtail, t1, t0);

  u3 = s1 + s0 - t1 - t0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(s1, s0, t1, t0, u3, u[2], u[1], u[0]);

  u[3] = u3;
  const int C2length = fast_expansion_sum_zeroelim(C1length, C1, 4, u, C2);

  s1 = acxtail * bcytail;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acxtail, bcytail, s1, s0);

  t1 = acytail * bcxtail;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(acytail, bcxtail, t1, t0);

  u3 = s1 + s0 - t1 - t0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(s1, s0, t1, t0, u3, u[2], u[1], u[0]);

  u[3] = u3;
  const int Dlength = fast_expansion_sum_zeroelim(C2length, C2, 4, u, D);

  return(D[Dlength - 1]);
}

double ribi::tricpp::counterclockwise(
  int& m_m_counterclockcount,
  const bool b_m_noexact,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc
)
{
  double detsum = 0.0;

  ++m_m_counterclockcount;

  const double detleft  = (pa[0] - pc[0]) * (pb[1] - pc[1]);
  const double detright = (pa[1] - pc[1]) * (pb[0] - pc[0]);
  const double det = detleft - detright;

  if (b_m_noexact)
  {
    return det;
  }

  if (detleft > 0.0)
  {
    if (detright <= 0.0)
    {
      return det;
    }
    else
    {
      detsum = detleft + detright;
    }
  }
  else if (detleft < 0.0)
  {
    if (detright >= 0.0)
    {
      return det;
    }
    else
    {
      detsum = -detleft - detright;
    }
  }
  else
  {
    return det;
  }

  const double errbound = Global().m_ccwerrboundA * detsum;
  if ((det >= errbound) || (-det >= errbound))
  {
    return det;
  }

  return counterclockwiseadapt(pa, pb, pc, detsum);
}

double ribi::tricpp::incircleadapt(
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const Vertex& pd,
  const double permanent
)
{
  double bdxcdy1, cdxbdy1, cdxady1, adxcdy1, adxbdy1, bdxady1;
  const double bdxcdy0 = 0.0;
  const double cdxbdy0 = 0.0;
  const double cdxady0 = 0.0;
  const double adxcdy0 = 0.0;
  const double adxbdy0 = 0.0;
  const double bdxady0 = 0.0;
  std::vector<double> bc(4,0.0);
  std::vector<double> ca(4,0.0);
  std::vector<double> ab(4,0.0);
  double bc3, ca3, ab3;
  std::vector<double> axbc(8,0.0);
  std::vector<double> axxbc(16,0.0);
  std::vector<double> aybc(8,0.0);
  std::vector<double> ayybc(16,0.0);
  std::vector<double> adet(32,0.0);
  //int axbclen, axxbclen, aybclen, ayybclen, alen;
  std::vector<double> bxca(8,0.0);
  std::vector<double> bxxca(16,0.0);
  std::vector<double> byca(8,0.0);
  std::vector<double> byyca(16,0.0);
  std::vector<double> bdet(32,0.0);
  std::vector<double> cxab(8,0.0);
  std::vector<double> cxxab(16,0.0);
  std::vector<double> cyab(8,0.0);
  std::vector<double> cyyab(16,0.0);
  std::vector<double> cdet(32,0.0);
  //int cxablen, cxxablen, cyablen, cyyablen, clen;
  std::vector<double> abdet(64,0.0);
  //int ablen;
  std::vector<double> fin1(1152,0.0);
  std::vector<double> fin2(1152,0.0);
  //double fin1(1152], fin2(1152];
  //double *finnow,
  //double *finother;
  //double *finswap = nullptr;
  //int finlength;

  double adxtail, bdxtail, cdxtail, adytail, bdytail, cdytail;
  double adxadx1, adyady1, bdxbdx1, bdybdy1, cdxcdx1, cdycdy1;
  const double adxadx0 = 0.0;
  const double adyady0 = 0.0;
  const double bdxbdx0 = 0.0;
  const double bdybdy0 = 0.0;
  const double cdxcdx0 = 0.0;
  const double cdycdy0 = 0.0;
  std::vector<double> aa(4,0.0);
  std::vector<double> bb(4,0.0);
  std::vector<double> cc(4,0.0);
  double aa3, bb3, cc3;
  double ti1, tj1;
  const double ti0 = 0.0;
  const double tj0 = 0.0;
  std::vector<double> u(4,0.0);
  std::vector<double> v(4,0.0);
  double u3, v3;
  std::vector<double> temp8(8,0.0);
  std::vector<double> temp16a(16,0.0);
  std::vector<double> temp16b(16,0.0);
  std::vector<double> temp16c(16,0.0);
  std::vector<double> temp32a(32,0.0);
  std::vector<double> temp32b(32,0.0);
  std::vector<double> temp48(48,0.0);
  std::vector<double> temp64(64,0.0);
  int temp8len, temp16alen, temp16blen, temp16clen;
  int temp32alen, temp32blen, temp48len, temp64len;
  std::vector<double> axtbb(8,0.0);
  std::vector<double> axtcc(8,0.0);
  std::vector<double> aytbb(8,0.0);
  std::vector<double> aytcc(8,0.0);
  int axtbblen, axtcclen, aytbblen, aytcclen;
  std::vector<double> bxtaa(8,0.0);
  std::vector<double> bxtcc(8,0.0);
  std::vector<double> bytaa(8,0.0);
  std::vector<double> bytcc(8,0.0);
  int bxtaalen, bxtcclen, bytaalen, bytcclen;
  std::vector<double> cxtaa(8,0.0);
  std::vector<double> cxtbb(8,0.0);
  std::vector<double> cytaa(8,0.0);
  std::vector<double> cytbb(8,0.0);
  int cxtaalen, cxtbblen, cytaalen, cytbblen;
  std::vector<double> axtbc(8,0.0);
  std::vector<double> aytbc(8,0.0);
  std::vector<double> bxtca(8,0.0);
  std::vector<double> bytca(8,0.0);
  std::vector<double> cxtab(8,0.0);
  std::vector<double> cytab(8,0.0);
  int axtbclen, aytbclen, bxtcalen, bytcalen, cxtablen, cytablen;
  std::vector<double> axtbct(16,0.0);
  std::vector<double> aytbct(16,0.0);
  std::vector<double> bxtcat(16,0.0);
  std::vector<double> bytcat(16,0.0);
  std::vector<double> cxtabt(16,0.0);
  std::vector<double> cytabt(16,0.0);
  int axtbctlen, aytbctlen, bxtcatlen, bytcatlen, cxtabtlen, cytabtlen;
  std::vector<double> axtbctt(8,0.0);
  std::vector<double> aytbctt(8,0.0);
  std::vector<double> bxtcatt(8,0.0);
  std::vector<double> bytcatt(8,0.0);
  std::vector<double> cxtabtt(8,0.0);
  std::vector<double> cytabtt(8,0.0);
  int axtbcttlen, aytbcttlen, bxtcattlen, bytcattlen, cxtabttlen, cytabttlen;
  std::vector<double> abt(8,0.0);
  std::vector<double> bct(8,0.0);
  std::vector<double> cat(8,0.0);
  int abtlen, bctlen, catlen;
  std::vector<double> abtt(4,0.0);
  std::vector<double> bctt(4,0.0);
  std::vector<double> catt(4,0.0);
  int abttlen, bcttlen, cattlen;
  double abtt3, bctt3, catt3;
  double negate;

  const double adx = pa[0] - pd[0];
  const double bdx = pb[0] - pd[0];
  const double cdx = pc[0] - pd[0];
  const double ady = pa[1] - pd[1];
  const double bdy = pb[1] - pd[1];
  const double cdy = pc[1] - pd[1];

  bdxcdy1 = bdx * cdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(bdx, cdy, bdxcdy1, bdxcdy0);

  cdxbdy1 = cdx * bdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(cdx, bdy, cdxbdy1, cdxbdy0);

  bc3 = bdxcdy1 + bdxcdy0 - cdxbdy1 - cdxbdy0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(bdxcdy1, bdxcdy0, cdxbdy1, cdxbdy0, bc3, bc[2], bc[1], bc[0]);

  bc[3] = bc3;
  const int axbclen = scale_expansion_zeroelim(4, bc, adx, axbc);
  const int axxbclen = scale_expansion_zeroelim(axbclen, axbc, adx, axxbc);
  const int aybclen = scale_expansion_zeroelim(4, bc, ady, aybc);
  const int ayybclen = scale_expansion_zeroelim(aybclen, aybc, ady, ayybc);
  const int alen = fast_expansion_sum_zeroelim(axxbclen, axxbc, ayybclen, ayybc, adet);

  cdxady1 = cdx * ady;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(cdx, ady, cdxady1, cdxady0);

  adxcdy1 = adx * cdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(adx, cdy, adxcdy1, adxcdy0);

  ca3 = cdxady1 + cdxady0 - adxcdy1 - adxcdy0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(cdxady1, cdxady0, adxcdy1, adxcdy0, ca3, ca[2], ca[1], ca[0]);

  ca[3] = ca3;
  const int bxcalen = scale_expansion_zeroelim(4, ca, bdx, bxca);
  const int bxxcalen = scale_expansion_zeroelim(bxcalen, bxca, bdx, bxxca);
  const int bycalen = scale_expansion_zeroelim(4, ca, bdy, byca);
  const int byycalen = scale_expansion_zeroelim(bycalen, byca, bdy, byyca);
  const int blen = fast_expansion_sum_zeroelim(bxxcalen, bxxca, byycalen, byyca, bdet);

  adxbdy1 = adx * bdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(adx, bdy, adxbdy1, adxbdy0);

  bdxady1 = bdx * ady;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(bdx, ady, bdxady1, bdxady0);

  ab3 = adxbdy1 + adxbdy0 - bdxady1 - bdxady0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(adxbdy1, adxbdy0, bdxady1, bdxady0, ab3, ab[2], ab[1], ab[0]);

  ab[3] = ab3;
  const int cxablen = scale_expansion_zeroelim(4, ab, cdx, cxab);
  const int cxxablen = scale_expansion_zeroelim(cxablen, cxab, cdx, cxxab);
  const int cyablen = scale_expansion_zeroelim(4, ab, cdy, cyab);
  const int cyyablen = scale_expansion_zeroelim(cyablen, cyab, cdy, cyyab);
  const int clen = fast_expansion_sum_zeroelim(cxxablen, cxxab, cyyablen, cyyab, cdet);

  const int ablen = fast_expansion_sum_zeroelim(alen, adet, blen, bdet, abdet);
  int finlength = fast_expansion_sum_zeroelim(ablen, abdet, clen, cdet, fin1);
  assert(finlength == static_cast<int>(fin1.size()));
  double det = std::accumulate(fin1.begin(),fin1.end(),0.0);
  //double det = estimate(fin1);

  double errbound = Global().m_iccerrboundB * permanent;
  if (det >= errbound || -det >= errbound)
  {
    return det;
  }

  adxtail = -adx + pa[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[0], pd[0], adx, adxtail);

  adytail = -ady + pa[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[1], pd[1], , adytail);

  bdxtail = -bdx + pb[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[0], pd[0], bdx, bdxtail);

  bdytail = -bdy + pb[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[1], pd[1], bdy, bdytail);

  cdxtail = -cdx + pc[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pc[0], pd[0], cdx, cdxtail);

  cdytail = -cdy + pc[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pc[1], pd[1], cdy, cdytail);

  if ( adxtail == 0.0 && bdxtail == 0.0 && cdxtail == 0.0
    && adytail == 0.0 && bdytail == 0.0 && cdytail == 0.0
  )
  {
    return det;
  }

  errbound = Global().m_iccerrboundC * permanent + Global().m_resulterrbound * std::abs(det);
  det +=
    ((adx * adx + ady * ady) * ((bdx * cdytail + cdy * bdxtail)
    - (bdy * cdxtail + cdx * bdytail))
    + 2.0 * (adx * adxtail + ady * adytail) * (bdx * cdy - bdy * cdx))
    + ((bdx * bdx + bdy * bdy) * ((cdx * adytail + ady * cdxtail)
    - (cdy * adxtail + adx * cdytail))
    + 2.0 * (bdx * bdxtail + bdy * bdytail) * (cdx * ady - cdy * adx))
    + ((cdx * cdx + cdy * cdy) * ((adx * bdytail + bdy * adxtail)
    - (ady * bdxtail + bdx * adytail))
    + 2.0 * (cdx * cdxtail + cdy * cdytail) * (adx * bdy - ady * bdx)
  );
  if ((det >= errbound) || (-det >= errbound))
  {
    return det;
  }

  std::vector<double> finnow = fin1;
  std::vector<double> finother = fin2;

  if (bdxtail != 0.0 || bdytail != 0.0 || (cdxtail != 0.0) || (cdytail != 0.0))
  {
    adxadx1 = adx * adx;
    //Square(adx, adxadx1, adxadx0); //x = a * a, y = 0.0

    adyady1 = ady * ady;
    //Square(ady, adyady1, adyady0); //x = a * a, y = 0.0

    Two_Two_Sum(adxadx1, adxadx0, adyady1, adyady0, aa3, aa[2], aa[1], aa[0]);
    aa[3] = aa3;
  }
  if (cdxtail != 0.0 || cdytail != 0.0 || adxtail != 0.0 || adytail != 0.0)
  {
    bdxbdx1 = bdx * bdx;
    //Square(bdx, bdxbdx1, bdxbdx0); //x = a * a, y = 0.0

    bdybdy1 = bdy * bdy;
    //Square(bdy, bdybdy1, bdybdy0); //x = a * a, y = 0.0

    Two_Two_Sum(bdxbdx1, bdxbdx0, bdybdy1, bdybdy0, bb3, bb[2], bb[1], bb[0]);
    bb[3] = bb3;
  }
  if (adxtail != 0.0 || adytail != 0.0 || bdxtail != 0.0 || bdytail != 0.0)
  {
    cdxcdx1 = cdx * cdx;
    //Square(cdx, cdxcdx1, cdxcdx0); //x = a * a, y = 0.0

    cdycdy1 = cdy * cdy;
    //Square(cdy, cdycdy1, cdycdy0); //x = a * a, y = 0.0

    Two_Two_Sum(cdxcdx1, cdxcdx0, cdycdy1, cdycdy0, cc3, cc[2], cc[1], cc[0]);
    cc[3] = cc3;
  }

  if (adxtail != 0.0)
  {
    axtbclen = scale_expansion_zeroelim(4, bc, adxtail, axtbc);
    temp16alen = scale_expansion_zeroelim(axtbclen, axtbc, 2.0 * adx,temp16a);

    axtcclen = scale_expansion_zeroelim(4, cc, adxtail, axtcc);
    temp16blen = scale_expansion_zeroelim(axtcclen, axtcc, bdy, temp16b);

    axtbblen = scale_expansion_zeroelim(4, bb, adxtail, axtbb);
    temp16clen = scale_expansion_zeroelim(axtbblen, axtbb, -cdy, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (adytail != 0.0)
  {
    aytbclen = scale_expansion_zeroelim(4, bc, adytail, aytbc);
    temp16alen = scale_expansion_zeroelim(aytbclen, aytbc, 2.0 * ady,temp16a);

    aytbblen = scale_expansion_zeroelim(4, bb, adytail, aytbb);
    temp16blen = scale_expansion_zeroelim(aytbblen, aytbb, cdx, temp16b);

    aytcclen = scale_expansion_zeroelim(4, cc, adytail, aytcc);
    temp16clen = scale_expansion_zeroelim(aytcclen, aytcc, -bdx, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (bdxtail != 0.0)
  {
    bxtcalen = scale_expansion_zeroelim(4, ca, bdxtail, bxtca);
    temp16alen = scale_expansion_zeroelim(bxtcalen, bxtca, 2.0 * bdx,temp16a);

    bxtaalen = scale_expansion_zeroelim(4, aa, bdxtail, bxtaa);
    temp16blen = scale_expansion_zeroelim(bxtaalen, bxtaa, cdy, temp16b);

    bxtcclen = scale_expansion_zeroelim(4, cc, bdxtail, bxtcc);
    temp16clen = scale_expansion_zeroelim(bxtcclen, bxtcc, -ady, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (bdytail != 0.0)
  {
    bytcalen = scale_expansion_zeroelim(4, ca, bdytail, bytca);
    temp16alen = scale_expansion_zeroelim(bytcalen, bytca, 2.0 * bdy,temp16a);

    bytcclen = scale_expansion_zeroelim(4, cc, bdytail, bytcc);
    temp16blen = scale_expansion_zeroelim(bytcclen, bytcc, adx, temp16b);

    bytaalen = scale_expansion_zeroelim(4, aa, bdytail, bytaa);
    temp16clen = scale_expansion_zeroelim(bytaalen, bytaa, -cdx, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (cdxtail != 0.0)
  {
    cxtablen = scale_expansion_zeroelim(4, ab, cdxtail, cxtab);
    temp16alen = scale_expansion_zeroelim(cxtablen, cxtab, 2.0 * cdx,temp16a);

    cxtbblen = scale_expansion_zeroelim(4, bb, cdxtail, cxtbb);
    temp16blen = scale_expansion_zeroelim(cxtbblen, cxtbb, ady, temp16b);

    cxtaalen = scale_expansion_zeroelim(4, aa, cdxtail, cxtaa);
    temp16clen = scale_expansion_zeroelim(cxtaalen, cxtaa, -bdy, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (cdytail != 0.0)
  {
    cytablen = scale_expansion_zeroelim(4, ab, cdytail, cytab);
    temp16alen = scale_expansion_zeroelim(cytablen, cytab, 2.0 * cdy,temp16a);

    cytaalen = scale_expansion_zeroelim(4, aa, cdytail, cytaa);
    temp16blen = scale_expansion_zeroelim(cytaalen, cytaa, bdx, temp16b);

    cytbblen = scale_expansion_zeroelim(4, bb, cdytail, cytbb);
    temp16clen = scale_expansion_zeroelim(cytbblen, cytbb, -adx, temp16c);

    temp32alen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32a);
    temp48len = fast_expansion_sum_zeroelim(temp16clen, temp16c,temp32alen, temp32a, temp48);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }

  if (adxtail != 0.0 || adytail != 0.0)
  {
    if (bdxtail != 0.0 || bdytail != 0.0 || cdxtail != 0.0 || cdytail != 0.0)
    {
      ti1 = bdxtail * cdy,
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, cdy, ti1, ti0);

      tj1 = bdx * cdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdx, cdytail, tj1, tj0);

      Two_Two_Sum(ti1, ti0, tj1, tj0, u3, u[2], u[1], u[0]);
      u[3] = u3;
      negate = -bdy;

      ti1 = cdxtail * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, negate, ti1, ti0);

      negate = -bdytail;

      tj1 = cdx * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdx, negate, tj1, tj0);


      Two_Two_Sum(ti1, ti0, tj1, tj0, v3, v[2], v[1], v[0]);

      v[3] = v3;
      bctlen = fast_expansion_sum_zeroelim(4, u, 4, v, bct);

      ti1 = bdxtail * cdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, cdytail, ti1, ti0);

      tj1 = cdxtail * bdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, bdytail, tj1, tj0);

      bctt3 = ti1 + ti0 - tj1 - tj0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(ti1, ti0, tj1, tj0, bctt3, bctt[2], bctt[1], bctt[0]);

      bctt[3] = bctt3;
      bcttlen = 4;
    }
    else
    {
      bct[0] = 0.0;
      bctlen = 1;
      bctt[0] = 0.0;
      bcttlen = 1;
    }

    if (adxtail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(axtbclen, axtbc, adxtail, temp16a);
      axtbctlen = scale_expansion_zeroelim(bctlen, bct, adxtail, axtbct);
      temp32alen = scale_expansion_zeroelim(axtbctlen, axtbct, 2.0 * adx,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (bdytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, cc, adxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, bdytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
      if (cdytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, bb, -adxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, cdytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);
        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }

      temp32alen = scale_expansion_zeroelim(axtbctlen, axtbct, adxtail,temp32a);
      axtbcttlen = scale_expansion_zeroelim(bcttlen, bctt, adxtail, axtbctt);
      temp16alen = scale_expansion_zeroelim(axtbcttlen, axtbctt, 2.0 * adx,temp16a);
      temp16blen = scale_expansion_zeroelim(axtbcttlen, axtbctt, adxtail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
    if (adytail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(aytbclen, aytbc, adytail, temp16a);
      aytbctlen = scale_expansion_zeroelim(bctlen, bct, adytail, aytbct);
      temp32alen = scale_expansion_zeroelim(aytbctlen, aytbct, 2.0 * ady,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;


      temp32alen = scale_expansion_zeroelim(aytbctlen, aytbct, adytail,temp32a);
      aytbcttlen = scale_expansion_zeroelim(bcttlen, bctt, adytail, aytbctt);
      temp16alen = scale_expansion_zeroelim(aytbcttlen, aytbctt, 2.0 * ady,temp16a);
      temp16blen = scale_expansion_zeroelim(aytbcttlen, aytbctt, adytail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
  }
  if (bdxtail != 0.0 || bdytail != 0.0)
  {
    if (cdxtail != 0.0 || cdytail != 0.0 || adxtail != 0.0 || adytail != 0.0)
    {
      ti1 = cdxtail * ady;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, ady, ti1, ti0);

      tj1 = cdx * adytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdx, adytail, tj1, tj0);

      Two_Two_Sum(ti1, ti0, tj1, tj0, u3, u[2], u[1], u[0]);
      u[3] = u3;
      negate = -cdy;

      ti1 = adxtail * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, negate, ti1, ti0);

      negate = -cdytail;

      tj1 = adx * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adx, negate, tj1, tj0);

      Two_Two_Sum(ti1, ti0, tj1, tj0, v3, v[2], v[1], v[0]);
      v[3] = v3;
      catlen = fast_expansion_sum_zeroelim(4, u, 4, v, cat);

      ti1 = cdxtail * adytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, adytail, ti1, ti0);

      tj1 = adxtail * cdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, cdytail, tj1, tj0);

      catt3 = ti1 + ti0 - tj1 - tj0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(ti1, ti0, tj1, tj0, catt3, catt[2], catt[1], catt[0]);

      catt[3] = catt3;
      cattlen = 4;
    }
    else
    {
      cat[0] = 0.0;
      catlen = 1;
      catt[0] = 0.0;
      cattlen = 1;
    }

    if (bdxtail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(bxtcalen, bxtca, bdxtail, temp16a);
      bxtcatlen = scale_expansion_zeroelim(catlen, cat, bdxtail, bxtcat);
      temp32alen = scale_expansion_zeroelim(bxtcatlen, bxtcat, 2.0 * bdx,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (cdytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, aa, bdxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, cdytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
      if (adytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, cc, -bdxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, adytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }

      temp32alen = scale_expansion_zeroelim(bxtcatlen, bxtcat, bdxtail,temp32a);
      bxtcattlen = scale_expansion_zeroelim(cattlen, catt, bdxtail, bxtcatt);
      temp16alen = scale_expansion_zeroelim(bxtcattlen, bxtcatt, 2.0 * bdx,temp16a);
      temp16blen = scale_expansion_zeroelim(bxtcattlen, bxtcatt, bdxtail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
    if (bdytail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(bytcalen, bytca, bdytail, temp16a);
      bytcatlen = scale_expansion_zeroelim(catlen, cat, bdytail, bytcat);
      temp32alen = scale_expansion_zeroelim(bytcatlen, bytcat, 2.0 * bdy,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;

      temp32alen = scale_expansion_zeroelim(bytcatlen, bytcat, bdytail,temp32a);
      bytcattlen = scale_expansion_zeroelim(cattlen, catt, bdytail, bytcatt);
      temp16alen = scale_expansion_zeroelim(bytcattlen, bytcatt, 2.0 * bdy,temp16a);
      temp16blen = scale_expansion_zeroelim(bytcattlen, bytcatt, bdytail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
  }
  if (cdxtail != 0.0 || cdytail != 0.0)
  {
    if (adxtail != 0.0 || adytail != 0.0 || bdxtail != 0.0 || bdytail != 0.0)
    {
      ti1 = adxtail * bdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, bdy, ti1, ti0);

      tj1 = adx * bdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adx, bdytail, tj1, tj0);

      Two_Two_Sum(ti1, ti0, tj1, tj0, u3, u[2], u[1], u[0]);
      u[3] = u3;
      negate = -ady;

      ti1 = bdxtail * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, negate, ti1, ti0);

      negate = -adytail;

      tj1 = bdx * negate;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdx, negate, tj1, tj0);

      Two_Two_Sum(ti1, ti0, tj1, tj0, v3, v[2], v[1], v[0]);
      v[3] = v3;
      abtlen = fast_expansion_sum_zeroelim(4, u, 4, v, abt);

      ti1 = adxtail * bdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, bdytail, ti1, ti0);

      tj1 = bdxtail * adytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, adytail, tj1, tj0);

      abtt3 = ti1 + ti0 - tj1 - tj0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(ti1, ti0, tj1, tj0, abtt3, abtt[2], abtt[1], abtt[0]);

      abtt[3] = abtt3;
      abttlen = 4;
    }
    else
    {
      abt[0] = 0.0;
      abtlen = 1;
      abtt[0] = 0.0;
      abttlen = 1;
    }

    if (cdxtail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(cxtablen, cxtab, cdxtail, temp16a);
      cxtabtlen = scale_expansion_zeroelim(abtlen, abt, cdxtail, cxtabt);
      temp32alen = scale_expansion_zeroelim(cxtabtlen, cxtabt, 2.0 * cdx,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (adytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, bb, cdxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, adytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
      if (bdytail != 0.0)
      {
        temp8len = scale_expansion_zeroelim(4, aa, -cdxtail, temp8);
        temp16alen = scale_expansion_zeroelim(temp8len, temp8, bdytail,temp16a);
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp16alen,temp16a, finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }

      temp32alen = scale_expansion_zeroelim(cxtabtlen, cxtabt, cdxtail,temp32a);
      cxtabttlen = scale_expansion_zeroelim(abttlen, abtt, cdxtail, cxtabtt);
      temp16alen = scale_expansion_zeroelim(cxtabttlen, cxtabtt, 2.0 * cdx,temp16a);
      temp16blen = scale_expansion_zeroelim(cxtabttlen, cxtabtt, cdxtail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
    if (cdytail != 0.0)
    {
      temp16alen = scale_expansion_zeroelim(cytablen, cytab, cdytail, temp16a);
      cytabtlen = scale_expansion_zeroelim(abtlen, abt, cdytail, cytabt);
      temp32alen = scale_expansion_zeroelim(cytabtlen, cytabt, 2.0 * cdy,temp32a);
      temp48len = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp32alen, temp32a, temp48);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp48len,temp48, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;


      temp32alen = scale_expansion_zeroelim(cytabtlen, cytabt, cdytail,temp32a);
      cytabttlen = scale_expansion_zeroelim(abttlen, abtt, cdytail, cytabtt);
      temp16alen = scale_expansion_zeroelim(cytabttlen, cytabtt, 2.0 * cdy,temp16a);
      temp16blen = scale_expansion_zeroelim(cytabttlen, cytabtt, cdytail,temp16b);
      temp32blen = fast_expansion_sum_zeroelim(temp16alen, temp16a,temp16blen, temp16b, temp32b);
      temp64len = fast_expansion_sum_zeroelim(temp32alen, temp32a,temp32blen, temp32b, temp64);
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, temp64len,temp64, finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
    }
  }

  return finnow[finlength - 1];
}


double ribi::tricpp::incircle(
  int& m_m_incirclecount,
  //const Behavior& b,
  const bool b_m_noexact,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const Vertex& pd
)
{
  m_m_incirclecount++;

  const double adx = pa[0] - pd[0];
  const double bdx = pb[0] - pd[0];
  const double cdx = pc[0] - pd[0];
  const double ady = pa[1] - pd[1];
  const double bdy = pb[1] - pd[1];
  const double cdy = pc[1] - pd[1];

  const double bdxcdy = bdx * cdy;
  const double cdxbdy = cdx * bdy;
  const double alift = adx * adx + ady * ady;

  const double cdxady = cdx * ady;
  const double adxcdy = adx * cdy;
  const double blift = bdx * bdx + bdy * bdy;

  const double adxbdy = adx * bdy;
  const double bdxady = bdx * ady;
  const double clift = cdx * cdx + cdy * cdy;

  const double det = alift * (bdxcdy - cdxbdy)
      + blift * (cdxady - adxcdy)
      + clift * (adxbdy - bdxady);

  if (b_m_noexact)
  {
    return det;
  }

  const double permanent
    = (std::abs(bdxcdy) + std::abs(cdxbdy)) * alift
    + (std::abs(cdxady) + std::abs(adxcdy)) * blift
    + (std::abs(adxbdy) + std::abs(bdxady)) * clift
  ;
  const double errbound = Global().m_iccerrboundA * permanent;
  if (det > errbound || -det > errbound)
  {
    return det;
  }

  return incircleadapt(pa, pb, pc, pd, permanent);
}



double ribi::tricpp::orient3dadapt(
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const Vertex& pd,
  const double aheight,
  const double bheight,
  const double cheight,
  const double dheight,
  const double permanent
)
{
  //double det, errbound;
  //double bdxcdy1, cdxbdy1, cdxady1, adxcdy1, adxbdy1, bdxady1;
  const double bdxcdy0 = 0.0;
  const double cdxbdy0 = 0.0;
  const double cdxady0 = 0.0;
  const double adxcdy0 = 0.0;
  const double adxbdy0 = 0.0;
  const double bdxady0 = 0.0;
  //double bc[4], ca[4], ab[4];
  std::vector<double> bc(4,0.0);
  std::vector<double> ca(4,0.0);
  std::vector<double> ab(4,0.0);
  //double bc3, ca3, ab3;
  std::vector<double> adet(8,0.0);
  std::vector<double> bdet(8,0.0);
  std::vector<double> cdet(8,0.0);
  //double adet(8,0.0), bdet(8,0.0), cdet(8,0.0);
  std::vector<double> abdet(16,0.0);
  //double abdet[16];
  //double *finnow, *finother, *finswap;
  std::vector<double> fin1(192,0.0);
  std::vector<double> fin2(192,0.0);
  //double fin1[192], fin2[192];
  double adxtail, bdxtail, cdxtail;
  double adytail, bdytail, cdytail;
  double adheighttail, bdheighttail, cdheighttail;
  double at_blarge, at_clarge;
  double bt_clarge, bt_alarge;
  double ct_alarge, ct_blarge;
  std::vector<double> at_b(4,0.0);
  std::vector<double> at_c(4,0.0);
  std::vector<double> bt_c(4,0.0);
  std::vector<double> bt_a(4,0.0);
  std::vector<double> ct_a(4,0.0);
  std::vector<double> ct_b(4,0.0);
  int at_blen, at_clen, bt_clen, bt_alen, ct_alen, ct_blen;
  double bdxt_cdy1, cdxt_bdy1, cdxt_ady1;
  double adxt_cdy1, adxt_bdy1, bdxt_ady1;
  const double bdxt_cdy0 = 0.0;
  const double cdxt_bdy0 = 0.0;
  const double cdxt_ady0 = 0.0;
  const double adxt_cdy0 = 0.0;
  const double adxt_bdy0 = 0.0;
  const double bdxt_ady0 = 0.0;
  double bdyt_cdx1, cdyt_bdx1, cdyt_adx1;
  double adyt_cdx1, adyt_bdx1, bdyt_adx1;
  const double bdyt_cdx0 = 0.0;
  const double cdyt_bdx0 = 0.0;
  const double cdyt_adx0 = 0.0;
  const double adyt_cdx0 = 0.0;
  const double adyt_bdx0 = 0.0;
  const double bdyt_adx0 = 0.0;
  std::vector<double> bct(8,0.0);
  std::vector<double> cat(8,0.0);
  std::vector<double> abt(8,0.0);
  int bctlen, catlen, abtlen;
  double bdxt_cdyt1, cdxt_bdyt1, cdxt_adyt1;
  double adxt_cdyt1, adxt_bdyt1, bdxt_adyt1;
  const double bdxt_cdyt0 = 0.0;
  const double cdxt_bdyt0 = 0.0;
  const double cdxt_adyt0 = 0.0;
  const double adxt_cdyt0 = 0.0;
  const double adxt_bdyt0 = 0.0;
  const double bdxt_adyt0 = 0.0;
  std::vector<double> u(4,0.0);
  std::vector<double> v(12,0.0);
  std::vector<double> w(16,0.0);
  double u3;
  int vlength, wlength;
  double negate;

  const double adx = pa[0] - pd[0];
  const double bdx = pb[0] - pd[0];
  const double cdx = pc[0] - pd[0];
  const double ady = pa[1] - pd[1];
  const double bdy = pb[1] - pd[1];
  const double cdy = pc[1] - pd[1];
  const double adheight = aheight - dheight;
  const double bdheight = bheight - dheight;
  const double cdheight = cheight - dheight;

  double bdxcdy1 = bdx * cdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(bdx, cdy, bdxcdy1, bdxcdy0);

  double cdxbdy1 = cdx * bdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(cdx, bdy, cdxbdy1, cdxbdy0);

  double bc3 = bdxcdy1 + bdxcdy0 - cdxbdy1 - cdxbdy0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(bdxcdy1, bdxcdy0, cdxbdy1, cdxbdy0, bc3, bc[2], bc[1], bc[0]);

  bc[3] = bc3;
  const int alen = scale_expansion_zeroelim(4, bc, adheight, adet);

  double cdxady1 = cdx * ady;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(cdx, ady, cdxady1, cdxady0);

  double adxcdy1 = adx * cdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(adx, cdy, adxcdy1, adxcdy0);

  double ca3 = cdxady1 + cdxady0 - adxcdy1 - adxcdy0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(cdxady1, cdxady0, adxcdy1, adxcdy0, ca3, ca[2], ca[1], ca[0]);

  ca[3] = ca3;
  const int blen = scale_expansion_zeroelim(4, ca, bdheight, bdet);

  double adxbdy1 = adx * bdy;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(adx, bdy, adxbdy1, adxbdy0);

  double bdxady1 = bdx * ady;
  //Two_Product(a,b,x,y): x = a*b, y = 0.0;
  //Two_Product(bdx, ady, bdxady1, bdxady0);

  double ab3 = adxbdy1 + adxbdy0 - bdxady1 - bdxady0;
  //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
  //Two_Two_Diff(adxbdy1, adxbdy0, bdxady1, bdxady0, ab3, ab[2], ab[1], ab[0]);

  ab[3] = ab3;
  const int clen = scale_expansion_zeroelim(4, ab, cdheight, cdet);

  const int ablen = fast_expansion_sum_zeroelim(alen, adet, blen, bdet, abdet);
  int finlength = fast_expansion_sum_zeroelim(ablen, abdet, clen, cdet, fin1);

  double det = std::accumulate(fin1.begin(),fin1.end(),0.0);
  //double det = estimate(fin1);
  double errbound = Global().m_o3derrboundB * permanent;
  if ((det >= errbound) || (-det >= errbound)) {
    return det;
  }

  adxtail = -adx + pa[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[0], pd[0], adx, adxtail);

  bdxtail = -bdx + pb[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[0], pd[0], bdx, bdxtail);

  cdxtail = -cdx + pc[0] - pd[0];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pc[0], pd[0], cdx, cdxtail);

  adytail = -ady + pa[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pa[1], pd[1], ady, adytail);

  bdytail = -bdy + pb[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pb[1], pd[1], bdy, bdytail);

  cdytail = -cdy + pc[1] - pd[1];
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(pc[1], pd[1], cdy, cdytail);

  adheighttail = -adheight + aheight - dheight;
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(aheight, dheight, adheight, adheighttail);

  bdheighttail = -bdheight + bheight - dheight;
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(bheight, dheight, bdheight, bdheighttail);

  cdheighttail = -cdheight + cheight - dheight;
  //Two_Diff_Tail(a,b,x,y): y = -x + a - b;
  //Two_Diff_Tail(cheight, dheight, cdheight, cdheighttail);

  if (adxtail == 0.0 && bdxtail == 0.0 && cdxtail == 0.0
    && adytail == 0.0 && bdytail == 0.0 && cdytail == 0.0
    && adheighttail == 0.0 && bdheighttail == 0.0 && cdheighttail == 0.0
  )
  {
    return det;
  }

  errbound = Global().m_o3derrboundC * permanent + Global().m_resulterrbound * std::abs(det);
  det += (adheight * ((bdx * cdytail + cdy * bdxtail)
    - (bdy * cdxtail + cdx * bdytail))
    + adheighttail * (bdx * cdy - bdy * cdx))
    + (bdheight * ((cdx * adytail + ady * cdxtail)
    - (cdy * adxtail + adx * cdytail))
    + bdheighttail * (cdx * ady - cdy * adx))
    + (cdheight * ((adx * bdytail + bdy * adxtail)
    - (ady * bdxtail + bdx * adytail))
    + cdheighttail * (adx * bdy - ady * bdx))
  ;
  if (det >= errbound || -det >= errbound)
  {
    return det;
  }

  std::vector<double> finnow = fin1;
  std::vector<double> finother = fin2;

  if (adxtail == 0.0)
  {
    if (adytail == 0.0)
    {
      at_b[0] = 0.0;
      at_blen = 1;
      at_c[0] = 0.0;
      at_clen = 1;
    }
    else
    {
      negate = -adytail;

      at_blarge = negate * bdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, bdx, at_blarge, at_b[0]);

      at_b[1] = at_blarge;
      at_blen = 2;

      at_clarge = adytail * cdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adytail, cdx, at_clarge, at_c[0]);

      at_c[1] = at_clarge;
      at_clen = 2;
    }
  }
  else
  {
    if (adytail == 0.0)
    {
      at_blarge = adxtail * bdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, bdy, at_blarge, at_b[0]);

      at_b[1] = at_blarge;
      at_blen = 2;
      negate = -adxtail;

      at_clarge = negate * cdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, cdy, at_clarge, at_c[0]);

      at_c[1] = at_clarge;
      at_clen = 2;
    }
    else
    {
      adxt_bdy1 = adxtail * bdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, bdy, adxt_bdy1, adxt_bdy0);

      adyt_bdx1 = adytail * bdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adytail, bdx, adyt_bdx1, adyt_bdx0);

      at_blarge = adxt_bdy1 + adxt_bdy0 - adyt_bdx1 - adyt_bdx0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(adxt_bdy1, adxt_bdy0, adyt_bdx1, adyt_bdx0,at_blarge, at_b[2], at_b[1], at_b[0]);

      at_b[3] = at_blarge;
      at_blen = 4;

      adyt_cdx1 = adytail * cdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adytail, cdx, adyt_cdx1, adyt_cdx0);

      adxt_cdy1 = adxtail * cdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, cdy, adxt_cdy1, adxt_cdy0);

      at_clarge = adyt_cdx1 + adyt_cdx0 - adxt_cdy1 - adxt_cdy0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(adyt_cdx1, adyt_cdx0, adxt_cdy1, adxt_cdy0,at_clarge, at_c[2], at_c[1], at_c[0]);

      at_c[3] = at_clarge;
      at_clen = 4;
    }
  }
  if (bdxtail == 0.0)
  {
    if (bdytail == 0.0)
    {
      bt_c[0] = 0.0;
      bt_clen = 1;
      bt_a[0] = 0.0;
      bt_alen = 1;
    }
    else
    {
      negate = -bdytail;

      bt_clarge = negate * cdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, cdx, bt_clarge, bt_c[0]);

      bt_c[1] = bt_clarge;
      bt_clen = 2;

      bt_alarge = bdytail * adx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdytail, adx, bt_alarge, bt_a[0]);

      bt_a[1] = bt_alarge;
      bt_alen = 2;
    }
  }
  else
  {
    if (bdytail == 0.0)
    {
      bt_clarge = bdxtail * cdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, cdy, bt_clarge, bt_c[0]);

      bt_c[1] = bt_clarge;
      bt_clen = 2;
      negate = -bdxtail;

      bt_alarge = negate * ady;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, ady, bt_alarge, bt_a[0]);

      bt_a[1] = bt_alarge;
      bt_alen = 2;
    }
    else
    {
      bdxt_cdy1 = bdxtail * cdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, cdy, bdxt_cdy1, bdxt_cdy0);

      bdyt_cdx1 = bdytail * cdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdytail, cdx, bdyt_cdx1, bdyt_cdx0);

      bt_clarge = bdxt_cdy1 + bdxt_cdy0 - bdyt_cdx1 - bdyt_cdx0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(bdxt_cdy1, bdxt_cdy0, bdyt_cdx1, bdyt_cdx0,bt_clarge, bt_c[2], bt_c[1], bt_c[0]);

      bt_c[3] = bt_clarge;
      bt_clen = 4;

      bdyt_adx1 = bdytail * adx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdytail, adx, bdyt_adx1, bdyt_adx0);

      bdxt_ady1 = bdxtail * ady;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, ady, bdxt_ady1, bdxt_ady0);

      bt_alarge = bdyt_adx1 + bdyt_adx0 - bdxt_ady1 - bdxt_ady0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(bdyt_adx1, bdyt_adx0, bdxt_ady1, bdxt_ady0,bt_alarge, bt_a[2], bt_a[1], bt_a[0]);

      bt_a[3] = bt_alarge;
      bt_alen = 4;
    }
  }
  if (cdxtail == 0.0)
  {
    if (cdytail == 0.0)
    {
      ct_a[0] = 0.0;
      ct_alen = 1;
      ct_b[0] = 0.0;
      ct_blen = 1;
    }
    else
    {
      negate = -cdytail;

      ct_alarge = negate * adx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, adx, ct_alarge, ct_a[0]);

      ct_a[1] = ct_alarge;
      ct_alen = 2;

      ct_blarge = cdytail * bdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdytail, bdx, ct_blarge, ct_b[0]);

      ct_b[1] = ct_blarge;
      ct_blen = 2;
    }
  }
  else
  {
    if (cdytail == 0.0)
    {
      ct_alarge = cdxtail * ady;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, ady, ct_alarge, ct_a[0]);

      ct_a[1] = ct_alarge;
      ct_alen = 2;
      negate = -cdxtail;

      ct_blarge = negate * bdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, bdy, ct_blarge, ct_b[0]);

      ct_b[1] = ct_blarge;
      ct_blen = 2;
    }
    else
    {
      cdxt_ady1 = cdxtail * ady;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, ady, cdxt_ady1, cdxt_ady0);

      cdyt_adx1 = cdytail * adx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdytail, adx, cdyt_adx1, cdyt_adx0);

      ct_alarge = cdxt_ady1 + cdxt_ady0 - cdyt_adx1 - cdyt_adx0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(cdxt_ady1, cdxt_ady0, cdyt_adx1, cdyt_adx0,ct_alarge, ct_a[2], ct_a[1], ct_a[0]);

      ct_a[3] = ct_alarge;
      ct_alen = 4;

      cdyt_bdx1 = cdytail * bdx;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdytail, bdx, cdyt_bdx1, cdyt_bdx0);

      cdxt_bdy1 = cdxtail * bdy;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, bdy, cdxt_bdy1, cdxt_bdy0);

      ct_blarge = cdyt_bdx1 + cdyt_bdx0 - cdxt_bdy1 - cdxt_bdy0;
      //Two_Two_Diff(a1,a0,b1,b0,x3,x2,x1,x0): x3 = a1 + a0 - b0 - b1, x2 = 0.0, x1 = 0.0, x0 = 0.0
      //Two_Two_Diff(cdyt_bdx1, cdyt_bdx0, cdxt_bdy1, cdxt_bdy0,ct_blarge, ct_b[2], ct_b[1], ct_b[0]);

      ct_b[3] = ct_blarge;
      ct_blen = 4;
    }
  }

  bctlen = fast_expansion_sum_zeroelim(bt_clen, bt_c, ct_blen, ct_b, bct);
  wlength = scale_expansion_zeroelim(bctlen, bct, adheight, w);
  finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);
  //finswap = finnow; finnow = finother; finother = finswap;
  std::swap(finnow,finother);

  catlen = fast_expansion_sum_zeroelim(ct_alen, ct_a, at_clen, at_c, cat);
  wlength = scale_expansion_zeroelim(catlen, cat, bdheight, w);
  finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);

  std::swap(finnow,finother);
  //finswap = finnow; finnow = finother; finother = finswap;

  abtlen = fast_expansion_sum_zeroelim(at_blen, at_b, bt_alen, bt_a, abt);
  wlength = scale_expansion_zeroelim(abtlen, abt, cdheight, w);
  finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);
  std::swap(finnow,finother);
  //finswap = finnow; finnow = finother; finother = finswap;

  if (adheighttail != 0.0)
  {
    vlength = scale_expansion_zeroelim(4, bc, adheighttail, v);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, vlength, v,finother);
    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (bdheighttail != 0.0)
  {
    vlength = scale_expansion_zeroelim(4, ca, bdheighttail, v);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, vlength, v,finother);
    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (cdheighttail != 0.0)
  {
    vlength = scale_expansion_zeroelim(4, ab, cdheighttail, v);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, vlength, v,finother);
    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }

  if (adxtail != 0.0)
  {
    if (bdytail != 0.0)
    {
      adxt_bdyt1 = adxtail * bdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(adxtail, bdytail, adxt_bdyt1, adxt_bdyt0);

      Two_One_Product(adxt_bdyt1, adxt_bdyt0, cdheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (cdheighttail != 0.0)
      {
        Two_One_Product(adxt_bdyt1, adxt_bdyt0, cdheighttail,u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
    if (cdytail != 0.0)
    {
      negate = -adxtail;

      adxt_cdyt1 = negate * cdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, cdytail, adxt_cdyt1, adxt_cdyt0);

      Two_One_Product(adxt_cdyt1, adxt_cdyt0, bdheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (bdheighttail != 0.0)
      {
        Two_One_Product(adxt_cdyt1, adxt_cdyt0, bdheighttail,u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,
                                                finother);
        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
  }
  if (bdxtail != 0.0)
  {
    if (cdytail != 0.0)
    {
      bdxt_cdyt1 = bdxtail * cdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(bdxtail, cdytail, bdxt_cdyt1, bdxt_cdyt0);
      Two_One_Product(bdxt_cdyt1, bdxt_cdyt0, adheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (adheighttail != 0.0)
      {
        Two_One_Product(bdxt_cdyt1, bdxt_cdyt0, adheighttail,
                        u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
    if (adytail != 0.0)
    {
      negate = -bdxtail;

      bdxt_adyt1 = negate * adytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, adytail, bdxt_adyt1, bdxt_adyt0);

      Two_One_Product(bdxt_adyt1, bdxt_adyt0, cdheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (cdheighttail != 0.0) {
        Two_One_Product(bdxt_adyt1, bdxt_adyt0, cdheighttail,
                        u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
  }
  if (cdxtail != 0.0)
  {
    if (adytail != 0.0)
    {
      cdxt_adyt1 = cdxtail * adytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(cdxtail, adytail, cdxt_adyt1, cdxt_adyt0);

      Two_One_Product(cdxt_adyt1, cdxt_adyt0, bdheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (bdheighttail != 0.0) {
        Two_One_Product(cdxt_adyt1, cdxt_adyt0, bdheighttail,u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);
        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
    if (bdytail != 0.0)
    {
      negate = -cdxtail;

      cdxt_bdyt1 = negate * bdytail;
      //Two_Product(a,b,x,y): x = a*b, y = 0.0;
      //Two_Product(negate, bdytail, cdxt_bdyt1, cdxt_bdyt0);

      Two_One_Product(cdxt_bdyt1, cdxt_bdyt0, adheight, u3, u[2], u[1], u[0]);
      u[3] = u3;
      finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);

      std::swap(finnow,finother);
      //finswap = finnow; finnow = finother; finother = finswap;
      if (adheighttail != 0.0)
      {
        Two_One_Product(cdxt_bdyt1, cdxt_bdyt0, adheighttail,
                        u3, u[2], u[1], u[0]);
        u[3] = u3;
        finlength = fast_expansion_sum_zeroelim(finlength, finnow, 4, u,finother);

        std::swap(finnow,finother);
        //finswap = finnow; finnow = finother; finother = finswap;
      }
    }
  }

  if (adheighttail != 0.0)
  {
    wlength = scale_expansion_zeroelim(bctlen, bct, adheighttail, w);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (bdheighttail != 0.0) {
    wlength = scale_expansion_zeroelim(catlen, cat, bdheighttail, w);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }
  if (cdheighttail != 0.0) {
    wlength = scale_expansion_zeroelim(abtlen, abt, cdheighttail, w);
    finlength = fast_expansion_sum_zeroelim(finlength, finnow, wlength, w,finother);

    std::swap(finnow,finother);
    //finswap = finnow; finnow = finother; finother = finswap;
  }

  return finnow[finlength - 1];
}


double ribi::tricpp::orient3d(
  //Mesh& m,
  int& m_m_orient3dcount,
  const bool b_m_noexact,
  //const Behavior& b,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const Vertex& pd,
  const double aheight,
  const double bheight,
  const double cheight,
  const double dheight
)
{
  ++m_m_orient3dcount;

  const double adx = pa[0] - pd[0];
  const double bdx = pb[0] - pd[0];
  const double cdx = pc[0] - pd[0];
  const double ady = pa[1] - pd[1];
  const double bdy = pb[1] - pd[1];
  const double cdy = pc[1] - pd[1];
  const double adheight = aheight - dheight;
  const double bdheight = bheight - dheight;
  const double cdheight = cheight - dheight;

  const double bdxcdy = bdx * cdy;
  const double cdxbdy = cdx * bdy;

  const double cdxady = cdx * ady;
  const double adxcdy = adx * cdy;

  const double adxbdy = adx * bdy;
  const double bdxady = bdx * ady;

  const double det
      = adheight * (bdxcdy - cdxbdy)
      + bdheight * (cdxady - adxcdy)
      + cdheight * (adxbdy - bdxady);

  if (b_m_noexact) {
    return det;
  }

  const double permanent
    = (std::abs(bdxcdy) + std::abs(cdxbdy)) * std::abs(adheight)
    + (std::abs(cdxady) + std::abs(adxcdy)) * std::abs(bdheight)
    + (std::abs(adxbdy) + std::abs(bdxady)) * std::abs(cdheight)
  ;
  const double errbound = Global().m_o3derrboundA * permanent;
  if (det > errbound || -det > errbound)
  {
    return det;
  }

  return orient3dadapt(pa, pb, pc, pd, aheight, bheight, cheight, dheight,permanent);
}

double ribi::tricpp::nonregular(
  Mesh& m,
  const Behavior& b,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const Vertex& pd
)
{
  //if (b.m_weighted == 0)
  {
    return incircle(m, b, pa, pb, pc, pd);
  }
  /*
  else if (b.m_weighted == 1)
  {
    return orient3d(
      m, b, pa, pb, pc, pd,
      pa[0] * pa[0] + pa[1] * pa[1] - pa[2],
      pb[0] * pb[0] + pb[1] * pb[1] - pb[2],
      pc[0] * pc[0] + pc[1] * pc[1] - pc[2],
      pd[0] * pd[0] + pd[1] * pd[1] - pd[2]
    );
  }
  else
  {
    return orient3d(m, b, pa, pb, pc, pd, pa[2], pb[2], pc[2], pd[2]);
  }
  */
}


void ribi::tricpp::findcircumcenter(
  int& m_m_circumcentercount,
  int& m_m_counterclockcount,
  //Mesh& m,
  bool b_m_noexact,
  const double b_m_offconstant,
  //const Behavior& b,
  const Vertex& torg,
  const Vertex& tdest,
  const Vertex& tapex,
  Vertex& circumcenter,
  double * const xi,
  double * const eta,
  const int offcenter
)
{
  //double xdo, ydo, xao, yao;
  //double dodist, aodist, dadist;
  double denominator = 0.0;
  //double dx, dy, dxoff, dyoff;

  m_m_circumcentercount++;

  //Compute the circumcenter of the triangle.
  const double xdo = tdest[0] - torg[0];
  const double ydo = tdest[1] - torg[1];
  const double xao = tapex[0] - torg[0];
  const double yao = tapex[1] - torg[1];
  const double dodist = xdo * xdo + ydo * ydo;
  const double aodist = xao * xao + yao * yao;
  const double dadist = (tdest[0] - tapex[0]) * (tdest[0] - tapex[0])
    + (tdest[1] - tapex[1]) * (tdest[1] - tapex[1]);
  if (b_m_noexact)
  {
    denominator = 0.5 / (xdo * yao - xao * ydo);
  }
  else
  {
    //Use the counterclockwise() routine to ensure a positive (and
    //  reasonably accurate) result, avoiding any possibility of
    //  division by zero.
    denominator = 0.5 / counterclockwise(m_m_counterclockcount, b_m_noexact, tdest, tapex, torg);
    //Don't count the above as an orientation test.
    m_m_counterclockcount--;
  }
  double dx = (yao * dodist - ydo * aodist) * denominator;
  double dy = (xdo * aodist - xao * dodist) * denominator;

  //Find the (squared) length of the triangle's shortest edge.  This
  //  serves as a conservative estimate of the insertion radius of the
  //  circumcenter's parent.  The estimate is used to ensure that
  //  the algorithm terminates even if very small angles appear in
  //  the input PSLG.
  if (dodist < aodist && dodist < dadist)
  {
    if (offcenter && b_m_offconstant > 0.0)
    {
      //Find the position of the off-center, as described by Alper Ungor.
      const double dxoff = 0.5 * xdo - b_m_offconstant * ydo;
      const double dyoff = 0.5 * ydo + b_m_offconstant * xdo;
      //If the off-center is closer to the origin than the
      //  circumcenter, use the off-center instead.
      if (dxoff * dxoff + dyoff * dyoff < dx * dx + dy * dy)
      {
        dx = dxoff;
        dy = dyoff;
      }
    }
  }
  else if (aodist < dadist)
  {
    if (offcenter && (b_m_offconstant > 0.0))
    {
      const double dxoff = 0.5 * xao + b_m_offconstant * yao;
      const double dyoff = 0.5 * yao - b_m_offconstant * xao;
      //If the off-center is closer to the origin than the
      //  circumcenter, use the off-center instead.
      if (dxoff * dxoff + dyoff * dyoff < dx * dx + dy * dy)
      {
        dx = dxoff;
        dy = dyoff;
      }
    }
  }
  else
  {
    if (offcenter && (b_m_offconstant > 0.0))
    {
      const double dxoff = 0.5 * (tapex[0] - tdest[0]) - b_m_offconstant * (tapex[1] - tdest[1]);
      const double dyoff = 0.5 * (tapex[1] - tdest[1]) + b_m_offconstant * (tapex[0] - tdest[0]);
      //If the off-center is closer to the destination than the
      //  circumcenter, use the off-center instead.
      if (dxoff * dxoff + dyoff * dyoff < (dx - xdo) * (dx - xdo) + (dy - ydo) * (dy - ydo))
      {
        dx = xdo + dxoff;
        dy = ydo + dyoff;
      }
    }
  }

  circumcenter[0] = torg[0] + dx;
  circumcenter[1] = torg[1] + dy;

  //To interpolate vertex attributes for the new vertex inserted at
  //  the circumcenter, define a coordinate system with a xi-axis,
  //  directed from the triangle's origin to its destination, and
  //  an eta-axis, directed from its origin to its apex.
  //  Calculate the xi and eta coordinates of the circumcenter.
  *xi = (yao * dx - xao * dy) * (2.0 * denominator);
  *eta = (xdo * dy - ydo * dx) * (2.0 * denominator);
}



void ribi::tricpp::checkmesh(
  Mesh& m,
  Behavior& b
)
{
  Otri oppotri, oppooppotri;
  Vertex triorg, tridest, triapex;
  Triangle ptr;                         //Temporary variable used by sym().

  //Temporarily turn on exact arithmetic if it's off.
  const int saveexact = b.m_noexact;
  b.m_noexact = 0;
  if (!b.m_quiet) {  std::cout << "  Checking consistency of mesh...\n"; }
  //Run through the list of triangles, checking each one.
  //TraversalInit(&m.m_triangles);
  //triangleloop.m_tri = triangletraverse(m);
  //while (triangleloop.m_tri != nullptr)
  for (auto& my_triangle: m.m_triangles)
  {
    if (my_triangle.IsDead()) continue;
    Otri triangleloop;
    triangleloop.m_tri = my_triangle;

    //Check all three edges of the triangle.
    for (triangleloop.m_orient = 0; triangleloop.m_orient != 3; ++triangleloop.m_orient)
    {
      const auto triorg =  triangleloop.GetOrigin();
      //org(triangleloop, triorg);
      const auto tridest = triangleloop.GetDest();
      //const auto tridest = triangleloop.GetDest();
      if (triangleloop.m_orient == 0)
      {
        //Only test for inversion once.
        //Test if the triangle is flat or inverted.
        const auto triapex = triangleloop.GetApex();
        //const auto triapex = triangleloop.GetApex();
        assert(counterclockwise(m.m_counterclockcount, b.m_noexact, triorg, tridest, triapex) > 0.0);
        //if (counterclockwise(m.m_counterclockcount, b.m_noexact, triorg, tridest, triapex) <= 0.0)
        //{
        //  TRACE("ERROR");
        //  TRACE("Inverted triangle");
        //  TRACE(triangleloop);
        //}
      }
      //Find the neighboring triangle on this edge.
      sym(triangleloop, oppotri);
      if (oppotri.m_tri != m.m_dummytri)
      {
        //Check that the triangle's neighbor knows it's a neighbor.
        sym(oppotri, oppooppotri);
        assert(!(triangleloop.m_tri != oppooppotri.m_tri || triangleloop.m_orient != oppooppotri.m_orient));
        //if ((triangleloop.m_tri != oppooppotri.m_tri)        || (triangleloop.m_orient != oppooppotri.m_orient))
        //{
        //  TRACE("ERROR");
        //  std::cout << "  !! !! Asymmetric triangle-triangle bond:\n";
        //  if (triangleloop.m_tri == oppooppotri.m_tri)
        //  {
        //    std::cout << "   (Right triangle, wrong orientation)\n";
        //  }
        //  std::cout << "    First ";
        //  printtriangle(m, b, &triangleloop);
        //  std::cout << "    Second (nonreciprocating) ";
        //  printtriangle(m, b, &oppotri);
        //  assert(!"Should not get here");
        //}
        //Check that both triangles agree on the identities
        //  of their shared vertices.
        const auto oppoorg = oppotri.GetOrigin();
        //org(oppotri, oppoorg);
        const auto oppodest = oppotri.GetDest();
        //dest(oppotri, oppodest);
        assert(!(triorg != oppodest || tridest != oppoorg));
        //if ((triorg != oppodest) || (tridest != oppoorg))
        //{
        //  TRACE("ERROR");
        //  std::cout << "  !! !! Mismatched edge coordinates between two triangles:\n"
        //    << "    First mismatched ";
        //  printtriangle(m, b, &triangleloop);
        //  std::cout << "    Second mismatched ";
        //  printtriangle(m, b, &oppotri);
        //  assert(!"Should not get here");
        //}
      }
    }
    //triangleloop.m_tri = triangletraverse(m);
  }

  //Restore the status of exact arithmetic.
  b.m_noexact = saveexact;
}


void ribi::tricpp::checkdelaunay(
  Mesh& m,
  Behavior& b
)
{
  Otri triangleloop;
  Otri oppotri;
  Osub opposubseg;
  Vertex triorg, tridest, triapex;
  Vertex oppoapex;
  //int shouldbedelaunay;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  //Temporarily turn on exact arithmetic if it's off.
  const int saveexact = b.m_noexact;
  b.m_noexact = 0;
  //Run through the list of triangles, checking each one.

  //TraversalInit(&m.m_triangles);
  //triangleloop.m_tri = triangletraverse(m);
  //while (triangleloop.m_tri != (Triangle *) NULL)
  //{
  for (auto my_triangle: m.m_triangles)
  {
    if (my_triangle.IsDead()) continue;
    triangleloop.m_tri = my_triangle;
    //Check all three edges of the triangle.
    for (triangleloop.m_orient = 0; triangleloop.m_orient < 3;         triangleloop.m_orient++)
    {
      const auto triorg = triangleloop.GetOrigin();
      const auto tridest = triangleloop.GetDest();
      const auto triapex = triangleloop.GetApex();
      sym(triangleloop, oppotri);

      oppoapex = oppotri.GetApex();
      //GetApex(oppotri, oppoapex);

      //Only test that the edge is locally Delaunay if there is an
      //  adjoining triangle whose pointer is larger (to ensure that
      //  each pair isn't tested twice).
      bool shouldbedelaunay
        =    oppotri.m_tri != m.m_dummytri
          && !deadtri(oppotri.m_tri)
          && triangleloop.m_tri < oppotri.m_tri
          && triorg != m.m_infvertex1
          && triorg != m.m_infvertex2
          && triorg != m.m_infvertex3
          && tridest != m.m_infvertex1
          && tridest != m.m_infvertex2
          && tridest != m.m_infvertex3
          && triapex != m.m_infvertex1
          && triapex != m.m_infvertex2
          && triapex != m.m_infvertex3
          && oppoapex != m.m_infvertex1
          && oppoapex != m.m_infvertex2
          && oppoapex != m.m_infvertex3
        ;
      if (m.m_checksegments && shouldbedelaunay) {
        //If a subsegment separates the triangles, then the edge is
        //  constrained, so no local Delaunay test should be done.
        tspivot(triangleloop, opposubseg);
        if (opposubseg.m_subseg != m.m_dummysub){
          shouldbedelaunay = false;
        }
      }
      if (shouldbedelaunay)
      {
        if (nonregular(m, b, triorg, tridest, triapex, oppoapex) > 0.0)
        {
          assert(!"Should not get here");
          /*
          //if (!b.m_weighted)
          {
            std::cout
              << "  !! !! Non-Delaunay pair of triangles:\n"
              << "    First non-Delaunay ";
            printtriangle(m, b, &triangleloop);
            std::cout
              << "    Second non-Delaunay ";
          }
          else
          {
            std::cout
              << "  !! !! Non-regular pair of triangles:\n"
              << "    First non-regular ";
            printtriangle(m, b, &triangleloop);
            std::cout
              << "    Second non-regular ";
          }
          printtriangle(m, b, &oppotri);
          horrors++;
          */
        }
      }
    }
    //triangleloop.m_tri = triangletraverse(m);
  }
  //Restore the status of exact arithmetic.
  b.m_noexact = saveexact;
}

void ribi::tricpp::enqueuebadtriang(
  Mesh& m,
  const Behavior& b,
  BadTriang * const badtri
)
{
  double length, multiplier;
  int exponent, expincrement;
  int queuenumber;
  int posexponent;

  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Queueing bad triangle:\n");
    std::cout << "    (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
           badtri->m_triangorg[0], badtri->m_triangorg[1],
           badtri->m_triangdest[0], badtri->m_triangdest[1],
           badtri->m_triangapex[0], badtri->m_triangapex[1]);
  }
  */
  //Determine the appropriate queue to put the bad triangle into.
  //  Recall that the key is the square of its shortest edge length.
  if (badtri->m_key >= 1.0)
  {
    length = badtri->m_key;
    posexponent = 1;
  }
  else
  {
    //`badtri->key' is 2.0 to a negative exponent, so we'll record that
    //  fact and use the reciprocal of `badtri->key', which is > 1.0.
    length = 1.0 / badtri->m_key;
    posexponent = 0;
  }
  //`length' is approximately 2.0 to what exponent?  The following code
  //  determines the answer in time logarithmic in the exponent.
  exponent = 0;
  while (length > 2.0)
  {
    //Find an approximation by repeated squaring of two.
    expincrement = 1;
    multiplier = 0.5;
    while (length * multiplier * multiplier > 1.0)
    {
      expincrement *= 2;
      multiplier *= multiplier;
    }
    //Reduce the value of `length', then iterate if necessary.
    exponent += expincrement;
    length *= multiplier;
  }
  //`length' is approximately squareroot(2.0) to what exponent?
  exponent = 2.0 * exponent + (length > boost::math::constants::root_two<double>());
  //`exponent' is now in the range 0...2047 for IEEE double precision.
  //  Choose a queue in the range 0...4095.  The shortest edges have the
  //  highest priority (queue 4095).
  if (posexponent)
  {
    queuenumber = 2047 - exponent;
  }
  else
  {
    queuenumber = 2048 + exponent;
  }

  //Are we inserting into an empty queue?
  if (m.m_queuefront[queuenumber] == nullptr)
  {
    //Yes, we are inserting into an empty queue.
    //  Will this become the highest-priority queue?
    if (queuenumber > m.m_firstnonemptyq)
    {
      //Yes, this is the highest-priority queue.
      m.m_nextnonemptyq[queuenumber] = m.m_firstnonemptyq;
      m.m_firstnonemptyq = queuenumber;
    }
    else
    {
      //No, this is not the highest-priority queue.
      //  Find the queue with next higher priority.
      int i = queuenumber + 1;
      while (m.m_queuefront[i] == nullptr)
      {
        i++;
      }
      //Mark the newly nonempty queue as following a higher-priority queue.
      m.m_nextnonemptyq[queuenumber] = m.m_nextnonemptyq[i];
      m.m_nextnonemptyq[i] = queuenumber;
    }
    //Put the bad triangle at the beginning of the (empty) queue.
    m.m_queuefront[queuenumber] = badtri;
  }
  else
  {
    //Add the bad triangle to the end of an already nonempty queue.
    m.m_queuetail[queuenumber]->m_nexttriang = badtri;
  }
  //Maintain a pointer to the last triangle of the queue.
  m.m_queuetail[queuenumber] = badtri;
  //Newly enqueued bad triangle has no successor in the queue.
  badtri->m_nexttriang = nullptr;
}

void ribi::tricpp::enqueuebadtri(
  Mesh& m,
  const Behavior& b,
  const Otri& enqtri,
  const double minedge,
  const Vertex& enqapex,
  const Vertex& enqorg,
  const Vertex& enqdest
)
{
  BadTriang newbad;

  //Allocate space for the bad triangle.
  //newbad = (struct BadTriang *) PoolAlloc(&m.m_badtriangles);
  newbad.m_poortri = enqtri.m_tri; //encode(*enqtri);
  newbad.m_key = minedge;
  newbad.m_triangapex = enqapex;
  newbad.m_triangorg = enqorg;
  newbad.m_triangdest = enqdest;
  enqueuebadtriang(m, b, newbad);
}

ribi::tricpp::BadTriang * ribi::tricpp::dequeuebadtriang(
  Mesh& m
)
{
  BadTriang *result = nullptr;

  //If no queues are nonempty, return NULL.
  if (m.m_firstnonemptyq < 0)
  {
    return nullptr;
  }
  //Find the first triangle of the highest-priority queue.
  result = m.m_queuefront[m.m_firstnonemptyq];
  //Remove the triangle from the queue.
  m.m_queuefront[m.m_firstnonemptyq] = result->m_nexttriang;
  //If this queue is now empty, note the new highest-priority
  //  nonempty queue.
  if (result == m.m_queuetail[m.m_firstnonemptyq])
  {
    m.m_firstnonemptyq = m.m_nextnonemptyq[m.m_firstnonemptyq];
  }
  return result;
}

int ribi::tricpp::checkseg4encroach(
  Mesh& m,
  const Behavior& b,
  const Osub * const testsubseg
)
{
  Otri neighbortri;
  Osub testsym;
  BadSubSeg *encroachedseg;
  double dotproduct;
  int encroached;
  int sides;
  Vertex eorg, edest, eapex;
  Triangle ptr;                     //Temporary variable used by stpivot().

  encroached = 0;
  sides = 0;

  eorg = testsubseg->GetOrigin();
  //GetOrigin(*testsubseg, eorg);

  edest = testsubseg->GetDest();
  //GetDest(*testsubseg, edest);

  //Check one neighbor of the subsegment.
  stpivot(*testsubseg, neighbortri);
  //Does the neighbor exist, or is this a boundary edge?
  if (neighbortri.m_tri != m.m_dummytri)
  {
    sides++;
    //Find a vertex opposite this subsegment.
    eapex = neighbortri->GetApex();
    //GetApex(neighbortri, eapex);
    //Check whether the apex is in the diametral lens of the subsegment
    //  (the diametral circle if `conformdel' is set).  A dot product
    //  of two sides of the triangle is used to check whether the angle
    //  at the apex is greater than (180 - 2 `minangle') degrees (for
    //  lenses; 90 degrees for diametral circles).
    dotproduct
      = (eorg[0] - eapex[0]) * (edest[0] - eapex[0])
      + (eorg[1] - eapex[1]) * (edest[1] - eapex[1])
    ;
    if (dotproduct < 0.0)
    {
      if (b.m_conformdel
        || (dotproduct * dotproduct >= (2.0 * b.m_goodangle - 1.0) * (2.0 * b.m_goodangle - 1.0)
          * ((eorg[0] - eapex[0]) * (eorg[0] - eapex[0])
          +  (eorg[1] - eapex[1]) * (eorg[1] - eapex[1]))
          * ((edest[0] - eapex[0]) * (edest[0] - eapex[0])
          +  (edest[1] - eapex[1]) * (edest[1] - eapex[1])))
      )
      {
        encroached = 1;
      }
    }
  }
  //Check the other neighbor of the subsegment.
  ssym(*testsubseg, testsym);
  stpivot(testsym, neighbortri);
  //Does the neighbor exist, or is this a boundary edge?
  if (neighbortri.m_tri != m.m_dummytri)
  {
    sides++;
    //Find the other vertex opposite this subsegment.
    eapex = neighbortri->GetApex();
    //GetApex(neighbortri, eapex);

    //Check whether the apex is in the diametral lens of the subsegment
    //  (or the diametral circle, if `conformdel' is set).
    dotproduct
      = (eorg[0] - eapex[0]) * (edest[0] - eapex[0])
      + (eorg[1] - eapex[1]) * (edest[1] - eapex[1])
    ;
    if (dotproduct < 0.0)
    {
      if (b.m_conformdel ||
          (dotproduct * dotproduct >=
           (2.0 * b.m_goodangle - 1.0) * (2.0 * b.m_goodangle - 1.0) *
           ((eorg[0] - eapex[0]) * (eorg[0] - eapex[0]) +
            (eorg[1] - eapex[1]) * (eorg[1] - eapex[1])) *
           ((edest[0] - eapex[0]) * (edest[0] - eapex[0]) +
            (edest[1] - eapex[1]) * (edest[1] - eapex[1]))))
      {
        encroached += 2;
      }
    }
  }

  if (encroached && (!b.m_nobisect || ((b.m_nobisect == 1) && (sides == 2))))
  {
    /*
    if (b.m_verbosity > 2)
    {
      std::cout <<
        "  Queueing encroached subsegment (%.12g, %.12g) (%.12g, %.12g).\n",
        eorg[0], eorg[1], edest[0], edest[1]);
    }
    */
    //Add the subsegment to the list of encroached subsegments.
    //  Be sure to get the orientation right.
    BadSubSeg encroachedseg;
    //encroachedseg = (struct BadSubSeg *) PoolAlloc(&m.m_badsubsegs);
    if (encroached == 1)
    {
      encroachedseg->m_encsubseg = sencode(*testsubseg);
      encroachedseg->m_subsegorg = eorg;
      encroachedseg->m_subsegdest = edest;
    }
    else
    {
      encroachedseg->m_encsubseg = sencode(testsym);
      encroachedseg->m_subsegorg = edest;
      encroachedseg->m_subsegdest = eorg;
    }
  }

  return encroached;
}

void ribi::tricpp::testtriangle(
  Mesh& m,
  const Behavior& b,
  const Otri * const testtri
)
{
  Otri tri1, tri2;
  Osub testsub;
  //Vertex torg, tdest, tapex;
  Vertex base1, base2;
  Vertex org1, dest1, org2, dest2;
  Vertex joinvertex;
  //double dxod, dyod, dxda, dyda, dxao, dyao;
  //double dxod2, dyod2, dxda2, dyda2, dxao2, dyao2;
  //double apexlen, orglen, destlen, minedge;
  double minedge;
  double angle;
  double area;
  double dist1, dist2;
  SubSeg sptr;                      //Temporary variable used by tspivot().
  Triangle ptr;           //Temporary variable used by oprev() and dnext().

  const auto torg = testtri->GetOrigin();
  const auto tdest = testtri->GetDest();//dest(*testtri, tdest);
  const auto tapex = testtri->GetApex();//apex(*testtri, tapex);
  const double dxod = torg[0] - tdest[0];
  const double dyod = torg[1] - tdest[1];
  const double dxda = tdest[0] - tapex[0];
  const double dyda = tdest[1] - tapex[1];
  const double dxao = tapex[0] - torg[0];
  const double dyao = tapex[1] - torg[1];
  const double dxod2 = dxod * dxod;
  const double dyod2 = dyod * dyod;
  const double dxda2 = dxda * dxda;
  const double dyda2 = dyda * dyda;
  const double dxao2 = dxao * dxao;
  const double dyao2 = dyao * dyao;
  //Find the lengths of the triangle's three edges.
  const double apexlen = dxod2 + dyod2;
  const double orglen = dxda2 + dyda2;
  const double destlen = dxao2 + dyao2;

  if (apexlen < orglen && apexlen < destlen)
  {
    //The edge opposite the apex is shortest.
    minedge = apexlen;
    //Find the square of the cosine of the angle at the apex.
    angle = dxda * dxao + dyda * dyao;
    angle = angle * angle / (orglen * destlen);
    base1 = torg;
    base2 = tdest;
    //otricopy(*testtri, tri1);
    tri1 = *testtri;
  }
  else if (orglen < destlen)
  {
    //The edge opposite the origin is shortest.
    minedge = orglen;
    //Find the square of the cosine of the angle at the origin.
    angle = dxod * dxao + dyod * dyao;
    angle = angle * angle / (apexlen * destlen);
    base1 = tdest;
    base2 = tapex;
    lnext(*testtri, tri1);
  }
  else
  {
    //The edge opposite the destination is shortest.
    minedge = destlen;
    //Find the square of the cosine of the angle at the destination.
    angle = dxod * dxda + dyod * dyda;
    angle = angle * angle / (apexlen * orglen);
    base1 = tapex;
    base2 = torg;
    lprev(*testtri, tri1);
  }

  if (b.m_vararea || b.m_fixedarea || b.m_usertest)
  {
    //Check whether the area is larger than permitted.
    area = 0.5 * (dxod * dyda - dyod * dxda);
    if (b.m_fixedarea && (area > b.m_maxarea))
    {
      //Add this triangle to the list of bad triangles.
      enqueuebadtri(m, b, testtri, minedge, tapex, torg, tdest);
      return;
    }

    //Nonpositive area constraints are treated as unconstrained.
    if ((b.m_vararea) && area > areabound(*testtri) &&
        (areabound(*testtri) > 0.0))
    {
      //Add this triangle to the list of bad triangles.
      enqueuebadtri(m, b, testtri, minedge, tapex, torg, tdest);
      return;
    }

    if (b.m_usertest)
    {
      //Check whether the user thinks this triangle is too large.
      if (IsTriangleUnsuitable(torg, tdest, tapex)) {
        enqueuebadtri(m, b, testtri, minedge, tapex, torg, tdest);
        return;
      }
    }
  }

  //Check whether the angle is smaller than permitted.
  if (angle > b.m_goodangle)
  {
    //Use the rules of Miller, Pav, and Walkington to decide that certain
    //  triangles should not be split, even if they have bad angles.
    //  A skinny triangle is not split if its shortest edge subtends a
    //  small input angle, and both endpoints of the edge lie on a
    //  concentric circular shell.  For convenience, I make a small
    //  adjustment to that rule:  I check if the endpoints of the edge
    //  both lie in segment interiors, equidistant from the apex where
    //  the two segments meet.
    //First, check if both points lie in segment interiors.
    if (base1.GetVertexType() == VertexType::SEGMENTVERTEX &&
        base2.GetVertexType() == VertexType::SEGMENTVERTEX)
    {
      //Check if both points lie in a common segment.  If they do, the
      //  skinny triangle is enqueued to be split as usual.
      tspivot(tri1, testsub);
      if (testsub.m_subseg == m.m_dummysub)
      {
        //No common segment.  Find a subsegment that contains `torg'.
        tri2 = tri1;
        //otricopy(tri1, tri2);
        do
        {
          oprevself(tri1);
          tspivot(tri1, testsub);
        } while (testsub.m_subseg == m.m_dummysub);
        //Find the endpoints of the containing segment.
        org1 = testsub.GetOrg();
        //GetOrg(testsub, org1);

        dest1 = testsub.GetDest();
        //GetDest(testsub, dest1);

        //Find a subsegment that contains `tdest'.
        do
        {
          dnextself(tri2);
          tspivot(tri2, testsub);
        } while (testsub.m_subseg == m.m_dummysub);
        //Find the endpoints of the containing segment.

        org2 = testsub.GetOrigin();
        //GetOrg(testsub, org2);

        dest2 = testsub.GetDest();
        //GetDest(testsub, dest2);

        //Check if the two containing segments have an endpoint in common.
        joinvertex = nullptr;
        if ((dest1[0] == org2[0]) && (dest1[1] == org2[1]))
        {
          joinvertex = dest1;
        }
        else if ((org1[0] == dest2[0]) && (org1[1] == dest2[1]))
        {
          joinvertex = org1;
        }
        if (joinvertex != nullptr)
        {
          //Compute the distance from the common endpoint (of the two
          //  segments) to each of the endpoints of the shortest edge.
          dist1 = ((base1[0] - joinvertex[0]) * (base1[0] - joinvertex[0]) +
                   (base1[1] - joinvertex[1]) * (base1[1] - joinvertex[1]));
          dist2 = ((base2[0] - joinvertex[0]) * (base2[0] - joinvertex[0]) +
                   (base2[1] - joinvertex[1]) * (base2[1] - joinvertex[1]));
          //If the two distances are equal, don't split the triangle.
          if ((dist1 < 1.001 * dist2) && (dist1 > 0.999 * dist2))
          {
            //Return now to avoid enqueueing the bad triangle.
            return;
          }
        }
      }
    }

    //Add this triangle to the list of bad triangles.
    enqueuebadtri(m, b, testtri, minedge, tapex, torg, tdest);
  }
}

void ribi::tricpp::makevertexmap(
  Mesh& m,
  const Behavior& b
)
{
  //Otri triangleloop;
  //Vertex triorg;
  /*
  if (b.m_verbosity)
  {
    std::cout << "    Constructing mapping from vertices to triangles.\n";
  }
  */
  //TraversalInit(&m.m_triangles);
  for (auto my_triangle: m.m_triangles)
  {
    if (my_triangle.IsDead()) continue;
    Otri triangleloop;
    triangleloop.tri = my_triangle;
    for (triangleloop.m_orient = 0; triangleloop.m_orient != 3; ++triangleloop.m_orient)
    {
      Vertex triorg = triangleloop.GetOrigin();
      //org(triangleloop, triorg);

      triorg = triangleloop.m_tri;
      //setvertex2tri(triorg, encode(triangleloop));
    }

  }
  /*
  triangleloop.m_tri = triangletraverse(m);
  while (triangleloop.m_tri != (Triangle *) NULL) {
    //Check all three vertices of the triangle.
    for (triangleloop.m_orient = 0; triangleloop.m_orient < 3;
         triangleloop.m_orient++) {
      org(triangleloop, triorg);
      setvertex2tri(triorg, encode(triangleloop));
    }
    triangleloop.m_tri = triangletraverse(m);
  }
  */
}

ribi::tricpp::LocateResult ribi::tricpp::preciselocate(
  Mesh& m,
  const Behavior& b,
  const Vertex& searchpoint,
  Otri * const searchtri,
  const int stopatsubsegment
)
{
  Otri backtracktri;
  Osub checkedge;
  //Vertex forg, fdest, fapex;
  //double orgorient, destorient;
  int moveleft;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  /*
  if (b.m_verbosity > 2)
  {
    std::cout << "  Searching for point (%.12g, %.12g).\n",
           searchpoint[0], searchpoint[1]);
  }
  */
  //Where are we?

  Vertex forg = searchtri->GetOrigin();
  //org(*searchtri, forg);

  Vertex fdest = searchtri->GetDest();
  //dest(*searchtri, fdest);

  Vertex fapex = searchtri->GetApex();
  //apex(*searchtri, fapex);

  while (1)
  {
    /*
    if (b.m_verbosity > 2) {
      std::cout << "    At (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
             forg[0], forg[1], fdest[0], fdest[1], fapex[0], fapex[1]);
    }
    */
    //Check whether the apex is the point we seek.
    if (fapex[0] == searchpoint[0] && fapex[1] == searchpoint[1])
    {
      lprevself(*searchtri);
      return ONVERTEX;
    }
    //Does the point lie on the other side of the line defined by the
    //  triangle edge opposite the triangle's destination?
    const double destorient = counterclockwise(m.m_counterclockcount, b.m_noexact, forg, fapex, searchpoint);
    //Does the point lie on the other side of the line defined by the
    //  triangle edge opposite the triangle's origin?
    const double orgorient = counterclockwise(m.m_counterclockcount, b.m_noexact, fapex, fdest, searchpoint);
    if (destorient > 0.0)
    {
      if (orgorient > 0.0)
      {
        //Move left if the inner product of (fapex - searchpoint) and
        //  (fdest - forg) is positive.  This is equivalent to drawing
        //  a line perpendicular to the line (forg, fdest) and passing
        //  through `fapex', and determining which side of this line
        //  `searchpoint' falls on.
        moveleft = (fapex[0] - searchpoint[0]) * (fdest[0] - forg[0]) +
                   (fapex[1] - searchpoint[1]) * (fdest[1] - forg[1]) > 0.0;
      }
      else
      {
        moveleft = 1;
      }
    }
    else
    {
      if (orgorient > 0.0)
      {
        moveleft = 0;
      }
      else
      {
        //The point we seek must be on the boundary of or inside this
        //  triangle.
        if (destorient == 0.0)
        {
          lprevself(*searchtri);
          return ONEDGE;
        }
        if (orgorient == 0.0)
        {
          lnextself(*searchtri);
          return ONEDGE;
        }
        return INTRIANGLE;
      }
    }

    //Move to another triangle.  Leave a trace `backtracktri' in case
    //  floating-point roundoff or some such bogey causes us to walk
    //  off a boundary of the triangulation.
    if (moveleft)
    {
      lprev(*searchtri, backtracktri);
      fdest = fapex;
    }
    else
    {
      lnext(*searchtri, backtracktri);
      forg = fapex;
    }
    sym(backtracktri, *searchtri);

    if (m.m_checksegments && stopatsubsegment)
    {
      //Check for walking through a subsegment.
      tspivot(backtracktri, checkedge);
      if (checkedge.m_subseg != m.m_dummysub)
      {
        //Go back to the last triangle.
        *searchtri = backtracktri;
        //otricopy(backtracktri, *searchtri);
        return OUTSIDE;
      }
    }
    //Check for walking right out of the triangulation.
    if (searchtri->m_tri == m.m_dummytri)
    {
      //Go back to the last triangle.
      *searchtri = backtracktri;
      //otricopy(backtracktri, *searchtri);
      return OUTSIDE;
    }

    fapex = searchtri->GetApex();
    //GetApex(*searchtri, fapex);
  }
}


ribi::tricpp::LocateResult ribi::tricpp::locate(
  Mesh& m,
  const Behavior& b,
  const Vertex& searchpoint,
  Otri * const searchtri
)
{
  void **sampleblock = nullptr;
  char *firsttri = nullptr;
  Otri sampletri;
  Vertex torg, tdest;
  unsigned long alignptr;
  double searchdist, dist;
  double ahead;
  long samplesperblock, totalsamplesleft, samplesleft;
  long population, totalpopulation;
  Triangle ptr;                         //Temporary variable used by sym().
  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Randomly sampling for a triangle near point (%.12g, %.12g).\n",
           searchpoint[0], searchpoint[1]);
  }
  */
  //Record the distance from the suggested starting triangle to the
  //  point we seek.

  Vertex torg = searchtri->GetOrigin();
  //org(*searchtri, torg);

  double searchdist = (searchpoint[0] - torg[0]) * (searchpoint[0] - torg[0]) +
               (searchpoint[1] - torg[1]) * (searchpoint[1] - torg[1]);
  /*
  if (b.m_verbosity > 2) {
    std::cout << "    Boundary triangle has origin (%.12g, %.12g).\n",
           torg[0], torg[1]);
  }
  */
  //If a recently encountered triangle has been recorded and has not been
  //  deallocated, test it as a good starting point.
  if (m.m_recenttri.m_tri != nullptr)
  {
    if (!deadtri(m.m_recenttri.m_tri))
    {
      torg = m.m_recenttri.GetOrigin();
      //org(m.m_recenttri, torg);

      if (torg[0] == searchpoint[0] && torg[1] == searchpoint[1])
      {
        *searchtri = m.m_recenttri;
        //otricopy(m.m_recenttri, *searchtri);
        return ONVERTEX;
      }
      dist = (searchpoint[0] - torg[0]) * (searchpoint[0] - torg[0]) +
             (searchpoint[1] - torg[1]) * (searchpoint[1] - torg[1]);
      if (dist < searchdist)
      {
        *searchtri = m.m_recenttri;
        //otricopy(m.m_recenttri, *searchtri);
        searchdist = dist;
        /*
        if (b.m_verbosity > 2) {
          std::cout << "    Choosing recent triangle with origin (%.12g, %.12g).\n",
                 torg[0], torg[1]);
        }
        */
      }
    }
  }

  //The number of random samples taken is proportional to the cube root of
  //  the number of triangles in the mesh.  The next bit of code assumes
  //  that the number of triangles increases monotonically (or at least
  //  doesn't decrease enough to matter).
  while (SAMPLEFACTOR * m.m_samples * m.m_samples * m.m_samples < m.m_triangles.m_items)
  {
    m.m_samples++;
  }

  //We'll draw ceiling(samples * triangles_per_block / maxitems) random samples
  //  from each block of triangles (except the first)--until we meet the
  //  sample quota.  The ceiling means that blocks at the end might be
  //  neglected, but I don't care.
  samplesperblock = (m.m_samples * g_triangles_per_block - 1) / m.m_triangles.m_maxitems + 1;
  //We'll draw ceiling(samples * itemsfirstblock / maxitems) random samples
  //  from the first block of triangles.
  samplesleft = (m.m_samples * m.m_triangles.m_itemsfirstblock - 1) /
                m.m_triangles.m_maxitems + 1;
  totalsamplesleft = m.m_samples;
  population = m.m_triangles.m_itemsfirstblock;
  totalpopulation = m.m_triangles.m_maxitems;
  sampleblock = m.m_triangles.m_firstblock;
  sampletri.m_orient = 0;
  while (totalsamplesleft > 0)
  {
    //If we're in the last block, `population' needs to be corrected.
    if (population > totalpopulation)
    {
      population = totalpopulation;
    }
    //Find a pointer to the first triangle in the block.
    alignptr = (unsigned long) (sampleblock + 1);
    firsttri = (char *) (alignptr +
                         (unsigned long) m.m_triangles.m_alignbytes -
                         (alignptr %
                          (unsigned long) m.m_triangles.m_alignbytes));

    //Choose `samplesleft' randomly sampled triangles in this block.
    do {
      sampletri.m_tri = (Triangle *) (firsttri +
                                    (DumbRand(population) *
                                     m.m_triangles.m_itembytes));
      if (!deadtri(sampletri.m_tri))
      {
        torg = sampletri.GetOrigin();
        //GetOrigin(sampletri, torg);

        dist = (searchpoint[0] - torg[0]) * (searchpoint[0] - torg[0]) +
               (searchpoint[1] - torg[1]) * (searchpoint[1] - torg[1]);
        if (dist < searchdist)
        {
          searchtri = sampletri;
          //otricopy(sampletri, *searchtri);
          searchdist = dist;
          /*
          if (b.m_verbosity > 2) {
            std::cout << "    Choosing triangle with origin (%.12g, %.12g).\n",
                   torg[0], torg[1]);
          }
          */
        }
      }

      samplesleft--;
      totalsamplesleft--;
    } while (samplesleft > 0 && totalsamplesleft > 0);

    if (totalsamplesleft > 0)
    {
      sampleblock = (void **) *sampleblock;
      samplesleft = samplesperblock;
      totalpopulation -= population;
      population = g_triangles_per_block;
    }
  }

  //Where are we?
  const auto torg = searchtri->GetOrigin();
  //org(*searchtri, torg);

  const auto tdest = searchtri->GetDest();
  //dest(*searchtri, tdest);
  //Check the starting triangle's vertices.
  if (torg[0] == searchpoint[0] && torg[1] == searchpoint[1])
  {
    return ONVERTEX;
  }
  if (tdest[0] == searchpoint[0] && tdest[1] == searchpoint[1])
  {
    lnextself(*searchtri);
    return ONVERTEX;
  }
  //Orient `searchtri' to fit the preconditions of calling preciselocate().
  ahead = counterclockwise(m.m_counterclockcount, b.m_noexact, torg, tdest, searchpoint);
  if (ahead < 0.0)
  {
    //Turn around so that `searchpoint' is to the left of the
    //  edge specified by `searchtri'.
    symself(*searchtri);
  }
  else if (ahead == 0.0)
  {
    //Check if `searchpoint' is between `torg' and `tdest'.
    if (((torg[0] < searchpoint[0]) == (searchpoint[0] < tdest[0]))
      &&((torg[1] < searchpoint[1]) == (searchpoint[1] < tdest[1])))
    {
      return ONEDGE;
    }
  }
  return preciselocate(m, b, searchpoint, searchtri, 0);
}

void ribi::tricpp::insertsubseg(
  Mesh& m,
  const Behavior& b,
  const Otri * const tri,
  const int subsegmark
)
{
  Otri oppotri;
  Osub newsubseg;
  //Vertex triorg, tridest;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  const auto triorg = tri->GetOrigin();
  //org(*tri, triorg);
  const auto tridest = tri->GetDest();
  //dest(*tri, tridest);

  //Mark vertices if possible.
  if (triorg.GetVertexMark() == 0)
  {
    triorg.SetMark(subsegmark);
    //setvertexmark(triorg, subsegmark);
  }
  if (tridest.GetVertexMark() == 0)
  {
    tridest.SetMark(subsegmark);
    //setvertexmark(tridest, subsegmark);
  }
  //Check if there's already a subsegment here.
  tspivot(*tri, newsubseg);
  if (newsubseg.m_subseg == m.m_dummysub)
  {
    //Make new subsegment and initialize its vertices.
    makesubseg(m, &newsubseg);

    newsubseg.SetOrigin(tridest);
    //SetsOrigin(newsubseg, tridest);

    newsubseg.SetDest(triorg);
    //SetDest(newsubseg, triorg);

    setsegorg(newsubseg, tridest);
    setsegdest(newsubseg, triorg);
    //Bond new subsegment to the two triangles it is sandwiched between.
    //  Note that the facing triangle `oppotri' might be equal to
    //  `dummytri' (outer space), but the new subsegment is bonded to it
    //  all the same.
    tsbond(*tri, newsubseg);
    sym(*tri, oppotri);
    ssymself(newsubseg);
    tsbond(oppotri, newsubseg);
    setmark(newsubseg, subsegmark);
    /*
    if (b.m_verbosity > 2)
    {
      std::cout << "  Inserting new ");
      printsubseg(m.m_dummysub,m_dummytri, &newsubseg);
    }
    */
  }
  else
  {
    if (newsubseg.GetMark() == 0)
    //if (mark(newsubseg) == 0)
    {
      newsubseg.SetMark(subsegmark);
      //setmark(newsubseg, subsegmark);
    }
  }
}

/*****************************************************************************/
//
// Terminology
//
// A "local transformation" replaces a small set of triangles with another
// set of triangles.  This may or may not involve inserting or deleting a
// vertex.
//
// The term "casing" is used to describe the set of triangles that are
// attached to the triangles being transformed, but are not transformed
// themselves.  Think of the casing as a fixed hollow structure inside
// which all the action happens.  A "casing" is only defined relative to
// a single transformation; each occurrence of a transformation will
// involve a different casing.
//
/*****************************************************************************/


void ribi::tricpp::flip(
  const Mesh& m,
  const Behavior& b,
  const Otri * const flipedge
)
{
  Otri botleft, botright;
  Otri topleft, topright;
  Otri top;
  Otri botlcasing, botrcasing;
  Otri toplcasing, toprcasing;
  Osub botlsubseg, botrsubseg;
  Osub toplsubseg, toprsubseg;
  //Vertex leftvertex, rightvertex, botvertex;
  Vertex farvertex;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  //Identify the vertices of the quadrilateral.
  const auto rightvertex = flipedge->GetOrigin();
  //org(*flipedge, rightvertex);

  const auto leftvertex = flipedge->GetDest();
  //dest(*flipedge, leftvertex);

  const auto botvertex = flipedge->GetApex();
  //apex(*flipedge, botvertex);

  sym(*flipedge, top);
#ifdef SELF_CHECK
  if (top.tri == m.dummytri) {
    std::cout << "Internal error in flip():  Attempt to flip on boundary.\n");
    lnextself(*flipedge);
    return;
  }
  if (m.checksegments) {
    tspivot(*flipedge, toplsubseg);
    if (toplsubseg.ss != m.dummysub) {
      std::cout << "Internal error in flip():  Attempt to flip a segment.\n");
      lnextself(*flipedge);
      return;
    }
  }
#endif //SELF_CHECK

  farvertex = top.GetApex();
  //GetApex(top, farvertex);

  //Identify the casing of the quadrilateral.
  lprev(top, topleft);
  sym(topleft, toplcasing);
  lnext(top, topright);
  sym(topright, toprcasing);
  lnext(*flipedge, botleft);
  sym(botleft, botlcasing);
  lprev(*flipedge, botright);
  sym(botright, botrcasing);
  //Rotate the quadrilateral one-quarter turn counterclockwise.
  bond(topleft, botlcasing);
  bond(botleft, botrcasing);
  bond(botright, toprcasing);
  bond(topright, toplcasing);

  if (m.m_checksegments) {
    //Check for subsegments and rebond them to the quadrilateral.
    tspivot(topleft, toplsubseg);
    tspivot(botleft, botlsubseg);
    tspivot(botright, botrsubseg);
    tspivot(topright, toprsubseg);
    if (toplsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(topright,m.m_dummysub);
    } else {
      tsbond(topright, toplsubseg);
    }
    if (botlsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(topleft,m.m_dummysub);
    } else {
      tsbond(topleft, botlsubseg);
    }
    if (botrsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(botleft,m.m_dummysub);
    } else {
      tsbond(botleft, botrsubseg);
    }
    if (toprsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(botright,m.m_dummysub);
    } else {
      tsbond(botright, toprsubseg);
    }
  }

  //New vertex assignments for the rotated quadrilateral.
  flipedge->SetOrigin(farvertex);
  //setorg(*flipedge, farvertex);

  flipedge->SetDest(botvertex);
  //setdest(*flipedge, botvertex);

  flipedge->SetApex(rightvertex);
  //setapex(*flipedge, rightvertex);

  top->SetOrigin(botvertex);
  //setorg(top, botvertex);

  top->SetDest(farvertex);
  //setdest(top, farvertex);

  top->SetApex(leftvertex);
  //setapex(top, leftvertex);
  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Edge flip results in left ");
    printtriangle(m, b, &top);
    std::cout << "  and right ");
    printtriangle(m, b, flipedge);
  }
  */
}

void ribi::tricpp::unflip(
  const Mesh& m,
  const Behavior& b,
  const Otri * const flipedge
)
{
  Otri botleft, botright;
  Otri topleft, topright;
  Otri top;
  Otri botlcasing, botrcasing;
  Otri toplcasing, toprcasing;
  Osub botlsubseg, botrsubseg;
  Osub toplsubseg, toprsubseg;
  Vertex leftvertex, rightvertex, botvertex;
  Vertex farvertex;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  //Identify the vertices of the quadrilateral.
  const auto rightvertex = flipedge->GetOrigin();
  //org(*flipedge, rightvertex);

  const auto leftvertex = flipedge->GetDes();
  //dest(*flipedge, leftvertex);

  const auto botvertex = flipedge->GetApex();
  //apex(*flipedge, botvertex);

  sym(*flipedge, top);
#ifdef SELF_CHECK
  if (top.tri == m.dummytri) {
    std::cout << "Internal error in unflip():  Attempt to flip on boundary.\n");
    lnextself(*flipedge);
    return;
  }
  if (m.checksegments) {
    tspivot(*flipedge, toplsubseg);
    if (toplsubseg.ss != m.dummysub) {
      std::cout << "Internal error in unflip():  Attempt to flip a subsegment.\n");
      lnextself(*flipedge);
      return;
    }
  }
#endif //SELF_CHECK

  farvertex = top.GetApex();
  //GetApex(top, farvertex);

  //Identify the casing of the quadrilateral.
  lprev(top, topleft);
  sym(topleft, toplcasing);
  lnext(top, topright);
  sym(topright, toprcasing);
  lnext(*flipedge, botleft);
  sym(botleft, botlcasing);
  lprev(*flipedge, botright);
  sym(botright, botrcasing);
  //Rotate the quadrilateral one-quarter turn clockwise.
  bond(topleft, toprcasing);
  bond(botleft, toplcasing);
  bond(botright, botlcasing);
  bond(topright, botrcasing);

  if (m.m_checksegments) {
    //Check for subsegments and rebond them to the quadrilateral.
    tspivot(topleft, toplsubseg);
    tspivot(botleft, botlsubseg);
    tspivot(botright, botrsubseg);
    tspivot(topright, toprsubseg);
    if (toplsubseg.m_subseg == m.m_dummysub)
    {
      tsdissolve(botleft,m.m_dummysub);
    } else {
      tsbond(botleft, toplsubseg);
    }
    if (botlsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(botright,m.m_dummysub);
    } else {
      tsbond(botright, botlsubseg);
    }
    if (botrsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(topright,m.m_dummysub);
    } else {
      tsbond(topright, botrsubseg);
    }
    if (toprsubseg.m_subseg == m.m_dummysub) {
      tsdissolve(topleft,m.m_dummysub);
    } else {
      tsbond(topleft, toprsubseg);
    }
  }

  //New vertex assignments for the rotated quadrilateral.
  flipedge->SetOrigin(botvertex);
  //setorg(*flipedge, botvertex);
  flipedge->SetDest(farvertex);
  //setdest(*flipedge, farvertex);
  flipedge->SetApex(leftvertex);
  //setapex(*flipedge, leftvertex);
  top->SetOrigin(farvertex);
  //setorg(top, farvertex);
  top->SetDest(botvertex);
  //setdest(top, botvertex);
  top->SetApex(rightvertex);
  //setapex(top, rightvertex);
  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Edge unflip results in left ");
    printtriangle(m, b, flipedge);
    std::cout << "  and right ");
    printtriangle(m, b, &top);
  }
  */
}

ribi::tricpp::InsertVertexResult ribi::tricpp::insertvertex(
  Mesh& m,
  const Behavior& b,
  const Vertex& newvertex,
  Otri * const searchtri,
  Osub * const splitseg,
  const int segmentflaws,
  const int triflaws
)
{
  Otri horiz;
  Otri top;
  Otri botleft, botright;
  Otri topleft, topright;
  Otri newbotleft, newbotright;
  Otri newtopright;
  Otri botlcasing, botrcasing;
  Otri toplcasing, toprcasing;
  Otri testtri;
  Osub botlsubseg, botrsubseg;
  Osub toplsubseg, toprsubseg;
  Osub brokensubseg;
  Osub checksubseg;
  Osub rightsubseg;
  Osub newsubseg;
  BadSubSeg *encroached;
  FlipStacker *newflip;
  Vertex first;
  Vertex leftvertex, rightvertex, botvertex, topvertex, farvertex;
  Vertex segmentorg, segmentdest;
  double attrib;
  double area;
  enum InsertVertexResult success;
  enum LocateResult intersect;
  int doflip;
  int mirrorflag;
  int enq;

  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;         //Temporary variable used by spivot() and tspivot().
  /*
  if (b.m_verbosity > 1) {
    std::cout << "  Inserting (%.12g, %.12g).\n", newvertex[0], newvertex[1]);
  }
  */
  if (splitseg == nullptr) {
    //Find the location of the vertex to be inserted.  Check if a good
    //  starting triangle has already been provided by the caller.
    if (searchtri->m_tri == m.m_dummytri)
    {
      //Find a boundary triangle.
      horiz.m_tri = m.m_dummytri;
      horiz.m_orient = 0;
      symself(horiz);
      //Search for a triangle containing `newvertex'.
      intersect = locate(m, b, newvertex, &horiz);
    } else {
      //Start searching from the triangle provided by the caller.
      horiz = searchtri;
      //otricopy(*searchtri, horiz);
      intersect = preciselocate(m, b, newvertex, &horiz, 1);
    }
  } else {
    //The calling routine provides the subsegment in which
    //  the vertex is inserted.
      horiz = searchtri;
    //otricopy(*searchtri, horiz);
    intersect = ONEDGE;
  }

  if (intersect == ONVERTEX) {
    //There's already a vertex there.  Return in `searchtri' a triangle
    //  whose origin is the existing vertex.
    searchtri = horiz;
    //otricopy(horiz, *searchtri);
    m.m_recenttri = horiz;
    //otricopy(horiz, m.m_recenttri);
    return DUPLICATEVERTEX;
  }
  if (intersect == ONEDGE || intersect == OUTSIDE)
  {
    //The vertex falls on an edge or boundary.
    if (m.m_checksegments && (splitseg == nullptr))
    {
      //Check whether the vertex falls on a subsegment.
      tspivot(horiz, brokensubseg);
      if (brokensubseg.m_subseg != m.m_dummysub)
      {
        //The vertex falls on a subsegment, and hence will not be inserted.
        if (segmentflaws)
        {
          enq = b.m_nobisect != 2;
          if (enq && (b.m_nobisect == 1))
          {
            //This subsegment may be split only if it is an
            //  internal boundary.
            sym(horiz, testtri);
            enq = testtri.m_tri != m.m_dummytri;
          }
          if (enq)
          {
            //Add the subsegment to the list of encroached subsegments.
            //encroached = (struct BadSubSeg *) PoolAlloc(&m.m_badsubsegs);
            BadSubSeg encroached;
            encroached->m_encsubseg = sencode(brokensubseg);
            encroached->m_subsegorg = brokensubseg.GetOrigin();
            //GetOrigin(brokensubseg, encroached->m_subsegorg);

            encroached->m_subsegdest = brokensubseg.GetDest();
            //GetDest(brokensubseg, encroached->m_subsegdest);

            /*
            if (b.m_verbosity > 2) {
              std::cout <<
          "  Queueing encroached subsegment (%.12g, %.12g) (%.12g, %.12g).\n",
                     encroached->m_subsegorg[0], encroached->m_subsegorg[1],
                     encroached->m_subsegdest[0], encroached->m_subsegdest[1]);
            }
            */
          }
        }
        //Return a handle whose primary edge contains the vertex,
        //  which has not been inserted.
        searchtri = horiz;
        //otricopy(horiz, *searchtri);
        m.m_recenttri = horiz;
        //otricopy(horiz, m.m_recenttri);
        return VIOLATINGVERTEX;
      }
    }

    //Insert the vertex on an edge, dividing one triangle into two (if
    //  the edge lies on a boundary) or two triangles into four.
    lprev(horiz, botright);
    sym(botright, botrcasing);
    sym(horiz, topright);
    //Is there a second triangle?  (Or does this edge lie on a boundary?)
    mirrorflag = topright.m_tri != m.m_dummytri;
    if (mirrorflag)
    {
      lnextself(topright);
      sym(topright, toprcasing);
      maketriangle(m, b, &newtopright);
    } else
    {
      //Splitting a boundary edge increases the number of boundary edges.
      m.m_hullsize++;
    }
    maketriangle(m, b, &newbotright);

    //Set the vertices of changed and new triangles.
    const auto rightvertex = horiz.GetOrigin();
    //GetOrigin(horiz, rightvertex);

    const auto leftvertex = horiz.GetDest();
    //dest(horiz, leftvertex);

    const auto botvertex = horiz.GetApex();
    //apex(horiz, botvertex);

    newbotright.SetOrigin(botvertex);
    //setorg(newbotright, botvertex);

    newbotright.SetDest(rightvertex);
    //setdest(newbotright, rightvertex);

    newbotright.SetApex(newvertex);
    //setapex(newbotright, newvertex);

    horiz.SetOrg(newvertex);
    //setorg(horiz, newvertex);

    for (int i = 0; i != m.m_eextras; i++)
    {
      //Set the element attributes of a new triangle.
      newbotright.SetElemAttrib(i,botright.GetElemAttrib(i));
      //setelemattribute(newbotright, i, elemattribute(botright, i));
    }
    if (b.m_vararea) {
      //Set the area constraint of a new triangle.
      setareabound(newbotright, areabound(botright));
    }
    if (mirrorflag)
    {
      const auto topvertex = topright.GetDest();
      //dest(topright, topvertex);

      const auto rightvertex = newtopright.GetOrigin();
      //setorg(newtopright, rightvertex);

      newtopright.SetDest(topvertex);
      //setdest(newtopright, topvertex);

      newtopright.SetApex(newvertex);
      //setapex(newtopright, newvertex);

      topright.SetOrigin(newvertex);
      //setorg(topright, newvertex);

      for (int i = 0; i != m.m_eextras; ++i)
      {
        //Set the element attributes of another new triangle.
        newtopright.SetElemAttrib(i,topright.GetElemAttrib(i));
        //setelemattribute(newtopright, i, elemattribute(topright, i));
      }
      if (b.m_vararea)
      {
        //Set the area constraint of another new triangle.
        newtopright.SetAreaBound(topright.GetAreaBound());
        //setareabound(newtopright, areabound(topright));
      }
    }

    //There may be subsegments that need to be bonded
    //  to the new triangle(s).
    if (m.m_checksegments)
    {
      tspivot(botright, botrsubseg);
      if (botrsubseg.m_subseg != m.m_dummysub) {
        tsdissolve(botright,m.m_dummysub);
        tsbond(newbotright, botrsubseg);
      }
      if (mirrorflag) {
        tspivot(topright, toprsubseg);
        if (toprsubseg.m_subseg != m.m_dummysub)
        {
          tsdissolve(topright,m.m_dummysub);
          tsbond(newtopright, toprsubseg);
        }
      }
    }

    //Bond the new triangle(s) to the surrounding triangles.
    bond(newbotright, botrcasing);
    lprevself(newbotright);
    bond(newbotright, botright);
    lprevself(newbotright);
    if (mirrorflag) {
      bond(newtopright, toprcasing);
      lnextself(newtopright);
      bond(newtopright, topright);
      lnextself(newtopright);
      bond(newtopright, newbotright);
    }

    if (splitseg != nullptr)
    {
      //Split the subsegment into two.
      splitseg->SetDest(newvertex);
      //SetDest(*splitseg, newvertex);

      segmentorg = splitseg->GetOrigin();
      //GetOrg(*splitseg, segmentorg);

      segmentdest = splitseg->GetDest();
      //GetDest(*splitseg, segmentdest);

      ssymself(*splitseg);
      spivot(*splitseg, rightsubseg);
      insertsubseg(m, b, &newbotright, mark(*splitseg));
      tspivot(newbotright, newsubseg);
      setsegorg(newsubseg, segmentorg);
      setsegdest(newsubseg, segmentdest);
      sbond(*splitseg, newsubseg);
      ssymself(newsubseg);
      sbond(newsubseg, rightsubseg);
      ssymself(*splitseg);
      //Transfer the subsegment's boundary marker to the vertex
      //  if required.
      if (vertexmark(newvertex) == 0)
      {
        setvertexmark(newvertex, mark(*splitseg));
      }
    }

    if (m.m_checkquality) {
      PoolRestart(m.m_flipstackers);
      //m.m_lastflip = (struct FlipStacker *) PoolAlloc(&m.m_flipstackers);
      m.m_lastflip->m_flippedtri = encode(horiz);
      m.m_lastflip->m_prevflip = (struct FlipStacker *) &insertvertex;
    }

#ifdef SELF_CHECK
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, leftvertex, botvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout <<
            "  Clockwise triangle prior to edge vertex insertion (bottom).\n");
    }
    if (mirrorflag) {
      if (counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, rightvertex, topvertex) < 0.0) {
        std::cout << "Internal error in insertvertex():\n");
        std::cout << "  Clockwise triangle prior to edge vertex insertion (top).\n");
      }
      if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, topvertex, newvertex) < 0.0) {
        std::cout << "Internal error in insertvertex():\n");
        std::cout <<
            "  Clockwise triangle after edge vertex insertion (top right).\n");
      }
      if (counterclockwise(m.m_counterclockcount, b.m_noexact, topvertex, leftvertex, newvertex) < 0.0) {
        std::cout << "Internal error in insertvertex():\n");
        std::cout <<
            "  Clockwise triangle after edge vertex insertion (top left).\n");
      }
    }
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, botvertex, newvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout <<
          "  Clockwise triangle after edge vertex insertion (bottom left).\n");
    }
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, botvertex, rightvertex, newvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout <<
        "  Clockwise triangle after edge vertex insertion (bottom right).\n");
    }
#endif //SELF_CHECK
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Updating bottom left ");
      printtriangle(m, b, &botright);
      if (mirrorflag) {
        std::cout << "  Updating top left ");
        printtriangle(m, b, &topright);
        std::cout << "  Creating top right ");
        printtriangle(m, b, &newtopright);
      }
      std::cout << "  Creating bottom right ");
      printtriangle(m, b, &newbotright);
    }
    */
    //Position `horiz' on the first edge to check for
    //  the Delaunay property.
    lnextself(horiz);
  } else {
    //Insert the vertex in a triangle, splitting it into three.
    lnext(horiz, botleft);
    lprev(horiz, botright);
    sym(botleft, botlcasing);
    sym(botright, botrcasing);
    maketriangle(m, b, &newbotleft);
    maketriangle(m, b, &newbotright);

    //Set the vertices of changed and new triangles.
    const auto rightvertex = horiz->GetOrigin();
    //org(horiz, rightvertex);
    const auto leftvertex = horiz->GetDest();
    //dest(horiz, leftvertex);
    const auto botvertex = horiz->GetApex();
    //apex(horiz, botvertex);
    newbotleft.SetOrigin(leftvertex);
    //setorg(newbotleft, leftvertex);
    newbotleft.SetDest(botvertex);
    //setdest(newbotleft, botvertex);
    newbotleft.SetApex(newvertex);
    //setapex(newbotleft, newvertex);
    newbotright.SetOrigin(botvertex);
    //setorg(newbotright, botvertex);
    newbotright.SetDest(rightvertex);
    //setdest(newbotright, rightvertex);
    newbotright.SetApex(newvertex);
    //setapex(newbotright, newvertex);
    horiz.SetApex(newvertex);
    //setapex(horiz, newvertex);
    for (int i = 0; i < m.m_eextras; i++) {
      //Set the element attributes of the new triangles.
      attrib = elemattribute(horiz, i);
      setelemattribute(newbotleft, i, attrib);
      setelemattribute(newbotright, i, attrib);
    }
    if (b.m_vararea) {
      //Set the area constraint of the new triangles.
      area = areabound(horiz);
      setareabound(newbotleft, area);
      setareabound(newbotright, area);
    }

    //There may be subsegments that need to be bonded
    //  to the new triangles.
    if (m.m_checksegments) {
      tspivot(botleft, botlsubseg);
      if (botlsubseg.m_subseg != m.m_dummysub) {
        tsdissolve(botleft,m.m_dummysub);
        tsbond(newbotleft, botlsubseg);
      }
      tspivot(botright, botrsubseg);
      if (botrsubseg.m_subseg != m.m_dummysub) {
        tsdissolve(botright,m.m_dummysub);
        tsbond(newbotright, botrsubseg);
      }
    }

    //Bond the new triangles to the surrounding triangles.
    bond(newbotleft, botlcasing);
    bond(newbotright, botrcasing);
    lnextself(newbotleft);
    lprevself(newbotright);
    bond(newbotleft, newbotright);
    lnextself(newbotleft);
    bond(botleft, newbotleft);
    lprevself(newbotright);
    bond(botright, newbotright);

    if (m.m_checkquality) {
      PoolRestart(&m.m_flipstackers);
      m.m_lastflip = (struct FlipStacker *) PoolAlloc(&m.m_flipstackers);
      m.m_lastflip->m_flippedtri = encode(horiz);
      m.m_lastflip->m_prevflip = (struct FlipStacker *) NULL;
    }

#ifdef SELF_CHECK
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, leftvertex, botvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout << "  Clockwise triangle prior to vertex insertion.\n");
    }
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, leftvertex, newvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout << "  Clockwise triangle after vertex insertion (top).\n");
    }
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, botvertex, newvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout << "  Clockwise triangle after vertex insertion (left).\n");
    }
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, botvertex, rightvertex, newvertex) < 0.0) {
      std::cout << "Internal error in insertvertex():\n");
      std::cout << "  Clockwise triangle after vertex insertion (right).\n");
    }
#endif //SELF_CHECK
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Updating top ");
      printtriangle(m, b, &horiz);
      std::cout << "  Creating left ");
      printtriangle(m, b, &newbotleft);
      std::cout << "  Creating right ");
      printtriangle(m, b, &newbotright);
    }
    */
  }

  //The insertion is successful by default, unless an encroached
  //  subsegment is found.
  success = SUCCESSFULVERTEX;
  //Circle around the newly inserted vertex, checking each edge opposite
  //  it for the Delaunay property.  Non-Delaunay edges are flipped.
  //  `horiz' is always the edge being checked.  `first' marks where to
  //  stop circling.

  first = horiz.GetOrigin();
  //GetOrigin(horiz, first);

  rightvertex = first;

  leftvertex = horiz.GetDest();
  //GetDest(horiz, leftvertex);

  //Circle until finished.
  while (1) {
    //By default, the edge will be flipped.
    doflip = 1;

    if (m.m_checksegments) {
      //Check for a subsegment, which cannot be flipped.
      tspivot(horiz, checksubseg);
      if (checksubseg.m_subseg != m.m_dummysub) {
        //The edge is a subsegment and cannot be flipped.
        doflip = 0;
        if (segmentflaws) {
          //Does the new vertex encroach upon this subsegment?
          if (checkseg4encroach(m, b, &checksubseg)) {
            success = ENCROACHINGVERTEX;
          }
        }
      }
    }

    if (doflip) {
      //Check if the edge is a boundary edge.
      sym(horiz, top);
      if (top.m_tri == m.m_dummytri)
      {
        //The edge is a boundary edge and cannot be flipped.
        doflip = 0;
      }
      else
      {
        //Find the vertex on the other side of the edge.

        farvertex = top.GetApex();
        //GetApex(top, farvertex);

        //In the incremental Delaunay triangulation algorithm, any of
        //  `leftvertex', `rightvertex', and `farvertex' could be vertices
        //  of the triangular bounding box.  These vertices must be
        //  treated as if they are infinitely distant, even though their
        //  "coordinates" are not.
        if ((leftvertex == m.m_infvertex1) || (leftvertex == m.m_infvertex2) ||
            (leftvertex == m.m_infvertex3)) {
          //`leftvertex' is infinitely distant.  Check the convexity of
          //  the boundary of the triangulation.  'farvertex' might be
          //  infinite as well, but trust me, this same condition should
          //  be applied.
          doflip = counterclockwise(m.m_counterclockcount, b.m_noexact, newvertex, rightvertex, farvertex)
                   > 0.0;
        } else if ((rightvertex == m.m_infvertex1) ||
                   (rightvertex == m.m_infvertex2) ||
                   (rightvertex == m.m_infvertex3)) {
          //`rightvertex' is infinitely distant.  Check the convexity of
          //  the boundary of the triangulation.  'farvertex' might be
          //  infinite as well, but trust me, this same condition should
          //  be applied.
          doflip = counterclockwise(m.m_counterclockcount, b.m_noexact, farvertex, leftvertex, newvertex)
                   > 0.0;
        } else if ((farvertex == m.m_infvertex1) ||
                   (farvertex == m.m_infvertex2) ||
                   (farvertex == m.m_infvertex3)) {
          //`farvertex' is infinitely distant and cannot be inside
          //  the circumcircle of the triangle `horiz'.
          doflip = 0;
        } else {
          //Test whether the edge is locally Delaunay.
          doflip = incircle(m, b, leftvertex, newvertex, rightvertex,
                            farvertex) > 0.0;
        }
        if (doflip)
        {
          //We made it!  Flip the edge `horiz' by rotating its containing
          //  quadrilateral (the two triangles adjacent to `horiz').
          //Identify the casing of the quadrilateral.
          lprev(top, topleft);
          sym(topleft, toplcasing);
          lnext(top, topright);
          sym(topright, toprcasing);
          lnext(horiz, botleft);
          sym(botleft, botlcasing);
          lprev(horiz, botright);
          sym(botright, botrcasing);
          //Rotate the quadrilateral one-quarter turn counterclockwise.
          bond(topleft, botlcasing);
          bond(botleft, botrcasing);
          bond(botright, toprcasing);
          bond(topright, toplcasing);
          if (m.m_checksegments) {
            //Check for subsegments and rebond them to the quadrilateral.
            tspivot(topleft, toplsubseg);
            tspivot(botleft, botlsubseg);
            tspivot(botright, botrsubseg);
            tspivot(topright, toprsubseg);
            if (toplsubseg.m_subseg == m.m_dummysub) {
              tsdissolve(topright);
            } else {
              tsbond(topright, toplsubseg);
            }
            if (botlsubseg.m_subseg == m.m_dummysub) {
              tsdissolve(topleft);
            } else {
              tsbond(topleft, botlsubseg);
            }
            if (botrsubseg.m_subseg == m.m_dummysub) {
              tsdissolve(botleft);
            } else {
              tsbond(botleft, botrsubseg);
            }
            if (toprsubseg.m_subseg == m.m_dummysub) {
              tsdissolve(botright);
            } else {
              tsbond(botright, toprsubseg);
            }
          }
          //New vertex assignments for the rotated quadrilateral.
          horiz.SetOrigin(farvertex);
          //SetOrigin(horiz, farvertex);

          horiz.SetDest(newvertex);
          //SetDest(horiz, newvertex);

          horiz.SetApex(rightvertex);
          //SetApex(horiz, rightvertex);

          top.SetOrigin(bewvertex);
          //SetOrigin(top, newvertex);

          top.SetDest(farvertex);
          //SetDest(top, farvertex);

          top.SetApex(leftvertex);
          //SetApex(top, leftvertex);

          for (int i = 0; i < m.m_eextras; i++) {
            //Take the average of the two triangles' attributes.
            attrib = 0.5 * (elemattribute(top, i) + elemattribute(horiz, i));
            setelemattribute(top, i, attrib);
            setelemattribute(horiz, i, attrib);
          }
          if (b.m_vararea) {
            if ((areabound(top) <= 0.0) || (areabound(horiz) <= 0.0)) {
              area = -1.0;
            } else {
              //Take the average of the two triangles' area constraints.
              //  This prevents small area constraints from migrating a
              //  long, long way from their original location due to flips.
              area = 0.5 * (areabound(top) + areabound(horiz));
            }
            setareabound(top, area);
            setareabound(horiz, area);
          }

          if (m.m_checkquality) {
            newflip = (struct FlipStacker *) PoolAlloc(&m.m_flipstackers);
            newflip->m_flippedtri = encode(horiz);
            newflip->m_prevflip = m.m_lastflip;
            m.m_lastflip = newflip;
          }

#ifdef SELF_CHECK
          if (newvertex != (vertex) NULL) {
            if (counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, newvertex, rightvertex) <
                0.0) {
              std::cout << "Internal error in insertvertex():\n");
              std::cout << "  Clockwise triangle prior to edge flip (bottom).\n");
            }
            //The following test has been removed because constrainededge()
            //  sometimes generates inverted triangles that insertvertex()
            //  removes.
/*
            if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, farvertex, leftvertex) <
                0.0) {
              std::cout << "Internal error in insertvertex():\n");
              std::cout << "  Clockwise triangle prior to edge flip (top).\n");
            }
*/
            if (counterclockwise(m.m_counterclockcount, b.m_noexact, farvertex, leftvertex, newvertex) <
                0.0) {
              std::cout << "Internal error in insertvertex():\n");
              std::cout << "  Clockwise triangle after edge flip (left).\n");
            }
            if (counterclockwise(m.m_counterclockcount, b.m_noexact, newvertex, rightvertex, farvertex) <
                0.0) {
              std::cout << "Internal error in insertvertex():\n");
              std::cout << "  Clockwise triangle after edge flip (right).\n");
            }
          }
#endif //SELF_CHECK
          if (b.m_verbosity > 2) {
            std::cout << "  Edge flip results in left ");
            lnextself(topleft);
            printtriangle(m, b, &topleft);
            std::cout << "  and right ");
            printtriangle(m, b, &horiz);
          }
          //On the next iterations, consider the two edges that were
          //  exposed (this is, are now visible to the newly inserted
          //  vertex) by the edge flip.
          lprevself(horiz);
          leftvertex = farvertex;
        }
      }
    }
    if (!doflip) {
      //The handle `horiz' is accepted as locally Delaunay.
      if (triflaws) {
        //Check the triangle `horiz' for quality.
        testtriangle(m, b, &horiz);
      }
      //Look for the next edge around the newly inserted vertex.
      lnextself(horiz);
      sym(horiz, testtri);
      //Check for finishing a complete revolution about the new vertex, or
      //  falling outside  of the triangulation.  The latter will happen
      //  when a vertex is inserted at a boundary.
      if ((leftvertex == first) || (testtri.m_tri == m.m_dummytri)) {
        //We're done.  Return a triangle whose origin is the new vertex.
        lnext(horiz, *searchtri);
        lnext(horiz, m.m_recenttri);
        return success;
      }
      //Finish finding the next edge around the newly inserted vertex.
      lnext(testtri, horiz);
      rightvertex = leftvertex;

      leftvertex = horiz.GetDest();
      //GetDest(horiz, leftvertex);
    }
  }
}

void ribi::tricpp::triangulatepolygon(
  Mesh& m,
  const Behavior& b,
  const Otri * const firstedge,
  Otri * const lastedge,
  const int edgecount,
  const int doflip,
  const int triflaws
)
{
  Otri testtri;
  Otri besttri;
  Otri tempedge;
  Vertex leftbasevertex, rightbasevertex;
  Vertex testvertex;
  Vertex bestvertex;
  //int bestnumber;

  Triangle ptr;   //Temporary variable used by sym(), onext(), and oprev().

  //Identify the base vertices.

  leftbasevertex = lastedge->GetApex();
  //GetApex(*lastedge, leftbasevertex);

  rightbasevertex = firstedge->GetDest();
  //GetDest(*firstedge, rightbasevertex);

  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Triangulating interior polygon at edge\n");
    std::cout << "    (%.12g, %.12g) (%.12g, %.12g)\n", leftbasevertex[0],
           leftbasevertex[1], rightbasevertex[0], rightbasevertex[1]);
  }
  */
  //Find the best vertex to connect the base to.
  onext(*firstedge, besttri);

  bestvertex = besttri.GetDest();
  //GetDest(besttri, bestvertex);

  testtri = besttri;
  //otricopy(besttri, testtri);
  int bestnumber = 1;
  for (int i = 2; i <= edgecount - 2; i++)
  {
    onextself(testtri);

    testvertex = testtri.GetDest();
    //GetDest(testtri, testvertex);

    //Is this a better vertex?
    if (incircle(m, b, leftbasevertex, rightbasevertex, bestvertex,testvertex) > 0.0)
    {
      besttri = testtri;
      //otricopy(testtri, besttri);
      bestvertex = testvertex;
      bestnumber = i;
    }
  }
  /*
  if (b.m_verbosity > 2) {
    std::cout << "    Connecting edge to (%.12g, %.12g)\n", bestvertex[0],
           bestvertex[1]);
  }
  */
  if (bestnumber > 1) {
    //Recursively triangulate the smaller polygon on the right.
    oprev(besttri, tempedge);
    triangulatepolygon(m, b, firstedge, &tempedge, bestnumber + 1, 1,
                       triflaws);
  }
  if (bestnumber < edgecount - 2) {
    //Recursively triangulate the smaller polygon on the left.
    sym(besttri, tempedge);
    triangulatepolygon(m, b, &besttri, lastedge, edgecount - bestnumber, 1,
                       triflaws);
    //Find `besttri' again; it may have been lost to edge flips.
    sym(tempedge, besttri);
  }
  if (doflip)
  {
    //Do one final edge flip.
    flip(m, b, &besttri);
    if (triflaws)
    {
      //Check the quality of the newly committed triangle.
      sym(besttri, testtri);
      testtriangle(m, b, &testtri);
    }
  }
  //Return the base triangle.
  lastedge = besttri;
  //otricopy(besttri, *lastedge);
}


void ribi::tricpp::deletevertex(
  Mesh& m,
  const Behavior& b,
  const Otri * const deltri
)
{
  Otri countingtri;
  Otri firstedge, lastedge;
  Otri deltriright;
  Otri lefttri, righttri;
  Otri leftcasing, rightcasing;
  Osub leftsubseg, rightsubseg;
  Vertex delvertex;
  Vertex neworg;
  //int edgecount;
  Triangle ptr;   //Temporary variable used by sym(), onext(), and oprev().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  delvertex = deltri->GetOrigin();
  //GetOrigin(*deltri, delvertex);
  /*
  if (b.m_verbosity > 1) {
    std::cout << "  Deleting (%.12g, %.12g).\n", delvertex[0], delvertex[1]);
  }
  */
  vertexdealloc(m, delvertex);

  //Count the degree of the vertex being deleted.
  onext(*deltri, countingtri);
  int edgecount = 1;
  while (*deltri != countingtri)
  //while (!otriequal(*deltri, countingtri))
  {
#ifdef SELF_CHECK
    if (countingtri.tri == m.dummytri) {
      std::cout << "Internal error in deletevertex():\n");
      std::cout << "  Attempt to delete boundary vertex.\n");
      throw std::logic_error(s.str().c_str());

    }
#endif //SELF_CHECK
    edgecount++;
    onextself(countingtri);
  }

#ifdef SELF_CHECK
  if (edgecount < 3) {
    std::cout << "Internal error in deletevertex():\n  Vertex has degree %d.\n",
           edgecount);
    throw std::logic_error(s.str().c_str());

  }
#endif //SELF_CHECK
  if (edgecount > 3) {
    //Triangulate the polygon defined by the union of all triangles
    //  adjacent to the vertex being deleted.  Check the quality of
    //  the resulting triangles.
    onext(*deltri, firstedge);
    oprev(*deltri, lastedge);
    triangulatepolygon(m, b, &firstedge, &lastedge, edgecount, 0,
                       !b.m_nobisect);
  }
  //Splice out two triangles.
  lprev(*deltri, deltriright);
  dnext(*deltri, lefttri);
  sym(lefttri, leftcasing);
  oprev(deltriright, righttri);
  sym(righttri, rightcasing);
  bond(*deltri, leftcasing);
  bond(deltriright, rightcasing);
  tspivot(lefttri, leftsubseg);
  if (leftsubseg.m_subseg != m.m_dummysub) {
    tsbond(*deltri, leftsubseg);
  }
  tspivot(righttri, rightsubseg);
  if (rightsubseg.m_subseg != m.m_dummysub) {
    tsbond(deltriright, rightsubseg);
  }

  //Set the new origin of `deltri' and check its quality.
  neworg = lefttri.GetOrigin();
  //GetOrigin(lefttri, neworg);

  deltri->SetOrigin(neworg);
  //SetOrigin(*deltri, neworg);

  if (!b.m_nobisect) {
    testtriangle(m, b, deltri);
  }

  //Delete the two spliced-out triangles.
  m.KillTriange(lefttri.m_tri);
  m.KillTriange(righttri.m_tri);
  //triangledealloc(m, lefttri.m_tri);
  //triangledealloc(m, righttri.m_tri);
}

void ribi::tricpp::undovertex(
  Mesh& m,
  const Behavior& b
)
{
  Otri fliptri;
  Otri botleft, botright, topright;
  Otri botlcasing, botrcasing, toprcasing;
  Otri gluetri;
  Osub botlsubseg, botrsubseg, toprsubseg;
  Vertex botvertex, rightvertex;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  //Walk through the list of transformations (flips and a vertex insertion)
  //  in the reverse of the order in which they were done, and undo them.
  while (m.m_lastflip != nullptr) {
    //Find a triangle involved in the last unreversed transformation.
    decode(m.m_lastflip->m_flippedtri, fliptri);

    //We are reversing one of three transformations:  a trisection of one
    //  triangle into three (by inserting a vertex in the triangle), a
    //  bisection of two triangles into four (by inserting a vertex in an
    //  edge), or an edge flip.
    if (m.m_lastflip->m_prevflip == nullptr) {
      //Restore a triangle that was split into three triangles,
      //  so it is again one triangle.
      dprev(fliptri, botleft);
      lnextself(botleft);
      onext(fliptri, botright);
      lprevself(botright);
      sym(botleft, botlcasing);
      sym(botright, botrcasing);

      botvertex = botleft.GetDest();
      //GetDest(botleft, botvertex);

      SetApex(fliptri, botvertex);
      lnextself(fliptri);
      bond(fliptri, botlcasing);
      tspivot(botleft, botlsubseg);
      tsbond(fliptri, botlsubseg);
      lnextself(fliptri);
      bond(fliptri, botrcasing);
      tspivot(botright, botrsubseg);
      tsbond(fliptri, botrsubseg);

      //Delete the two spliced-out triangles.
      m.KillTriangle(botleft.m_tri);
      m.KillTriangle(botright.m_tri);
      //triangledealloc(m, botleft.m_tri);
      //triangledealloc(m, botright.m_tri);
    } else if (m.m_lastflip->m_prevflip == (struct FlipStacker *) &insertvertex) {
      //Restore two triangles that were split into four triangles,
      //  so they are again two triangles.
      lprev(fliptri, gluetri);
      sym(gluetri, botright);
      lnextself(botright);
      sym(botright, botrcasing);

      rightvertex = botright.GetDest();
      //GetDest(botright, rightvertex);

      fliptri.SetOrigin(rightvertex);
      //SetOrigin(fliptri, rightvertex);

      bond(gluetri, botrcasing);
      tspivot(botright, botrsubseg);
      tsbond(gluetri, botrsubseg);

      //Delete the spliced-out triangle.
      m.KillTriangle(botright.m_tri);
      //triangledealloc(m, botright.m_tri);

      sym(fliptri, gluetri);
      if (gluetri.m_tri != m.m_dummytri) {
        lnextself(gluetri);
        dnext(gluetri, topright);
        sym(topright, toprcasing);

        gluetri.SetOrigin(rightvertex);
        //SetOrigin(gluetri, rightvertex);

        bond(gluetri, toprcasing);
        tspivot(topright, toprsubseg);
        tsbond(gluetri, toprsubseg);

        //Delete the spliced-out triangle.
        m.KillTriangle(topright.m_tri);
        //triangledealloc(m, topright.m_tri);
      }

      //This is the end of the list, sneakily encoded.
      m.m_lastflip->m_prevflip = nullptr;
    }
    else
    {
      //Undo an edge flip.
      unflip(m, b, &fliptri);
    }

    //Go on and process the next transformation.
    m.m_lastflip = m.m_lastflip->m_prevflip;
  }
}

/*****************************************************************************/
//
// The divide-and-conquer bounding box
//
// I originally implemented the divide-and-conquer and incremental Delaunay
// triangulations using the edge-based data structure presented by Guibas
// and Stolfi.  Switching to a triangle-based data structure doubled the
// speed.  However, I had to think of a few extra tricks to maintain the
// elegance of the original algorithms.
//
// The "bounding box" used by my variant of the divide-and-conquer
// algorithm uses one triangle for each edge of the convex hull of the
// triangulation.  These bounding triangles all share a common apical
// vertex, which is represented by NULL and which represents nothing.
// The bounding triangles are linked in a circular fan about this NULL
// vertex, and the edges on the convex hull of the triangulation appear
// opposite the NULL vertex.  You might find it easiest to imagine that
// the NULL vertex is a point in 3D space behind the center of the
// triangulation, and that the bounding triangles form a sort of cone.
//
// This bounding box makes it easy to represent degenerate cases.  For
// instance, the triangulation of two vertices is a single edge.  This edge
// is represented by two bounding box triangles, one on each "side" of the
// edge.  These triangles are also linked together in a fan about the NULL
// vertex.
//
// The bounding box also makes it easy to traverse the convex hull, as the
// divide-and-conquer algorithm needs to do.
//
/*****************************************************************************/

//Use vertex*, because a quicksort is used
void ribi::tricpp::vertexsort(
  Vertex * const sortarray,
  const int arraysize
)
{
  int left, right;
  int pivot;
  double pivotx, pivoty;
  //Vertex temp;

  if (arraysize == 2) {
    //Recursive base case.
    if ((sortarray[0][0] > sortarray[1][0]) ||
        ((sortarray[0][0] == sortarray[1][0]) &&
         (sortarray[0][1] > sortarray[1][1]))) {
      std::swap(sortarray[0],sortarray[1]);
    }
    return;
  }
  //Choose a random pivot to split the array.
  pivot = (int) DumbRand((unsigned int) arraysize);
  pivotx = sortarray[pivot][0];
  pivoty = sortarray[pivot][1];
  //Split the array.
  left = -1;
  right = arraysize;
  while (left < right) {
    //Search for a vertex whose x-coordinate is too large for the left.
    do {
      left++;
    } while ((left <= right) && ((sortarray[left][0] < pivotx) ||
                                 ((sortarray[left][0] == pivotx) &&
                                  (sortarray[left][1] < pivoty))));
    //Search for a vertex whose x-coordinate is too small for the right.
    do {
      right--;
    } while ((left <= right) && ((sortarray[right][0] > pivotx) ||
                                 ((sortarray[right][0] == pivotx) &&
                                  (sortarray[right][1] > pivoty))));
    if (left < right) {
      std::swap(sortarray[left],sortarray[right]);
    }
  }
  if (left > 1) {
    //Recursively sort the left subset.
    vertexsort(sortarray, left);
  }
  if (right < arraysize - 2) {
    //Recursively sort the right subset.
    vertexsort(&sortarray[right + 1], arraysize - right - 1);
  }
}

void ribi::tricpp::vertexmedian(
  Vertex * const sortarray,
  const int arraysize,
  const int median,
  const int axis
)
{
  //int left, right;
  //int pivot;
  //double pivot1, pivot2;

  if (arraysize == 2) {
    //Recursive base case.
    if ((sortarray[0][axis] > sortarray[1][axis]) ||
        ((sortarray[0][axis] == sortarray[1][axis]) &&
         (sortarray[0][1 - axis] > sortarray[1][1 - axis])))
    {
      std::swap(sortarray[0],sortarray[1]);
    }
    return;
  }
  //Choose a random pivot to split the array.
  int pivot = (int) DumbRand((unsigned int) arraysize);
  double pivot1 = sortarray[pivot][axis];
  double pivot2 = sortarray[pivot][1 - axis];
  //Split the array.
  int left = -1;
  int right = arraysize;
  while (left < right) {
    //Search for a vertex whose x-coordinate is too large for the left.
    do {
      left++;
    } while ((left <= right) && ((sortarray[left][axis] < pivot1) ||
                                 ((sortarray[left][axis] == pivot1) &&
                                  (sortarray[left][1 - axis] < pivot2))));
    //Search for a vertex whose x-coordinate is too small for the right.
    do {
      right--;
    } while ((left <= right) && ((sortarray[right][axis] > pivot1) ||
                                 ((sortarray[right][axis] == pivot1) &&
                                  (sortarray[right][1 - axis] > pivot2))));
    if (left < right)
    {
      std::swap(sortarray[left],sortarray[right]);
    }
  }
  //Unlike in vertexsort(), at most one of the following
  //  conditionals is true.
  if (left > median) {
    //Recursively shuffle the left subset.
    vertexmedian(sortarray, left, median, axis);
  }
  if (right < median - 1) {
    //Recursively shuffle the right subset.
    vertexmedian(&sortarray[right + 1], arraysize - right - 1,
                 median - right - 1, axis);
  }
}


void ribi::tricpp::alternateaxes(
  Vertex * const sortarray,
  const int arraysize,
  int axis
)
{
  //int divider;
  int divider = arraysize >> 1;
  if (arraysize <= 3) {
    //Recursive base case:  subsets of two or three vertices will be
    //  handled specially, and should always be sorted by x-coordinate.
    axis = 0;
  }
  //Partition with a horizontal or vertical cut.
  vertexmedian(sortarray, arraysize, divider, axis);
  //Recursively partition the subsets with a cross cut.
  if (arraysize - divider >= 2) {
    if (divider >= 2) {
      alternateaxes(sortarray, divider, 1 - axis);
    }
    alternateaxes(&sortarray[divider], arraysize - divider, 1 - axis);
  }
}

void ribi::tricpp::mergehulls(
  Mesh& m,
  const Behavior& b,
  Otri * const farleft,
  Otri * const innerleft,
  Otri * const innerright,
  Otri * const farright,
  const int axis
)
{
  Otri leftcand, rightcand;
  Otri baseedge;
  Otri nextedge;
  Otri sidecasing, topcasing, outercasing;
  Otri checkedge;
  Vertex innerleftdest;
  Vertex innerrightorg;
  Vertex innerleftapex, innerrightapex;
  Vertex farleftpt, farrightpt;
  Vertex farleftapex, farrightapex;
  Vertex lowerleft, lowerright;
  Vertex upperleft, upperright;
  Vertex nextapex;
  Vertex checkvertex;
  int changemade;
  int badedge;
  int leftfinished, rightfinished;
  Triangle ptr;                         //Temporary variable used by sym().

  innerleftdest = innerleft->GetDest();
  //GetDest(*innerleft, innerleftdest);

  innerleftapex = innerleft->GetApex();
  //GetApex(*innerleft, innerleftapex);

  innerrightorg = innerright->GetOrigin();
  //GetOrigin(*innerright, innerrightorg);

  innerrightapex = innerright->GetApex();
  //GetApex(*innerright, innerrightapex);

  //Special treatment for horizontal cuts.
  if (b.m_dwyer && (axis == 1))
  {
    farleftpt = farleft->GetOrigin();
    //GetOrigin(*farleft, farleftpt);

    farleftapex = farleft->GetApex();
    //GetApex(*farleft, farleftapex);

    farrightpt = farright->GetDest();
    //GetDest(*farright, farrightpt);

    farrightapex = farright->GetApex();
    //GetApex(*farright, farrightapex);

    //The pointers to the extremal vertices are shifted to point to the
    //  topmost and bottommost vertex of each hull, rather than the
    //  leftmost and rightmost vertices.
    while (farleftapex[1] < farleftpt[1])
    {
      lnextself(*farleft);
      symself(*farleft);
      farleftpt = farleftapex;

      farleftapex = farleft->GetApex();
      //GetApex(*farleft, farleftapex);
    }
    sym(*innerleft, checkedge);

    checkvertex = checkedge.GetApex();
    //GetApex(checkedge, checkvertex);

    while (checkvertex[1] > innerleftdest[1])
    {
      lnext(checkedge, *innerleft);
      innerleftapex = innerleftdest;
      innerleftdest = checkvertex;
      sym(*innerleft, checkedge);

      checkvertex = checkedge->GetApex();
      //GetApex(checkedge, checkvertex);
    }
    while (innerrightapex[1] < innerrightorg[1])
    {
      lnextself(*innerright);
      symself(*innerright);
      innerrightorg = innerrightapex;

      innerrightapex = innerright->GetApex();
      //GetApex(*innerright, innerrightapex);
    }
    sym(*farright, checkedge);

    checkvertex = checkedge.GetApex();
    //GetApex(checkedge, checkvertex);

    while (checkvertex[1] > farrightpt[1])
    {
      lnext(checkedge, *farright);
      farrightapex = farrightpt;
      farrightpt = checkvertex;
      sym(*farright, checkedge);

      checkvertex = checkedge.GetApex();
      //GetApex(checkedge, checkvertex);
    }
  }
  //Find a line tangent to and below both hulls.
  do {
    changemade = 0;
    //Make innerleftdest the "bottommost" vertex of the left hull.
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, innerleftdest, innerleftapex, innerrightorg) >
        0.0) {
      lprevself(*innerleft);
      symself(*innerleft);
      innerleftdest = innerleftapex;

      innerleftapex = innerleft->GetApex();
      //GetApex(*innerleft, innerleftapex);

      changemade = 1;
    }
    //Make innerrightorg the "bottommost" vertex of the right hull.
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, innerrightapex, innerrightorg, innerleftdest) >
        0.0) {
      lnextself(*innerright);
      symself(*innerright);
      innerrightorg = innerrightapex;

      innerrightapex = innerright->GetApex();
      //GetApex(*innerright, innerrightapex);

      changemade = 1;
    }
  } while (changemade);
  //Find the two candidates to be the next "gear tooth."
  sym(*innerleft, leftcand);
  sym(*innerright, rightcand);
  //Create the bottom new bounding triangle.
  maketriangle(m, b, &baseedge);
  //Connect it to the bounding boxes of the left and right triangulations.
  bond(baseedge, *innerleft);
  lnextself(baseedge);
  bond(baseedge, *innerright);
  lnextself(baseedge);

  baseedge.SetOrigin(innerrightorg);
  //SetOrigin(baseedge, innerrightorg);

  baseedge.SetDest(innerleftdest);
  //SetDest(baseedge, innerleftdest);

  //Apex is intentionally left NULL.
  if (b.m_verbosity > 2) {
    std::cout << "  Creating base bounding ";
    printtriangle(m, b, &baseedge);
  }
  //Fix the extreme triangles if necessary.
    farleftpt = farleft->GetOrigin()
  //GetOrigin(*farleft, farleftpt);

  if (innerleftdest == farleftpt)
  {
    lnext(baseedge, *farleft);
  }

  farrightpt = farright->GetDest();
  //GetDest(*farright, farrightpt);

  if (innerrightorg == farrightpt)
  {
    lprev(baseedge, *farright);
  }
  //The vertices of the current knitting edge.
  lowerleft = innerleftdest;
  lowerright = innerrightorg;
  //The candidate vertices for knitting.

  upperleft = leftcand.GetApex();
  //GetApex(leftcand, upperleft);

  upperright = rightcand.GetApex();
  //GetApex(rightcand, upperright);

  //Walk up the gap between the two triangulations, knitting them together.
  while (1) {
    //Have we reached the top?  (This isn't quite the right question,
    //  because even though the left triangulation might seem finished now,
    //  moving up on the right triangulation might reveal a new vertex of
    //  the left triangulation.  And vice-versa.)
    leftfinished = counterclockwise(m.m_counterclockcount, b.m_noexact, upperleft, lowerleft, lowerright) <=
                   0.0;
    rightfinished = counterclockwise(m.m_counterclockcount, b.m_noexact, upperright, lowerleft, lowerright)
                 <= 0.0;
    if (leftfinished && rightfinished) {
      //Create the top new bounding triangle.
      maketriangle(m, b, &nextedge);

      nextedge.SetOrigin(lowerleft);
      //SetOrigin(nextedge, lowerleft);

      nextedge.SetDest(lowerright);
      //SetDest(nextedge, lowerright);

      //Apex is intentionally left NULL.
      //Connect it to the bounding boxes of the two triangulations.
      bond(nextedge, baseedge);
      lnextself(nextedge);
      bond(nextedge, rightcand);
      lnextself(nextedge);
      bond(nextedge, leftcand);
      if (b.m_verbosity > 2) {
        std::cout << "  Creating top bounding ");
        printtriangle(m, b, &nextedge);
      }
      //Special treatment for horizontal cuts.
      if (b.m_dwyer && (axis == 1))
      {
        farleftpt = farleft->GetOrigin();
        //GetOrigin(*farleft, farleftpt);

        farleftapex = farleft->GetApex();
        //GetApex(*farleft, farleftapex);

        farrightpt = farright->GetDest();
        //GetDest(*farright, farrightpt);

        farrightapex = farright->GetApex();
        //GetApex(*farright, farrightapex);

        sym(*farleft, checkedge);

        checkvertex = checkedge.GetApex();
        //GetApex(checkedge, checkvertex);

        //The pointers to the extremal vertices are restored to the
        //  leftmost and rightmost vertices (rather than topmost and
        //  bottommost).
        while (checkvertex[0] < farleftpt[0]) {
          lprev(checkedge, *farleft);
          farleftapex = farleftpt;
          farleftpt = checkvertex;
          sym(*farleft, checkedge);

          checkvertex = checkedge.GetApex();
          //GetApex(checkedge, checkvertex);
        }
        while (farrightapex[0] > farrightpt[0])
        {
          lprevself(*farright);
          symself(*farright);
          farrightpt = farrightapex;

          farrightapex = farright->GetApex();
          //GetApex(*farright, farrightapex);
        }
      }
      return;
    }
    //Consider eliminating edges from the left triangulation.
    if (!leftfinished) {
      //What vertex would be exposed if an edge were deleted?
      lprev(leftcand, nextedge);
      symself(nextedge);

      nextapex = nextedge.GetApex();
      //GetApex(nextedge, nextapex);

      //If nextapex is NULL, then no vertex would be exposed; the
      //  triangulation would have been eaten right through.
      if (nextapex != nullptr) {
        //Check whether the edge is Delaunay.
        badedge = incircle(m, b, lowerleft, lowerright, upperleft, nextapex) >
                  0.0;
        while (badedge) {
          //Eliminate the edge with an edge flip.  As a result, the
          //  left triangulation will have one more boundary triangle.
          lnextself(nextedge);
          sym(nextedge, topcasing);
          lnextself(nextedge);
          sym(nextedge, sidecasing);
          bond(nextedge, topcasing);
          bond(leftcand, sidecasing);
          lnextself(leftcand);
          sym(leftcand, outercasing);
          lprevself(nextedge);
          bond(nextedge, outercasing);
          //Correct the vertices to reflect the edge flip.

          leftcand.SetOrigin(lowerleft);
          //SetOrigin(leftcand, lowerleft);

          leftcand.SetDest(nullptr);
          //SetDest(leftcand, NULL);

          leftcand.SetApex(nextapex);
          //SetApex(leftcand, nextapex);

          nextedge.SetOrigin(nullptr);
          //SetOrigin(nextedge, NULL);

          nextedge.SetDest(upperleft);
          //SetDest(nextedge, upperleft);

          nextedge.SetApex(nextapex);
          //SetApex(nextedge, nextapex);

          //Consider the newly exposed vertex.
          upperleft = nextapex;
          //What vertex would be exposed if another edge were deleted?
          nextedge = sidecasing;
          //otricopy(sidecasing, nextedge);

          nextapex = nextedge.GetApex();
          //GetApex(nextedge, nextapex);

          if (nextapex != nullptr) {
            //Check whether the edge is Delaunay.
            badedge = incircle(m, b, lowerleft, lowerright, upperleft,
                               nextapex) > 0.0;
          } else {
            //Avoid eating right through the triangulation.
            badedge = 0;
          }
        }
      }
    }
    //Consider eliminating edges from the right triangulation.
    if (!rightfinished) {
      //What vertex would be exposed if an edge were deleted?
      lnext(rightcand, nextedge);
      symself(nextedge);

      nextapex = nextedge.GetApex();
      //GetApex(nextedge, nextapex);

      //If nextapex is NULL, then no vertex would be exposed; the
      //  triangulation would have been eaten right through.
      if (nextapex != nullptr) {
        //Check whether the edge is Delaunay.
        badedge = incircle(m, b, lowerleft, lowerright, upperright, nextapex) >
                  0.0;
        while (badedge) {
          //Eliminate the edge with an edge flip.  As a result, the
          //  right triangulation will have one more boundary triangle.
          lprevself(nextedge);
          sym(nextedge, topcasing);
          lprevself(nextedge);
          sym(nextedge, sidecasing);
          bond(nextedge, topcasing);
          bond(rightcand, sidecasing);
          lprevself(rightcand);
          sym(rightcand, outercasing);
          lnextself(nextedge);
          bond(nextedge, outercasing);
          //Correct the vertices to reflect the edge flip.
          rightcand.SetOrigin(nullptr);
          //setorg(rightcand, NULL);

          rightcand.SetDest(lowwerright);
          //setdest(rightcand, lowerright);

          rightcand.SetApex(nextapex);
          //setapex(rightcand, nextapex);

          nextedge.SetOrigin(upperright);
          //setorg(nextedge, upperright);

          nextedge.SetDest(nullptr);
          //setdest(nextedge, NULL);

          nextedge.SetApex(nextapex);
          //setapex(nextedge, nextapex);

          //Consider the newly exposed vertex.
          upperright = nextapex;
          //What vertex would be exposed if another edge were deleted?

          nextedge = sidecasing;
          //otricopy(sidecasing, nextedge);

          nextapex = nextedge.GetApex();
          //apex(nextedge, nextapex);

          if (nextapex)
          {
            //Check whether the edge is Delaunay.
            badedge = incircle(m.m_incirclecount, b.m_noexact, lowerleft, lowerright, upperright,nextapex) > 0.0;
          }
          else
          {
            //Avoid eating right through the triangulation.
            badedge = 0;
          }
        }
      }
    }
    if (leftfinished || (!rightfinished && (incircle(m.m_incirclecount, b.m_noexact, upperleft, lowerleft, lowerright, upperright) > 0.0)))
    {
      //Knit the triangulations, adding an edge from `lowerleft'
      //  to `upperright'.
      bond(baseedge, rightcand);
      lprev(rightcand, baseedge);

      baseedge.SetDest(lowerleft);
      //setdest(baseedge, lowerleft);

      lowerright = upperright;
      sym(baseedge, rightcand);

      rightcand.SetApex(upperight);
      //apex(rightcand, upperright);
    }
    else
    {
      //Knit the triangulations, adding an edge from `upperleft'
      //  to `lowerright'.
      bond(baseedge, leftcand);
      lnext(leftcand, baseedge);

      baseedge->SetOrigin(lowerright);
      //setorg(baseedge, lowerright);

      lowerleft = upperleft;
      sym(baseedge, leftcand);

      leftcand.SetApex(upperleft);
      //apex(leftcand, upperleft);
    }
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Connecting ");
      printtriangle(m, b, &baseedge);
    }
    */
  }
}

void ribi::tricpp::divconqrecurse(
  Mesh& m,
  const Behavior& b,
  const Vertex * const sortarray,
  const int vertices,
  const int axis,
  Otri * const farleft,
  Otri * const farright
)
{
  Otri midtri, tri1, tri2, tri3;
  Otri innerleft, innerright;
  double area;
  int divider;
  /*
  if (b.m_verbosity > 2) {
    std::cout << "  Triangulating %d vertices.\n", vertices);
  }
  */
  if (vertices == 2) {
    //The triangulation of two vertices is an edge.  An edge is
    //  represented by two bounding triangles.
    maketriangle(m, b, farleft);

    farleft->SetOrigin(sortarray[0]);
    //setorg(*farleft, sortarray[0]);

    farleft->SetDest(sortarray[1]);
    //setdest(*farleft, sortarray[1]);

    //The apex is intentionally left NULL.
    farleft->SetApex(nullptr);

    maketriangle(m, b, farright);

    farright->SetOrigin(sortarray[1]);
    //setorg(*farright, sortarray[1]);

    farright->SetDest(sortarray[0]);
    //setdest(*farright, sortarray[0]);

    //The apex is intentionally left NULL.
    farright->SetApex(nullptr);

    bond(*farleft, *farright);
    lprevself(*farleft);
    lnextself(*farright);
    bond(*farleft, *farright);
    lprevself(*farleft);
    lnextself(*farright);
    bond(*farleft, *farright);
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Creating ");
      printtriangle(m, b, farleft);
      std::cout << "  Creating ");
      printtriangle(m, b, farright);
    }
    */
    //Ensure that the origin of `farleft' is sortarray[0].
    lprev(*farright, *farleft);
    return;
  }
  else if (vertices == 3)
  {
    //The triangulation of three vertices is either a triangle (with
    //  three bounding triangles) or two edges (with four bounding
    //  triangles).  In either case, four triangles are created.
    maketriangle(m, b, &midtri);
    maketriangle(m, b, &tri1);
    maketriangle(m, b, &tri2);
    maketriangle(m, b, &tri3);
    area = counterclockwise(m.m_counterclockcount, b.m_noexact, sortarray[0], sortarray[1], sortarray[2]);
    if (area == 0.0)
    {
      //Three collinear vertices; the triangulation is two edges.
      midtri.SetOrigin(sortarray[0]);
      //SetOrigin(midtri, sortarray[0]);

      midtri.SetDest(sortarray[1]);
      //SetDest(midtri, sortarray[1]);

      tri1.SetOrigin(sortarray[1]);
      //SetOrigin(tri1, sortarray[1]);

      tri1.SetDest(sortarray[0]);
      //SetDest(tri1, sortarray[0]);

      tri2.SetOrigin(sortarray[2]);
      //SetOrigin(tri2, sortarray[2]);

      tri2.SetDest(sortarray[1]);
      //SetDest(tri2, sortarray[1]);

      tri3.SetOrigin(sortarray[1]);
      //SetOrigin(tri3, sortarray[1]);

      tri3.SetDest(sortarray[2]);
      //SetDest(tri3, sortarray[2]);

      //All apices are intentionally left NULL.
      bond(midtri, tri1);
      bond(tri2, tri3);
      lnextself(midtri);
      lprevself(tri1);
      lnextself(tri2);
      lprevself(tri3);
      bond(midtri, tri3);
      bond(tri1, tri2);
      lnextself(midtri);
      lprevself(tri1);
      lnextself(tri2);
      lprevself(tri3);
      bond(midtri, tri1);
      bond(tri2, tri3);
      //Ensure that the origin of `farleft' is sortarray[0].
      farleft = tri1;
      //otricopy(tri1, *farleft);
      //Ensure that the destination of `farright' is sortarray[2].
      farright = tri2;
      //otricopy(tri2, *farright);
    }
    else
    {
      //The three vertices are not collinear; the triangulation is one
      //  triangle, namely `midtri'.

      midtri.SetOrigin(sortarray[0]);
      //SetOrigin(midtri, sortarray[0]);

      tri1.SetDest(sortarray[0]);
      //SetDest(tri1, sortarray[0]);

      tri3.SetOrigin(sortarray[0]);
      //SetOrigin(tri3, sortarray[0]);

      //Apices of tri1, tri2, and tri3 are left NULL.
      if (area > 0.0)
      {
        //The vertices are in counterclockwise order.
        midtri.SetDest(sortarray[1]);
        //SetDest(midtri, sortarray[1]);

        tri1.SetOrigin(sortarray[1]);
        //SetOrigin(tri1, sortarray[1]);

        tri2.SetDest(sortarray[1]);
        //SetDest(tri2, sortarray[1]);

        midtri.SetApex(sortarray[2]);
        //SetApex(midtri, sortarray[2]);

        tri2.SetOrigin(sortarray[2]);
        //SetOrigin(tri2, sortarray[2]);

        tri3.SetDest(sortarray[2]);
        //SetDest(tri3, sortarray[2]);
      }
      else
      {
        //The vertices are in clockwise order.
        midtri.SetOrigin(sortarray[2]);
        //SetDest(midtri, sortarray[2]);

        tri1.SetOrigin(sortarray[2]);
        //SetOrigin(tri1, sortarray[2]);

        tri2.SetDest(sortarray[2]);
        //SetDest(tri2, sortarray[2]);

        midtri.SetApex(sortarray[1]);
        //SetApex(midtri, sortarray[1]);

        tri2.SetOrigin(sortarray[1]);
        //SetOrigin(tri2, sortarray[1]);

        tri3.SetDest(sortarray[1]);
        //SetDest(tri3, sortarray[1]);
      }
      //The topology does not depend on how the vertices are ordered.
      bond(midtri, tri1);
      lnextself(midtri);
      bond(midtri, tri2);
      lnextself(midtri);
      bond(midtri, tri3);
      lprevself(tri1);
      lnextself(tri2);
      bond(tri1, tri2);
      lprevself(tri1);
      lprevself(tri3);
      bond(tri1, tri3);
      lnextself(tri2);
      lprevself(tri3);
      bond(tri2, tri3);
      //Ensure that the origin of `farleft' is sortarray[0].
      farleft = tri1;
      //otricopy(tri1, *farleft);

      //Ensure that the destination of `farright' is sortarray[2].
      if (area > 0.0)
      {
        farright = tri2;
        //otricopy(tri2, *farright);
      }
      else
      {
        lnext(*farleft, *farright);
      }
    }
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Creating ");
      printtriangle(m, b, &midtri);
      std::cout << "  Creating ");
      printtriangle(m, b, &tri1);
      std::cout << "  Creating ");
      printtriangle(m, b, &tri2);
      std::cout << "  Creating ");
      printtriangle(m, b, &tri3);
    }
    */
    return;
  } else {
    //Split the vertices in half.
    divider = vertices >> 1;
    //Recursively triangulate each half.
    divconqrecurse(m, b, sortarray, divider, 1 - axis, farleft, &innerleft);
    divconqrecurse(m, b, &sortarray[divider], vertices - divider, 1 - axis,&innerright, farright);
    /*
    if (b.m_verbosity > 1)
    {
      std::cout << "  Joining triangulations with %d and %d vertices.\n", divider,
             vertices - divider);
    }
    */
    //Merge the two triangulations into one.
    mergehulls(m, b, farleft, &innerleft, &innerright, farright, axis);
  }
}

long ribi::tricpp::removeghosts(
  Mesh& m,
  const Behavior& b,
  Otri * const startghost
)
{
  Otri searchedge;
  Otri dissolveedge;
  Otri deadtriangle;
  Vertex markorg;
  long hullsize;
  Triangle ptr;                         //Temporary variable used by sym().
  /*
  if (b.m_verbosity) {
    std::cout << "  Removing ghost triangles.\n");
  }
  */
  //Find an edge on the convex hull to start point location from.
  lprev(*startghost, searchedge);
  symself(searchedge);
  m.m_dummytri[0] = encode(searchedge);
  //Remove the bounding box and count the convex hull edges.

  dissolveedge = startghost;
  //otricopy(*startghost, dissolveedge);

  hullsize = 0;
  do
  {
    hullsize++;
    lnext(dissolveedge, deadtriangle);
    lprevself(dissolveedge);
    symself(dissolveedge);
    //Remove a bounding triangle from a convex hull triangle.
    dissolve(dissolveedge);
    //Find the next bounding triangle.
    sym(deadtriangle, dissolveedge);
    //Delete the bounding triangle.
    //triangledealloc(m, deadtriangle.m_tri);
    m.KillTriangle(deadtriangle.m_tri);
  }
  while (dissolveedge != *startghost);
  //while (!otriequal(dissolveedge, *startghost));
  return hullsize;
}

long ribi::tricpp::divconqdelaunay(
  Mesh& m,
  const Behavior& b
)
{
  //vertex *sortarray;
  std::vector<Vertex> sortarray;
  struct Otri hullleft, hullright;
  int divider;
  int i = 0;
  //int j = 0;

  /*
  if (b.m_verbosity) {
    std::cout << "  Sorting vertices.\n");
  }
  */
  //Allocate an array of pointers to vertices for sorting.
  //sortarray = (vertex *) trimalloc(m.invertices * (int) sizeof(vertex));
  sortarray.resize(m.m_invertices);

  TraversalInit(&m.m_vertices);
  for (i = 0; i < m.m_invertices; i++) {
    sortarray[i] = vertextraverse(m);
  }
  //Sort the vertices.
  vertexsort(&sortarray[0], m.m_invertices);
  //Discard duplicate vertices, which can really mess up the algorithm.
  i = 0;
  for (int j = 1; j < m.m_invertices; j++)
  {
    if ((sortarray[i][0] == sortarray[j][0]) && (sortarray[i][1] == sortarray[j][1]))
    {
      /*
      if (!b.m_quiet)
      {
        std::cout << "Warning:  A duplicate vertex at ("
          << sortarray[j][0] << ", "
          << sortarray[j][1] << ") appeared and was ignored.\n"
        ;
      }
      */
      sortarray[j]->SetVertexType(VertexType::UNDEADVERTEX);
      //setvertextype(sortarray[j], VertexType::UNDEADVERTEX);
      m.m_undeads++;
    } else {
      i++;
      sortarray[i] = sortarray[j];
    }
  }
  i++;
  if (b.m_dwyer)
  {
    //Re-sort the array of vertices to accommodate alternating cuts.
    divider = i >> 1;
    if (i - divider >= 2) {
      if (divider >= 2) {
        alternateaxes(&sortarray[0], divider, 1);
      }
      alternateaxes(&sortarray[divider], i - divider, 1);
    }
  }
  /*
  if (b.m_verbosity) {
    std::cout << "  Forming triangulation.\n";
  }
  */
  //Form the Delaunay triangulation.
  divconqrecurse(m, b, &sortarray[0], i, 0, &hullleft, &hullright);

  //delete sortarray;
  //sortarray = nullptr;

  return removeghosts(m, b, &hullleft);
}


void ribi::tricpp::boundingbox(
  Mesh& m,
  const Behavior& b
)
{
  Otri inftri;          //Handle for the triangular bounding box.

  /*
  if (b.m_verbosity)
  {
    std::cout << "  Creating triangular bounding box.\n";
  }
  */
  //Find the width (or height, whichever is larger) of the triangulation.
  double width = m.m_xmax - m.m_xmin;
  if (m.m_ymax - m.m_ymin > width) {
    width = m.m_ymax - m.m_ymin;
  }
  if (width == 0.0) {
    width = 1.0;
  }
  //Create the vertices of the bounding box.
  m.m_infvertex1 = Vertex(); //(Vertex) TriMalloc(m.m_vertices.m_itembytes);
  m.m_infvertex2 = Vertex() //TriMalloc(m.m_vertices.m_itembytes);
  m.m_infvertex3 = Vertex() //TriMalloc(m.m_vertices.m_itembytes);
  m.m_infvertex1[0] = m.m_xmin - 50.0 * width;
  m.m_infvertex1[1] = m.m_ymin - 40.0 * width;
  m.m_infvertex2[0] = m.m_xmax + 50.0 * width;
  m.m_infvertex2[1] = m.m_ymin - 40.0 * width;
  m.m_infvertex3[0] = 0.5 * (m.m_xmin + m.m_xmax);
  m.m_infvertex3[1] = m.m_ymax + 60.0 * width;

  //Create the bounding box.
  maketriangle(m, b, &inftri);

  inftri.SetOrigin(m.m_infvertex1);
  //setorg(inftri, m.m_infvertex1);

  inftri.SetDest(m.m_infvertex2);
  ///setdest(inftri, m.m_infvertex2);

  inftri.SetApex(m.m_infvertex3);
  //setapex(inftri, m.m_infvertex3);

  //Link dummytri to the bounding box so we can always find an
  //  edge to begin searching (point location) from.
  m.m_dummytri[0] = inftri.m_tri;
  /*
  if (b.m_verbosity > 2)
  {
    std::cout << "  Creating ";
    printtriangle(m, b, &inftri);
  }
  */
}


long ribi::tricpp::removebox(
  Mesh& m,
  const Behavior& b
)
{
  Otri deadtriangle;
  Otri searchedge;
  Otri checkedge;
  Otri nextedge, finaledge, dissolveedge;
  Vertex markorg;
  long hullsize;
  Triangle ptr;                         //Temporary variable used by sym().
  /*
  if (b.m_verbosity) {
    std::cout << "  Removing triangular bounding box.\n");
  }
  */
  //Find a boundary triangle.
  nextedge.m_tri = m.m_dummytri;
  nextedge.m_orient = 0;
  symself(nextedge);
  //Mark a place to stop.
  lprev(nextedge, finaledge);
  lnextself(nextedge);
  symself(nextedge);
  //Find a triangle (on the boundary of the vertex set) that isn't
  //  a bounding box triangle.
  lprev(nextedge, searchedge);
  symself(searchedge);
  //Check whether nextedge is another boundary triangle
  //  adjacent to the first one.
  lnext(nextedge, checkedge);
  symself(checkedge);
  if (checkedge.m_tri == m.m_dummytri) {
    //Go on to the next triangle.  There are only three boundary
    //  triangles, and this next triangle cannot be the third one,
    //  so it's safe to stop here.
    lprevself(searchedge);
    symself(searchedge);
  }
  //Find a new boundary edge to search from, as the current search
  //  edge lies on a bounding box triangle and will be deleted.
  m.m_dummytri[0] = encode(searchedge);
  hullsize = -2l;
  while (nextedge != finaledge)
  //while (!otriequal(nextedge, finaledge))
  {
    hullsize++;
    lprev(nextedge, dissolveedge);
    symself(dissolveedge);
    //If not using a PSLG, the vertices should be marked now.
    //  (If using a PSLG, markhull() will do the job.)
    //Disconnect the bounding box triangle from the mesh triangle.
    dissolve(dissolveedge);
    lnext(nextedge, deadtriangle);
    sym(deadtriangle, nextedge);
    //Get rid of the bounding box triangle.
    triangledealloc(m, deadtriangle.m_tri);
    //Do we need to turn the corner?
    if (nextedge.m_tri == m.m_dummytri)
    {
      //Turn the corner.
      nextedge = dissolveedge;
      //otricopy(dissolveedge, nextedge);
    }
  }
  triangledealloc(m, finaledge.m_tri);

  delete m.m_infvertex1;
  m.m_infvertex1 = nullptr;
  delete m.m_infvertex2;
  m.m_infvertex2 = nullptr;
  delete m.m_infvertex3;
  m.m_infvertex3 = nullptr;

  return hullsize;
}


int ribi::tricpp::incrementaldelaunay(Mesh& m,const Behavior& b)
{
  Otri starttri;
  Vertex vertexloop;

  //Create a triangular bounding box.
  boundingbox(m, b);
  /*
  if (b.m_verbosity) {
    std::cout << "  Incrementally inserting vertices.\n");
  }
  */
  TraversalInit(&m.m_vertices);
  vertexloop = vertextraverse(m);
  while (vertexloop != nullptr)
  {
    starttri.m_tri = m.m_dummytri;
    if (insertvertex(m, b, vertexloop, &starttri, nullptr, 0, 0) == DUPLICATEVERTEX)
    {
      /*
      if (!b.m_quiet)
      {
        std::cout
          << "Warning:  A duplicate vertex at (" << vertexloop[0]
          << ", " << vertexloop[1] << ") appeared and was ignored.\n"
        ;
      }
      */
      setvertextype(vertexloop, VertexType::UNDEADVERTEX);
      m.m_undeads++;
    }
    vertexloop = vertextraverse(m);
  }
  //Remove the bounding box.
  return removebox(m, b);
}



void ribi::tricpp::createeventheap(
  Mesh& m,
  Event *** eventheap,
  Event ** events,
  Event ** freeevents
)
{
  Vertex thisvertex;
  int maxevents;


  maxevents = (3 * m.m_invertices) / 2;
  *eventheap = (struct Event **) TriMalloc(maxevents *
                                           (int) sizeof(struct Event *));
  *events = (struct Event *) TriMalloc(maxevents * (int) sizeof(struct Event));
  TraversalInit(&m.m_vertices);
  for (int i = 0; i < m.m_invertices; i++)
  {
    thisvertex = vertextraverse(m);
    (*events)[i].m_eventptr = (void *) thisvertex;
    (*events)[i].m_xkey = thisvertex[0];
    (*events)[i].m_ykey = thisvertex[1];
    eventheapinsert(*eventheap, i, *events + i);
  }
  *freeevents =  nullptr;
  for (int i = maxevents - 1; i >= m.m_invertices; i--)
  {
    (*events)[i].m_eventptr = (void *) *freeevents;
    *freeevents = *events + i;
  }
}


bool ribi::tricpp::rightofhyperbola(
  //Mesh& m,
  int& m_m_hyperbolacount,
  const Otri * const fronttri,
  const Vertex& newsite
)
{


  ++m_m_hyperbolacount;

  const Vertex leftvertex = fronttri->GetDest();
  //dest(*fronttri, leftvertex);

  const Vertex rightvertex = fronttri->GetApex();
  //apex(*fronttri, rightvertex);

  if ( leftvertex[1] < rightvertex[1]
    || (leftvertex[1] == rightvertex[1] && leftvertex[0] < rightvertex[0])
  )
  {
    if (newsite[0] >= rightvertex[0]) { return true; }
  }
  else
  {
    if (newsite[0] <= leftvertex[0]) { return false; }
  }
  const double dxa = leftvertex[0] - newsite[0];
  const double dya = leftvertex[1] - newsite[1];
  const double dxb = rightvertex[0] - newsite[0];
  const double dyb = rightvertex[1] - newsite[1];
  return dya * (dxb * dxb + dyb * dyb) > dyb * (dxa * dxa + dya * dya);
}

double ribi::tricpp::circletop(
  Mesh& m,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const double ccwabc
)
{
  m.m_circletopcount++;
  const double xac = pa[0] - pc[0];
  const double yac = pa[1] - pc[1];
  const double xbc = pb[0] - pc[0];
  const double ybc = pb[1] - pc[1];
  const double xab = pa[0] - pb[0];
  const double yab = pa[1] - pb[1];
  const double aclen2 = xac * xac + yac * yac;
  const double bclen2 = xbc * xbc + ybc * ybc;
  const double ablen2 = xab * xab + yab * yab;
  return pc[1] + (xac * bclen2 - xbc * aclen2 + sqrt(aclen2 * bclen2 * ablen2))
               / (2.0 * ccwabc);
}

void ribi::tricpp::check4deadevent(
  const Otri * const checktri,
  //const Event ** const freeevents,
  Event ** const eventheap,
  int * const heapsize
)
{
  const Vertex eventvertex = checktri->GetOrigon();
  //org(*checktri, eventvertex);

  if (eventvertex != nullptr)
  {
    Event * deadevent = (Event *) eventvertex;
    const int eventnum = deadevent->m_heapposition;
    deadevent->m_eventptr = (void *) *freeevents;
    *freeevents = deadevent;
    eventheapdelete(eventheap, *heapsize, eventnum);
    (*heapsize)--;

    checktri->SetOrigin(nullptr);
    //SetOrigin(*checktri,nullptr);
  }
}

ribi::tricpp::SplayNode * ribi::tricpp::splay(
  Mesh& m,
  SplayNode * const splaytree,
  const Vertex& searchpoint,
  Otri * const searchtri
)
{
  if (splaytree == nullptr)
  {
    return nullptr;
  }

  SplayNode *child, *grandchild;
  SplayNode *lefttree, *righttree;
  SplayNode *leftright;

  Vertex checkvertex = splaytree->m_keyedge->GetDest();

  //dest(splaytree->m_keyedge, checkvertex);
  if (checkvertex == splaytree->m_keydest)
  {
    const int rightofroot = rightofhyperbola(m, &splaytree->m_keyedge, searchpoint);
    if (rightofroot)
    {
      *searchtri = splaytree->m_keyedge
      //otricopy(splaytree->m_keyedge, *searchtri);
      child = splaytree->m_rchild;
    }
    else
    {
      child = splaytree->m_lchild;
    }
    if (child == nullptr)
    {
      return splaytree;
    }
    checkvertex = child->m_keyedge->GetDest();
    //dest(child->m_keyedge, checkvertex);

    if (checkvertex != child->m_keydest)
    {
      child = splay(m, child, searchpoint, searchtri);
      if (child == nullptr)
      {
        if (rightofroot)
        {
          splaytree->m_rchild = nullptr;
        }
        else
        {
          splaytree->m_lchild = nullptr;
        }
        return splaytree;
      }
    }
    const int rightofchild = rightofhyperbola(m, &child->m_keyedge, searchpoint);
    if (rightofchild)
    {
      searchtri = child->m_keyedge;
      //otricopy(child->m_keyedge, *searchtri);

      grandchild = splay(m, child->m_rchild, searchpoint, searchtri);
      child->m_rchild = grandchild;
    }
    else
    {
      grandchild = splay(m, child->m_lchild, searchpoint, searchtri);
      child->m_lchild = grandchild;
    }
    if (grandchild == nullptr) {
      if (rightofroot) {
        splaytree->m_rchild = child->m_lchild;
        child->m_lchild = splaytree;
      } else {
        splaytree->m_lchild = child->m_rchild;
        child->m_rchild = splaytree;
      }
      return child;
    }
    if (rightofchild)
    {
      if (rightofroot)
      {
        splaytree->m_rchild = child->m_lchild;
        child->m_lchild = splaytree;
      } else
      {
        splaytree->m_lchild = grandchild->m_rchild;
        grandchild->m_rchild = splaytree;
      }
      child->m_rchild = grandchild->m_lchild;
      grandchild->m_lchild = child;
    } else {
      if (rightofroot) {
        splaytree->m_rchild = grandchild->m_lchild;
        grandchild->m_lchild = splaytree;
      } else {
        splaytree->m_lchild = child->m_rchild;
        child->m_rchild = splaytree;
      }
      child->m_lchild = grandchild->m_rchild;
      grandchild->m_rchild = child;
    }
    return grandchild;
  } else {
    lefttree = splay(m, splaytree->m_lchild, searchpoint, searchtri);
    righttree = splay(m, splaytree->m_rchild, searchpoint, searchtri);

    PoolDealloc(&m.m_splaynodes, (void *) splaytree);
    if (lefttree == nullptr) {
      return righttree;
    } else if (righttree == nullptr) {
      return lefttree;
    } else if (lefttree->m_rchild == nullptr) {
      lefttree->m_rchild = righttree->m_lchild;
      righttree->m_lchild = lefttree;
      return righttree;
    } else if (righttree->m_lchild == nullptr) {
      righttree->m_lchild = lefttree->m_rchild;
      lefttree->m_rchild = righttree;
      return lefttree;
    } else {
//     std::cout << "Holy Toledo!!!\n");
      leftright = lefttree->m_rchild;
      while (leftright->m_rchild != nullptr) {
        leftright = leftright->m_rchild;
      }
      leftright->m_rchild = righttree;
      return lefttree;
    }
  }
}

ribi::tricpp::SplayNode * ribi::tricpp::splayinsert(
  Mesh& m,
  SplayNode * const splayroot,
  const Otri * const newkey,
  const Vertex& searchpoint
)
{
  //SplayNode *newsplaynode;

  SplayNode *newsplaynode = (SplayNode *) PoolAlloc(&m.m_splaynodes);

  newsplaynode->m_keyedge = newkey;
  //otricopy(*newkey, newsplaynode->m_keyedge);

  newsplaynode->m_keydest = newkey->GetDest();
  //GetDest(*newkey, newsplaynode->m_keydest);

  if (splayroot == nullptr) {
    newsplaynode->m_lchild = nullptr;
    newsplaynode->m_rchild = nullptr;
  } else if (rightofhyperbola(m, &splayroot->m_keyedge, searchpoint)) {
    newsplaynode->m_lchild = splayroot;
    newsplaynode->m_rchild = splayroot->m_rchild;
    splayroot->m_rchild = nullptr;
  } else {
    newsplaynode->m_lchild = splayroot->m_lchild;
    newsplaynode->m_rchild = splayroot;
    splayroot->m_lchild = nullptr;
  }
  return newsplaynode;
}

ribi::tricpp::SplayNode * ribi::tricpp::circletopinsert(
  Mesh& m,
  const Behavior& b,
  SplayNode * const splayroot,
  const Otri * const newkey,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const double topy
)
{
  //double ccwabc;
  //double xac, yac, xbc, ybc;
  //double aclen2, bclen2;
  double searchpoint[2];
  Otri dummytri;

  const double ccwabc = counterclockwise(m.m_counterclockcount, b.m_noexact, pa, pb, pc);
  const double xac = pa[0] - pc[0];
  const double yac = pa[1] - pc[1];
  const double xbc = pb[0] - pc[0];
  const double ybc = pb[1] - pc[1];
  const double aclen2 = xac * xac + yac * yac;
  const double bclen2 = xbc * xbc + ybc * ybc;
  searchpoint[0] = pc[0] - (yac * bclen2 - ybc * aclen2) / (2.0 * ccwabc);
  searchpoint[1] = topy;
  return splayinsert(m, splay(m, splayroot, (Vertex) searchpoint, &dummytri),
                     newkey, (Vertex) searchpoint);
}

ribi::tricpp::SplayNode * ribi::tricpp::frontlocate(
  Mesh& m,
  SplayNode * splayroot,
  const Otri * const bottommost,
  const Vertex& searchvertex,
  Otri * const searchtri,
  int * const farright
)
{
  //int farrightflag;
  Triangle ptr;                       //Temporary variable used by onext().

  searchtri = bottommost;
  //otricopy(*bottommost, *searchtri);

  splayroot = splay(m, splayroot, searchvertex, searchtri);

  int farrightflag = 0;
  while (!farrightflag && rightofhyperbola(m, searchtri, searchvertex))
  {
    onextself(*searchtri);
    farrightflag = *searchtri == *bottommost;
    //farrightflag = otriequal(*searchtri, *bottommost);
  }
  *farright = farrightflag;
  return splayroot;
}

long ribi::tricpp::sweeplinedelaunay(
  Mesh& m,
  const Behavior& b
)
{
  Event **eventheap;
  Event *events;
  Event *freeevents;
  Event *nextevent;
  Event *newevent;
  SplayNode *splayroot;
  Otri bottommost;
  Otri searchtri;
  Otri fliptri;
  Otri lefttri, righttri, farlefttri, farrighttri;
  Otri inserttri;
  Vertex firstvertex, secondvertex;
  Vertex nextvertex, lastvertex;
  Vertex connectvertex;
  Vertex leftvertex, midvertex, rightvertex;
  double lefttest, righttest;
  int heapsize;
  int check4events, farrightflag;
  Triangle ptr;   //Temporary variable used by sym(), onext(), and oprev().

  PoolInit(&m.m_splaynodes, sizeof(struct SplayNode), SPLAYNODEPERBLOCK,
           SPLAYNODEPERBLOCK, 0);
  splayroot = nullptr;
  /*
  if (b.m_verbosity) {
    std::cout << "  Placing vertices in event heap.\n");
  }
  */
  createeventheap(m, &eventheap, &events, &freeevents);
  heapsize = m.m_invertices;
  /*
  if (b.m_verbosity) {
    std::cout << "  Forming triangulation.\n");
  }
  */
  maketriangle(m, b, &lefttri);
  maketriangle(m, b, &righttri);
  bond(lefttri, righttri);
  lnextself(lefttri);
  lprevself(righttri);
  bond(lefttri, righttri);
  lnextself(lefttri);
  lprevself(righttri);
  bond(lefttri, righttri);
  firstvertex = eventheap[0]->m_eventptr;
  eventheap[0]->m_eventptr = freeevents;
  freeevents = eventheap[0];
  eventheapdelete(eventheap, heapsize, 0);
  --heapsize;
  do
  {
    if (heapsize == 0)
    {
      throw std::runtime_error("Triangle: Input vertices are all identical");
    }
    secondvertex = eventheap[0]->m_eventptr;
    eventheap[0]->m_eventptr = freeevents;
    freeevents = eventheap[0];
    eventheapdelete(eventheap, heapsize, 0);
    --heapsize;
    if (firstvertex[0] == secondvertex[0] && firstvertex[1] == secondvertex[1])
    {
      /*
      if (!b.m_quiet) {
        std::cout << "Warning:  A duplicate vertex at (%.12g, %.12g) appeared and was ignored.\n",
          secondvertex[0],
          secondvertex[1]
        );
      }
      */
      secondvertex.SetVertexType(VertexType::UNDEADVERTEX);
      //setvertextype(secondvertex, VertexType::UNDEADVERTEX);
      m.m_undeads++;
    }
  } while ((firstvertex[0] == secondvertex[0]) &&
           (firstvertex[1] == secondvertex[1]));

  lefttri.SetOrigin(firstvertex);
  //setorg(lefttri, firstvertex);

  lefttri.SetDest(secondvertex);
  //setdest(lefttri, secondvertex);

  righttri.SetOrigin(secondvertex);
  //setorg(righttri, secondvertex);

  righttri.SetDest(firstvertex);
  //setdest(righttri, firstvertex);
  lprev(lefttri, bottommost);
  lastvertex = secondvertex;
  while (heapsize > 0)
  {
    nextevent = eventheap[0];
    eventheapdelete(eventheap, heapsize, 0);
    heapsize--;
    check4events = 1;
    if (nextevent->m_xkey < m.m_xmin)
    {
      decode(nextevent->m_eventptr, fliptri);
      oprev(fliptri, farlefttri);
      check4deadevent(&farlefttri, &freeevents, eventheap, &heapsize);
      onext(fliptri, farrighttri);
      check4deadevent(&farrighttri, &freeevents, eventheap, &heapsize);

      if (farlefttri == bottommost))
      //if (otriequal(farlefttri, bottommost))
      {
        lprev(fliptri, bottommost);
      }
      flip(m, b, &fliptri);

      fliptri.SetApex(nullptr);
      //setapex(fliptri, NULL);

      lprev(fliptri, lefttri);
      lnext(fliptri, righttri);
      sym(lefttri, farlefttri);

      if (std::rand() % SAMPLERATE == 0)
      {
        symself(fliptri);

        leftvertex = fliptri.GetDest();
        //GetDest(fliptri, leftvertex);

        midvertex = fliptri.GetApex();
        //GetApex(fliptri, midvertex);

        rightvertex = fliptri.GetOrigin();
        //GetOrigin(fliptri, rightvertex);

        splayroot
          = circletopinsert(m, b, splayroot, &lefttri, leftvertex, midvertex, rightvertex, nextevent->m_ykey);
      }
    }
    else
    {
      nextvertex = nextevent->m_eventptr;
      if (nextvertex[0] == lastvertex[0] && nextvertex[1] == lastvertex[1])
      {
        /*
        if (!b.m_quiet)
        {
          std::cout <<
            "Warning:  A duplicate vertex at (%.12g, %.12g) appeared and was ignored.\n",
            nextvertex[0],
            nextvertex[1]
          );
        }
        */
        setvertextype(nextvertex, VertexType::UNDEADVERTEX);
        m.m_undeads++;
        check4events = 0;
      } else {
        lastvertex = nextvertex;

        splayroot = frontlocate(m, splayroot, &bottommost, nextvertex,
                                &searchtri, &farrightflag);

        check4deadevent(&searchtri, &freeevents, eventheap, &heapsize);

        farrighttri = searchtri;
        //otricopy(searchtri, farrighttri);

        sym(searchtri, farlefttri);
        maketriangle(m, b, &lefttri);
        maketriangle(m, b, &righttri);

        connectvertex = farrighttri.GetDest();
        //dest(farrighttri, connectvertex);

        lefttri.SetOrigin(connectvertex);
        //setorg(lefttri, connectvertex);

        lefttri.SetDest(nextvertex);
        //setdest(lefttri, nextvertex);

        righttri.SetOrigin(nextvertex);
        //setorg(righttri, nextvertex);

        righttri.SetDest(connectvertex);
        //setdest(righttri, connectvertex);

        bond(lefttri, righttri);
        lnextself(lefttri);
        lprevself(righttri);
        bond(lefttri, righttri);
        lnextself(lefttri);
        lprevself(righttri);
        bond(lefttri, farlefttri);
        bond(righttri, farrighttri);
        if (!farrightflag && farrighttri == bottommost)
        //if (!farrightflag && otriequal(farrighttri, bottommost))
        {
          bottommost = lefttri;
          //otricopy(lefttri, bottommost);
        }

        if (std::rand() % SAMPLERATE == 0)
        {
          splayroot = splayinsert(m, splayroot, &lefttri, nextvertex);
        }
        else if (std::rand() % SAMPLERATE == 0)
        {
          lnext(righttri, inserttri);
          splayroot = splayinsert(m, splayroot, &inserttri, nextvertex);
        }
      }
    }
    nextevent->m_eventptr = freeevents;
    freeevents = nextevent;

    if (check4events)
    {
      leftvertex = farlefttri.GetApex();
      //GetApex(farlefttri, leftvertex);

      midvertex = lefttri.GetDest();
      //GetDest(lefttri, midvertex);

      rightvertex = lefttri.GetApex();
      //GetApex(lefttri, rightvertex);

      lefttest = counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, midvertex, rightvertex);
      if (lefttest > 0.0)
      {
        newevent = freeevents;
        freeevents = (struct Event *) freeevents->m_eventptr;
        newevent->m_xkey = m.m_xminextreme;
        newevent->m_ykey = circletop(m, leftvertex, midvertex, rightvertex,lefttest);
        newevent->m_eventptr = (void *) encode(lefttri);
        eventheapinsert(eventheap, heapsize, newevent);
        heapsize++;

        lefttri.SetOrigin(newevent);
        //SetOrigin(lefttri, newevent);
      }

      leftvertex = righttri.GetApex();
      //apex(righttri, leftvertex);

      midvertex = righttri.GetOrigin();
      //org(righttri, midvertex);

      rightvertex = farrighttri.GetApex();
      //apex(farrighttri, rightvertex);

      double righttest = counterclockwise(m.m_counterclockcount, b.m_noexact, leftvertex, midvertex, rightvertex);
      if (righttest > 0.0)
      {
        newevent = freeevents;
        freeevents = (struct Event *) freeevents->m_eventptr;
        newevent->m_xkey = m.m_xminextreme;
        newevent->m_ykey = circletop(m, leftvertex, midvertex, rightvertex,
                                   righttest);
        newevent->m_eventptr = (void *) encode(farrighttri);
        eventheapinsert(eventheap, heapsize, newevent);
        heapsize++;
        farrighttri.SetOrigin(newevent);
        //SetOrigin(farrighttri, newevent);
      }
    }
  }

  PoolDeinit(&m.m_splaynodes);
  lprevself(bottommost);
  return removeghosts(m, b, &bottommost);
}

long ribi::tricpp::delaunay(Mesh& m,const Behavior& b)
{
  long hulledges;

  m.m_eextras = 0;
  initializetrisubpools(m, b);
  /*
  if (!b.m_quiet) {
    std::cout << "Constructing Delaunay triangulation ");
    if (b.m_incremental) {
      std::cout << "by incremental method.\n");
    } else if (b.m_sweepline) {
      std::cout << "by sweepline method.\n");
    } else {
      std::cout << "by divide-and-conquer method.\n");
    }
  }
  */
  if (b.m_incremental)
  {
    hulledges = incrementaldelaunay(m, b);
  }
  else if (b.m_sweepline)
  {
    hulledges = sweeplinedelaunay(m, b);
  }
  else
  {
    hulledges = divconqdelaunay(m, b);
  }

  if (m.m_triangles.m_items == 0)
  {
    //The input vertices were all collinear, so there are no triangles.
    return 0l;
  }
  else
  {
    return hulledges;
  }
}

long ribi::tricpp::reconstruct(
  Mesh& m,
  const Behavior& b,
  std::string& elefilename,
  const std::string& areafilename,
  const std::string& polyfilename,
  FILE * const polyfile
)
{
  FILE *elefile;
  FILE *areafile;
  char inputline[g_max_inputline_size];
  char *stringptr;
  int areaelements;
  Otri triangleloop;
  Otri triangleleft;
  Otri checktri;
  Otri checkleft;
  Otri checkneighbor;
  Osub subsegloop;
  Triangle *vertexarray;
  Triangle *prevlink;
  Triangle nexttri;
  Vertex tdest, tapex;
  Vertex checkdest, checkapex;
  Vertex shorg;
  Vertex segmentorg, segmentdest;
  double area;
  int corner[3];
  int end[2];
  int killvertexindex;
  int incorners;
  int segmentmarkers;
  int boundmarker;
  int aroundvertex;
  long hullsize;
  int notfound;
  long i, i;
  int i, j;
  Triangle ptr;                         //Temporary variable used by sym().

  //Read the triangles from an .ele file.
  //elefile = fopen(elefilename.c_str(), "r");
  std::vector<std::string> v = ribi::fileio::FileIo().FileToVector(elefilename);
  assert(!v.empty());
  {
    const std::vector<std::string> w = SeperateString(v[0],' ');
    assert(w.size() == 3);
    m.m_inelements = boost::lexical_cast<int>(w[0]);
    incorners = boost::lexical_cast<int>(w[1]);
    m.m_eextras = boost::lexical_cast<int>(w[2]);
  }
  //std::ifstream elefile(elefilename.c_str());
  /*
  if (elefile == nullptr) {
    std::stringstream s;
    s << "Triangle: Cannot access file '" << elefilename << "'";
    throw std::runtime_error(s.str().c_str());
  }
  */
  //Read number of triangles, number of vertices per triangle, and
  //  number of triangle attributes from .ele file.
  /*
  stringptr = readline(inputline, elefile);
  m.m_inelements = (int) strtol(stringptr, &stringptr, 0);
  stringptr = FindField(stringptr);
  if (*stringptr == '\0') {
    incorners = 3;
  } else {
    incorners = (int) strtol(stringptr, &stringptr, 0);
    if (incorners < 3)
    {
      std::stringstream s;
      s << "Triangle: Triangles in " << elefilename << " must have at least 3 vertices";
      throw std::logic_error(s.str().c_str());
    }
  }
  stringptr = FindField(stringptr);
  if (*stringptr == '\0') {
    m.m_eextras = 0;
  } else {
    m.m_eextras = (int) strtol(stringptr, &stringptr, 0);
  }
  initializetrisubpools(m, b);
  */
  //Create the triangles.
  for (int i = 0; i != m.m_inelements; ++i)
  {
    Triangle triangle;
    m.m_triangles.push_back(triangle);
    //maketriangle(m, b, &triangleloop);
    //Mark the triangle as living.
    //triangleloop.m_tri[3] = (Triangle) triangleloop.m_tri;
  }

  segmentmarkers = 0;

  //Read number of segments and number of segment
  //  boundary markers from .poly file.
  stringptr = readline(inputline, polyfile);
  m.m_insegments = (int) strtol(stringptr, &stringptr, 0);
  stringptr = FindField(stringptr);
  if (*stringptr != '\0')
  {
    segmentmarkers = (int) strtol(stringptr, &stringptr, 0);
  }
  //Create the subsegments.
  for (int i = 0; i != m.m_insegments; ++i)
  {

    makesubseg(m, &subsegloop);
    //Mark the subsegment as living.
    subsegloop.m_subseg[2] = (SubSeg) subsegloop.m_subseg;
  }

  if (b.m_vararea)
  {
    //Open an .area file, check for consistency with the .ele file.
    areafile = fopen(areafilename.c_str(), "r");
    if (areafile == nullptr) {
      std::stringstream s;
      s << "Triangle: Cannot access file "
        << areafilename << "."
      ;
      throw std::runtime_error(s.str().c_str());
    }
    stringptr = readline(inputline, areafile);
    areaelements = (int) strtol(stringptr, &stringptr, 0);
    if (areaelements != m.m_inelements) {
      std::stringstream s;
      s << "Triangle: " << elefilename << " and "
        << areafilename
        << " disagree on number of triangles"
      ;
      throw std::runtime_error(s.str().c_str());
    }
  }
  /*
  if (!b.m_quiet)
  {
    std::cout << "Reconstructing mesh.\n";
  }
  */
  //Allocate a temporary array that maps each vertex to some adjacent
  //  triangle.  I took care to allocate all the permanent memory for
  //  triangles and subsegments first.
  vertexarray = (Triangle *) TriMalloc(m.m_vertices.m_items *
                                       (int) sizeof(Triangle));
  //Each vertex is initially unrepresented.
  for (int i = 0; i < m.m_vertices.m_items; i++)
  {
    vertexarray[i] = (Triangle) m.m_dummytri;
  }
  /*
  if (b.m_verbosity)
   {
    std::cout << "  Assembling triangles.\n");
  }
  */
  //Read the triangles from the .ele file, and link
  //  together those that share an edge.
  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  i = b.m_firstnumber;
  while (triangleloop.m_tri != nullptr)
  {
    //Read triangle number and the triangle's three corners.
    stringptr = readline(inputline, elefile);
    for (j = 0; j < 3; j++)
    {
      stringptr = FindField(stringptr);
      if (*stringptr == '\0')
      {
        std::stringstream s;
        s << "Triangle: Triangle "
          << i
          << " is missing vertex "
          << (j + 1) << " in " << elefilename;
        throw std::logic_error(s.str().c_str());
      }
      else
      {
        corner[j] = (int) strtol(stringptr, &stringptr, 0);
        if (corner[j] < b.m_firstnumber || corner[j] >= b.m_firstnumber + m.m_invertices)
        {
          std::stringstream s;
          s << "Triangle: Triangle " << i << " has an invalid vertex index";
          throw std::logic_error(s.str().c_str());
        }
      }
    }

    //Find out about (and throw away) extra nodes.
    for (int j = 3; j < incorners; j++)
    {
      stringptr = FindField(stringptr);
      if (*stringptr != '\0')
      {
        killvertexindex = (int) strtol(stringptr, &stringptr, 0);
        if (killvertexindex >= b.m_firstnumber && killvertexindex < b.m_firstnumber + m.m_invertices)
        {
          //Delete the non-corner vertex if it's not already deleted.
          m.KillVertex(killvertexindex);
          //const auto& killvertex = m.GetVertex(killvertexindex);
          //if (vertextype(killvertex) != VertexType::DEADVERTEX) {
          //  vertexdealloc(m, killvertex);
          // }
        }
      }
    }

    //Read the triangle's attributes.
    for (int j = 0; j != m.m_eextras; ++j)
    {
      stringptr = FindField(stringptr);
      if (*stringptr == '\0')
      {
        triangleloop.SetElemAttrib(j,0);
        //setelemattribute(triangleloop, j, 0);
      }
      else
      {
        triangleloop.SetElemAttrib(j,strtod(stringptr, &stringptr));
        //setelemattribute(triangleloop, j,strtod(stringptr, &stringptr));
      }
    }

    if (b.m_vararea)
    {
      //Read an area constraint from the .area file.
      stringptr = readline(inputline, areafile);
      stringptr = FindField(stringptr);
      if (*stringptr == '\0')
      {
        area = -1.0;                      //No constraint on this triangle.
      }
      else
      {
        area = strtod(stringptr, &stringptr);
      }
      setareabound(triangleloop, area);
    }

    //Set the triangle's vertices.
    triangleloop.m_orient = 0;

    triangleloop.SetOrigin(getvertex(m.m_vertices, b, corner[0]));
    //setorg(triangleloop, getvertex(m.m_vertices, b, corner[0]));

    triangleloop.SetDest(getvertex(m.m_vertices, b, corner[1]));
    //setdest(triangleloop, getvertex(m.m_vertices, b, corner[1]));

    triangleloop.SetApex(getvertex(m.m_vertices, b, corner[2]));
    //setapex(triangleloop, getvertex(m.m_vertices, b, corner[2]));

    //Try linking the triangle to others that share these vertices.
    for (triangleloop.m_orient = 0; triangleloop.m_orient != 3; ++triangleloop.m_orient)
    {
      //Take the number for the origin of triangleloop.
      aroundvertex = corner[triangleloop.m_orient];
      //Look for other triangles having this vertex.
      nexttri = vertexarray[aroundvertex - b.m_firstnumber];
      //Link the current triangle to the next one in the stack.
      triangleloop.m_tri[6 + triangleloop.m_orient] = nexttri;
      //Push the current triangle onto the stack.
      vertexarray[aroundvertex - b.m_firstnumber] = encode(triangleloop);
      decode(nexttri, checktri);
      if (checktri.m_tri != m.m_dummytri)
      {
        tdest = triangleloop.GetDest();
        //dest(triangleloop, tdest);

        tapex = triangleloop.GetApex();
        //apex(triangleloop, tapex);

        //Look for other triangles that share an edge.
        do
        {
          checkdest = checktri.GetDest();
          //dest(checktri, checkdest);

          checkapex = checktri.GetApex();
          //apex(checktri, checkapex);

          if (tapex == checkdest)
          {
            //The two triangles share an edge; bond them together.
            lprev(triangleloop, triangleleft);
            bond(triangleleft, checktri);
          }
          if (tdest == checkapex)
          {
            //The two triangles share an edge; bond them together.
            lprev(checktri, checkleft);
            bond(triangleloop, checkleft);
          }
          //Find the next triangle in the stack.
          nexttri = checktri.m_tri[6 + checktri.m_orient];
          decode(nexttri, checktri);
        } while (checktri.m_tri != m.m_dummytri);
      }
    }
    triangleloop.m_tri = triangletraverse(m);
    i++;
  }
  /*
  fclose(elefile);
  if (b.m_vararea)
  {
    fclose(areafile);
  }
  */
  hullsize = 0;                      //Prepare to count the boundary edges.
  {
    /*
    if (b.m_verbosity) {
      std::cout << "  Marking segments in triangulation.\n");
    }
    */
    //Read the segments from the .poly file, and link them
    //  to their neighboring triangles.
    boundmarker = 0;
    TraversalInit(&m.m_subsegs);
    subsegloop.m_subseg = subsegtraverse(m);
    i = b.m_firstnumber;
    while (subsegloop.m_subseg != nullptr)
    {
      //Read the endpoints of each segment, and possibly a boundary marker.
      stringptr = readline(inputline, polyfile);
      //Skip the first (segment number) field.
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        s << "Triangle: Segment "
          << i
          << " has no endpoints in "
          << polyfilename
        ;
        throw std::logic_error(s.str().c_str());
      } else
      {
        end[0] = (int) strtol(stringptr, &stringptr, 0);
      }
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        s << "Triangle: Segment " << i
          << " is missing its second endpoint in "
          << polyfilename
        ;
        throw std::logic_error(s.str().c_str());
      }
      else
      {
        end[1] = (int) strtol(stringptr, &stringptr, 0);
      }
      if (segmentmarkers)
      {
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          boundmarker = 0;
        } else {
          boundmarker = (int) strtol(stringptr, &stringptr, 0);
        }
      }
      for (int j = 0; j < 2; j++)
      {
        if (end[j] < b.m_firstnumber || end[j] >= b.m_firstnumber + m.m_invertices)
        {
          std::stringstream s;
          s << "Triangle: Segment "
            << i
            << " has an invalid vertex index"
          ;
          throw std::logic_error(s.str().c_str());
        }
      }

      //set the subsegment's vertices.
      subsegloop.m_subseg_orient = 0;
      segmentorg = getvertex(m.m_vertices, b, end[0]);
      segmentdest = getvertex(m.m_vertices, b, end[1]);

      subsegloop.SetsOrigin(segmentorg);
      //SetsOrigin(subsegloop, segmentorg);

      subsegloop.SetDest(segmentdest);
      //SetDest(subsegloop, segmentdest);

      setsegorg(subsegloop, segmentorg);
      setsegdest(subsegloop, segmentdest);
      setmark(subsegloop, boundmarker);
      //Try linking the subsegment to triangles that share these vertices.
      for (subsegloop.m_subseg_orient = 0; subsegloop.m_subseg_orient < 2;
           subsegloop.m_subseg_orient++)
      {
        //Take the number for the destination of subsegloop.
        aroundvertex = end[1 - subsegloop.m_subseg_orient];
        //Look for triangles having this vertex.
        prevlink = &vertexarray[aroundvertex - b.m_firstnumber];
        nexttri = vertexarray[aroundvertex - b.m_firstnumber];
        decode(nexttri, checktri);

        shorg = subsegloop.GetOrigin();
        //GetOrigin(subsegloop, shorg);

        notfound = 1;
        //Look for triangles having this edge.  Note that I'm only
        //  comparing each triangle's destination with the subsegment;
        //  each triangle's apex is handled through a different vertex.
        //  Because each triangle appears on three vertices' lists, each
        //  occurrence of a triangle on a list can (and does) represent
        //  an edge.  In this way, most edges are represented twice, and
        //  every triangle-subsegment bond is represented once.
        while (notfound && (checktri.m_tri != m.m_dummytri))
        {

          checkdest = checktri.GetDest();
          //GetDest(checktri, checkdest);

          if (shorg == checkdest)
          {
            //We have a match.  Remove this triangle from the list.
            *prevlink = checktri.m_tri[6 + checktri.m_orient];
            //Bond the subsegment to the triangle.
            tsbond(checktri, subsegloop);
            //Check if this is a boundary edge.
            sym(checktri, checkneighbor);
            if (checkneighbor.m_tri == m.m_dummytri) {
              //The next line doesn't insert a subsegment (because there's
              //  already one there), but it sets the boundary markers of
              //  the existing subsegment and its vertices.
              insertsubseg(m, b, &checktri, 1);
              hullsize++;
            }
            notfound = 0;
          }
          //Find the next triangle in the stack.
          prevlink = &checktri.m_tri[6 + checktri.m_orient];
          nexttri = checktri.m_tri[6 + checktri.m_orient];
          decode(nexttri, checktri);
        }
      }
      subsegloop.m_subseg = subsegtraverse(m);
      i++;
    }
  }

  //Mark the remaining edges as not being attached to any subsegment.
  //Also, count the (yet uncounted) boundary edges.
  for (i = 0; i < m.m_vertices.m_items; i++) {
    //Search the stack of triangles adjacent to a vertex.
    nexttri = vertexarray[i];
    decode(nexttri, checktri);
    while (checktri.m_tri != m.m_dummytri) {
      //Find the next triangle in the stack before this
      //  information gets overwritten.
      nexttri = checktri.m_tri[6 + checktri.m_orient];
      //No adjacent subsegment.  (This overwrites the stack info.)
      tsdissolve(checktri);
      sym(checktri, checkneighbor);
      if (checkneighbor.m_tri == m.m_dummytri) {
        insertsubseg(m, b, &checktri, 1);
        hullsize++;
      }
      decode(nexttri, checktri);
    }
  }

  delete vertexarray;
  vertexarray = nullptr;
  return hullsize;
}

ribi::tricpp::FindDirectionResult ribi::tricpp::finddirection(
  Mesh& m,
  const Behavior& b,
  Otri * const searchtri,
  const Vertex& searchpoint
)
{
  Otri checktri;
  Vertex startvertex;
  Vertex leftvertex, rightvertex;
  Triangle ptr;  // Temporary variable used by onext() and oprev().

  startvertex = searchtri->GetOrigin();
  //GetOrigin(*searchtri, startvertex);

  rightvertex = searchtri->GetDest();
  //GetDest(*searchtri, rightvertex);

  leftvertex = searchtri->GetApex();
  //GetApex(*searchtri, leftvertex);

  //Is `searchpoint' to the left?
  double leftccw = counterclockwise(m.m_counterclockcount, b.m_noexact, searchpoint, startvertex, leftvertex);
  int leftflag = leftccw > 0.0;
  //Is `searchpoint' to the right?
  double rightccw = counterclockwise(m.m_counterclockcount, b.m_noexact, startvertex, searchpoint, rightvertex);
  int rightflag = rightccw > 0.0;
  if (leftflag && rightflag) {
    //`searchtri' faces directly away from `searchpoint'.  We could go left
    //  or right.  Ask whether it's a triangle or a boundary on the left.
    onext(*searchtri, checktri);
    if (checktri.m_tri == m.m_dummytri) {
      leftflag = 0;
    } else {
      rightflag = 0;
    }
  }
  while (leftflag) {
    //Turn left until satisfied.
    onextself(*searchtri);
    if (searchtri->m_tri == m.m_dummytri) {
      std::stringstream s;
      s << "Triangle: Internal error in finddirection(): "
        << "Unable to find a triangle leading from ("
        << startvertex[0] << ", " << startvertex[1] << ") to"
        << "  (" << searchpoint[0] << ", " << searchpoint[1] << ")."
      ;
      throw std::logic_error(s.str().c_str());
    }

    leftvertex = searchtri->GetApex();
    //GetApex(*searchtri, leftvertex);

    rightccw = leftccw;
    leftccw = counterclockwise(m.m_counterclockcount, b.m_noexact, searchpoint, startvertex, leftvertex);
    leftflag = leftccw > 0.0;
  }
  while (rightflag) {
    //Turn right until satisfied.
    oprevself(*searchtri);
    if (searchtri->m_tri == m.m_dummytri) {
      std::stringstream s;
      s << "Triangle: Internal error in finddirection():  Unable to find a "
        << "triangle leading from (" << startvertex[0] << ", " << startvertex[1] << ") to"
        << "  (" << searchpoint[0] << ", " << searchpoint[1] << ")"
      ;
      throw std::logic_error(s.str().c_str());
    }

    rightvertex = searchtri->GetDest();
    //GetDest(*searchtri, rightvertex);

    leftccw = rightccw;
    rightccw = counterclockwise(m.m_counterclockcount, b.m_noexact, startvertex, searchpoint, rightvertex);
    rightflag = rightccw > 0.0;
  }
  if (leftccw == 0.0) {
    return LEFTCOLLINEAR;
  } else if (rightccw == 0.0) {
    return RIGHTCOLLINEAR;
  } else {
    return WITHIN;
  }
}

void ribi::tricpp::segmentintersection(
  Mesh& m,
  const Behavior& b,
  Otri * const splittri,
  Osub * const splitsubseg,
  const Vertex& endpoint2
)
{
  Osub opposubseg;
  Vertex endpoint1;
  Vertex torg, tdest;
  Vertex leftvertex, rightvertex;
  Vertex newvertex;
  //InsertVertexResult success;
  //enum finddirectionresult collinear;
  double ex, ey;
  double tx, ty;
  double etx, ety;
  double split, denom;

  Triangle ptr;                       //Temporary variable used by onext().
  SubSeg sptr;                        //Temporary variable used by snext().

  //Find the other three segment endpoints.
  endpoint1 = splittri->GetApex();
  //GetApex(*splittri, endpoint1);

  torg = splittri->GetOrigin();
  //GetOrigin(*splittri, torg);

  tdest = splittri->GetDest();
  //GetDest(*splittri, tdest);

  //Segment intersection formulae; see the Antonio reference.
  tx = tdest[0] - torg[0];
  ty = tdest[1] - torg[1];
  ex = endpoint2[0] - endpoint1[0];
  ey = endpoint2[1] - endpoint1[1];
  etx = torg[0] - endpoint2[0];
  ety = torg[1] - endpoint2[1];
  denom = ty * ex - tx * ey;
  if (denom == 0.0) {
    std::stringstream s;
    s << "Triangle: Internal error in segmentintersection(): "
      << "Attempt to find intersection of parallel segments";
    throw std::logic_error(s.str().c_str());
  }
  split = (ey * etx - ex * ety) / denom;
  //Create the new vertex.
  newvertex = (Vertex) PoolAlloc(&m.m_vertices);
  //Interpolate its coordinate and attributes.
  for (int i = 0; i < 2 + m.m_nextras; i++) {
    newvertex[i] = torg[i] + split * (tdest[i] - torg[i]);
  }
  setvertexmark(newvertex, mark(*splitsubseg));
  setvertextype(newvertex, VertexType::INPUTVERTEX);
  /*
  if (b.m_verbosity > 1) {
    std::cout <<
  "  Splitting subsegment (%.12g, %.12g) (%.12g, %.12g) at (%.12g, %.12g).\n",
           torg[0], torg[1], tdest[0], tdest[1], newvertex[0], newvertex[1]);
  }
  */
  //Insert the intersection vertex.  This should always succeed.
  const InsertVertexResult success = insertvertex(m, b, newvertex, splittri, splitsubseg, 0, 0);
  if (success != SUCCESSFULVERTEX) {
    std::stringstream s;
    /*
    std::cout << "Internal error in segmentintersection():\n");
    std::cout << "  Failure to split a segment.\n");
    */
    throw std::logic_error(s.str().c_str());

  }
  //Record a triangle whose origin is the new vertex.
  setvertex2tri(newvertex, encode(*splittri));
  if (m.m_steinerleft > 0) {
    m.m_steinerleft--;
  }

  //Divide the segment into two, and correct the segment endpoints.
  ssymself(*splitsubseg);
  spivot(*splitsubseg, opposubseg);
  sdissolve(*splitsubseg);
  sdissolve(opposubseg);
  do {
    setsegorg(*splitsubseg, newvertex);
    snextself(*splitsubseg);
  } while (splitsubseg->m_subseg != m.m_dummysub);
  do {
    setsegorg(opposubseg, newvertex);
    snextself(opposubseg);
  } while (opposubseg.m_subseg != m.m_dummysub);

  //Inserting the vertex may have caused edge flips.  We wish to rediscover
  //  the edge connecting endpoint1 to the new intersection vertex.
  //enum finddirectionresult collinear =finddirection(m, b, splittri, endpoint1);
  rightvertex = splittri->GetDest();
  //GetDest(*splittri, rightvertex);

  leftvertex = splittri->GetApex();
  //GetApex(*splittri, leftvertex);

  if ((leftvertex[0] == endpoint1[0]) && (leftvertex[1] == endpoint1[1])) {
    onextself(*splittri);
  } else if ((rightvertex[0] != endpoint1[0]) ||
             (rightvertex[1] != endpoint1[1])) {
    std::stringstream s;
    /*
    std::cout << "Internal error in segmentintersection():\n");
    std::cout << "  Topological inconsistency after splitting a segment.\n");
    */
    throw std::logic_error(s.str().c_str());

  }
  //`splittri' should have destination endpoint1.
}

int ribi::tricpp::scoutsegment(
  Mesh& m,
  const Behavior& b,
  Otri * const searchtri,
  const Vertex& endpoint2,
  const int newmark
)
{
  Otri crosstri;
  Osub crosssubseg;
  Vertex leftvertex, rightvertex;
  //enum finddirectionresult collinear;
  SubSeg sptr;                      //Temporary variable used by tspivot().

  const FindDirectionResult collinear = finddirection(m, b, searchtri, endpoint2);

  rightvertex = searchtri->GetDest();
  //GetDest(*searchtri, rightvertex);

  leftvertex = searchtri->GetApex();
  //GetApex(*searchtri, leftvertex);

  if (((leftvertex[0] == endpoint2[0]) && (leftvertex[1] == endpoint2[1])) ||
      ((rightvertex[0] == endpoint2[0]) && (rightvertex[1] == endpoint2[1])))
  {
    //The segment is already an edge in the mesh.
    if ((leftvertex[0] == endpoint2[0]) && (leftvertex[1] == endpoint2[1])) {
      lprevself(*searchtri);
    }
    //Insert a subsegment, if there isn't already one there.
    insertsubseg(m, b, searchtri, newmark);
    return 1;
  } else if (collinear == LEFTCOLLINEAR) {
    //We've collided with a vertex between the segment's endpoints.
    //Make the collinear vertex be the triangle's origin.
    lprevself(*searchtri);
    insertsubseg(m, b, searchtri, newmark);
    //Insert the remainder of the segment.
    return scoutsegment(m, b, searchtri, endpoint2, newmark);
  } else if (collinear == RIGHTCOLLINEAR) {
    //We've collided with a vertex between the segment's endpoints.
    insertsubseg(m, b, searchtri, newmark);
    //Make the collinear vertex be the triangle's origin.
    lnextself(*searchtri);
    //Insert the remainder of the segment.
    return scoutsegment(m, b, searchtri, endpoint2, newmark);
  } else {
    lnext(*searchtri, crosstri);
    tspivot(crosstri, crosssubseg);
    //Check for a crossing segment.
    if (crosssubseg.m_subseg == m.m_dummysub)
    {
      return 0;
    }
    else
    {
      //Insert a vertex at the intersection.
      segmentintersection(m, b, &crosstri, &crosssubseg, endpoint2);

      searchtri = crosstri;
      //otricopy(crosstri, *searchtri);

      insertsubseg(m, b, searchtri, newmark);
      //Insert the remainder of the segment.
      return scoutsegment(m, b, searchtri, endpoint2, newmark);
    }
  }
}

void ribi::tricpp::conformingedge(
  Mesh& m,
  const Behavior& b,
  const Vertex& endpoint1,
  const Vertex& endpoint2,
  const int newmark
)
{
  Otri searchtri1, searchtri2;
  Osub brokensubseg;
  Vertex newvertex;
  Vertex midvertex1, midvertex2;
  //InsertVertexResult success;

  SubSeg sptr;                      //Temporary variable used by tspivot().
  /*
  if (b.m_verbosity > 2) {
    std::cout << "Forcing segment into triangulation by recursive splitting:\n");
    std::cout << "  (%.12g, %.12g) (%.12g, %.12g)\n", endpoint1[0], endpoint1[1],
           endpoint2[0], endpoint2[1]);
  }
  */
  //Create a new vertex to insert in the middle of the segment.
  newvertex = (Vertex) PoolAlloc(&m.m_vertices);
  //Interpolate coordinates and attributes.
  for (int i = 0; i < 2 + m.m_nextras; i++) {
    newvertex[i] = 0.5 * (endpoint1[i] + endpoint2[i]);
  }
  setvertexmark(newvertex, newmark);
  setvertextype(newvertex, VertexType::SEGMENTVERTEX);
  //No known triangle to search from.
  searchtri1.m_tri = m.m_dummytri;
  //Attempt to insert the new vertex.
  InsertVertexResult success = insertvertex(m, b, newvertex, &searchtri1, nullptr,
                         0, 0);
  if (success == DUPLICATEVERTEX)
  {
    /*
    if (b.m_verbosity > 2) {
      std::cout << "  Segment intersects existing vertex (%.12g, %.12g).\n",
             newvertex[0], newvertex[1]);
    }
    */
    //Use the vertex that's already there.
    vertexdealloc(m, newvertex);

    newvertex = searchtri1.GetOrigin();
    //GetOrigin(searchtri1, newvertex);

  } else {
    if (success == VIOLATINGVERTEX)
    {
      /*
      if (b.m_verbosity > 2) {
        std::cout << "  Two segments intersect at (%.12g, %.12g).\n",
               newvertex[0], newvertex[1]);
      }
      */
      //By fluke, we've landed right on another segment.  Split it.
      tspivot(searchtri1, brokensubseg);
      success = insertvertex(m, b, newvertex, &searchtri1, &brokensubseg,
                             0, 0);
      if (success != SUCCESSFULVERTEX)
      {
        std::stringstream s;
        /*
        std::cout << "Internal error in conformingedge():\n");
        std::cout << "  Failure to split a segment.\n");
        */
        throw std::logic_error(s.str().c_str());

      }
    }
    //The vertex has been inserted successfully.
    if (m.m_steinerleft > 0)
    {
      m.m_steinerleft--;
    }
  }

  searchtri2 = searchtri1;
  //otricopy(searchtri1, searchtri2);

  //`searchtri1' and `searchtri2' are fastened at their origins to
  //  `newvertex', and will be directed toward `endpoint1' and `endpoint2'
  //  respectively.  First, we must get `searchtri2' out of the way so it
  //  won't be invalidated during the insertion of the first half of the
  //  segment.
  finddirection(m, b, &searchtri2, endpoint2);
  if (!scoutsegment(m, b, &searchtri1, endpoint1, newmark)) {
    //The origin of searchtri1 may have changed if a collision with an
    //  intervening vertex on the segment occurred.

    midvertex1 = searchtri1.GetOrigin();
    //GetOrigin(searchtri1, midvertex1);

    conformingedge(m, b, midvertex1, endpoint1, newmark);
  }
  if (!scoutsegment(m, b, &searchtri2, endpoint2, newmark)) {
    //The origin of searchtri2 may have changed if a collision with an
    //  intervening vertex on the segment occurred.

    midvertex2 = searchtri2.GetOrigin();
    //GetOrigin(searchtri2, midvertex2);

    conformingedge(m, b, midvertex2, endpoint2, newmark);
  }
}

void ribi::tricpp::delaunayfixup(
  Mesh& m,
  const Behavior& b,
  Otri * const fixuptri,
  const int leftside
)
{
  Otri neartri;
  Otri fartri;
  Osub faredge;
  Vertex nearvertex, leftvertex, rightvertex, farvertex;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  lnext(*fixuptri, neartri);
  sym(neartri, fartri);
  //Check if the edge opposite the origin of fixuptri can be flipped.
  if (fartri.m_tri == m.m_dummytri)
  {
    return;
  }
  tspivot(neartri, faredge);
  if (faredge.m_subseg != m.m_dummysub) {
    return;
  }
  //Find all the relevant vertices.
  nearvertex = neartri.GetApex();
  //GetApex(neartri, nearvertex);

  leftvertex = neartri.GetOrigin();
  //GetOrigin(neartri, leftvertex);

  rightvertex = neartri.GetDest();
  //GetDest(neartri, rightvertex);

  farvertex = fartri.GetApex();
  //GetApex(fartri, farvertex);

  //Check whether the previous polygon vertex is a reflex vertex.
  if (leftside) {
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, nearvertex, leftvertex, farvertex) <= 0.0) {
      //leftvertex is a reflex vertex too.  Nothing can
      //  be done until a convex section is found.
      return;
    }
  } else {
    if (counterclockwise(m.m_counterclockcount, b.m_noexact, farvertex, rightvertex, nearvertex) <= 0.0) {
      //rightvertex is a reflex vertex too.  Nothing can
      //  be done until a convex section is found.
      return;
    }
  }
  if (counterclockwise(m.m_counterclockcount, b.m_noexact, rightvertex, leftvertex, farvertex) > 0.0) {
    //fartri is not an inverted triangle, and farvertex is not a reflex
    //  vertex.  As there are no reflex vertices, fixuptri isn't an
    //  inverted triangle, either.  Hence, test the edge between the
    //  triangles to ensure it is locally Delaunay.
    if (incircle(m, b, leftvertex, farvertex, rightvertex, nearvertex) <=
        0.0) {
      return;
    }
    //Not locally Delaunay; go on to an edge flip.
  }        //else fartri is inverted; remove it from the stack by flipping.
  flip(m, b, &neartri);
  lprevself(*fixuptri);    //Restore the origin of fixuptri after the flip.
  //Recursively process the two triangles that result from the flip.
  delaunayfixup(m, b, fixuptri, leftside);
  delaunayfixup(m, b, &fartri, leftside);
}

void ribi::tricpp::constrainededge(
  Mesh& m,
  const Behavior& b,
  const Otri * const starttri,
  const Vertex& endpoint2,
  const int newmark
)
{
  Otri fixuptri, fixuptri2;
  Osub crosssubseg;
  Vertex endpoint1;
  Vertex farvertex;
  double area;
  //int collision;
  //int done;
  Triangle ptr;             //Temporary variable used by sym() and oprev().
  SubSeg sptr;                      //Temporary variable used by tspivot().


  endpoint1 = starttri->GetOrigin();
  //GetOrigin(*starttri, endpoint1);

  lnext(*starttri, fixuptri);
  flip(m, b, &fixuptri);
  //`collision' indicates whether we have found a vertex directly
  //  between endpoint1 and endpoint2.
  int collision = 0;
  int done = 0;
  do
  {
    farvertex = fixuptri.GetOrigin();
    //GetOrigin(fixuptri, farvertex);

    //`farvertex' is the extreme point of the polygon we are "digging"
    //  to get from endpoint1 to endpoint2.
    if ((farvertex[0] == endpoint2[0]) && (farvertex[1] == endpoint2[1])) {
      oprev(fixuptri, fixuptri2);
      //Enforce the Delaunay condition around endpoint2.
      delaunayfixup(m, b, &fixuptri, 0);
      delaunayfixup(m, b, &fixuptri2, 1);
      done = 1;
    } else {
      //Check whether farvertex is to the left or right of the segment
      //  being inserted, to decide which edge of fixuptri to dig
      //  through next.
      area = counterclockwise(m.m_counterclockcount, b.m_noexact, endpoint1, endpoint2, farvertex);
      if (area == 0.0) {
        //We've collided with a vertex between endpoint1 and endpoint2.
        collision = 1;
        oprev(fixuptri, fixuptri2);
        //Enforce the Delaunay condition around farvertex.
        delaunayfixup(m, b, &fixuptri, 0);
        delaunayfixup(m, b, &fixuptri2, 1);
        done = 1;
      } else {
        if (area > 0.0) {        //farvertex is to the left of the segment.
          oprev(fixuptri, fixuptri2);
          //Enforce the Delaunay condition around farvertex, on the
          //  left side of the segment only.
          delaunayfixup(m, b, &fixuptri2, 1);
          //Flip the edge that crosses the segment.  After the edge is
          //  flipped, one of its endpoints is the fan vertex, and the
          //  destination of fixuptri is the fan vertex.
          lprevself(fixuptri);
        } else {                //farvertex is to the right of the segment.
          delaunayfixup(m, b, &fixuptri, 0);
          //Flip the edge that crosses the segment.  After the edge is
          //  flipped, one of its endpoints is the fan vertex, and the
          //  destination of fixuptri is the fan vertex.
          oprevself(fixuptri);
        }
        //Check for two intersecting segments.
        tspivot(fixuptri, crosssubseg);
        if (crosssubseg.m_subseg == m.m_dummysub) {
          flip(m, b, &fixuptri);    //May create inverted triangle at left.
        } else {
          //We've collided with a segment between endpoint1 and endpoint2.
          collision = 1;
          //Insert a vertex at the intersection.
          segmentintersection(m, b, &fixuptri, &crosssubseg, endpoint2);
          done = 1;
        }
      }
    }
  } while (!done);
  //Insert a subsegment to make the segment permanent.
  insertsubseg(m, b, &fixuptri, newmark);
  //If there was a collision with an interceding vertex, install another
  //  segment connecting that vertex with endpoint2.
  if (collision) {
    //Insert the remainder of the segment.
    if (!scoutsegment(m, b, &fixuptri, endpoint2, newmark)) {
      constrainededge(m, b, &fixuptri, endpoint2, newmark);
    }
  }
}

void ribi::tricpp::insertsegment(
  Mesh& m,
  const Behavior& b,
  Vertex endpoint1,
  Vertex endpoint2,
  const int newmark
)
{
  Otri searchtri1, searchtri2;
  Triangle encodedtri;
  Vertex checkvertex;
  Triangle ptr;                         //Temporary variable used by sym().
  /*
  if (b.m_verbosity > 1) {
    std::cout << "  Connecting (%.12g, %.12g) to (%.12g, %.12g).\n",
           endpoint1[0], endpoint1[1], endpoint2[0], endpoint2[1]);
  }
  */
  //Find a triangle whose origin is the segment's first endpoint.
  checkvertex = nullptr;
  encodedtri = vertex2tri(endpoint1);
  if (encodedtri != nullptr)
  {
    decode(encodedtri, searchtri1);

    checkvertex = searchtri1.GetOrigin();
    //GetOrigin(searchtri1, checkvertex);
  }
  if (checkvertex != endpoint1) {
    //Find a boundary triangle to search from.
    searchtri1.m_tri = m.m_dummytri;
    searchtri1.m_orient = 0;
    symself(searchtri1);
    //Search for the segment's first endpoint by point location.
    if (locate(m, b, endpoint1, &searchtri1) != ONVERTEX) {
      std::stringstream s;
      /*
      std::cout <<
        "Internal error in insertsegment():  Unable to locate PSLG vertex\n");
      std::cout << "  (%.12g, %.12g) in triangulation.\n",
             endpoint1[0], endpoint1[1]);
      */
      throw std::logic_error(s.str().c_str());

    }
  }
  //Remember this triangle to improve subsequent point location.
  m.m_recenttri = searchtri1;
  //otricopy(searchtri1, m.m_recenttri);

  //Scout the beginnings of a path from the first endpoint
  //  toward the second.
  if (scoutsegment(m, b, &searchtri1, endpoint2, newmark)) {
    //The segment was easily inserted.
    return;
  }
  //The first endpoint may have changed if a collision with an intervening
  //  vertex on the segment occurred.
  endpoint1 = searchtri1.GetOrigin();
  //GetOrigin(searchtri1, endpoint1);

  //Find a triangle whose origin is the segment's second endpoint.
  checkvertex = nullptr;
  encodedtri = vertex2tri(endpoint2);
  if (encodedtri != nullptr)
  {
    decode(encodedtri, searchtri2);

    checkvertex = searchtri2.GetOrigin();
    //GetOrigin(searchtri2, checkvertex);
  }
  if (checkvertex != endpoint2) {
    //Find a boundary triangle to search from.
    searchtri2.m_tri = m.m_dummytri;
    searchtri2.m_orient = 0;
    symself(searchtri2);
    //Search for the segment's second endpoint by point location.
    if (locate(m, b, endpoint2, &searchtri2) != ONVERTEX) {
      std::stringstream s;
      /*
      std::cout <<
        "Internal error in insertsegment():  Unable to locate PSLG vertex\n");
      std::cout << "  (%.12g, %.12g) in triangulation.\n",
             endpoint2[0], endpoint2[1]);
      */
      throw std::logic_error(s.str().c_str());

    }
  }
  //Remember this triangle to improve subsequent point location.
  m.m_recenttri = searchtri2;
  //otricopy(searchtri2, m.m_recenttri);

  //Scout the beginnings of a path from the second endpoint
  //  toward the first.
  if (scoutsegment(m, b, &searchtri2, endpoint1, newmark)) {
    //The segment was easily inserted.
    return;
  }
  //The second endpoint may have changed if a collision with an intervening
  //  vertex on the segment occurred.
  endpoint2 = searchtri2.GetOrigin();
  //GetOrigin(searchtri2, endpoint2);

  if (b.m_splitseg) {
    //Insert vertices to force the segment into the triangulation.
    conformingedge(m, b, endpoint1, endpoint2, newmark);
  } else {
    //Insert the segment directly into the triangulation.
    constrainededge(m, b, &searchtri1, endpoint2, newmark);
  }
}


void ribi::tricpp::markhull(
  Mesh& m,
  const Behavior& b
)
{
  Otri hulltri;
  Otri nexttri;
  Otri starttri;
  Triangle ptr;             //Temporary variable used by sym() and oprev().

  //Find a triangle handle on the hull.
  hulltri.m_tri = m.m_dummytri;
  hulltri.m_orient = 0;
  symself(hulltri);
  //Remember where we started so we know when to stop.
  starttri = hulltri;
  //otricopy(hulltri, starttri);

  //Go once counterclockwise around the convex hull.
  do
  {
    //Create a subsegment if there isn't already one here.
    insertsubseg(m, b, &hulltri, 1);
    //To find the next hull edge, go clockwise around the next vertex.
    lnextself(hulltri);
    oprev(hulltri, nexttri);
    while (nexttri.m_tri != m.m_dummytri)
    {
      hulltri = nexttri;
      //otricopy(nexttri, hulltri);
      oprev(hulltri, nexttri);
    }
  } while ( hulltri != starttri) //!otriequal(hulltri, starttri) );
}

void ribi::tricpp::formskeleton(
  Mesh& m,
  const Behavior& b,
  FILE * const polyfile,
  const std::string& polyfilename
)
{
  char inputline[g_max_inputline_size];
  Vertex endpoint1, endpoint2;
  int segmentmarkers;
  int end1, end2;
  int boundmarker;


  {
    /*
    if (!b.m_quiet) {
      std::cout << "Recovering segments in Delaunay triangulation.\n");
    }
    */
    //Read the segments from a .poly file.
    //Read number of segments and number of boundary markers.
    char * stringptr = readline(inputline, polyfile); //RJCB
    m.m_insegments = (int) strtol(stringptr, &stringptr, 0);
    stringptr = FindField(stringptr);
    if (*stringptr == '\0') {
      segmentmarkers = 0;
    } else {
      segmentmarkers = (int) strtol(stringptr, &stringptr, 0);
    }
    //If the input vertices are collinear, there is no triangulation,
    //  so don't try to insert segments.
    if (m.m_triangles.m_items == 0) {
      return;
    }

    //If segments are to be inserted, compute a mapping
    //  from vertices to triangles.
    if (m.m_insegments > 0) {
      makevertexmap(m, b);
      /*
      if (b.m_verbosity) {
        std::cout << "  Recovering PSLG segments.\n");
      }
      */
    }

    boundmarker = 0;
    //Read and insert the segments.
    for (int i = 0; i < m.m_insegments; i++) {
      stringptr = readline(inputline, polyfile);
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        s << "Error:  Segment " << (b.m_firstnumber + i) << " has no endpoints in " << polyfilename << ".\n",
        throw std::logic_error(s.str().c_str());
      }
      else
      {
        end1 = (int) strtol(stringptr, &stringptr, 0);
      }
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        s << "Error:  Segment " << (b.m_firstnumber + i)
          << " is missing its second endpoint in " << polyfilename
          << ".\n";
        throw std::logic_error(s.str().c_str());

      } else {
        end2 = (int) strtol(stringptr, &stringptr, 0);
      }
      if (segmentmarkers) {
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          boundmarker = 0;
        } else {
          boundmarker = (int) strtol(stringptr, &stringptr, 0);
        }
      }
      if (end1 < b.m_firstnumber || end1 >= b.m_firstnumber + m.m_invertices)
      {
        if (!b.m_quiet)
        {
          std::cout
            << "Warning:  Invalid first endpoint of segment "
            << (b.m_firstnumber + i) << " in "
            << polyfilename << ".\n"
          ;
        }
      } else if ((end2 < b.m_firstnumber) ||
                 (end2 >= b.m_firstnumber + m.m_invertices)) {
        if (!b.m_quiet)
        {
          std::cout
            << "Warning:  Invalid second endpoint of segment "
            << (b.m_firstnumber + i) << " in "
            << polyfilename << ".\n"
          ;
        }
      }
      else
      {
        //Find the vertices numbered `end1' and `end2'.
        endpoint1 = getvertex(m.m_vertices, b, end1);
        endpoint2 = getvertex(m.m_vertices, b, end2);
        if ((endpoint1[0] == endpoint2[0]) && (endpoint1[1] == endpoint2[1]))
        {
          if (!b.m_quiet)
          {
            std::cout << "Warning:  Endpoints of segment "
              <<(b.m_firstnumber + i) << " are coincident in "
              << polyfilename << ".\n"
            ;
          }
        }
        else
        {
          insertsegment(m, b, endpoint1, endpoint2, boundmarker);
        }
      }
    }
  }
  else
  {
    m.m_insegments = 0;
  }
  if (b.m_convex)
  {
    if (b.m_verbosity > 0)
    {
      std::cout << "  Enclosing convex hull with segments.\n";
    }
    markhull(m, b);
  }
}

void ribi::tricpp::infecthull(
  Mesh& m,
  const Behavior& b
)
{
  Otri hulltri;
  Otri nexttri;
  Otri starttri;
  Osub hullsubseg;
  Triangle **deadtriangle;
  Vertex horg, hdest;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  if (b.m_verbosity) {
    std::cout << "  Marking concavities (external triangles) for elimination.\n");
  }
  //Find a triangle handle on the hull.
  hulltri.m_tri = m.m_dummytri;
  hulltri.m_orient = 0;
  symself(hulltri);
  //Remember where we started so we know when to stop.
  starttri = hulltri;
  //otricopy(hulltri, starttri);

  //Go once counterclockwise around the convex hull.
  do {
    //Ignore triangles that are already infected.
    if (!infected(hulltri)) {
      //Is the triangle protected by a subsegment?
      tspivot(hulltri, hullsubseg);
      if (hullsubseg.m_subseg == m.m_dummysub) {
        //The triangle is not protected; infect it.
        if (!infected(hulltri)) {
          infect(hulltri);
          deadtriangle = (Triangle **) PoolAlloc(&m.m_viri);
          *deadtriangle = hulltri.m_tri;
        }
      } else {
        //The triangle is protected; set boundary markers if appropriate.
        if (mark(hullsubseg) == 0)
        {
          setmark(hullsubseg, 1);

          horg = hulltri.GetOrigin();
          //GetOrigin(hulltri, horg);

          GetDest(hulltri, hdest);
          if (vertexmark(horg) == 0)
          {
            setvertexmark(horg, 1);
          }
          if (vertexmark(hdest) == 0)
          {
            setvertexmark(hdest, 1);
          }
        }
      }
    }
    //To find the next hull edge, go clockwise around the next vertex.
    lnextself(hulltri);
    oprev(hulltri, nexttri);
    while (nexttri.m_tri != m.m_dummytri)
    {
      hulltri = nexttri;
      //otricopy(nexttri, hulltri);
      oprev(hulltri, nexttri);
    }
  }
  while (hulltri != starttri);
  //while (!otriequal(hulltri, starttri));
}


void ribi::tricpp::plague(
  Mesh& m,
  const Behavior& b
)
{
  Otri testtri;
  Otri neighbor;
  Triangle **virusloop;
  Triangle **deadtriangle;
  Osub neighborsubseg;
  Vertex testvertex;
  Vertex norg, ndest;
  Vertex deadorg, deaddest, deadapex;
  int killorg;
  Triangle ptr;             //Temporary variable used by sym() and onext().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  if (b.m_verbosity) {
    std::cout << "  Marking neighbors of marked triangles.\n");
  }
  //Loop through all the infected triangles, spreading the virus to
  //  their neighbors, then to their neighbors' neighbors.
  TraversalInit(&m.m_viri);
  virusloop = (Triangle **) Traverse(&m.m_viri);
  while (virusloop != nullptr) {
    testtri.m_tri = *virusloop;
    //A triangle is marked as infected by messing with one of its pointers
    //  to subsegments, setting it to an illegal value.  Hence, we have to
    //  temporarily uninfect this triangle so that we can examine its
    //  adjacent subsegments.
    uninfect(testtri);
    /*
    if (b.m_verbosity > 2) {
      //Assign the triangle an orientation for convenience in
      //  checking its vertices.
      testtri.m_orient = 0;
      GetOrigin(testtri, deadorg);

      GetDest(testtri, deaddest);

      GetApex(testtri, deadapex);
      std::cout << "    Checking (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
             deadorg[0], deadorg[1], deaddest[0], deaddest[1],
             deadapex[0], deadapex[1]);
    }
    */
    //Check each of the triangle's three neighbors.
    for (testtri.m_orient = 0; testtri.m_orient < 3; testtri.m_orient++) {
      //Find the neighbor.
      sym(testtri, neighbor);
      //Check for a subsegment between the triangle and its neighbor.
      tspivot(testtri, neighborsubseg);
      //Check if the neighbor is nonexistent or already infected.
      if ((neighbor.m_tri == m.m_dummytri) || infected(neighbor)) {
        if (neighborsubseg.m_subseg != m.m_dummysub) {
          //There is a subsegment separating the triangle from its
          //  neighbor, but both triangles are dying, so the subsegment
          //  dies too.
          subsegdealloc(m, neighborsubseg.m_subseg);
          if (neighbor.m_tri != m.m_dummytri) {
            //Make sure the subsegment doesn't get deallocated again
            //  later when the infected neighbor is visited.
            uninfect(neighbor);
            tsdissolve(neighbor);
            infect(neighbor);
          }
        }
      }
      else
      {
        //The neighbor exists and is not infected.
        if (neighborsubseg.m_subseg == m.m_dummysub) {
          //There is no subsegment protecting the neighbor, so
          //  the neighbor becomes infected.
          /*
          if (b.m_verbosity > 2)
          {
            GetOrigin(neighbor, deadorg);
            GetDest(neighbor, deaddest);
            GetApex(neighbor, deadapex);
            std::cout <<
              "    Marking (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
                   deadorg[0], deadorg[1], deaddest[0], deaddest[1],
                   deadapex[0], deadapex[1];
          }
          */
          infect(neighbor);
          //Ensure that the neighbor's neighbors will be infected.
          deadtriangle = (Triangle **) PoolAlloc(&m.m_viri);
          *deadtriangle = neighbor.m_tri;
        } else {               //The neighbor is protected by a subsegment.
          //Remove this triangle from the subsegment.
          stdissolve(neighborsubseg);
          //The subsegment becomes a boundary.  Set markers accordingly.
          if (mark(neighborsubseg) == 0)
          {
            setmark(neighborsubseg, 1);
          }

          norg = neighbor.GetOrigin();
          //GetOrigin(neighbor, norg);

          ndest = neighbor.GetDest();
          //GetDest(neighbor, ndest);

          if (vertexmark(norg) == 0)
          {
            setvertexmark(norg, 1);
          }
          if (vertexmark(ndest) == 0)
          {
            setvertexmark(ndest, 1);
          }
        }
      }
    }
    //Remark the triangle as infected, so it doesn't get added to the
    //  virus pool again.
    infect(testtri);
    virusloop = (Triangle **) Traverse(&m.m_viri);
  }

  if (b.m_verbosity) {
    std::cout << "  Deleting marked triangles.\n");
  }

  TraversalInit(&m.m_viri);
  virusloop = (Triangle **) Traverse(&m.m_viri);
  while (virusloop != nullptr) {
    testtri.m_tri = *virusloop;

    //Check each of the three corners of the triangle for elimination.
    //  This is done by walking around each vertex, checking if it is
    //  still connected to at least one live triangle.
    for (testtri.m_orient = 0; testtri.m_orient < 3; testtri.m_orient++)
    {
      testvertex = testtri.GetOrigin();
      //GetOrigin(testtri, testvertex);

      //Check if the vertex has already been tested.
      if (testvertex != nullptr)
      {
        killorg = 1;
        //Mark the corner of the triangle as having been tested.

        testtri.SetOrigin(nullptr);
        //SetOrigin(testtri, NULL);

        //Walk counterclockwise about the vertex.
        onext(testtri, neighbor);
        //Stop upon reaching a boundary or the starting triangle.
        while (neighbor.m_tri != m.m_dummytri && neighbor != testtri)
        //while (neighbor.m_tri != m.m_dummytri && !otriequal(neighbor, testtri))
        {
          if (infected(neighbor))
          {
            //Mark the corner of this triangle as having been tested.
            neighbor.SetOrigin(nullptr);
            //SetOrigin(neighbor, NULL);
          }
          else
          {
            //A live triangle.  The vertex survives.
            killorg = 0;
          }
          //Walk counterclockwise about the vertex.
          onextself(neighbor);
        }
        //If we reached a boundary, we must walk clockwise as well.
        if (neighbor.m_tri == m.m_dummytri) {
          //Walk clockwise about the vertex.
          oprev(testtri, neighbor);
          //Stop upon reaching a boundary.
          while (neighbor.m_tri != m.m_dummytri)
          {
            if (infected(neighbor)) {
              //Mark the corner of this triangle as having been tested.
              neighbor.SetOrigin(nullptr);
              //SetOrigin(neighbor, NULL);
            } else {
              //A live triangle.  The vertex survives.
              killorg = 0;
            }
            //Walk clockwise about the vertex.
            oprevself(neighbor);
          }
        }
        if (killorg) {
          if (b.m_verbosity > 1) {
            std::cout << "    Deleting vertex (%.12g, %.12g)\n",
                   testvertex[0], testvertex[1]);
          }
          setvertextype(testvertex, VertexType::UNDEADVERTEX);
          m.m_undeads++;
        }
      }
    }

    //Record changes in the number of boundary edges, and disconnect
    //  dead triangles from their neighbors.
    for (testtri.m_orient = 0; testtri.m_orient < 3; testtri.m_orient++) {
      sym(testtri, neighbor);
      if (neighbor.m_tri == m.m_dummytri) {
        //There is no neighboring triangle on this edge, so this edge
        //  is a boundary edge.  This triangle is being deleted, so this
        //  boundary edge is deleted.
        m.m_hullsize--;
      } else {
        //Disconnect the triangle from its neighbor.
        dissolve(neighbor);
        //There is a neighboring triangle on this edge, so this edge
        //  becomes a boundary edge when this triangle is deleted.
        m.m_hullsize++;
      }
    }
    //Return the dead triangle to the pool of triangles.
    triangledealloc(m, testtri.m_tri);
    virusloop = (Triangle **) Traverse(&m.m_viri);
  }
  //Empty the virus pool.
  PoolRestart(&m.m_viri);
}

void ribi::tricpp::regionplague(
  Mesh& m,
  const Behavior& b,
  const double attribute,
  const double area
)
{
  Otri testtri;
  Otri neighbor;
  Triangle **virusloop;
  Triangle **regiontri;
  Osub neighborsubseg;
  Vertex regionorg, regiondest, regionapex;
  Triangle ptr;             //Temporary variable used by sym() and onext().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  //Loop through all the infected triangles, spreading the attribute
  //  and/or area constraint to their neighbors, then to their neighbors'
  //  neighbors.
  TraversalInit(&m.m_viri);
  virusloop = (Triangle **) Traverse(&m.m_viri);
  while (virusloop != nullptr)
  {
    testtri.m_tri = *virusloop;
    //A triangle is marked as infected by messing with one of its pointers
    //  to subsegments, setting it to an illegal value.  Hence, we have to
    //  temporarily uninfect this triangle so that we can examine its
    //  adjacent subsegments.
    uninfect(testtri);
    if (b.m_regionattrib) {
      //Set an attribute.
      setelemattribute(testtri, m.m_eextras, attribute);
    }
    if (b.m_vararea) {
      //Set an area constraint.
      setareabound(testtri, area);
    }
    /*
    if (b.m_verbosity > 2) {
      //Assign the triangle an orientation for convenience in
      //  checking its vertices.
      testtri.m_orient = 0;
      GetOrigin(testtri, regionorg);
      dest(testtri, regiondest);
      apex(testtri, regionapex);
      std::cout << "    Checking (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
             regionorg[0], regionorg[1], regiondest[0], regiondest[1],
             regionapex[0], regionapex[1]);
    }
    */
    //Check each of the triangle's three neighbors.
    for (testtri.m_orient = 0; testtri.m_orient < 3; testtri.m_orient++) {
      //Find the neighbor.
      sym(testtri, neighbor);
      //Check for a subsegment between the triangle and its neighbor.
      tspivot(testtri, neighborsubseg);
      //Make sure the neighbor exists, is not already infected, and
      //  isn't protected by a subsegment.
      if ((neighbor.m_tri != m.m_dummytri) && !infected(neighbor)
          && (neighborsubseg.m_subseg == m.m_dummysub))
      {
        /*
        if (b.m_verbosity > 2)
        {
          GetOrigin(neighbor, regionorg);

          regiondest = neighbor.GetDest();
          //GetDest(neighbor, regiondest);

          regionapex = neighbor.GetApex();
          //GetApex(neighbor, regionapex);

          std::cout << "    Marking (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n",
                 regionorg[0], regionorg[1], regiondest[0], regiondest[1],
                 regionapex[0], regionapex[1]);
        }
        */
        //Infect the neighbor.
        infect(neighbor);
        //Ensure that the neighbor's neighbors will be infected.
        regiontri = (Triangle **) PoolAlloc(&m.m_viri);
        *regiontri = neighbor.m_tri;
      }
    }
    //Remark the triangle as infected, so it doesn't get added to the
    //  virus pool again.
    infect(testtri);
    virusloop = (Triangle **) Traverse(&m.m_viri);
  }

  //Uninfect all triangles.
  TraversalInit(&m.m_viri);
  virusloop = (Triangle **) Traverse(&m.m_viri);
  while (virusloop != nullptr) {
    testtri.m_tri = *virusloop;
    uninfect(testtri);
    virusloop = (Triangle **) Traverse(&m.m_viri);
  }
  //Empty the virus pool.
  PoolRestart(m.m_viri);
}

void ribi::tricpp::carveholes(
  Mesh& m,
  const Behavior& b,
  double * const holelist,
  const int holes,
  double * const regionlist,
  const int regions
)
{
  Otri searchtri;
  Otri triangleloop;
  Otri *regiontris;
  Triangle **holetri;
  Triangle **regiontri;
  Vertex searchorg, searchdest;
  LocateResult intersect;

  Triangle ptr;                         //Temporary variable used by sym().
  /*
  if (!(b.m_quiet || (b.m_noholes && b.m_convex))) {
    std::cout << "Removing unwanted triangles.\n");
    if (b.m_verbosity && (holes > 0)) {
      std::cout << "  Marking holes for elimination.\n");
    }
  }
  */
  if (regions > 0)
  {
    //Allocate storage for the triangles in which region points fall.
    regiontris = (struct Otri *) TriMalloc(regions *
                                           (int) sizeof(struct Otri));
  } else {
    regiontris = (struct Otri *) NULL;
  }

  if (((holes > 0) && !b.m_noholes) || !b.m_convex || (regions > 0)) {
    //Initialize a pool of viri to be used for holes, concavities,
    //  regional attributes, and/or regional area constraints.
    PoolInit(&m.m_viri, sizeof(Triangle *), VIRUSPERBLOCK, VIRUSPERBLOCK, 0);
  }

  if (!b.m_convex) {
    //Mark as infected any unprotected triangles on the boundary.
    //  This is one way by which concavities are created.
    infecthull(m, b);
  }

  if ((holes > 0) && !b.m_noholes) {
    //Infect each triangle in which a hole lies.
    for (int i = 0; i < 2 * holes; i += 2) {
      //Ignore holes that aren't within the bounds of the mesh.
      if ((holelist[i] >= m.m_xmin) && (holelist[i] <= m.m_xmax)
          && (holelist[i + 1] >= m.m_ymin) && (holelist[i + 1] <= m.m_ymax)) {
        //Start searching from some triangle on the outer boundary.
        searchtri.m_tri = m.m_dummytri;
        searchtri.m_orient = 0;
        symself(searchtri);
        //Ensure that the hole is to the left of this boundary edge;
        //  otherwise, locate() will falsely report that the hole
        //  falls within the starting triangle.

        searchorg = searchtri.GetOrigin();
        //GetOrigin(searchtri, searchorg);

        searchdest = searchtri.GetDest();
        //GetDest(searchtri, searchdest);

        if (counterclockwise(m.m_counterclockcount, b.m_noexact, searchorg, searchdest, &holelist[i]) >
            0.0) {
          //Find a triangle that contains the hole.
          intersect = locate(m, b, &holelist[i], &searchtri);
          if ((intersect != OUTSIDE) && (!infected(searchtri))) {
            //Infect the triangle.  This is done by marking the triangle
            //  as infected and including the triangle in the virus pool.
            infect(searchtri);
            holetri = (Triangle **) PoolAlloc(&m.m_viri);
            *holetri = searchtri.m_tri;
          }
        }
      }
    }
  }

  //Now, we have to find all the regions BEFORE we carve the holes, because
  //  locate() won't work when the triangulation is no longer convex.
  //  (Incidentally, this is the reason why regional attributes and area
  //  constraints can't be used when refining a preexisting mesh, which
  //  might not be convex; they can only be used with a freshly
  //  triangulated PSLG.)
  if (regions > 0) {
    //Find the starting triangle for each region.
    for (int i = 0; i < regions; i++) {
      regiontris[i].m_tri = m.m_dummytri;
      //Ignore region points that aren't within the bounds of the mesh.
      if ((regionlist[4 * i] >= m.m_xmin) && (regionlist[4 * i] <= m.m_xmax) &&
          (regionlist[4 * i + 1] >= m.m_ymin) &&
          (regionlist[4 * i + 1] <= m.m_ymax))
      {
        //Start searching from some triangle on the outer boundary.
        searchtri.m_tri = m.m_dummytri;
        searchtri.m_orient = 0;
        symself(searchtri);
        //Ensure that the region point is to the left of this boundary
        //  edge; otherwise, locate() will falsely report that the
        //  region point falls within the starting triangle.
        searchorg = searchtri.GetOrigin();
        //org(searchtri, searchorg);

        searchdest = searchtri.GetDest();
        //dest(searchtri, searchdest);

        if (counterclockwise(m.m_counterclockcount, b.m_noexact, searchorg, searchdest, &regionlist[4 * i]) >
            0.0)
        {
          //Find a triangle that contains the region point.
          intersect = locate(m, b, &regionlist[4 * i], &searchtri);
          if (intersect != OUTSIDE && !infected(searchtri)))
          {
            //Record the triangle for processing after the
            //  holes have been carved.
            regiontris[i] = searchtri;
            //otricopy(searchtri, regiontris[i]);
          }
        }
      }
    }
  }

  if (m.m_viri.m_items > 0) {
    //Carve the holes and concavities.
    plague(m, b);
  }
  //The virus pool should be empty now.

  if (regions > 0)
  {
    /*
    if (!b.m_quiet) {
      if (b.m_regionattrib) {

        if (b.m_vararea) {
          std::cout << "Spreading regional attributes and area constraints.\n");
        } else {
          std::cout << "Spreading regional attributes.\n");
        }
      } else { 
        std::cout << "Spreading regional area constraints.\n");
      }
    }
    */
    if (b.m_regionattrib && !b.m_do_refine) {
      //Assign every triangle a regional attribute of zero.
      TraversalInit(&m.m_triangles);
      triangleloop.m_orient = 0;
      triangleloop.m_tri = triangletraverse(m);
      while (triangleloop.m_tri != (Triangle *) NULL) {
        setelemattribute(triangleloop, m.m_eextras, 0.0);
        triangleloop.m_tri = triangletraverse(m);
      }
    }
    for (int i = 0; i < regions; i++) {
      if (regiontris[i].m_tri != m.m_dummytri) {
        //Make sure the triangle under consideration still exists.
        //  It may have been eaten by the virus.
        if (!deadtri(regiontris[i].m_tri)) {
          //Put one triangle in the virus pool.
          infect(regiontris[i]);
          regiontri = (Triangle **) PoolAlloc(&m.m_viri);
          *regiontri = regiontris[i].m_tri;
          //Apply one region's attribute and/or area constraint.
          regionplague(m, b, regionlist[4 * i + 2], regionlist[4 * i + 3]);
          //The virus pool should be empty now.
        }
      }
    }
    if (b.m_regionattrib && !b.m_do_refine) {
      //Note the fact that each triangle has an additional attribute.
      m.m_eextras++;
    }
  }

  //Free up memory.
  if (((holes > 0) && !b.m_noholes) || !b.m_convex || (regions > 0)) {
    PoolDeinit(&m.m_viri);
  }
  if (regions > 0) {
    delete regiontris;
    regiontris = nullptr;
  }
}

void ribi::tricpp::tallyencs(
  Mesh& m,
  const Behavior& b
)
{
  Osub subsegloop;
  //int dummy;

  TraversalInit(&m.m_subsegs);
  subsegloop.m_subseg_orient = 0;
  subsegloop.m_subseg = subsegtraverse(m);
  while (subsegloop.m_subseg != (SubSeg *) NULL) {
    //If the segment is encroached, add it to the list.
    checkseg4encroach(m, b, &subsegloop);
    subsegloop.m_subseg = subsegtraverse(m);
  }
}

void ribi::tricpp::splitencsegs(
  Mesh& m,
  const Behavior& b,
  const int triflaws
)
{
  Otri enctri;
  Otri testtri;
  Osub testsh;
  Osub currentenc;
  BadSubSeg *encloop;
  Vertex eorg, edest, eapex;
  Vertex newvertex;
  InsertVertexResult success;
  double segmentlength, nearestpoweroftwo;
  double split;
  double multiplier, divisor;
  int acuteorg, acuteorg2, acutedest, acutedest2;

  Triangle ptr;                     //Temporary variable used by stpivot().
  SubSeg sptr;                        //Temporary variable used by snext().

  //Note that steinerleft == -1 if an unlimited number
  //  of Steiner points is allowed.
  while ((m.m_badsubsegs.m_items > 0) && (m.m_steinerleft != 0))
  {
    TraversalInit(&m.m_badsubsegs);
    encloop = badsubsegtraverse(m);
    while ((encloop != nullptr) && (m.m_steinerleft != 0))
    {
      sdecode(encloop->m_encsubseg, currentenc);

      eorg = currentenc.GetOrigin();
      //GetOrigin(currentenc, eorg);

      edest = currentenc.GetDest();
      //GetDest(currentenc, edest);

      //Make sure that this segment is still the same segment it was
      //  when it was determined to be encroached.  If the segment was
      //  enqueued multiple times (because several newly inserted
      //  vertices encroached it), it may have already been split.
      if (!deadsubseg(currentenc.m_subseg) &&
          (eorg == encloop->m_subsegorg) && (edest == encloop->m_subsegdest)) {
        //To decide where to split a segment, we need to know if the
        //  segment shares an endpoint with an adjacent segment.
        //  The concern is that, if we simply split every encroached
        //  segment in its center, two adjacent segments with a small
        //  angle between them might lead to an infinite loop; each
        //  vertex added to split one segment will encroach upon the
        //  other segment, which must then be split with a vertex that
        //  will encroach upon the first segment, and so on forever.
        //To avoid this, imagine a set of concentric circles, whose
        //  radii are powers of two, about each segment endpoint.
        //  These concentric circles determine where the segment is
        //  split.  (If both endpoints are shared with adjacent
        //  segments, split the segment in the middle, and apply the
        //  concentric circles for later splittings.)

        //Is the origin shared with another segment?
        stpivot(currentenc, enctri);
        lnext(enctri, testtri);
        tspivot(testtri, testsh);
        acuteorg = testsh.m_subseg != m.m_dummysub;
        //Is the destination shared with another segment?
        lnextself(testtri);
        tspivot(testtri, testsh);
        acutedest = testsh.m_subseg != m.m_dummysub;

        //If we're using Chew's algorithm (rather than Ruppert's)
        //  to define encroachment, delete free vertices from the
        //  subsegment's diametral circle.
        if (!b.m_conformdel && !acuteorg && !acutedest)
        {
          eapex = enctri.GetApex();
          //GetApex(enctri, eapex);

          while ((vertextype(eapex) == VertexType::FREEVERTEX) &&
                 ((eorg[0] - eapex[0]) * (edest[0] - eapex[0]) +
                  (eorg[1] - eapex[1]) * (edest[1] - eapex[1]) < 0.0)) {
            deletevertex(m, b, &testtri);
            stpivot(currentenc, enctri);

            eapex = enctri.GetApex();
            //GetApex(enctri, eapex);

            lprev(enctri, testtri);
          }
        }

        //Now, check the other side of the segment, if there's a triangle
        //  there.
        sym(enctri, testtri);
        if (testtri.m_tri != m.m_dummytri) {
          //Is the destination shared with another segment?
          lnextself(testtri);
          tspivot(testtri, testsh);
          acutedest2 = testsh.m_subseg != m.m_dummysub;
          acutedest = acutedest || acutedest2;
          //Is the origin shared with another segment?
          lnextself(testtri);
          tspivot(testtri, testsh);
          acuteorg2 = testsh.m_subseg != m.m_dummysub;
          acuteorg = acuteorg || acuteorg2;

          //Delete free vertices from the subsegment's diametral circle.
          if (!b.m_conformdel && !acuteorg2 && !acutedest2)
          {
            eapex = testtri.GetOrigin();
            //GetOrigin(testtri, eapex);

            while ((vertextype(eapex) == VertexType::FREEVERTEX) &&
                   ((eorg[0] - eapex[0]) * (edest[0] - eapex[0]) +
                    (eorg[1] - eapex[1]) * (edest[1] - eapex[1]) < 0.0)) {
              deletevertex(m, b, &testtri);
              sym(enctri, testtri);

              eapex = testtri.GetApex();
              //GetApex(testtri, eapex);

              lprevself(testtri);
            }
          }
        }

        //Use the concentric circles if exactly one endpoint is shared
        //  with another adjacent segment.
        if (acuteorg || acutedest) {
          segmentlength = sqrt((edest[0] - eorg[0]) * (edest[0] - eorg[0]) +
                               (edest[1] - eorg[1]) * (edest[1] - eorg[1]));
          //Find the power of two that most evenly splits the segment.
          //  The worst case is a 2:1 ratio between subsegment lengths.
          nearestpoweroftwo = 1.0;
          while (segmentlength > 3.0 * nearestpoweroftwo) {
            nearestpoweroftwo *= 2.0;
          }
          while (segmentlength < 1.5 * nearestpoweroftwo) {
            nearestpoweroftwo *= 0.5;
          }
          //Where do we split the segment?
          split = nearestpoweroftwo / segmentlength;
          if (acutedest) {
            split = 1.0 - split;
          }
        } else {
          //If we're not worried about adjacent segments, split
          //  this segment in the middle.
          split = 0.5;
        }

        //Create the new vertex.
        newvertex = (Vertex) PoolAlloc(&m.m_vertices);
        //Interpolate its coordinate and attributes.
        for (int i = 0; i < 2 + m.m_nextras; i++) {
          newvertex[i] = eorg[i] + split * (edest[i] - eorg[i]);
        }

        if (!b.m_noexact) {
          //Roundoff in the above calculation may yield a `newvertex'
          //  that is not precisely collinear with `eorg' and `edest'.
          //  Improve collinearity by one step of iterative refinement.
          multiplier = counterclockwise(m.m_counterclockcount, b.m_noexact, eorg, edest, newvertex);
          divisor = ((eorg[0] - edest[0]) * (eorg[0] - edest[0]) +
                     (eorg[1] - edest[1]) * (eorg[1] - edest[1]));
          if ((multiplier != 0.0) && (divisor != 0.0)) {
            multiplier = multiplier / divisor;
            //Watch out for NANs.
            if (multiplier == multiplier) {
              newvertex[0] += multiplier * (edest[1] - eorg[1]);
              newvertex[1] += multiplier * (eorg[0] - edest[0]);
            }
          }
        }

        newvertex.SetMark(currentenc.GetMark());
        //setvertexmark(newvertex, mark(currentenc));

        newvertex.SetVertexType(VertexType::SEGMENTVERTEX);
        //setvertextype(newvertex, VertexType::SEGMENTVERTEX);
        /*
        if (b.m_verbosity > 1)
        {
          std::cout <<
            "  Splitting subsegment (%.12g, %.12g) (%.12g, %.12g) at (%.12g, %.12g).\n",
            eorg[0], eorg[1], edest[0], edest[1],
            newvertex[0], newvertex[1]
          );
        }
        //Check whether the new vertex lies on an endpoint.
        if (((newvertex[0] == eorg[0]) && (newvertex[1] == eorg[1])) ||
            ((newvertex[0] == edest[0]) && (newvertex[1] == edest[1]))) {
          std::stringstream s;
          s
            << "Error:  Ran out of precision at ("
            << newvertex[0] << ", "
            << newvertex[1] << ").\n"
            << "I attempted to split a segment to a smaller size than\n"
            << "  can be accommodated by the finite precision of\n"
            << "  floating point arithmetic.\n"
          ;
          throw std::logic_error(s.str().c_str());
        }
        */
        //Insert the splitting vertex.  This should always succeed.
        success = insertvertex(m, b, newvertex, &enctri, &currentenc,
                               1, triflaws);
        assert(!(success != SUCCESSFULVERTEX && success != ENCROACHINGVERTEX));
        /*
        if ((success != SUCCESSFULVERTEX) && (success != ENCROACHINGVERTEX))
        {
          std::stringstream s;
          std::cout << "Internal error in splitencsegs():\n");
          std::cout << "  Failure to split a segment.\n");
          throw std::logic_error(s.str().c_str());

        }
        */
        if (m.m_steinerleft > 0)
        {
          m.m_steinerleft--;
        }
        //Check the two new subsegments to see if they're encroached.
        checkseg4encroach(m, b, &currentenc);
        snextself(currentenc);
        checkseg4encroach(m, b, &currentenc);
      }

      badsubsegdealloc(m, encloop);
      encloop = badsubsegtraverse(m);
    }
  }
}

void ribi::tricpp::tallyfaces(
  Mesh& m,
  const Behavior& b
)
{
  Otri triangleloop;

  TraversalInit(&m.m_triangles);
  triangleloop.m_orient = 0;
  triangleloop.m_tri = triangletraverse(m);
  while (triangleloop.m_tri != (Triangle *) NULL) {
    //If the triangle is bad, enqueue it.
    testtriangle(m, b, &triangleloop);
    triangleloop.m_tri = triangletraverse(m);
  }
}

void ribi::tricpp::splittriangle(
  Mesh& m,
  const Behavior& b,
  const BadTriang * const badtri
)
{
  //Otri badotri;
  //Vertex borg, bdest, bapex;
  Vertex newvertex;
  double xi, eta;
  InsertVertexResult success;
  int errorflag;

  Otri badotri = badtri->m_poortri;
  //decode(badtri->m_poortri, badotri);

  const auto borg = badotri.GetOrigin();
  //org(badotri, borg);
  const auto bdest = badotri.GetDest();
  //dest(badotri, bdest);
  const auto bapex = badotri.GetApex();
  //apex(badotri, bapex);
  //Make sure that this triangle is still the same triangle it was
  //  when it was tested and determined to be of bad quality.
  //  Subsequent transformations may have made it a different triangle.
  /*
  if (!deadtri(badotri.m_tri) && (borg == badtri->m_triangorg) &&
      (bdest == badtri->m_triangdest) && (bapex == badtri->m_triangapex))
    {
    if (b.m_verbosity > 1) {
      std::cout << "  Splitting this triangle at its circumcenter:\n");
      std::cout << "    (%.12g, %.12g) (%.12g, %.12g) (%.12g, %.12g)\n", borg[0],
             borg[1], bdest[0], bdest[1], bapex[0], bapex[1]);
    }
  */
  {
  //errorflag = 0;
  //Create a new vertex at the triangle's circumcenter.
  //newvertex = (Vertex) PoolAlloc(&m.m_vertices);
  Vertex newvertex;
  findcircumcenter(m, b, borg, bdest, bapex, newvertex, &xi, &eta, 1);

  //Check whether the new vertex lies on a triangle vertex.
  assert(!((newvertex[0] == borg[0]) && (newvertex[1] == borg[1])) ||
      ((newvertex[0] == bdest[0]) && (newvertex[1] == bdest[1])) ||
      ((newvertex[0] == bapex[0]) && (newvertex[1] == bapex[1]))
  );
  /*

  if (((newvertex[0] == borg[0]) && (newvertex[1] == borg[1])) ||
      ((newvertex[0] == bdest[0]) && (newvertex[1] == bdest[1])) ||
      ((newvertex[0] == bapex[0]) && (newvertex[1] == bapex[1])))
  {
    if (!b.m_quiet)
    {
      std::cout <<
           "Warning:  New vertex (%.12g, %.12g) falls on existing vertex.\n",
             newvertex[0], newvertex[1]);
      errorflag = 1;
    }
    vertexdealloc(m, newvertex);
  }
  else
  */
  {
    for (int i = 2; i < 2 + m.m_nextras; i++)
    {
      //Interpolate the vertex attributes at the circumcenter.
      newvertex[i] = borg[i] + xi * (bdest[i] - borg[i])
                            + eta * (bapex[i] - borg[i]);
    }
    //The new vertex must be in the interior, and therefore is a
    //  free vertex with a marker of zero.
    newvertex.SetMark(0);
    //setvertexmark(newvertex, 0);
    newvertex.SetVertexType(VertexType::FREEVERTEX);
    //setvertextype(newvertex, VertexType::FREEVERTEX);

    //Ensure that the handle `badotri' does not represent the longest
    //  edge of the triangle.  This ensures that the circumcenter must
    //  fall to the left of this edge, so point location will work.
    //  (If the angle org-apex-dest exceeds 90 degrees, then the
    //  circumcenter lies outside the org-dest edge, and eta is
    //  negative.  Roundoff error might prevent eta from being
    //  negative when it should be, so I test eta against xi.)
    if (eta < xi)
    {
      lprevself(badotri);
    }

    //Insert the circumcenter, searching from the edge of the triangle,
    //  and maintain the Delaunay property of the triangulation.
    success = insertvertex(m, b, newvertex, &badotri, nullptr,
                           1, 1);
    if (success == SUCCESSFULVERTEX)
    {
      if (m.m_steinerleft > 0) {
        m.m_steinerleft--;
      }
    }
    else if (success == ENCROACHINGVERTEX)
    {
      //If the newly inserted vertex encroaches upon a subsegment,
      //  delete the new vertex.
      undovertex(m, b);
      /*
      if (b.m_verbosity > 1) {
        std::cout << "  Rejecting (%.12g, %.12g).\n", newvertex[0], newvertex[1]);
      }
      */
      //vertexdealloc(m, newvertex);
      m.KillVertex(newvertex);
    }
    else if (success == VIOLATINGVERTEX)
    {
      //Failed to insert the new vertex, but some subsegment was
      //  marked as being encroached.
      //vertexdealloc(m, newvertex);
      m.KillVertex(newvertex);
    }
    else
    {                                 //success == DUPLICATEVERTEX
      //Couldn't insert the new vertex because a vertex is already there.
      /*
      if (!b.m_quiet) {
        std::cout <<
          "Warning:  New vertex (%.12g, %.12g) falls on existing vertex.\n",
               newvertex[0], newvertex[1]);
        errorflag = 1;
      }
      vertexdealloc(m, newvertex);
      */
      m.KillVertex(newvertex);
    }

  assert(!errorflag);
  /*
  if (errorflag)
  {
    std::stringstream s;

    if (b.m_verbosity)
    {
      s
        << "  The new vertex is at the circumcenter of triangle\n"
        << "    (" << borg[0] << ", " << borg[1] << ") ("
        << bdest[0] << ", " << bdest[1] << ") (" << bapex[0] << ", " << bapex[1] << ")\n"
      ;
    }
    s
      << "This probably means that I am trying to refine triangles\n"
      << "  to a smaller size than can be accommodated by the finite\n"
      << "  precision of floating point arithmetic.  (You can be\n"
      << "  sure of this if I fail to terminate.)\n"
    ;
    std::cout << s << std::endl;
  }
  */
}

void ribi::tricpp::enforcequality(
  Mesh& m,
  const Behavior& b
)
{
  struct BadTriang *badtri;


  if (!b.m_quiet) {
    std::cout << "Adding Steiner points to enforce quality.\n");
  }
  //Initialize the pool of encroached subsegments.
  PoolInit(&m.m_badsubsegs, sizeof(struct BadSubSeg), BADSUBSEGPERBLOCK,
           BADSUBSEGPERBLOCK, 0);
  if (b.m_verbosity) {
    std::cout << "  Looking for encroached subsegments.\n");
  }
  //Test all segments to see if they're encroached.
  tallyencs(m, b);
  if (b.m_verbosity && (m.m_badsubsegs.m_items > 0)) {
    std::cout << "  Splitting encroached subsegments.\n");
  }
  //Fix encroached subsegments without noting bad triangles.
  splitencsegs(m, b, 0);
  //At this point, if we haven't run out of Steiner points, the
  //  triangulation should be (conforming) Delaunay.

  //Next, we worry about enforcing triangle quality.
  if ((b.m_minangle > 0.0) || b.m_vararea || b.m_fixedarea || b.m_usertest) {
    //Initialize the pool of bad triangles.
    PoolInit(&m.m_badtriangles, sizeof(struct BadTriang), g_bad_triangles_per_block,
             g_bad_triangles_per_block, 0);
    //Initialize the queues of bad triangles.
    for (int i = 0; i < 4096; i++) {
      m.m_queuefront[i] = (struct BadTriang *) NULL;
    }
    m.m_firstnonemptyq = -1;
    //Test all triangles to see if they're bad.
    tallyfaces(m, b);
    //Initialize the pool of recently flipped triangles.
    PoolInit(&m.m_flipstackers, sizeof(struct FlipStacker), FLIPSTACKERPERBLOCK,
             FLIPSTACKERPERBLOCK, 0);
    m.m_checkquality = 1;
    if (b.m_verbosity) {
      std::cout << "  Splitting bad triangles.\n");
    }
    while ((m.m_badtriangles.m_items > 0) && (m.m_steinerleft != 0)) {
      //Fix one bad triangle by inserting a vertex at its circumcenter.
      badtri = dequeuebadtriang(m);
      splittriangle(m, b, badtri);
      if (m.m_badsubsegs.m_items > 0) {
        //Put bad triangle back in queue for another try later.
        enqueuebadtriang(m, b, badtri);
        //Fix any encroached subsegments that resulted.
        //  Record any new bad triangles that result.
        splitencsegs(m, b, 1);
      } else {
        //Return the bad triangle to the pool.
        PoolDealloc(&m.m_badtriangles, (void *) badtri);
      }
    }
  }
  //At this point, if the "-D" switch was selected and we haven't run out
  //  of Steiner points, the triangulation should be (conforming) Delaunay
  //  and have no low-quality triangles.

  //Might we have run out of Steiner points too soon?
  if (!b.m_quiet && b.m_conformdel && (m.m_badsubsegs.m_items > 0) &&
      (m.m_steinerleft == 0)) {
    std::cout << "\nWarning:  I ran out of Steiner points, but the mesh has\n");
    if (m.m_badsubsegs.m_items == 1) {
      std::cout << "  one encroached subsegment, and therefore might not be truly\n"
             );
    } else {
      std::cout << "  %ld encroached subsegments, and therefore might not be truly\n"
             , m.m_badsubsegs.m_items);
    }
    std::cout << "  Delaunay.  If the Delaunay property is important to you,\n");
    std::cout << "  try increasing the number of Steiner points (controlled by\n");
    std::cout << "  the -S switch) slightly and try again.\n\n");
  }
}



void ribi::tricpp::highorder(
  Mesh& m,
  const Behavior& b
)
{
  Otri triangleloop, trisym;
  Osub checkmark;
  Vertex newvertex;
  Vertex torg, tdest;

  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  if (!b.m_quiet) {
    std::cout << "Adding vertices for second-order triangles.\n");
  }
  //The following line ensures that dead items in the pool of nodes
  //  cannot be allocated for the extra nodes associated with high
  //  order elements.  This ensures that the primary nodes (at the
  //  corners of elements) will occur earlier in the output files, and
  //  have lower indices, than the extra nodes.
  m.m_vertices.m_deaditemstack = nullptr; //(void *) NULL;

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  //To loop over the set of edges, loop over all triangles, and look at
  //  the three edges of each triangle.  If there isn't another triangle
  //  adjacent to the edge, operate on the edge.  If there is another
  //  adjacent triangle, operate on the edge only if the current triangle
  //  has a smaller pointer than its neighbor.  This way, each edge is
  //  considered only once.
  while (triangleloop.m_tri != (Triangle *) NULL) {
    for (triangleloop.m_orient = 0; triangleloop.m_orient < 3;
         triangleloop.m_orient++) {
      sym(triangleloop, trisym);
      if ((triangleloop.m_tri < trisym.m_tri) || (trisym.m_tri == m.m_dummytri))
      {
        torg = triangleloop.GetOrigin();
        //GetOrigin(triangleloop, torg);

        tdest = triangleloop.GetDest();
        //GetDest(triangleloop, tdest);

        //Create a new node in the middle of the edge.  Interpolate
        //  its attributes.
        newvertex = (Vertex) PoolAlloc(&m.m_vertices);
        for (int i = 0; i < 2 + m.m_nextras; i++) {
          newvertex[i] = 0.5 * (torg[i] + tdest[i]);
        }
        //Set the new node's marker to zero or one, depending on
        //  whether it lies on a boundary.
        setvertexmark(newvertex, trisym.m_tri == m.m_dummytri);
        setvertextype(newvertex,
          trisym.m_tri == m.m_dummytri
          ? VertexType::FREEVERTEX : VertexType::SEGMENTVERTEX
        );
        {
          tspivot(triangleloop, checkmark);
          //If this edge is a segment, transfer the marker to the new node.
          if (checkmark.m_subseg != m.m_dummysub) {
            setvertexmark(newvertex, mark(checkmark));
            setvertextype(newvertex, VertexType::SEGMENTVERTEX);
          }
        }
        if (b.m_verbosity > 1) {
          std::cout << "  Creating (%.12g, %.12g).\n", newvertex[0], newvertex[1]);
        }
        //Record the new node in the (one or two) adjacent elements.
        triangleloop.m_tri[m.m_highorderindex + triangleloop.m_orient] =
                (Triangle) newvertex;
        if (trisym.m_tri != m.m_dummytri) {
          trisym.m_tri[m.m_highorderindex + trisym.m_orient] = (Triangle) newvertex;
        }
      }
    }
    triangleloop.m_tri = triangletraverse(m);
  }
}

void ribi::tricpp::ReadNodes(
  Mesh& m,
  const Behavior& b,
  const std::string& polyfilename
)
{
  const auto v = ribi::fileio::FileIo().FileToVector(polyfilename);
  const auto first_line_strings = SeperateString(v[0],' ');
  assert(first_line_strings.size() == 4);
  const int n_vertices = boost::lexical_cast<int>(first_line_strings[0]);
  const int mesh_dimensionality = boost::lexical_cast<int>(first_line_strings[1]);
  const int n_extras = boost::lexical_cast<int>(first_line_strings[2]);
  const int n_nodemarkers = boost::lexical_cast<int>(first_line_strings[3]);

  if (n_vertices < 3)
  {
    std::stringstream s;
    s << "Error:  Input must have at least three input vertices.\n";
    throw std::logic_error(s.str().c_str());
  }
  m.m_invertices = n_vertices;

  assert(mesh_dimensionality == 2);
  assert(n_extras == 0);
  assert(n_nodemarkers == 1);

  initializevertexpool(m, b);

  for (int i = 0; i != n_vertices; ++i)
  {
    const int index = i + 1;
    assert(index >= 0);
    assert(index < static_cast<int>(v.size()));
    const std::string& line = v[index];
    Vertex vertexloop = (Vertex) PoolAlloc(&m.m_vertices);
    const std::vector<std::string> w = SeperateString(line,' ');
    assert(w.size() == 4);
    assert(index == boost::lexical_cast<int>(w[0]));
    if (i == 0)
    {
      const int firstnode = boost::lexical_cast<int>(w[0]);
      assert(firstnode == 1);
    }
    const double x = boost::lexical_cast<double>(w[1]);
    const double y = boost::lexical_cast<double>(w[2]);
    vertexloop[0] = x;
    vertexloop[1] = y;
    {
      const int currentmarker = boost::lexical_cast<int>(w[3]);
      assert(currentmarker == 1);
      setvertexmark(vertexloop, currentmarker);
    }
    setvertextype(vertexloop, VertexType::INPUTVERTEX);
    // Determine the smallest and largest x and y coordinates
    if (i == 0)
    {
      m.m_xmin = m.m_xmax = x;
      m.m_ymin = m.m_ymax = y;
    }
    else
    {
      m.m_xmin = (x < m.m_xmin) ? x : m.m_xmin;
      m.m_xmax = (x > m.m_xmax) ? x : m.m_xmax;
      m.m_ymin = (y < m.m_ymin) ? y : m.m_ymin;
      m.m_ymax = (y > m.m_ymax) ? y : m.m_ymax;
    }
  }

  // Nonexistent x value used as a flag to mark circle events in sweepline
  //   Delaunay algorithm.
  m.m_xminextreme = 10 * m.m_xmin - 9 * m.m_xmax;
}


void ribi::tricpp::readholes(
  const Behavior& b,
  FILE * const polyfile,
  //const char * const polyfilename,
  double ** const hlist,
  int * const holes,
  double ** const rlist,
  int *regions
)
{
  double *holelist;
  double *regionlist;
  char inputline[g_max_inputline_size];
  int index;
  //

  //Read the holes.
  char * stringptr = readline(inputline, polyfile);
  *holes = (int) strtol(stringptr, &stringptr, 0);
  if (*holes > 0) {
    holelist = (double *) TriMalloc(2 * *holes * (int) sizeof(double));
    *hlist = holelist;
    for (int i = 0; i < 2 * *holes; i += 2) {
      stringptr = readline(inputline, polyfile);
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        std::cout << "Error:  Hole %d has no x coordinate.\n",
               b.m_firstnumber + (i >> 1));
        throw std::logic_error(s.str().c_str());

      } else {
        holelist[i] = (double) strtod(stringptr, &stringptr);
      }
      stringptr = FindField(stringptr);
      if (*stringptr == '\0') {
        std::stringstream s;
        std::cout << "Error:  Hole %d has no y coordinate.\n",
               b.m_firstnumber + (i >> 1));
        throw std::logic_error(s.str().c_str());

      } else {
        holelist[i + 1] = (double) strtod(stringptr, &stringptr);
      }
    }
  } else {
    *hlist = (double *) NULL;
  }

  if ((b.m_regionattrib || b.m_vararea) && !b.m_do_refine) {
    //Read the area constraints.
    stringptr = readline(inputline, polyfile);

    if (stringptr == 0) goto my_end; //RJCB


    *regions = (int) strtol(stringptr, &stringptr, 0);
    if (*regions > 0) {
      regionlist = (double *) TriMalloc(4 * *regions * (int) sizeof(double));
      *rlist = regionlist;
      index = 0;
      for (int i = 0; i < *regions; i++)
      {
        stringptr = readline(inputline, polyfile);
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          std::stringstream s;
          std::cout << "Error:  Region %d has no x coordinate.\n",
                 b.m_firstnumber + i);
          throw std::logic_error(s.str().c_str());

        } else {
          regionlist[index++] = (double) strtod(stringptr, &stringptr);
        }
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          std::stringstream s;
          std::cout << "Error:  Region %d has no y coordinate.\n",
                 b.m_firstnumber + i);
          throw std::logic_error(s.str().c_str());

        } else {
          regionlist[index++] = (double) strtod(stringptr, &stringptr);
        }
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          std::stringstream s;
          std::cout <<
            "Error:  Region %d has no region attribute or area constraint.\n",
                 b.m_firstnumber + i);
          throw std::logic_error(s.str().c_str());

        } else {
          regionlist[index++] = (double) strtod(stringptr, &stringptr);
        }
        stringptr = FindField(stringptr);
        if (*stringptr == '\0') {
          regionlist[index] = regionlist[index - 1];
        } else {
          regionlist[index] = (double) strtod(stringptr, &stringptr);
        }
        index++;
      }
    }

    my_end: ;//RJCB

  } else {
    //Set `*regions' to zero to avoid an accidental free() later.
    *regions = 0;
    *rlist = (double *) NULL;
  }
  fclose(polyfile);
}
/*****************************************************************************/
//
// finishfile()   Write the command line to the output file so the user
//                can remember how the file was generated.  Close the file.
//
/*****************************************************************************/
void finishfile(
  FILE * const outfile,
  const std::vector<std::string>& args
)
{
  const int argc = static_cast<int>(args.size());
  std::fstd::cout << outfile, "# Generated by");
  for (int i = 0; i != argc; ++i) {
    std::fstd::cout << outfile, " ");
    std::fputs(args[i].c_str(), outfile);
  }
  std::fstd::cout << outfile, "\n");
  std::fclose(outfile);
}

void ribi::tricpp::writenodes(
  Mesh& m,
  const Behavior& b,
  const std::string& nodefilename,
  const std::vector<std::string>& args
)
{
  //FILE *outfile = nullptr;
  Vertex vertexloop;
  long outvertices;
  int vertexnumber;


  if (b.m_jettison) {
    outvertices = m.m_vertices.m_items - m.m_undeads;
  } else {
    outvertices = m.m_vertices.m_items;
  }


  FILE * const outfile = fopen(nodefilename.c_str(),"w");
  //Number of vertices, number of dimensions, number of vertex attributes,
  //  and number of boundary markers (zero or one).
  fstd::cout <<
    outfile,
    "%ld  %d  %d  %d\n",
    outvertices,
    2, //m.m_mesh_dim,
    m.m_nextras,
    1 - b.m_nobound
  );

  TraversalInit(&m.m_vertices);
  vertexnumber = b.m_firstnumber;
  vertexloop = vertextraverse(m);
  while (vertexloop != nullptr)
  {
    if (!b.m_jettison || (vertextype(vertexloop) != VertexType::UNDEADVERTEX))
    {

      //Vertex number, x and y coordinates.
      fstd::cout << outfile, "%4d    %.17g  %.17g", vertexnumber, vertexloop[0],
              vertexloop[1]);
      for (int i = 0; i < m.m_nextras; i++) {
        //Write an attribute.
        fstd::cout << outfile, "  %.17g", vertexloop[i + 2]);
      }
      if (b.m_nobound) {
        fstd::cout << outfile, "\n");
      } else {
        //Write the boundary marker.
        fstd::cout << outfile, "    %d\n", vertexmark(vertexloop));
      }

      setvertexmark(vertexloop, vertexnumber);
      vertexnumber++;
    }
    vertexloop = vertextraverse(m);
  }

  finishfile(outfile, args);
}

void ribi::tricpp::numbernodes(Mesh& m, const Behavior& b)
{
  //Vertex vertexloop;
  //int vertexnumber;

  TraversalInit(&m.m_vertices);
  int vertexnumber = b.m_firstnumber;
  Vertex vertexloop = vertextraverse(m);
  while (vertexloop != nullptr) {
    setvertexmark(vertexloop, vertexnumber);
    if (!b.m_jettison || (vertextype(vertexloop) != VertexType::UNDEADVERTEX)) {
      vertexnumber++;
    }
    vertexloop = vertextraverse(m);
  }
}

void ribi::tricpp::writeelements(
  Mesh& m,
  const Behavior& b,
  const std::string& elefilename,
  const std::vector<std::string>& args
)
{
  //FILE *outfile;
  Otri triangleloop;
  Vertex p1, p2, p3;
  Vertex mid1, mid2, mid3;
  long elementnumber;

  std::ofstream outfile(elefilename.c_str());
  //FILE * const outfile = fopen(elefilename.c_str(), "w");
  //Number of triangles, vertices per triangle, attributes per triangle.
  outfile
    << m.m_triangles.m_items << " "
    << ((b.m_order + 1) * (b.m_order + 2) / 2) << " "
    << m.m_eextras << "\n"
  ;
  //fstd::cout << outfile, "%ld  %d  %d\n", m.m_triangles.m_items,
  //        (b.m_order + 1) * (b.m_order + 2) / 2, m.m_eextras);

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  triangleloop.m_orient = 0;
  elementnumber = b.m_firstnumber;
  while (triangleloop.m_tri != nullptr)
  {
    p1 = triangleloop.GetOrigin();
    //GetOrigin(triangleloop, p1);

    GetDest(triangleloop, p2);

    p3 = triangleloop.GetApex();
    //GetApex(triangleloop, p3);

    if (b.m_order == 1)
    {
      //Triangle number, indices for three vertices.
      fstd::cout << outfile, "%4ld    %4d  %4d  %4d", elementnumber,
              vertexmark(p1), vertexmark(p2), vertexmark(p3);
    }
    else
    {
      mid1 = (Vertex) triangleloop.m_tri[m.m_highorderindex + 1];
      mid2 = (Vertex) triangleloop.m_tri[m.m_highorderindex + 2];
      mid3 = (Vertex) triangleloop.m_tri[m.m_highorderindex];
      //Triangle number, indices for six vertices.
      fstd::cout << outfile, "%4ld    %4d  %4d  %4d  %4d  %4d  %4d", elementnumber,
              vertexmark(p1), vertexmark(p2), vertexmark(p3), vertexmark(mid1),
              vertexmark(mid2), vertexmark(mid3);
    }

    for (int i = 0; i < m.m_eextras; i++) {
      fstd::cout << outfile, "  %.17g", elemattribute(triangleloop, i);
    }
    fstd::cout << outfile, "\n";

    triangleloop.m_tri = triangletraverse(m);
    elementnumber++;
  }

  finishfile(outfile, args);
}

void ribi::tricpp::writepoly(
  Mesh& m,
  const Behavior& b,
  const std::string& polyfilename,
  const double * const holelist,
  const int holes,
  const double * const regionlist,
  const int regions,
  const std::vector<std::string>& args
)
{
  //FILE *outfile;
  long holenumber, regionnumber;
  Osub subsegloop;
  Vertex endpoint1, endpoint2;
  long subsegnumber;


  std::ofstream outfile(polyfilename.c_str());
  //The zero indicates that the vertices are in a separate .node file.
  //  Followed by number of dimensions, number of vertex attributes,
  //  and number of boundary markers (zero or one).
  outfile
    << 0 //vertices are in a separate .node file.
    << ' '
    << 2 //mesh_dim
    << ' '
    << m.m_nextras
    << ' '
    << (1 - b.m_nobound)
    << '\n'
  ;
  //Number of segments, number of boundary markers (zero or one).
  outfile << m.m_subsegs.m_items << " " << (1 - b.m_nobound) << '\n';

  TraversalInit(&m.m_subsegs);
  subsegloop.m_subseg = subsegtraverse(m);
  subsegloop.m_subseg_orient = 0;
  subsegnumber = b.m_firstnumber;
  while (subsegloop.m_subseg != nullptr)
  {
    endpoint1 = subsegloop.GetOrigin();
    //GetOrigin(subsegloop, endpoint1);

    endpoint2 = subsegloop.GetDest();
    //GetDest(subsegloop, endpoint2);

    //Segment number, indices of its two endpoints, and possibly a marker.
    if (b.m_nobound)
    {
      outfile
        << subsegnumber
        << ' '
        << endpoint1.GetMark()
        << ' '
        << endpoint2.GetMark()
        << '\n'
      ;
    }
    else
    {
      outfile
        << subsegnumber
        << ' '
        << endpoint1.GetMark()
        << ' '
        << endpoint2.GetMark()
        << ' '
        << subsegloop.GetMark()
        << '\n'
        ;
    }

    subsegloop.m_subseg = subsegtraverse(m);
    subsegnumber++;
  }

  outfile << holes << '\n';
  for (holenumber = 0; holenumber < holes; holenumber++)
  {
    //Hole number, x and y coordinates.
    outfile
      << (b.m_firstnumber + holenumber)
      << ' '
      << holelist[2 * holenumber]
      << ' '
      << holelist[2 * holenumber + 1]
      << '\n'
    ;
  }
  if (regions > 0)
  {
    outfile << regions << '\n';
    for (regionnumber = 0; regionnumber < regions; regionnumber++)
    {
      //Region number, x and y coordinates, attribute, maximum area.
      outfile
        << (b.m_firstnumber + regionnumber)
        << ' '
        << regionlist[4 * regionnumbe  + 0]
        << ' '
        << regionlist[4 * regionnumber + 1]
        << ' '
        << regionlist[4 * regionnumber + 2]
        << ' '
        << regionlist[4 * regionnumber + 3]
        << '\n'
      ;
    }
  }

  finishfile(outfile, args);
}


void ribi::tricpp::writeedges(
  Mesh& m,
  const Behavior& b,
  const std::string& edgefilename,
  const std::vector<std::string>& args
)
{
  //FILE *outfile;
  Otri triangleloop, trisym;
  Osub checkmark;
  Vertex p1, p2;
  long edgenumber;
  Triangle ptr;                         //Temporary variable used by sym().
  SubSeg sptr;                      //Temporary variable used by tspivot().

  std::ofstream outfile(edgefilename.c_str());
  //Number of edges, number of boundary markers (zero or one).
  outfile << m.m_edges << ' ' << (1 - b.m_nobound) << '\n'

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  edgenumber = b.m_firstnumber;
  //To loop over the set of edges, loop over all triangles, and look at
  //  the three edges of each triangle.  If there isn't another triangle
  //  adjacent to the edge, operate on the edge.  If there is another
  //  adjacent triangle, operate on the edge only if the current triangle
  //  has a smaller pointer than its neighbor.  This way, each edge is
  //  considered only once.
  while (triangleloop.m_tri != nullptr)
  {
    for (triangleloop.m_orient = 0; triangleloop.m_orient < 3;
         triangleloop.m_orient++) {
      sym(triangleloop, trisym);
      if ((triangleloop.m_tri < trisym.m_tri) || (trisym.m_tri == m.m_dummytri)) {
        p1 = triangleloop.GetOrigin();
        //org(triangleloop, p1);
        p2 = triangleloop.GetDest();
        //dest(triangleloop, p2);
        if (b.m_nobound) {
          //Edge number, indices of two endpoints.
          outfile
            << edgenumber
            << ' '
            << p1.GetMark() //vertexmark(p1)
            << ' '
            << p2.GetMark() //vertexmark(p2)
          ;
        }
        else
        {
          //Edge number, indices of two endpoints, and a boundary marker.
          //  If there's no subsegment, the boundary marker is zero.
          {
            tspivot(triangleloop, checkmark);
            if (checkmark.m_subseg == m.m_dummysub)
            {
              outfile
                << edgenumber
                << ' '
                << p1.GetMark()
                << ' '
                << p2.GetMark()
                <<' '
                << 0 //Marker: no subsegment, thus zero
                << '\n'
              ;
            }
            else
            {
              outfile
                << edgenumber
                <<' '
                << p1.GetMark()
                << ' '
                << p2.GetMark()
                << ' '
                << checkmark.GetMark()
                << '\n'
              ;
            }
          }
          else
          {
            outfile
              << edgenumber
              << ' '
              << p1.GetMark()
              << ' '
              << p2.GetMark()
              << ' '
              << (trisym.m_tri == m.m_dummytri)
              << '\n'
            ;
          }
        }
        edgenumber++;
      }
    }
    triangleloop.m_tri = triangletraverse(m);
  }

  finishfile(outfile, args);
}

void ribi::tricpp::writevoronoi(
  Mesh& m,
  const Behavior& b,
  const std::string& vnodefilename,
  const std::string& vedgefilename,
  const std::vector<std::string>& args
)
{
  Otri triangleloop, trisym;
  Vertex torg, tdest, tapex;
  double circumcenter[2];
  double xi, eta;
  long vnodenumber, vedgenumber;
  int p1, p2;

  Triangle ptr;                         //Temporary variable used by sym().


  FILE * outfile = fopen(vnodefilename.c_str(), "w");
  //Number of triangles, two dimensions, number of vertex attributes,
  //  no markers.
  fstd::cout << outfile, "%ld  %d  %d  %d\n", m.m_triangles.m_items, 2, m.m_nextras, 0);

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  triangleloop.m_orient = 0;
  vnodenumber = b.m_firstnumber;
  while (triangleloop.m_tri != nullptr)
  {
    torg = triangleloop.GetOrigin();
    //GetOrigin(triangleloop, torg);

    tdest = triangleloop.GetDest();
    //GetDest(triangleloop, tdest);

    tapex = triangleloop.GetApex();
    //GetApex(triangleloop, tapex);

    findcircumcenter(m, b, torg, tdest, tapex, circumcenter, &xi, &eta, 0);
    //Voronoi vertex number, x and y coordinates.
    fstd::cout << outfile, "%4ld    %.17g  %.17g", vnodenumber, circumcenter[0],
            circumcenter[1];
    for (int i = 2; i < 2 + m.m_nextras; i++) {
      //Interpolate the vertex attributes at the circumcenter.
      fstd::cout << outfile, "  %.17g", torg[i] + xi * (tdest[i] - torg[i])
                                         + eta * (tapex[i] - torg[i]));
    }
    fstd::cout << outfile, "\n";

    * (int *) (triangleloop.m_tri + 6) = (int) vnodenumber;
    triangleloop.m_tri = triangletraverse(m);
    vnodenumber++;
  }

  finishfile(outfile, args);


  outfile = fopen(vedgefilename.c_str(), "w");
  //Number of edges, zero boundary markers.
  fstd::cout << outfile, "%ld  %d\n", m.m_edges, 0);
  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  vedgenumber = b.m_firstnumber;
  //To loop over the set of edges, loop over all triangles, and look at
  //  the three edges of each triangle.  If there isn't another triangle
  //  adjacent to the edge, operate on the edge.  If there is another
  //  adjacent triangle, operate on the edge only if the current triangle
  //  has a smaller pointer than its neighbor.  This way, each edge is
  //  considered only once.
  while (triangleloop.m_tri != (Triangle *) NULL) {
    for (triangleloop.m_orient = 0; triangleloop.m_orient < 3;
         triangleloop.m_orient++) {
      sym(triangleloop, trisym);
      if ((triangleloop.m_tri < trisym.m_tri) || (trisym.m_tri == m.m_dummytri)) {
        //Find the number of this triangle (and Voronoi vertex).
        p1 = * (int *) (triangleloop.m_tri + 6);
        if (trisym.m_tri == m.m_dummytri)
        {
          torg = triangleloop.GetOrigin();
          //GetOrigin(triangleloop, torg);

          tdest = triangleloop.GetDest();
          //GetDest(triangleloop, tdest);

          //Write an infinite ray.  Edge number, index of one endpoint, -1,
          //  and x and y coordinates of a vector representing the
          //  direction of the ray.
          fstd::cout << outfile, "%4ld   %d  %d   %.17g  %.17g\n", vedgenumber,
                  p1, -1, tdest[1] - torg[1], torg[0] - tdest[0];
        }
        else
        {
          //Find the number of the adjacent triangle (and Voronoi vertex).
          p2 = * (int *) (trisym.m_tri + 6);
          //Finite edge.  Write indices of two endpoints.
          fstd::cout << outfile, "%4ld   %d  %d\n", vedgenumber, p1, p2;
        }
        vedgenumber++;
      }
    }
    triangleloop.m_tri = triangletraverse(m);
  }

  finishfile(outfile, args);
}

void ribi::tricpp::writeneighbors(
  Mesh& m,
  const Behavior& b,
  const std::string& neighborfilename,
  const std::vector<std::string>& args
)
{
  //FILE *outfile;
  Otri triangleloop, trisym;
  long elementnumber;
  int neighbor1, neighbor2, neighbor3;
  Triangle ptr;                         //Temporary variable used by sym().

  std::ofstream outfile(neighborfilename.c_str());

  //Number of triangles, three neighbors per triangle.
  outfile << "%ld  %d\n", m.m_triangles.m_items, 3;

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  triangleloop.m_orient = 0;
  elementnumber = b.m_firstnumber;
  while (triangleloop.m_tri != nullptr)
  {
    * (int *) (triangleloop.m_tri + 6) = (int) elementnumber;
    triangleloop.m_tri = triangletraverse(m);
    elementnumber++;
  }
  * (int *) (m.m_dummytri + 6) = -1;

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  elementnumber = b.m_firstnumber;
  while (triangleloop.m_tri != nullptr) {
    triangleloop.m_orient = 1;
    sym(triangleloop, trisym);
    neighbor1 = * (int *) (trisym.m_tri + 6);
    triangleloop.m_orient = 2;
    sym(triangleloop, trisym);
    neighbor2 = * (int *) (trisym.m_tri + 6);
    triangleloop.m_orient = 0;
    sym(triangleloop, trisym);
    neighbor3 = * (int *) (trisym.m_tri + 6);
    //Triangle number, neighboring triangle numbers.
    fstd::cout << outfile, "%4ld    %d  %d  %d\n", elementnumber,
            neighbor1, neighbor2, neighbor3);

    triangleloop.m_tri = triangletraverse(m);
    elementnumber++;
  }

  finishfile(outfile, args);
}


void ribi::tricpp::writeoff(
  Mesh& m,
  const Behavior& b,
  const std::string& offfilename,
  const std::vector<std::string>& args
)
{
  //FILE *outfile;
  struct Otri triangleloop;
  Vertex vertexloop;
  Vertex p1, p2, p3;
  long outvertices;

  if (b.m_jettison)
  {
    outvertices = m.m_vertices.m_items - m.m_undeads;
  } else {
    outvertices = m.m_vertices.m_items;
  }

  std::ofstream outfile(offfilename.c_str());

  //Number of vertices, triangles, and edges.
  outfile << "OFF\n%ld  %ld  %ld\n", outvertices, m.m_triangles.m_items,
          m.m_edges);

  //Write the vertices.
  TraversalInit(&m.m_vertices);
  vertexloop = vertextraverse(m);
  while (vertexloop != nullptr) {
    if (!b.m_jettison || (vertextype(vertexloop) != VertexType::UNDEADVERTEX)) {
      //The "0.0" is here because the OFF format uses 3D coordinates.
      fstd::cout << outfile, " %.17g  %.17g  %.17g\n", vertexloop[0], vertexloop[1],
              0.0);
    }
    vertexloop = vertextraverse(m);
  }

  //Write the triangles.
  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  triangleloop.m_orient = 0;
  while (triangleloop.m_tri != nullptr)
  {
    p1 = triangleloop.GetOrigin();
    //GetOrigin(triangleloop, p1);

    p2 = triangleloop.GetDest();
    //GetDest(triangleloop, p2);

    p3 = triangleloop.GetApex();
    //GetApex(triangleloop, p3);

    //The "3" means a three-vertex polygon.
    fstd::cout << outfile, " 3   %4d  %4d  %4d\n", vertexmark(p1) - b.m_firstnumber,
            vertexmark(p2) - b.m_firstnumber, vertexmark(p3) - b.m_firstnumber);
    triangleloop.m_tri = triangletraverse(m);
  }
  finishfile(outfile, args);
}

void ribi::tricpp::quality_statistics(
  Mesh& m,
  const Behavior& b
)
{
  Otri triangleloop;
  Vertex p[3];
  double cossquaretable[8];
  double ratiotable[16];
  double dx[3], dy[3];
  double edgelength[3];
  double dotproduct;
  double cossquare;
  double triarea;
  double shortest, longest;
  double trilongest2;
  double smallestarea, biggestarea;
  double triminaltitude2;
  double minaltitude;
  double triaspect2;
  double worstaspect;
  double smallestangle, biggestangle;
  double radconst, degconst;
  int angletable[18];
  int aspecttable[16];
  int aspectindex;
  int tendegree;
  int acutebiggest;
  int i, ii, j, k;

  radconst = boost::math::constants::pi<double>() / 18.0;
  degconst = 180.0 / boost::math::constants::pi<double>();
  for (i = 0; i < 8; i++) {
    cossquaretable[i] = cos(radconst * (double) (i + 1));
    cossquaretable[i] = cossquaretable[i] * cossquaretable[i];
  }
  for (i = 0; i < 18; i++) {
    angletable[i] = 0;
  }

  ratiotable[0]  =      1.5;      ratiotable[1]  =     2.0;
  ratiotable[2]  =      2.5;      ratiotable[3]  =     3.0;
  ratiotable[4]  =      4.0;      ratiotable[5]  =     6.0;
  ratiotable[6]  =     10.0;      ratiotable[7]  =    15.0;
  ratiotable[8]  =     25.0;      ratiotable[9]  =    50.0;
  ratiotable[10] =    100.0;      ratiotable[11] =   300.0;
  ratiotable[12] =   1000.0;      ratiotable[13] = 10000.0;
  ratiotable[14] = 100000.0;      ratiotable[15] =     0.0;
  for (i = 0; i < 16; i++) {
    aspecttable[i] = 0;
  }

  worstaspect = 0.0;
  minaltitude = m.m_xmax - m.m_xmin + m.m_ymax - m.m_ymin;
  minaltitude = minaltitude * minaltitude;
  shortest = minaltitude;
  longest = 0.0;
  smallestarea = minaltitude;
  biggestarea = 0.0;
  worstaspect = 0.0;
  smallestangle = 0.0;
  biggestangle = 2.0;
  acutebiggest = 1;

  TraversalInit(&m.m_triangles);
  triangleloop.m_tri = triangletraverse(m);
  triangleloop.m_orient = 0;
  while (triangleloop.m_tri != nullptr)
  {
    p[0] = triangleloop.GetOrigin();
    //GetOrigin(triangleloop, p[0]);

    p[1] = triangleloop.GetDest();
    //GetDest(triangleloop, p[1]);

    p[2] = triangleloop.GetApex();
    //GetApex(triangleloop, p[2]);

    trilongest2 = 0.0;

    for (i = 0; i < 3; i++)
    {
      j = i + 1 % 3; //plus1mod3_cpp[i];
      k = i + 2 % 3; //minus1mod3_cpp[i];
      dx[i] = p[j][0] - p[k][0];
      dy[i] = p[j][1] - p[k][1];
      edgelength[i] = dx[i] * dx[i] + dy[i] * dy[i];
      if (edgelength[i] > trilongest2)
      {
        trilongest2 = edgelength[i];
      }
      if (edgelength[i] > longest) {
        longest = edgelength[i];
      }
      if (edgelength[i] < shortest) {
        shortest = edgelength[i];
      }
    }

    triarea = counterclockwise(m.m_counterclockcount, b.m_noexact, p[0], p[1], p[2]);
    if (triarea < smallestarea) {
      smallestarea = triarea;
    }
    if (triarea > biggestarea) {
      biggestarea = triarea;
    }
    triminaltitude2 = triarea * triarea / trilongest2;
    if (triminaltitude2 < minaltitude) {
      minaltitude = triminaltitude2;
    }
    triaspect2 = trilongest2 / triminaltitude2;
    if (triaspect2 > worstaspect) {
      worstaspect = triaspect2;
    }
    aspectindex = 0;
    while ((triaspect2 > ratiotable[aspectindex] * ratiotable[aspectindex])
           && (aspectindex < 15)) {
      aspectindex++;
    }
    aspecttable[aspectindex]++;

    for (i = 0; i < 3; i++) {
      j = plus1mod3_cpp[i];
      k = minus1mod3_cpp[i];
      dotproduct = dx[j] * dx[k] + dy[j] * dy[k];
      cossquare = dotproduct * dotproduct / (edgelength[j] * edgelength[k]);
      tendegree = 8;
      for (ii = 7; ii >= 0; ii--) {
        if (cossquare > cossquaretable[ii]) {
          tendegree = ii;
        }
      }
      if (dotproduct <= 0.0) {
        angletable[tendegree]++;
        if (cossquare > smallestangle) {
          smallestangle = cossquare;
        }
        if (acutebiggest && (cossquare < biggestangle)) {
          biggestangle = cossquare;
        }
      } else {
        angletable[17 - tendegree]++;
        if (acutebiggest || (cossquare > biggestangle)) {
          biggestangle = cossquare;
          acutebiggest = 0;
        }
      }
    }
    triangleloop.m_tri = triangletraverse(m);
  }

  shortest = sqrt(shortest);
  longest = sqrt(longest);
  minaltitude = sqrt(minaltitude);
  worstaspect = sqrt(worstaspect);
  smallestarea *= 0.5;
  biggestarea *= 0.5;
  if (smallestangle >= 1.0) {
    smallestangle = 0.0;
  } else {
    smallestangle = degconst * acos(sqrt(smallestangle));
  }
  if (biggestangle >= 1.0) {
    biggestangle = 180.0;
  } else {
    if (acutebiggest) {
      biggestangle = degconst * acos(sqrt(biggestangle));
    } else {
      biggestangle = 180.0 - degconst * acos(sqrt(biggestangle));
    }
  }
  /*
  std::cout << "  Smallest area: %16.5g   |  Largest area: %16.5g\n",
         smallestarea, biggestarea;
  std::cout << "  Shortest edge: %16.5g   |  Longest edge: %16.5g\n",
         shortest, longest;
  std::cout << "  Shortest altitude: %12.5g   |  Largest aspect ratio: %8.5g\n\n",
         minaltitude, worstaspect;

  std::cout << "  Triangle aspect ratio histogram:\n");
  std::cout << "  1.1547 - %-6.6g    :  %8d    | %6.6g - %-6.6g     :  %8d\n",
         ratiotable[0], aspecttable[0], ratiotable[7], ratiotable[8],
         aspecttable[8];
  for (i = 1; i < 7; i++) {
    std::cout << "  %6.6g - %-6.6g    :  %8d    | %6.6g - %-6.6g     :  %8d\n",
           ratiotable[i - 1], ratiotable[i], aspecttable[i],
           ratiotable[i + 7], ratiotable[i + 8], aspecttable[i + 8];
  }
  std::cout << "  %6.6g - %-6.6g    :  %8d    | %6.6g -            :  %8d\n",
         ratiotable[6], ratiotable[7], aspecttable[7], ratiotable[14],
         aspecttable[15]);
  std::cout << "  (Aspect ratio is longest edge divided by shortest altitude)\n\n");

  std::cout << "  Smallest angle: %15.5g   |  Largest angle: %15.5g\n\n",
         smallestangle, biggestangle);

  std::cout << "  Angle histogram:\n");
  for (i = 0; i < 9; i++) {
    std::cout << "    %3d - %3d degrees:  %8d    |    %3d - %3d degrees:  %8d\n",
           i * 10, i * 10 + 10, angletable[i],
           i * 10 + 90, i * 10 + 100, angletable[i + 9]);
  }
  std::cout << "\n");
  */
}

/*
void ribi::tricpp::statistics(
  Mesh& m,
  const Behavior& b
)
{
  std::cout << "\nStatistics:\n\n");
  std::cout << "  Input vertices: %d\n" << m.m_invertices;
  if (b.m_do_refine) {
    std::cout << "  Input triangles: %d\n", m.m_inelements);
  }
  {
    std::cout << "  Input segments: %d\n"<< m.m_insegments;
    if (!b.m_do_refine) {
      std::cout << "  Input holes: %d\n" << m.m_holes;
    }
  }

  std::cout << "\n  Mesh vertices: %ld\n", m.m_vertices.m_items - m.m_undeads);
  std::cout << "  Mesh triangles: %ld\n", m.m_triangles.m_items);
  std::cout << "  Mesh edges: %ld\n", m.m_edges);
  std::cout << "  Mesh exterior boundary edges: %ld\n", m.m_hullsize);
  if (b.m_do_refine)
  {
    std::cout << "  Mesh interior boundary edges: %ld\n" << (
           m.m_subsegs.m_items - m.m_hullsize);
    std::cout << "  Mesh subsegments (constrained edges): %ld\n",
           m.m_subsegs.m_items);
  }
  std::cout << "\n");

  if (b.m_verbosity) {
    quality_statistics(m, b);
    std::cout << "Memory allocation statistics:\n\n");
    std::cout << "  Maximum number of vertices: %ld\n", m.m_vertices.m_maxitems);
    std::cout << "  Maximum number of triangles: %ld\n", m.m_triangles.m_maxitems);
    if (m.m_subsegs.m_maxitems > 0) {
      std::cout << "  Maximum number of subsegments: %ld\n", m.m_subsegs.m_maxitems);
    }
    if (m.m_viri.m_maxitems > 0) {
      std::cout << "  Maximum number of viri: %ld\n", m.m_viri.m_maxitems);
    }
    if (m.m_badsubsegs.m_maxitems > 0) {
      std::cout << "  Maximum number of encroached subsegments: %ld\n",
             m.m_badsubsegs.m_maxitems);
    }
    if (m.m_badtriangles.m_maxitems > 0) {
      std::cout << "  Maximum number of bad triangles: %ld\n",
             m.m_badtriangles.m_maxitems);
    }
    if (m.m_flipstackers.m_maxitems > 0) {
      std::cout << "  Maximum number of stacked triangle flips: %ld\n",
             m.m_flipstackers.m_maxitems);
    }
    if (m.m_splaynodes.m_maxitems > 0) {
      std::cout << "  Maximum number of splay tree nodes: %ld\n",
             m.m_splaynodes.m_maxitems);
    }
    std::cout << "  Approximate heap memory use (bytes): %ld\n\n",
           m.m_vertices.m_maxitems * m.m_vertices.m_itembytes +
           m.m_triangles.m_maxitems * m.m_triangles.m_itembytes +
           m.m_subsegs.m_maxitems * m.m_subsegs.m_itembytes +
           m.m_viri.m_maxitems * m.m_viri.m_itembytes +
           m.m_badsubsegs.m_maxitems * m.m_badsubsegs.m_itembytes +
           m.m_badtriangles.m_maxitems * m.m_badtriangles.m_itembytes +
           m.m_flipstackers.m_maxitems * m.m_flipstackers.m_itembytes +
           m.m_splaynodes.m_maxitems * m.m_splaynodes.m_itembytes);

    std::cout << "Algorithmic statistics:\n\n");
    //if (!b.m_weighted)
    {
      std::cout << "  Number of incircle tests: %ld\n", m.m_incirclecount);
    }
    std::cout << "  Number of 2D orientation tests: %ld\n", m.m_counterclockcount);
    if (m.m_hyperbolacount > 0) {
      std::cout << "  Number of right-of-hyperbola tests: %ld\n",
             m.m_hyperbolacount);
    }
    if (m.m_circletopcount > 0) {
      std::cout << "  Number of circle top computations: %ld\n",
             m.m_circletopcount);
    }
    if (m.m_circumcentercount > 0) {
      std::cout << "  Number of triangle circumcenter computations: %ld\n",
             m.m_circumcentercount);
    }
    std::cout << "\n");
  }
}
*/

int ribi::tricpp::triangle_cpp_main(const std::vector<std::string>& args)
{
  Mesh m;
  Behavior b(args);
  double *holearray;                                        //Array of holes.
  double *regionarray;   //Array of regional attributes and area constraints.
  FILE *polyfile = nullptr;
  m.m_steinerleft = b.m_steiner;

  ReadNodes(
    m,
    b,
    b.m_inpolyfilename
  );

  if (b.m_do_refine)
  {
    //Read and reconstruct a mesh.
    m.m_hullsize
      = reconstruct(
      m,
      b,
      b.m_inelefilename,
      b.m_areafilename,
      b.m_inpolyfilename,
      polyfile
    );
  }
  else
  {
    m.m_hullsize = delaunay(m, b);              //Triangulate the vertices.
  }

  //Ensure that no vertex can be mistaken for a triangular bounding
  //  box vertex in insertvertex().
  m.m_infvertex1 = nullptr;
  m.m_infvertex2 = nullptr;
  m.m_infvertex3 = nullptr;

  {
    m.m_checksegments = 1;                //Segments will be introduced next.
    if (!b.m_do_refine)
    {
      //Insert PSLG segments and/or convex hull segments.
      formskeleton(m, b, polyfile, b.m_inpolyfilename);
    }
  }
  if (m.m_triangles.m_items > 0)
  {
    readholes(
      b,
      polyfile,
      &holearray,
      &m.m_holes,
      &regionarray,
      &m.m_regions
    );
    if (!b.m_do_refine)
    {
      //Carve out holes and concavities.
      carveholes(m, b, holearray, m.m_holes, regionarray, m.m_regions);
    }
  }
  else
  {
    //Without a PSLG, there can be no holes or regional attributes
    //  or area constraints.  The following are set to zero to avoid
    //  an accidental free() later.
    m.m_holes = 0;
    m.m_regions = 0;
  }

  if (b.m_quality && m.m_triangles.m_items > 0)
  {
    enforcequality(m, b);           //Enforce angle and area constraints.
  }

  //Calculate the number of edges.
  m.m_edges = (3l * m.m_triangles.m_items + m.m_hullsize) / 2l;

  if (b.m_order > 1)
  {
    highorder(m, b);       //Promote elements to higher polynomial order.
  }
  //If not using iteration numbers, don't write a .node file if one was
  //  read, because the original one would be overwritten!
  if (b.m_nonodewritte)
  {
    if (!b.m_quiet)
    {
      std::cout << "NOT writing a .node file.\n";
    }
    numbernodes(m, b);         //We must remember to number the vertices.
  }
  else
  {
    writenodes(m, b, b.m_outnodefilename, args);
  }
  if (b.m_noelewritten)
  {
    if (!b.m_quiet)
    {
      std::cout << "NOT writing an .ele file.\n";
    }
  }
  else
  {
    writeelements(m, b, b.m_outelefilename, args);
  }
  //The -c switch (convex switch) causes a PSLG to be written
  //  even if none was read.

  {
    //If not using iteration numbers, don't overwrite the .poly file.
    if (b.m_nopolywritten || b.m_noiterationnum)
    {
      if (!b.m_quiet) {
        std::cout << "NOT writing a .poly file.\n";
      }
    }
    else
    {
      writepoly(
        m,
        b,
        b.m_outpolyfilename,
        holearray,
        m.m_holes,
        regionarray,
        m.m_regions,
        args
      );
    }
  }
  if (m.m_regions > 0) {
    delete regionarray;
    regionarray = nullptr;
  }
  if (m.m_holes > 0) {
    delete holearray;
    holearray = nullptr;
  }
  if (b.m_geomview) {
    writeoff(m, b, b.m_offfilename, args);
  }
  if (b.m_edgesout) {
    writeedges(m, b, b.m_edgefilename, args);
  }
  if (b.m_voronoi) {
    writevoronoi(m, b, b.m_vnodefilename, b.m_vedgefilename, args);
  }
  if (b.m_neighbors) {
    writeneighbors(m, b, b.m_neighborfilename, args);
  }

  if (!b.m_quiet) {
    statistics(m, b);
  }
  if (b.m_do_check) {
    checkmesh(m, b);
    checkdelaunay(m, b);
  }
  triangledeinit(m, b);
  return 0;
}

/*
void ribi::tricpp::printtriangle(
  const Mesh& m,
  const Behavior& b,
  const Otri * const t
)
{
  Otri printtri;
  Osub printsh;
  Vertex printvertex;

  std::cout
    << "triangle " << t->m_tri << " with orientation " << t->m_orient << ":\n";

  decode(t->m_tri[0], printtri);
  if (printtri.m_tri == m.m_dummytri)
  {
    std::cout << "    [0] = Outer space\n";
  }
  else
  {
    std::cout
      << "    [0] = " << printtri.m_tri
      << "  " << printtri.m_orient << "\n"
    ;
  }
  decode(t->m_tri[1], printtri);
  if (printtri.m_tri == m.m_dummytri) {
    std::cout << "    [1] = Outer space\n");
  } else {
    std::cout << "    [1] = x%lx  %d\n", (unsigned long) printtri.m_tri,
           printtri.m_orient);
  }
  decode(t->m_tri[2], printtri);
  if (printtri.m_tri == m.m_dummytri) {
    std::cout << "    [2] = Outer space\n");
  } else {
    std::cout << "    [2] = x%lx  %d\n", (unsigned long) printtri.m_tri,
           printtri.m_orient);
  }

  GetOrigin(*t, printvertex);
  if (printvertex == nullptr)
    std::cout << "    Origin[%d] = NULL\n", (t->m_orient + 1) % 3 + 3);
  else
    std::cout << "    Origin[%d] = x%lx  (%.12g, %.12g)\n",
           (t->m_orient + 1) % 3 + 3, (unsigned long) printvertex,
           printvertex[0], printvertex[1]);
  GetDest(*t, printvertex);
  if (printvertex == nullptr)
    std::cout << "    Dest  [%d] = NULL\n", (t->m_orient + 2) % 3 + 3);
  else
    std::cout << "    Dest  [%d] = x%lx  (%.12g, %.12g)\n",
           (t->m_orient + 2) % 3 + 3, (unsigned long) printvertex,
           printvertex[0], printvertex[1]);
  GetApex(*t, printvertex);
  if (printvertex == nullptr)
    std::cout << "    Apex  [%d] = NULL\n", t->m_orient + 3);
  else
    std::cout << "    Apex  [%d] = x%lx  (%.12g, %.12g)\n",
           t->m_orient + 3, (unsigned long) printvertex,
           printvertex[0], printvertex[1]);

  {
    sdecode(t->m_tri[6], printsh);
    if (printsh.m_subseg != m.m_dummysub) {
      std::cout << "    [6] = x%lx  %d\n", (unsigned long) printsh.m_subseg,
             printsh.m_subseg_orient);
    }
    sdecode(t->m_tri[7], printsh);
    if (printsh.m_subseg != m.m_dummysub) {
      std::cout << "    [7] = x%lx  %d\n", (unsigned long) printsh.m_subseg,
             printsh.m_subseg_orient);
    }
    sdecode(t->m_tri[8], printsh);
    if (printsh.m_subseg != m.m_dummysub) {
      std::cout << "    [8] = x%lx  %d\n", (unsigned long) printsh.m_subseg,
             printsh.m_subseg_orient);
    }
  }

  if (b.m_vararea) {
    std::cout << "    Area constraint:  %.4g\n", areabound(*t));
  }
}
*/

/*
void ribi::tricpp::printsubseg(
  const SubSeg * const m_dummysub,
  const Triangle * const m_dummytri,
  const Osub& osub
)
{
  std::stringstream s;
  Osub printsh;
  Otri printtri;
  Vertex printvertex;

  s
    << "subsegment "
    << osub.m_subseg
    << " with orientation "
    << osub.m_subseg_orient
    << " and mark "
    << mark(*osub)
    << ":\n"
  ;
  sdecode(osub.m_subseg[0], printsh);
  if (printsh.m_subseg == m_dummysub)
  {
    s << "    [0] = No subsegment\n";
  }
  else
  {
    s << "    [0] = " << printsh.m_subseg << " " << printsh.m_subseg_orient << '\n';

  }
  sdecode(osub.m_subseg[1], printsh);
  if (printsh.m_subseg == m_dummysub)
  {
    s << "    [1] = No subsegment\n";
  } else
  {
    s << "    [1] = " << printsh.m_subseg << " " << printsh.m_subseg_orient << '\n';
  }

  GetOrigin(*osub, printvertex);
  if (printvertex == nullptr)
  {
    s << "    Origin[" << (2 + osub.m_subseg_orient) << "] = NULL\n";
  }
  else
  {
    s << "    Origin[" << (2 + osub.m_subseg_orient) << "] = "
      << printvertex << "  (" << printvertex[0] << ", " << printvertex[1] << ")\n"
    ;
  }
  GetDest(*osub, printvertex);
  if (printvertex == nullptr)
  {
    s << "    Dest  [%d] = NULL\n", 3 - osub.m_subseg_orient);
  }
  else
  {
    s << "    Dest  [%d] = x%lx  (%.12g, %.12g)\n",
      3 - osub.m_subseg_orient, (unsigned long) printvertex,
      printvertex[0], printvertex[1]
    );
  }
  decode(osub.m_subseg[6], printtri);
  if (printtri.m_tri == m_dummytri)
  {
    s << "    [6] = Outer space\n");
  }
  else
  {
    s << "    [6] = x%lx  %d\n", (unsigned long) printtri.m_tri,
      printtri.m_orient
    );
  }
  decode(osub.m_subseg[7], printtri);
  if (printtri.m_tri == m_dummytri)
  {
    s << "    [7] = Outer space\n");
  } else
  {
    s << "    [7] = x%lx  %d\n", (unsigned long) printtri.m_tri,
      printtri.m_orient
    );
  }

  GetOrg(*osub, printvertex);
  if (printvertex == nullptr)
  {
    s << "    Segment origin[%d] = NULL\n", 4 + osub.m_subseg_orient);
  }
  else
  {
    s << "    Segment origin[%d] = x%lx  (%.12g, %.12g)\n",
      4 + osub.m_subseg_orient, (unsigned long) printvertex,
      printvertex[0], printvertex[1]
    );
  }
  GetDest(*osub, printvertex);
  if (printvertex == nullptr)
  {
    s << "    Segment dest  [%d] = NULL\n", 5 - osub.m_subseg_orient);
  }
  else
  {
    s << "    Segment dest  [%d] = x%lx  (%.12g, %.12g)\n",
      5 - osub.m_subseg_orient, (unsigned long) printvertex,
      printvertex[0], printvertex[1]
    );
  }
}
*/

#pragma GCC diagnostic pop //RJCB
