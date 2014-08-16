#ifndef TRIANGLE_CPP_H
#define TRIANGLE_CPP_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "trianglecppfwd.h"

#include "trianglecpplocateresult.h"
#include "trianglecppfinddirectionresult.h"
#include "trianglecppedge.h"
#include "trianglecpptriangle.h"
#include "trianglecpptypedefs.h"
#include "trianglecppvertex.h"
#include "trianglecppinsertvertexresult.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/// alternateaxes()   Sorts the vertices as appropriate for the divide-and-
///                   conquer algorithm with alternating cuts.
///
/// Partitions by x-coordinate if axis == 0; by y-coordinate if axis == 1.
/// For the base case, subsets containing only two or three vertices are
/// always sorted by x-coordinate.
void alternateaxes(
  Vertex * const sortarray,
  const int arraysize,
  int axis
);

/// Deallocate space for a bad subsegment, marking it
/// dead.
/*
void badsubsegdealloc(
  //Mesh& m,
  std::vector<BadSubSeg>& m_badsubsegs,
  BadSubSeg& dyingseg
);
*/
/// badsubsegtraverse()   Traverse the bad subsegments, skipping dead ones.
//BadSubSeg * badsubsegtraverse(Mesh& m);

/// boundingbox()   Form an "infinite" bounding triangle to insert vertices
///                 into.
/// The vertices at "infinity" are assigned finite coordinates, which are
/// used by the point location routines, but (mostly) ignored by the
/// Delaunay edge flip routines.
void boundingbox(Mesh& m, const Arguments& b);

/// carveholes()   Find the holes and infect them.  Find the area
///                constraints and infect them.  Infect the convex hull.
///                Spread the infection and kill triangles.  Spread the
///                area constraints.
///
/// This routine mainly calls other routines to carry out all these
/// functions.
void carveholes(
  Mesh& m,
  const Arguments& b,
  std::vector<double>& holelist,
  //double * const holelist,
  //const int holes,
  std::vector<double>& regionlist
  //double * const regionlist,
  //const int regions
);

void check4deadevent(
  const Otri * const checktri,
  /* const */ Event ** const freeevents,
  Event ** const eventheap,
  int * const heapsize
);

///Ensure that the mesh is (constrained) Delaunay.
void checkdelaunay(
  Mesh& m,
  int& m_m_incirclecount
  //const bool m_m_noexact,
  //Arguments& b
);

///Test the mesh for topological consistency.
void checkmesh(
  Mesh& m,
  //const std::vector<boost::shared_ptr<Triangle>>& m_m_triangles,
  int& m_m_counterclockcount
  //Arguments& b
  //const bool b_m_noexact
);

/// Check a subsegment to see if it is encroached; add
///                       it to the list if it is.
///
/// A subsegment is encroached if there is a vertex in its diametral lens.
/// For Ruppert's algorithm (-D switch), the "diametral lens" is the
/// diametral circle.  For Chew's algorithm (default), the diametral lens is
/// just big enough to enclose two isosceles triangles whose bases are the
/// subsegment.  Each of the two isosceles triangles has two angles equal
/// to `b->minangle'.
///
/// Chew's algorithm does not require diametral lenses at all--but they save
/// time.  Any vertex inside a subsegment's diametral lens implies that the
/// triangle adjoining the subsegment will be too skinny, so it's only a
/// matter of time before the encroaching vertex is deleted by Chew's
/// algorithm.  It's faster to simply not insert the doomed vertex in the
/// first place, which is why I use diametral lenses with Chew's algorithm.
///
/// Returns a nonzero value if the subsegment is encroached.
int checkseg4encroach(
  //Mesh& m,
  boost::shared_ptr<Triangle> m_m_dummytri,
  //const Arguments& b,
  const bool b_m_conformdel,
  const double b_m_goodangle,
  const bool b_m_nobisect,
  boost::shared_ptr<Osub> testsubseg
);

double circletop(
  Mesh& m,
  const Vertex& pa,
  const Vertex& pb,
  const Vertex& pc,
  const double ccwabc
);

boost::shared_ptr<SplayNode> circletopinsert(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<SplayNode> splayroot,
  const boost::shared_ptr<Otri>& newkey,
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const double topy
);



/// conformingedge()   Force a segment into a conforming Delaunay
///                    triangulation by inserting a vertex at its midpoint,
///                    and recursively forcing in the two half-segments if
///                    necessary.
///
/// Generates a sequence of subsegments connecting `endpoint1' to
/// `endpoint2'.  `newmark' is the boundary marker of the segment, assigned
/// to each new splitting vertex and subsegment.
///
/// Note that conformingedge() does not always maintain the conforming
/// Delaunay property.  Once inserted, segments are locked into place;
/// vertices inserted later (to force other segments in) may render these
/// fixed segments non-Delaunay.  The conforming Delaunay property will be
/// restored by enforcequality() by splitting encroached subsegments.
void conformingedge(
  Mesh& m,
  const Arguments& b,
  const Vertex& endpoint1,
  const Vertex& endpoint2,
  const int newmark
);



/// constrainededge()   Force a segment into a constrained Delaunay
///                     triangulation by deleting the triangles it
///                     intersects, and triangulating the polygons that
///                     form on each side of it.
///
/// Generates a single subsegment connecting `endpoint1' to `endpoint2'.
/// The triangle `starttri' has `endpoint1' as its origin.  `newmark' is the
/// boundary marker of the segment.
///
/// To insert a segment, every triangle whose interior intersects the
/// segment is deleted.  The union of these deleted triangles is a polygon
/// (which is not necessarily monotone, but is close enough), which is
/// divided into two polygons by the new segment.  This routine's task is
/// to generate the Delaunay triangulation of these two polygons.
///
/// You might think of this routine's behavior as a two-step process.  The
/// first step is to walk from endpoint1 to endpoint2, flipping each edge
/// encountered.  This step creates a fan of edges connected to endpoint1,
/// including the desired edge to endpoint2.  The second step enforces the
/// Delaunay condition on each side of the segment in an incremental manner:
/// proceeding along the polygon from endpoint1 to endpoint2 (this is done
/// independently on each side of the segment), each vertex is "enforced"
/// as if it had just been inserted, but affecting only the previous
/// vertices.  The result is the same as if the vertices had been inserted
/// in the order they appear on the polygon, so the result is Delaunay.
///
/// In truth, constrainededge() interleaves these two steps.  The procedure
/// walks from endpoint1 to endpoint2, and each time an edge is encountered
/// and flipped, the newly exposed vertex (at the far end of the flipped
/// edge) is "enforced" upon the previously flipped edges, usually affecting
/// only one side of the polygon (depending upon which side of the segment
/// the vertex falls on).
///
/// The algorithm is complicated by the need to handle polygons that are not
/// convex.  Although the polygon is not necessarily monotone, it can be
/// triangulated in a manner similar to the stack-based algorithms for
/// monotone polygons.  For each reflex vertex (local concavity) of the
/// polygon, there will be an inverted triangle formed by one of the edge
/// flips.  (An inverted triangle is one with negative area - that is, its
/// vertices are arranged in clockwise order - and is best thought of as a
/// wrinkle in the fabric of the mesh.)  Each inverted triangle can be
/// thought of as a reflex vertex pushed on the stack, waiting to be fixed
/// later.
///
/// A reflex vertex is popped from the stack when a vertex is inserted that
/// is visible to the reflex vertex.  (However, if the vertex behind the
/// reflex vertex is not visible to the reflex vertex, a new inverted
/// triangle will take its place on the stack.)  These details are handled
/// by the delaunayfixup() routine above.
void constrainededge(
  Mesh& m,
  const Arguments& b,
  const Otri * const starttri,
  const boost::shared_ptr<Vertex>& endpoint2,
  const int newmark
);

