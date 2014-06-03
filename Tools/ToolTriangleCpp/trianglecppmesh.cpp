#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppmesh.h"

#include <cassert>

#include "trianglecppbadsubseg.h"
#include "trianglecppdefines.h"
#include "trianglecppglobals.h"
#include "trianglecppedge.h"
#pragma GCC diagnostic pop

ribi::tricpp::Mesh::Mesh(
  const ArgumentsPtr& arguments,
  const Edges& edges,
  const Triangles& triangles,
  const Vertices& vertices
)
  : m_arguments(arguments),
    m_edges(edges),
    m_triangles(triangles),
    m_vertices(vertices)
{

}


#ifdef TRIANGLECPP_REALLY_USE_THIS_20140603
ribi::tricpp::Mesh::Mesh()
  :
    //m_areaboundindex{0},
    m_badsubsegs{},
    m_badtriangles{},
    m_checkquality{0},
    m_checksegments{0},
    m_circletopcount{0},
    m_circumcentercount{0},
    m_counterclockcount{0},
    //m_do_readnodefile{false},
    m_dummysub{},
    //m_dummysubbase{nullptr},
    m_dummytri{},
    //m_dummytribase{nullptr},
    m_edges{0},
    m_eextras{0},
    m_elemattribindex{0},
    m_firstnonemptyq{0},
    m_flipstackers{},
    m_holes{0},
    m_hullsize{0},
    m_hyperbolacount{0},
    m_incirclecount{0},
    m_inelements{0},
    m_infvertex1{},
    m_infvertex2{},
    m_infvertex3{},
    m_insegments{0},
    m_invertices{0},
    m_lastflip{},
    m_nextnonemptyq{},
    m_orient3dcount{0},
    m_queuefront{},
    m_queuetail{},
    m_recenttri{},
    m_regions{0},
    m_samples{1}, //Point location should take at least one sample
    m_splaynodes{},
    m_steinerleft{0},
    m_subsegs{},
    m_triangles{},
    m_undeads{0},
    //m_vertex2triindex{0},
    m_vertices{},
    m_viri{},
    m_xmax{0.0},
    m_xmin{0.0},
    m_xminextreme{0.0},
    m_ymax{0.0},
    m_ymin{0.0}
{

}

void ribi::tricpp::Mesh::Enqueuebadtri(
  const boost::shared_ptr<Otri>& enqtri,
  const double minedge,
  const boost::shared_ptr<Vertex>& enqapex,
  const boost::shared_ptr<Vertex>& enqorg,
  const boost::shared_ptr<Vertex>& enqdest
)
{
  // Allocates a badtriang data structure for the triangle, then passes it to
  // enqueuebadtriang().
  boost::shared_ptr<BadTriang> newbad(new BadTriang);

  //Allocate space for the bad triangle.
  //newbad = (struct BadTriang *) PoolAlloc(&m.m_badtriangles);
  newbad->m_poortri = enqtri->m_triangles[enqtri->m_orient]; //encode(*enqtri);
  newbad->m_key = minedge;
  newbad->m_triangapex = enqapex;
  newbad->m_triangorg = enqorg;
  newbad->m_triangdest = enqdest;
  Enqueuebadtriang(newbad);
  //enqueuebadtriang(m,newbad);
}
*/


void ribi::tricpp::Mesh::Enqueuebadtriang(boost::shared_ptr<BadTriang> badtri)
{
  m_badtriangles.push_back(badtri);
  #ifdef KEEP_THIS_20140520
  // The queue is actually a set of 4096 queues.  I use multiple queues to
  // give priority to smaller angles.  I originally implemented a heap, but
  // the queues are faster by a larger margin than I'd suspected.

  double length = 0.0;
  //double multiplier;
  //int exponent;
  //int expincrement;
  int queuenumber = -1;
  bool posexponent = false;

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
    posexponent = true;
  }
  else
  {
    //`badtri->key' is 2.0 to a negative exponent, so we'll record that
    //  fact and use the reciprocal of `badtri->key', which is > 1.0.
    length = 1.0 / badtri->m_key;
    posexponent = false;
  }
  //`length' is approximately 2.0 to what exponent?  The following code
  //  determines the answer in time logarithmic in the exponent.
  int exponent = 0;
  while (length > 2.0)
  {
    //Find an approximation by repeated squaring of two.
    int expincrement = 1;
    double multiplier = 0.5;
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
  if (m.m_queuefront.empty())
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
  #endif
}

const ribi::tricpp::Vertex& ribi::tricpp::Mesh::GetVertex(const int index) const noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_vertices.size()));
  return m_vertices[index];
}

/*
Vertex& ribi::tricpp::Mesh::GetVertex(const int index) noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_vertices));
  return m_vertices[index];
}
*/

void ribi::tricpp::Mesh::KillVertex(const int index) noexcept
{
  assert(index >= 0);
  assert(index < static_cast<int>(m_vertices.size()));
  assert(!m_vertices.empty());
  std::swap(m_vertices[index],m_vertices[m_vertices.size() - 1]);
  m_vertices.pop_back();
}

/*
ribi::tricpp::Vertex ribi::tricpp::vertextraverse(Mesh& m)
{
  Vertex newvertex;

  do
  {
    newvertex = (Vertex) Traverse(&m.m_vertices);
    if (newvertex == nullptr)
    {
      return nullptr;
    }
  } while (IsDeadVertexType(newvertex)); // Skip dead ones
  return newvertex;
}
*/
#endif