double counterclockwise(
  int& m_m_counterclockcount,
  const bool b_m_noexact,
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc
);

/// counterclockwise()   Return a positive value if the points pa, pb, and
///                      pc occur in counterclockwise order; a negative
///                      value if they occur in clockwise order; and zero
///                      if they are collinear.  The result is also a rough
///                      approximation of twice the signed area of the
///                      triangle defined by the three points.
///
/// Uses exact arithmetic if necessary to ensure a correct answer.  The
/// result returned is the determinant of a matrix.  This determinant is
/// computed adaptively, in the sense that exact arithmetic is used only to
/// the degree it is needed to ensure that the returned value has the
/// correct sign.  Hence, this function is usually quite fast, but will run
/// more slowly when the input points are collinear or nearly so.
///
/// See my Robust Predicates paper for details.
double counterclockwiseadapt(
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const double detsum
);

void createeventheap(
  Mesh& m,
  Event *** eventheap,
  Event ** events,
  Event ** freeevents
);


/// delaunay()   Form a Delaunay triangulation.
long delaunay(Mesh& m, const Arguments& b);



/// delaunayfixup()   Enforce the Delaunay condition at an edge, fanning out
///                   recursively from an existing vertex.  Pay special
///                   attention to stacking inverted triangles.
///
/// This is a support routine for inserting segments into a constrained
/// Delaunay triangulation.
///
/// The origin of fixuptri is treated as if it has just been inserted, and
/// the local Delaunay condition needs to be enforced.  It is only enforced
/// in one sector, however, that being the angular range defined by
/// fixuptri.
///
/// This routine also needs to make decisions regarding the "stacking" of
/// triangles.  (Read the description of constrainededge() below before
/// reading on here, so you understand the algorithm.)  If the position of
/// the new vertex (the origin of fixuptri) indicates that the vertex before
/// it on the polygon is a reflex vertex, then "stack" the triangle by
/// doing nothing.  (fixuptri is an inverted triangle, which is how stacked
/// triangles are identified.)
///
/// Otherwise, check whether the vertex before that was a reflex vertex.
/// If so, perform an edge flip, thereby eliminating an inverted triangle
/// (popping it off the stack).  The edge flip may result in the creation
/// of a new inverted triangle, depending on whether or not the new vertex
/// is visible to the vertex three edges behind on the polygon.
///
/// If neither of the two vertices behind the new vertex are reflex
/// vertices, fixuptri and fartri, the triangle opposite it, are not
/// inverted; hence, ensure that the edge between them is locally Delaunay.
///
/// `leftside' indicates whether or not fixuptri is to the left of the
/// segment being inserted.  (Imagine that the segment is pointing up from
/// endpoint1 to endpoint2.)
void delaunayfixup(
  Mesh& m,
  const Arguments& b,
  Otri * const fixuptri,
  const int leftside
);



/// deletevertex()   Delete a vertex from a Delaunay triangulation, ensuring
///                  that the triangulation remains Delaunay.
///
/// The origin of `deltri' is deleted.  The union of the triangles adjacent
/// to this vertex is a polygon, for which the Delaunay triangulation is
/// found.  Two triangles are removed from the mesh.
///
/// Only interior vertices that do not lie on segments or boundaries may be
/// deleted.
void deletevertex(
  Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<Otri>& deltri
);

/// dequeuebadtriang()   Remove a triangle from the front of the queue.
boost::shared_ptr<BadTriang> dequeuebadtriang(Mesh& m);



/// divconqdelaunay()   Form a Delaunay triangulation by the divide-and-
///                     conquer method.
///
/// Sorts the vertices, calls a recursive procedure to triangulate them, and
/// removes the bounding box, setting boundary markers as appropriate.
long divconqdelaunay(
  Mesh& m,
  const Arguments& b
);

/// divconqrecurse()   Recursively form a Delaunay triangulation by the
///                    divide-and-conquer method.
///
/// Recursively breaks down the problem into smaller pieces, which are
/// knitted together by mergehulls().  The base cases (problems of two or
/// three vertices) are handled specially here.
///
/// On completion, `farleft' and `farright' are bounding triangles such that
/// the origin of `farleft' is the leftmost vertex (breaking ties by
/// choosing the highest leftmost vertex), and the destination of
/// `farright' is the rightmost vertex (breaking ties by choosing the
/// lowest rightmost vertex).
///
//Use vertex* instead of iterators for now
void divconqrecurse(
  Mesh& m,
  const Arguments& b,
  const std::vector<boost::shared_ptr<Vertex>>& sortarray,
  //const Vertex * const sortarray,
  //const int vertices,
  const int axis,
  boost::shared_ptr<Otri> farleft,
  boost::shared_ptr<Otri> farright
);

/// dummyinit()   Initialize the triangle that fills "outer space" and the
///               omnipresent subsegment.
///
/// The triangle that fills "outer space," called `dummytri', is pointed to
/// by every triangle and subsegment on a boundary (be it outer or inner) of
/// the triangulation.  Also, `dummytri' points to one of the triangles on
/// the convex hull (until the holes and concavities are carved), making it
/// possible to find a starting triangle for point location.
///
/// The omnipresent subsegment, `dummysub', is pointed to by every triangle
/// or subsegment that doesn't have a full complement of real subsegments
/// to point to.
///
/// `dummytri' and `dummysub' are generally required to fulfill only a few
/// invariants:  their vertices must remain NULL and `dummytri' must always
/// be bonded (at offset zero) to some triangle on the convex hull of the
/// mesh, via a boundary edge.  Otherwise, the connections of `dummytri' and
/// `dummysub' may change willy-nilly.  This makes it possible to avoid
/// writing a good deal of special-case code (in the edge flip, for example)
/// for dealing with the boundary of the mesh, places where no subsegment is
/// present, and so forth.  Other entities are frequently bonded to
/// `dummytri' and `dummysub' as if they were real mesh entities, with no
/// harm done.
void dummyinit(
  Mesh& m
  //const Arguments& b,
  //const int trianglebytes,
  //const int subsegbytes
);

/// enforcequality()   Remove all the encroached subsegments and bad
///                    triangles from the triangulation.
//Adds Steiner points, then splits bad (*) Triangles
// (*) Triangles with angle < min_angle || area > max_area)
void enforcequality(
  Mesh& m
  //const Arguments& b
);


/// fast_expansion_sum_zeroelim()   Sum two expansions, eliminating zero
///                                 components from the output expansion.
/// Sets h = e + f.  See my Robust Predicates paper for details.
/// If round-to-even is used (as with IEEE 754), maintains the strongly
/// nonoverlapping property.  (That is, if e is strongly nonoverlapping, h
/// will be also.)  Does NOT maintain the nonoverlapping or nonadjacent
/// properties.
//fast_expansion_sum_zeroelim(a,b,c): c = std::accumulate(a.begin(),a.end()) + std::accumulate(b.begin(),b.end());
double fast_expansion_sum_zeroelim(
//int fast_expansion_sum_zeroelim(
  //const int elen,
  const std::vector<double>& e,
  //const double * const e,
  //const int flen,
  const std::vector<double>& f
  //const double * const f,
  //std::vector<double>& h
  //double * const h
);



/// findcircumcenter()   Find the circumcenter of a triangle.

/// The result is returned both in terms of x-y coordinates and xi-eta
/// (barycentric) coordinates.  The xi-eta coordinate system is defined in
/// terms of the triangle:  the origin of the triangle is the origin of the
/// coordinate system; the destination of the triangle is one unit along the
/// xi axis; and the apex of the triangle is one unit along the eta axis.
/// This procedure also returns the square of the length of the triangle's
/// shortest edge.
void findcircumcenter(
  int& m_m_circumcentercount,
  int& m_m_counterclockcount,
  //Mesh& m,
  bool b_m_noexact,
  const double b_m_offconstant,
  //const Arguments& b,
  const boost::shared_ptr<Vertex>& torg,
  const boost::shared_ptr<Vertex>& tdest,
  const boost::shared_ptr<Vertex>& tapex,
  boost::shared_ptr<Vertex>& circumcenter,
  double& xi,
  double& eta,
  const int offcenter
);



/// finddirection()   Find the first triangle on the path from one point
///                   to another.

/// Finds the triangle that intersects a line segment drawn from the
/// origin of `searchtri' to the point `searchpoint', and returns the result
/// in `searchtri'.  The origin of `searchtri' does not change, even though
/// the triangle returned may differ from the one passed in.  This routine
/// is used to find the direction to move in to get from one point to
/// another.

/// The return value notes whether the destination or apex of the found
/// triangle is collinear with the two points in question.


FindDirectionResult finddirection(
  Mesh& m,
  const Arguments& b,
  Otri * const searchtri,
  const boost::shared_ptr<Vertex>& searchpoint
);

/// flip()   Transform two triangles to two different triangles by flipping
///          an edge counterclockwise within a quadrilateral.

/// Imagine the original triangles, abc and bad, oriented so that the
/// shared edge ab lies in a horizontal plane, with the vertex b on the left
/// and the vertex a on the right.  The vertex c lies below the edge, and
/// the vertex d lies above the edge.  The `flipedge' handle holds the edge
/// ab of triangle abc, and is directed left, from vertex a to vertex b.

/// The triangles abc and bad are deleted and replaced by the triangles cdb
/// and dca.  The triangles that represent abc and bad are NOT deallocated;
/// they are reused for dca and cdb, respectively.  Hence, any handles that
/// may have held the original triangles are still valid, although not
/// directed as they were before.

/// Upon completion of this routine, the `flipedge' handle holds the edge
/// dc of triangle dca, and is directed down, from vertex d to vertex c.
/// (Hence, the two triangles have rotated counterclockwise.)

/// WARNING:  This transformation is geometrically valid only if the
/// quadrilateral adbc is convex.  Furthermore, this transformation is
/// valid only if there is not a subsegment between the triangles abc and
/// bad.  This routine does not check either of these preconditions, and
/// it is the responsibility of the calling routine to ensure that they are
/// met.  If they are not, the streets shall be filled with wailing and
/// gnashing of teeth.
void flip(
  const Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<Otri>& flipedge
);

/// formskeleton()   Create the segments of a triangulation, including PSLG
///                  segments and edges on the convex hull.
///
/// The PSLG segments are read from a .poly file.  The return value is the
/// number of segments in the file.
//RJCB: ?creates all Edges
//void formskeleton(
//  Mesh& m,
//  const Arguments& b,
//  //FILE * const polyfile,
//  const std::string& polyfilename
//);

SplayNode * frontlocate(
  Mesh& m,
  SplayNode * splayroot,
  const Otri * const bottommost,
  const Vertex& searchvertex,
  Otri * const searchtri,
  int * const farright
);

/// getvertex()   Get a specific vertex, by number, from the list.
///
/// The first vertex is number 'firstnumber'.
///
/// Note that this takes O(n) time (with a small constant, if VERTEXPERBLOCK
/// is large).  I don't care to take the trouble to make it work in constant
/// time.
/*
Vertex getvertex(
  const std::vector<Vertex>& vertices, //m_vertices
  const Arguments& b,
  const int number
);
*/


/// highorder()   Create extra nodes for quadratic subparametric elements.
/*
void highorder(
  Mesh& m,
  const Arguments& b
);
*/

double incircle(
  int& m_m_incirclecount,
  //Mesh& m,
  const bool b_m_noexact,
  //const Arguments& b,
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const boost::shared_ptr<Vertex>& pd
);



/// incircle()   Return a positive value if the point pd lies inside the
///              circle passing through pa, pb, and pc; a negative value if
///              it lies outside; and zero if the four points are cocircular.*/
///              The points pa, pb, and pc must be in counterclockwise
///              order, or the sign of the result will be reversed.

/// Uses exact arithmetic if necessary to ensure a correct answer.  The
/// result returned is the determinant of a matrix.  This determinant is
/// computed adaptively, in the sense that exact arithmetic is used only to
/// the degree it is needed to ensure that the returned value has the
/// correct sign.  Hence, this function is usually quite fast, but will run
/// more slowly when the input points are cocircular or nearly so.

/// See my Robust Predicates paper for details.


double incircleadapt(
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const boost::shared_ptr<Vertex>& pd,
  const double permanent
);



/// Form a Delaunay triangulation by incrementally
///                         inserting vertices.
///
/// Returns the number of edges on the convex hull of the triangulation.
int incrementaldelaunay(Mesh& m,const Arguments& b);



/// infecthull()   Virally infect all of the triangles of the convex hull
///                that are not protected by subsegments.  Where there are
///                subsegments, set boundary markers as appropriate.
void infecthull(
  Mesh& m,
  const Arguments& b
);

/// initializetrisubpools()   Calculate the sizes of the triangle and
///                           subsegment data structures and initialize
///                           their memory pools.
/// This routine also computes the `highorderindex', `elemattribindex', and
/// `areaboundindex' indices used to find values within each triangle.
/*
void initializetrisubpools(
  Mesh& m,
  const Arguments& b
);
*/

/// initializevertexpool()   Calculate the size of the vertex data structure
///                          and initialize its memory pool.
///
/// This routine also computes the `vertexmarkindex' and `vertex2triindex'
/// indices used to find values within each vertex.
/*
void initializevertexpool(
  Mesh& m,
  const Arguments& b
);
*/

/// insertsegment()   Insert a PSLG segment into a triangulation.
void insertsegment(
  Mesh& m,
  const Arguments& b,
  Vertex endpoint1,
  Vertex endpoint2,
  const int newmark
);

/// insertsubseg()   Create a new subsegment and insert it between two
///                  triangles.
/// The new subsegment is inserted at the edge described by the handle
/// `tri'.  Its vertices are properly initialized.  The marker `subsegmark'
/// is applied to the subsegment and, if appropriate, its vertices.
void insertsubseg(
  Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<Otri>& tri,
  const int subsegmark
);

/// insertvertex()   Insert a vertex into a Delaunay triangulation,
///                  performing flips as necessary to maintain the Delaunay
///                  property.
/// The point `insertvertex' is located.  If `searchtri.tri' is not NULL,
/// the search for the containing triangle begins from `searchtri'.  If
/// `searchtri.tri' is NULL, a full point location procedure is called.
/// If `insertvertex' is found inside a triangle, the triangle is split into
/// three; if `insertvertex' lies on an edge, the edge is split in two,
/// thereby splitting the two adjacent triangles into four.  Edge flips are
/// used to restore the Delaunay property.  If `insertvertex' lies on an
/// existing vertex, no action is taken, and the value DUPLICATEVERTEX is
/// returned.  On return, `searchtri' is set to a handle whose origin is the
/// existing vertex.
///
/// Normally, the parameter `splitseg' is set to NULL, implying that no
/// subsegment should be split.  In this case, if `insertvertex' is found to
/// lie on a segment, no action is taken, and the value VIOLATINGVERTEX is
/// returned.  On return, `searchtri' is set to a handle whose primary edge
/// is the violated subsegment.
///
/// If the calling routine wishes to split a subsegment by inserting a
/// vertex in it, the parameter `splitseg' should be that subsegment.  In
/// this case, `searchtri' MUST be the triangle handle reached by pivoting
/// from that subsegment; no point location is done.
///
/// `segmentflaws' and `triflaws' are flags that indicate whether or not
/// there should be checks for the creation of encroached subsegments or bad
/// quality triangles.  If a newly inserted vertex encroaches upon
/// subsegments, these subsegments are added to the list of subsegments to
/// be split if `segmentflaws' is set.  If bad triangles are created, these
/// are added to the queue if `triflaws' is set.
///
/// If a duplicate vertex or violated segment does not prevent the vertex
/// from being inserted, the return value will be ENCROACHINGVERTEX if the
/// vertex encroaches upon a subsegment (and checking is enabled), or
/// SUCCESSFULVERTEX otherwise.  In either case, `searchtri' is set to a
/// handle whose origin is the newly inserted vertex.
///
/// insertvertex() does not use flip() for reasons of speed; some
/// information can be reused from edge flip to edge flip, like the
/// locations of subsegments.
InsertVertexResult insertvertex(
  Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<Vertex>& newvertex,
  boost::shared_ptr<Otri>& searchtri,
  boost::shared_ptr<Osub>& splitseg,
  const int segmentflaws,
  const bool triflaws
);

/// locate()   Find a triangle or edge containing a given point.
///
/// Searching begins from one of:  the input `searchtri', a recently
/// encountered triangle `recenttri', or from a triangle chosen from a
/// random sample.  The choice is made by determining which triangle's
/// origin is closest to the point we are searching for.  Normally,
/// `searchtri' should be a handle on the convex hull of the triangulation.
///
/// Details on the random sampling method can be found in the Mucke, Saias,
/// and Zhu paper cited in the header of this code.
///
/// On completion, `searchtri' is a triangle that contains `searchpoint'.
///
/// Returns ONVERTEX if the point lies on an existing vertex.  `searchtri'
/// is a handle whose origin is the existing vertex.
///
/// Returns ONEDGE if the point lies on a mesh edge.  `searchtri' is a
/// handle whose primary edge is the edge on which the point lies.
///
/// Returns INTRIANGLE if the point lies strictly within a triangle.
/// `searchtri' is a handle on the triangle that contains the point.
///
/// Returns OUTSIDE if the point lies outside the mesh.  `searchtri' is a
/// handle whose primary edge the point is to the right of.  This might
/// occur when the circumcenter of a triangle falls just slightly outside
/// the mesh due to floating-point roundoff error.  It also occurs when
/// seeking a hole or region point that a foolish user has placed outside
/// the mesh.
///
/// WARNING:  This routine is designed for convex triangulations, and will
/// not generally work after the holes and concavities have been carved.


LocateResult locate(
  Mesh& m,
  int& m_m_counterclockcount,
  const Arguments& b,
  const boost::shared_ptr<Vertex>& searchpoint,
  boost::shared_ptr<Otri>& searchtri
);

///Create a new subsegment with orientation zero.
boost::shared_ptr<Osub> makesubseg(
//void makesubseg(
  //Mesh& m,
  boost::shared_ptr<Triangle>& m_m_dummytri,
  boost::shared_ptr<Edge>& m_m_dummysub
  //Osub& newsubseg
);

///Create a new triangle with orientation zero.
boost::shared_ptr<ribi::tricpp::Otri> maketriangle(
  //Mesh& m,
  const boost::shared_ptr<Triangle>& m_m_dummytri,
  const boost::shared_ptr<Edge>& m_m_dummysub,
  const int m_m_eextras,
  //const Arguments& b,
  const bool b_m_vararea
  //boost::shared_ptr<Otri>& newotri
);



/// makevertexmap()   Construct a mapping from vertices to triangles to
///                   improve the speed of point location for segment
///                   insertion.
///
/// Traverses all the triangles, and provides each corner of each triangle
/// with a pointer to that triangle.  Of course, pointers will be
/// overwritten by other pointers because (almost) each vertex is a corner
/// of several triangles, but in the end every vertex will point to some
/// triangle that contains it.
void makevertexmap(
  Mesh& m
  //const Arguments& b
);

///Cover the convex hull of a triangulation with subsegments.
void markhull(
  Mesh& m,
  const Arguments& b
);

/// Merge two adjacent Delaunay triangulations into a
///                single Delaunay triangulation.
///
/// This is similar to the algorithm given by Guibas and Stolfi, but uses
/// a triangle-based, rather than edge-based, data structure.
///
/// The algorithm walks up the gap between the two triangulations, knitting
/// them together.  As they are merged, some of their bounding triangles
/// are converted into real triangles of the triangulation.  The procedure
/// pulls each hull's bounding triangles apart, then knits them together
/// like the teeth of two gears.  The Delaunay property determines, at each
/// step, whether the next "tooth" is a bounding triangle of the left hull
/// or the right.  When a bounding triangle becomes real, its apex is
/// changed from NULL to a real vertex.
///
/// Only two new triangles need to be allocated.  These become new bounding
/// triangles at the top and bottom of the seam.  They are used to connect
/// the remaining bounding triangles (those that have not been converted
/// into real triangles) into a single fan.
///
/// On entry, `farleft' and `innerleft' are bounding triangles of the left
/// triangulation.  The origin of `farleft' is the leftmost vertex, and
/// the destination of `innerleft' is the rightmost vertex of the
/// triangulation.  Similarly, `innerright' and `farright' are bounding
/// triangles of the right triangulation.  The origin of `innerright' and
/// destination of `farright' are the leftmost and rightmost vertices.
///
/// On completion, the origin of `farleft' is the leftmost vertex of the
/// merged triangulation, and the destination of `farright' is the rightmost
/// vertex.
void mergehulls(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<Otri> farleft,
  boost::shared_ptr<Otri> innerleft,
  boost::shared_ptr<Otri> innerright,
  boost::shared_ptr<Otri> farright,
  const int axis
);

/// Return a positive value if the point pd is incompatible
///                with the circle or plane passing through pa, pb, and pc
///                (meaning that pd is inside the circle or below the
///                plane); a negative value if it is compatible; and zero if
///                the four points are cocircular/coplanar.  The points pa,
///                pb, and pc must be in counterclockwise order, or the sign
///                of the result will be reversed.
///
/// If the -w switch is used, the points are lifted onto the parabolic
/// lifting map, then they are dropped according to their weights, then the
/// 3D orientation test is applied.  If the -W switch is used, the points'
/// heights are already provided, so the 3D orientation test is applied
/// directly.  If neither switch is used, the incircle test is applied.
double nonregular(
  //Mesh& m,
  int& m_m_incirclecount,
  //const Arguments& b,
  //const bool b_m_noexact,
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const boost::shared_ptr<Vertex>& pd
);

/// Number the vertices.
///
/// Each vertex is assigned a marker equal to its number.
///
/// Used when writenodes() is not called because no .node file is written.
void numbernodes(Mesh& m, const Arguments& b);

double orient3d(
  //Mesh& m,
  int& m_m_orient3dcount,
  const bool b_m_noexact,
  //const Arguments& b,
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const boost::shared_ptr<Vertex>& pd,
  const double aheight,
  const double bheight,
  const double cheight,
  const double dheight
);



/// Return a positive value if the point pd lies below the
///              plane passing through pa, pb, and pc; "below" is defined so
///              that pa, pb, and pc appear in counterclockwise order when
///              viewed from above the plane.  Returns a negative value if
///              pd lies above the plane.  Returns zero if the points are
///              coplanar.  The result is also a rough approximation of six
///              times the signed volume of the tetrahedron defined by the
///              four points.
///
/// Uses exact arithmetic if necessary to ensure a correct answer.  The
/// result returned is the determinant of a matrix.  This determinant is
/// computed adaptively, in the sense that exact arithmetic is used only to
/// the degree it is needed to ensure that the returned value has the
/// correct sign.  Hence, this function is usually quite fast, but will run
/// more slowly when the input points are coplanar or nearly so.
///
/// See my Robust Predicates paper for details.
double orient3dadapt(
  const boost::shared_ptr<Vertex>& pa,
  const boost::shared_ptr<Vertex>& pb,
  const boost::shared_ptr<Vertex>& pc,
  const boost::shared_ptr<Vertex>& pd,
  const double aheight,
  const double bheight,
  const double cheight,
  const double dheight,
  const double permanent
);



/// Spread the virus from all infected triangles to any neighbors
///            not protected by subsegments.  Delete all infected triangles.
///
/// This is the procedure that actually creates holes and concavities.
///
/// This procedure operates in two phases.  The first phase identifies all
/// the triangles that will die, and marks them as infected.  They are
/// marked to ensure that each triangle is added to the virus pool only
/// once, so the procedure will terminate.
///
/// The second phase actually eliminates the infected triangles.  It also
/// eliminates orphaned vertices.
void plague(
  Mesh& m,
  const Arguments& b
);



/// Find a triangle or edge containing a given point.
///
/// Begins its search from `searchtri'.  It is important that `searchtri'
/// be a handle with the property that `searchpoint' is strictly to the left
/// of the edge denoted by `searchtri', or is collinear with that edge and
/// does not intersect that edge.  (In particular, `searchpoint' should not
/// be the origin or destination of that edge.)
///
/// These conditions are imposed because preciselocate() is normally used in
/// one of two situations:
///
/// (1)  To try to find the location to insert a new point.  Normally, we
///      know an edge that the point is strictly to the left of.  In the
///      incremental Delaunay algorithm, that edge is a bounding box edge.
///      In Ruppert's Delaunay refinement algorithm for quality meshing,
///      that edge is the shortest edge of the triangle whose circumcenter
///      is being inserted.
///
/// (2)  To try to find an existing point.  In this case, any edge on the
///      convex hull is a good starting edge.  You must screen out the
///      possibility that the vertex sought is an endpoint of the starting
///      edge before you call preciselocate().
///
/// On completion, `searchtri' is a triangle that contains `searchpoint'.
///
/// This implementation differs from that given by Guibas and Stolfi.  It
/// walks from triangle to triangle, crossing an edge only if `searchpoint'
/// is on the other side of the line containing that edge.  After entering
/// a triangle, there are two edges by which one can leave that triangle.
/// If both edges are valid (`searchpoint' is on the other side of both
/// edges), one of the two is chosen by drawing a line perpendicular to
/// the entry edge (whose endpoints are `forg' and `fdest') passing through
/// `fapex'.  Depending on which side of this perpendicular `searchpoint'
/// falls on, an exit edge is chosen.
///
/// This implementation is empirically faster than the Guibas and Stolfi
/// point location routine (which I originally used), which tends to spiral
/// in toward its target.
///
/// Returns ONVERTEX if the point lies on an existing vertex.  `searchtri'
/// is a handle whose origin is the existing vertex.
///
/// Returns ONEDGE if the point lies on a mesh edge.  `searchtri' is a
/// handle whose primary edge is the edge on which the point lies.
///
/// Returns INTRIANGLE if the point lies strictly within a triangle.
/// `searchtri' is a handle on the triangle that contains the point.
///
/// Returns OUTSIDE if the point lies outside the mesh.  `searchtri' is a
/// handle whose primary edge the point is to the right of.  This might
/// occur when the circumcenter of a triangle falls just slightly outside
/// the mesh due to floating-point roundoff error.  It also occurs when
/// seeking a hole or region point that a foolish user has placed outside
/// the mesh.
///
/// If `stopatsubsegment' is nonzero, the search will stop if it tries to
/// walk through a subsegment, and will return OUTSIDE.
///
/// WARNING:  This routine is designed for convex triangulations, and will
/// not generally work after the holes and concavities have been carved.
/// However, it can still be used to find the circumcenter of a triangle, as
/// long as the search is begun from the triangle in question.
LocateResult preciselocate(
  //Mesh& m,
  const bool m_m_checksegments,
  int& m_m_counterclockcount,
  //const Arguments& b,
  const bool b_m_noexact,
  const boost::shared_ptr<Vertex>& searchpoint,
  const boost::shared_ptr<Otri>& searchtri,
  const int stopatsubsegment
);

/// printsubseg()   Print out the details of an oriented subsegment.
///
/// I originally wrote this procedure to simplify debugging; it can be
/// called directly from the debugger, and presents information about an
/// oriented subsegment in digestible form.  It's also used when the highest
/// level of verbosity (`-VVV') is specified.
/*
void printsubseg(
  const SubSeg * const m_dummysub,
  const Triangle * const m_dummytri,
  const Osub& s
);
*/

/// printtriangle()   Print out the details of an oriented triangle.
///
/// I originally wrote this procedure to simplify debugging; it can be
/// called directly from the debugger, and presents information about an
/// oriented triangle in digestible form.  It's also used when the
/// highest level of verbosity (`-VVV') is specified.
/*
void printtriangle(
  const Mesh& m,
  const Arguments& b,
  const Otri * const t
);
*/

void quality_statistics(
  Mesh& m,
  const Arguments& b
);




/// readholes()   Read the holes, and possibly regional attributes and area
///               constraints, from a .poly file.
void readholes(
  //const Mesh * const /* m */,
  const Arguments& b,
  //FILE * const polyfile,
  const std::string& polyfilename,
  //const char * const polyfilename,
  std::vector<double >& hlist, //hole list
  //double ** const hlist,
  //int * const holes,
  std::vector<double>& rlist //region list
  //double ** const rlist,
  //int *regions
);



/// readnodes()   Read the vertices from a file, which may be a .node or
///               .poly file.
std::vector<boost::shared_ptr<Vertex>> ReadVertices(
//void ReadNodes(
  //Mesh& m,
  //const Arguments& b,
  const std::string& polyfilename
);

/// reconstruct()   Reconstruct a triangulation from its .ele (and possibly
///                 .poly) file.  Used when the -r switch is used.
///
/// Reads an .ele file and reconstructs the original mesh.  If the -p switch
/// is used, this procedure will also read a .poly file and reconstruct the
/// subsegments of the original mesh.  If the -a switch is used, this
/// procedure will also read an .area file and set a maximum area constraint
/// on each triangle.
///
/// Vertices that are not corners of triangles, such as nodes on edges of
/// subparametric elements, are discarded.
///
/// This routine finds the adjacencies between triangles (and subsegments)
/// by forming one stack of triangles for each vertex.  Each triangle is on
/// three different stacks simultaneously.  Each triangle's subsegment
/// pointers are used to link the items in each stack.  This memory-saving
/// feature makes the code harder to read.  The most important thing to keep
/// in mind is that each triangle is removed from a stack precisely when
/// the corresponding pointer is adjusted to refer to a subsegment rather
/// than the next triangle of the stack.
long ReadSubSegs(
  std::vector<boost::shared_ptr<Vertex>>& vertices,
  //Mesh& m,
  //const Arguments& b,
  const std::string& elefilename,
  //const std::string& areafilename,
  const std::string& polyfilename
  //FILE * const polyfile
);



/// regionplague()   Spread regional attributes and/or area constraints
///                  (from a .poly file) throughout the mesh.
///
/// This procedure operates in two phases.  The first phase spreads an
/// attribute and/or an area constraint through a (segment-bounded) region.
/// The triangles are marked to ensure that each triangle is added to the
/// virus pool only once, so the procedure will terminate.
///
/// The second phase uninfects all infected triangles, returning them to
/// normal.
void regionplague(
  Mesh& m,
  const Arguments& b,
  const double attribute,
  const double area
);



/// removebox()   Remove the "infinite" bounding triangle, setting boundary
///               markers as appropriate.
///
/// The triangular bounding box has three boundary triangles (one for each
/// side of the bounding box), and a bunch of triangles fanning out from
/// the three bounding box vertices (one triangle for each edge of the
/// convex hull of the inner mesh).  This routine removes these triangles.
///
/// Returns the number of edges on the convex hull of the triangulation.
long removebox(
  Mesh& m,
  const Arguments& b
);

long removeghosts(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<Otri> startghost
);

bool rightofhyperbola(
  //Mesh& m,
  int& m_m_hyperbolacount,
  const Otri * const fronttri,
  const Vertex& newsite
);



/// scale_expansion_zeroelim()   Multiply an expansion by a scalar,
///                              eliminating zero components from the
///                              output expansion.
///
/// Sets h = be.  See my Robust Predicates paper for details.
///
/// Maintains the nonoverlapping property.  If round-to-even is used (as
/// with IEEE 754), maintains the strongly nonoverlapping and nonadjacent
/// properties as well.  (That is, if e has one of these properties, so
/// will h.)
///
//scale_expansion_zeroelim(v,s): return std::accumulate(v.begin(),v.end()) * s

double scale_expansion_zeroelim(
//void scale_expansion_zeroelim(
//bool scale_expansion_zeroelim(
  //const int elen,
  //const double * const e,
  const std::vector<double>& e,
  const double b
  //double& h
  //double * const h
);

/// scoutsegment()   Scout the first triangle on the path from one endpoint
///                  to another, and check for completion (reaching the
///                  second endpoint), a collinear vertex, or the
///                  intersection of two segments.
///
/// Returns one if the entire segment is successfully inserted, and zero if
/// the job must be finished by conformingedge() or constrainededge().
///
/// If the first triangle on the path has the second endpoint as its
/// destination or apex, a subsegment is inserted and the job is done.
///
/// If the first triangle on the path has a destination or apex that lies on
/// the segment, a subsegment is inserted connecting the first endpoint to
/// the collinear vertex, and the search is continued from the collinear
/// vertex.
///
/// If the first triangle on the path has a subsegment opposite its origin,
/// then there is a segment that intersects the segment being inserted.
/// Their intersection vertex is inserted, splitting the subsegment.
int scoutsegment(
  Mesh& m,
  const Arguments& b,
  Otri * const searchtri,
  const Vertex& endpoint2,
  const int newmark
);

/// segmentintersection()   Find the intersection of an existing segment
///                         and a segment that is being inserted.  Insert
///                         a vertex at the intersection, splitting an
///                         existing subsegment.
///
/// The segment being inserted connects the apex of splittri to endpoint2.
/// splitsubseg is the subsegment being split, and MUST adjoin splittri.
/// Hence, endpoints of the subsegment being split are the origin and
/// destination of splittri.
///
/// On completion, splittri is a handle having the newly inserted
/// intersection point as its origin, and endpoint1 as its destination.
void segmentintersection(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<Otri>& splittri,
  boost::shared_ptr<Osub>& splitsubseg,
  const boost::shared_ptr<Vertex>& endpoint2
);

boost::shared_ptr<SplayNode> splay(
  Mesh& m,
  boost::shared_ptr<SplayNode>& splaytree,
  const boost::shared_ptr<Vertex>& searchpoint,
  boost::shared_ptr<Otri>& searchtri
);

boost::shared_ptr<SplayNode> splayinsert(
  Mesh& m,
  boost::shared_ptr<SplayNode> splayroot,
  boost::shared_ptr<Otri> newkey,
  const boost::shared_ptr<Vertex>& searchpoint
);

/// splitencsegs()   Split all the encroached subsegments.
///
/// Each encroached subsegment is repaired by splitting it - inserting a
/// vertex at or near its midpoint.  Newly inserted vertices may encroach
/// upon other subsegments; these are also repaired.
//
/// `triflaws' is a flag that specifies whether one should take note of new
/// bad triangles that result from inserting vertices to repair encroached
/// subsegments.
void splitencsegs(
  Mesh& m,
  const Arguments& b,
  const int triflaws
);

/// splittriangle()   Inserts a vertex at the circumcenter of a triangle.
///                   Deletes the newly inserted vertex if it encroaches
///                   upon a segment.
void splittriangle(
  Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<BadTriang>& badtri
);

/// statistics()   Print all sorts of cool facts.
/*
void statistics(
  Mesh& m,
  const Arguments& b
);
*/
/// subsegdealloc()   Deallocate space for a subsegment, marking it dead.
void subsegdealloc(
  Mesh& m,
  boost::shared_ptr<Edge>& dyingsubseg
);

/// subsegtraverse()   Traverse the subsegments, skipping dead ones.
//SubSeg *subsegtraverse(Mesh& m);

long sweeplinedelaunay(
  Mesh& m,
  const Arguments& b
);

/// tallyencs()   Traverse the entire list of subsegments, and check each
///               to see if it is encroached.  If so, add it to the list.
void tallyencs(
  Mesh& m,
  const Arguments& b
);


/// tallyfaces()   Test every triangle in the mesh for quality measures.
void tallyfaces(Mesh& m,const Arguments& b);

/// testtriangle()   Test a triangle for quality and size.
///
/// Tests a triangle to see if it satisfies the minimum angle condition and
/// the maximum area condition.  Triangles that aren't up to spec are added
/// to the bad triangle queue.
void testtriangle(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<Otri>& testtri
);



/// main() or triangulate()   Gosh, do everything.
///
/// The sequence is roughly as follows.  Many of these steps can be skipped,
/// depending on the command line switches.
///
/// - Initialize constants and parse the command line.
/// - Read the vertices from a file and either
///   - triangulate them (no -r), or
///   - read an old mesh from files and reconstruct it (-r).
/// - Insert the PSLG segments (-p), and possibly segments on the convex
///     hull (-c).
/// - Read the holes (-p), regional attributes (-pA), and regional area
///     constraints (-pa).  Carve the holes and concavities, and spread the
///     regional attributes and area constraints.
/// - Enforce the constraints on minimum angle (-q) and maximum area (-a).
///     Also enforce the conforming Delaunay property (-q and -a).
/// - Compute the number of edges in the resulting mesh.
/// - Promote the mesh's linear triangles to higher order elements (-o).
/// - Write the output files and print the statistics.
/// - Check the consistency and Delaunay property of the mesh (-C).
int triangle_cpp_main(
  const std::vector<std::string>& args
);

/// triangledealloc()   Deallocate space for a triangle, marking it dead.
void triangledealloc(
  std::vector<boost::shared_ptr<Triangle>>& m_m_triangles,
  //Mesh& m,
  boost::shared_ptr<Triangle>& dyingtriangle
);

/// triangledeinit()   Free all remaining allocated memory.
/*
void triangledeinit(
  Mesh& m,
  const Arguments& b
);
*/

/// triangletraverse()   Traverse the triangles, skipping dead ones.
//Triangle * triangletraverse(Mesh& m);

void triangulate(
  const char * const ,
  const TriangulateIo * const ,
  const TriangulateIo * const ,
  const TriangulateIo * const
);



/// triangulatepolygon()   Find the Delaunay triangulation of a polygon that
///                        has a certain "nice" shape.  This includes the
///                        polygons that result from deletion of a vertex or
///                        insertion of a segment.
///
/// This is a conceptually difficult routine.  The starting assumption is
/// that we have a polygon with n sides.  n - 1 of these sides are currently
/// represented as edges in the mesh.  One side, called the "base", need not
/// be.
///
/// Inside the polygon is a structure I call a "fan", consisting of n - 1
/// triangles that share a common origin.  For each of these triangles, the
/// edge opposite the origin is one of the sides of the polygon.  The
/// primary edge of each triangle is the edge directed from the origin to
/// the destination; note that this is not the same edge that is a side of
/// the polygon.  `firstedge' is the primary edge of the first triangle.
/// From there, the triangles follow in counterclockwise order about the
/// polygon, until `lastedge', the primary edge of the last triangle.
/// `firstedge' and `lastedge' are probably connected to other triangles
/// beyond the extremes of the fan, but their identity is not important, as
/// long as the fan remains connected to them.
///
/// Imagine the polygon oriented so that its base is at the bottom.  This
/// puts `firstedge' on the far right, and `lastedge' on the far left.
/// The right vertex of the base is the destination of `firstedge', and the
/// left vertex of the base is the apex of `lastedge'.
///
/// The challenge now is to find the right sequence of edge flips to
/// transform the fan into a Delaunay triangulation of the polygon.  Each
/// edge flip effectively removes one triangle from the fan, committing it
/// to the polygon.  The resulting polygon has one fewer edge.  If `doflip'
/// is set, the final flip will be performed, resulting in a fan of one
/// (useless?) triangle.  If `doflip' is not set, the final flip is not
/// performed, resulting in a fan of two triangles, and an unfinished
/// triangular polygon that is not yet filled out with a single triangle.
/// On completion of the routine, `lastedge' is the last remaining triangle,
/// or the leftmost of the last two.
///
/// Although the flips are performed in the order described above, the
/// decisions about what flips to perform are made in precisely the reverse
/// order.  The recursive triangulatepolygon() procedure makes a decision,
/// uses up to two recursive calls to triangulate the "subproblems"
/// (polygons with fewer edges), and then performs an edge flip.
///
/// The "decision" it makes is which vertex of the polygon should be
/// connected to the base.  This decision is made by testing every possible
/// vertex.  Once the best vertex is found, the two edges that connect this
/// vertex to the base become the bases for two smaller polygons.  These
/// are triangulated recursively.  Unfortunately, this approach can take
/// O(n^2) time not only in the worst case, but in many common cases.  It's
/// rarely a big deal for vertex deletion, where n is rarely larger than
/// ten, but it could be a big deal for segment insertion, especially if
/// there's a lot of long segments that each cut many triangles.  I ought to
/// code a faster algorithm some day.
///
/// The `edgecount' parameter is the number of sides of the polygon,
/// including its base.  `triflaws' is a flag that determines whether the
/// new triangles should be tested for quality, and enqueued if they are
/// bad.
void triangulatepolygon(
  Mesh& m,
  const Arguments& b,
  boost::shared_ptr<Otri> firstedge,
  boost::shared_ptr<Otri> lastedge,
  const int edgecount,
  const int doflip,
  const int triflaws
);



/// undovertex()   Undo the most recent vertex insertion.
//
/// Walks through the list of transformations (flips and a vertex insertion)
/// in the reverse of the order in which they were done, and undoes them.
/// The inserted vertex is removed from the triangulation and deallocated.
/// Two triangles (possibly just one) are also deallocated.
void undovertex(
  Mesh& m,
  const Arguments& b
);

/// unflip()   Transform two triangles to two different triangles by
///            flipping an edge clockwise within a quadrilateral.  Reverses
///            the flip() operation so that the data structures representing
///            the triangles are back where they were before the flip().
///
/// Imagine the original triangles, abc and bad, oriented so that the
/// shared edge ab lies in a horizontal plane, with the vertex b on the left
/// and the vertex a on the right.  The vertex c lies below the edge, and
/// the vertex d lies above the edge.  The `flipedge' handle holds the edge
/// ab of triangle abc, and is directed left, from vertex a to vertex b.
///
/// The triangles abc and bad are deleted and replaced by the triangles cdb
/// and dca.  The triangles that represent abc and bad are NOT deallocated;
/// they are reused for cdb and dca, respectively.  Hence, any handles that
/// may have held the original triangles are still valid, although not
/// directed as they were before.
///
/// Upon completion of this routine, the `flipedge' handle holds the edge
/// cd of triangle cdb, and is directed up, from vertex c to vertex d.
/// (Hence, the two triangles have rotated clockwise.)
///
/// WARNING:  This transformation is geometrically valid only if the
/// quadrilateral adbc is convex.  Furthermore, this transformation is
/// valid only if there is not a subsegment between the triangles abc and
/// bad.  This routine does not check either of these preconditions, and
/// it is the responsibility of the calling routine to ensure that they are
/// met.  If they are not, the streets shall be filled with wailing and
/// gnashing of teeth.
void unflip(
  const Mesh& m,
  const Arguments& b,
  const boost::shared_ptr<Otri>& flipedge
);

/// vertexdealloc()   Deallocate space for a vertex, marking it dead.
void vertexdealloc(
  std::vector<boost::shared_ptr<Vertex>>& vertices,
  boost::shared_ptr<Vertex>& dyingvertex
);

//void vertexdealloc(
//  std::vector<Vertex>& vertices,
//  Vertex& dyingvertex
//);

/// vertexmedian()   An order statistic algorithm, almost.  Shuffles an
///                  array of vertices so that the first `median' vertices
///                  occur lexicographically before the remaining vertices.
///
/// Uses the x-coordinate as the primary key if axis == 0; the y-coordinate
/// if axis == 1.  Very similar to the vertexsort() procedure, but runs in
/// randomized linear time.
void vertexmedian(
  std::vector<Vertex>& vertices,
  //Vertex * const sortarray,
  const int arraysize,
  const int median,
  const int axis
);

/// vertexsort()   Sort an array of vertices by x-coordinate, using the
///                y-coordinate as a secondary key.
///
/// Uses quicksort.  Randomized O(n log n) time.  No, I did not make any of
/// the usual quicksort mistakes.
//Use vertex*, because a quicksort is used
/*
void vertexsort(
  Vertex * const sortarray,
  const int arraysize
);
*/
/// writeedges()   Write the edges to an .edge file.
void writeedges(
  Mesh& m,
  const Arguments& b,
  const std::string& edgefilename,
  const std::vector<std::string>& args
);

/// writeelements()   Write the triangles to an .ele file.
void writeelements(
  Mesh& m,
  const Arguments& b,
  const std::string& elefilename,
  const std::vector<std::string>& args
);

void writeneighbors(
  Mesh& m,
  const Arguments& b,
  const std::string& neighborfilename,
  const std::vector<std::string>& args
);

/// writenodes()   Number the vertices and write them to a .node file.
///
/// To save memory, the vertex numbers are written over the boundary markers
/// after the vertices are written to a file.
void writenodes(
  Mesh& m,
  const Arguments& b,
  const std::string& nodefilename,
  const std::vector<std::string>& args
);

/// writeoff()   Write the triangulation to an .off file.
/// OFF stands for the Object File Format, a format used by the Geometry
/// Center's Geomview package.
void writeoff(
  Mesh& m,
  const Arguments& b,
  const std::string& offfilename,
  const std::vector<std::string>& args
);

/// writepoly()   Write the segments and holes to a .poly file.
void writepoly(
  Mesh& m,
  const Arguments& b,
  const std::string& polyfilename,
  const std::vector<double>& holes,
  //const double * const holelist,
  //const int holes,
  const std::vector<double>& regions,
  //const double * const regionlist,
  //const int regions,
  const std::vector<std::string>& args
);

/// writevoronoi()   Write the Voronoi diagram to a .v.node and .v.edge
///                  file.
///
/// The Voronoi diagram is the geometric dual of the Delaunay triangulation.
/// Hence, the Voronoi vertices are listed by traversing the Delaunay
/// triangles, and the Voronoi edges are listed by traversing the Delaunay
/// edges.
///
/// WARNING:  In order to assign numbers to the Voronoi vertices, this
/// procedure messes up the subsegments or the extra nodes of every
/// element.  Hence, you should call this procedure last.
void writevoronoi(
  Mesh& m,
  const Arguments& b,
  const std::string& vnodefilename,
  const std::string& vedgefilename,
  const std::vector<std::string>& args
);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLE_CPP_H
