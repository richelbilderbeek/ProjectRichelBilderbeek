#ifndef TRIANGLECPPMESH_H
#define TRIANGLECPPMESH_H


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>
#include <boost/shared_ptr.hpp>
//#include "trianglecppmemorypool.h"
//#include "trianglecppbadtriang.h"
//#include "trianglecppflipstacker.h"
//#include "trianglecppedge.h"
//#include "trianglecppotri.h"
//#include "trianglecppsplaynode.h"
#include "trianglecppfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

/// Mesh data structure.  Triangle operates on only one mesh, but the mesh
///   structure is used (instead of global variables) to allow reentrancy.
struct Mesh
{
  typedef boost::shared_ptr<const Arguments> ArgumentsPtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<Triangle> TrianglePtr;
  typedef boost::shared_ptr<Vertex> VertexPtr;

  typedef std::vector<EdgePtr> Edges;
  typedef std::vector<TrianglePtr> Triangles;
  typedef std::vector<VertexPtr> Vertices;

  private:

  friend class MeshBuilder;
  Mesh(
    const ArgumentsPtr& arguments,
    const Edges& edges,
    const Triangles& triangles,
    const Vertices& vertices
  );

  private:

  const ArgumentsPtr m_arguments;
  const Edges m_edges;
  const Triangles m_triangles;
  const Vertices m_vertices;

  /*
  Mesh();
  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;


  ///Add a bad triangle to the end of a queue.
  void Enqueuebadtri(
    const boost::shared_ptr<Otri>& enqtri,
    const double minedge,
    const boost::shared_ptr<Vertex>& enqapex,
    const boost::shared_ptr<Vertex>& enqorg,
    const boost::shared_ptr<Vertex>& enqdest
  );

  ///Add a bad triangle data structure to the end of a queue.
  void Enqueuebadtriang(boost::shared_ptr<BadTriang> badtri);

  const Vertex& GetVertex(const int index) const noexcept;
  //Vertex& GetVertex(const int index) noexcept;
  void KillSubSeg(boost::shared_ptr<Edge>& subseg) noexcept;
  void KillTriangle(boost::shared_ptr<Triangle> triangle) noexcept;
  void KillVertex(const int index) noexcept;

  //int m_areaboundindex; //REPLACE BY CONST            /// Index to find area bound of a triangle.
  //MemoryPool m_badsubsegs; /// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<BadSubSeg> m_badsubsegs;
  //MemoryPool m_badtriangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<boost::shared_ptr<BadTriang>> m_badtriangles;
  int m_checkquality;                  /// Has quality triangulation begun yet?
  int m_checksegments;         /// Are there segments in the triangulation yet?
  long m_circletopcount;       /// Number of circle top calculations performed.
  long m_circumcentercount;  /// Number of circumcenter calculations performed.
  long m_counterclockcount;     /// Number of counterclockwise tests performed.
  //static const bool m_do_readnodefile = false;          /// Has a .node file been read?
  boost::shared_ptr<Edge> m_dummysub; /// Pointer to the omnipresent subsegment.  Referenced by any triangle or ///   subsegment that isn't really connected to a subsegment at that ///   location.
  //SubSeg * m_dummysubbase;      /// Keep base address so we can free() it later.
  boost::shared_ptr<Triangle> m_dummytri; /// Pointer to the `triangle' that occupies all of "outer space."
  //Triangle *m_dummytribase;    /// Keep base address so we can free() it later.
  long m_edges;                                     /// Number of output edges.
  int m_eextras;                         /// Number of attributes per triangle.
  int m_elemattribindex;            /// Index to find attributes of a triangle.
  int m_firstnonemptyq; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  //MemoryPool m_flipstackers;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<FlipStacker> m_flipstackers;

  /// Index to find extra nodes for high-order elements.
  //The index within each triangle at which the extra nodes (above three)
  //  associated with high order elements are found.  There are three
  //  pointers to other triangles, three pointers to corners, and possibly
  //  three pointers to subsegments before the extra nodes.
  //static const int m_highorderindex = 9;
  int m_holes;                                       /// Number of input holes.
  int m_hullsize;                          /// Number of edges in convex hull.
  long m_hyperbolacount;      /// Number of right-of-hyperbola tests performed.
  int m_incirclecount;                 /// Number of incircle tests performed.
  int m_inelements;                              /// Number of input triangles.
  boost::shared_ptr<Vertex> m_infvertex1; /// Triangular bounding box vertices.
  boost::shared_ptr<Vertex> m_infvertex2; /// Triangular bounding box vertices.
  boost::shared_ptr<Vertex> m_infvertex3; /// Triangular bounding box vertices.
  int m_insegments;                               /// Number of input segments.
  int m_invertices;                               /// Number of input vertices.
  std::vector<FlipStacker> m_lastflip; /// Variable that maintains the stack of recently flipped triangles.
  //static const int m_mesh_dim = 2;                                /// Dimension (ought to be 2).
  std::vector<int> m_nextnonemptyq; //[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  //static const int m_nextras = 0; /// Number of attributes per vertex.
  long m_orient3dcount;           /// Number of 3D orientation tests performed.
  std::vector<boost::shared_ptr<BadTriang>> m_queuefront; //[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  std::vector<boost::shared_ptr<BadTriang>> m_queuetail; //[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  Otri m_recenttri; /// Pointer to a recently visited triangle.  Improves point location if proximate vertices are inserted sequentially.
  int m_regions;                                   /// Number of input regions.
  long m_samples;              /// Number of random samples for point location.
  //MemoryPool m_splaynodes;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<SplayNode> m_splaynodes;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int m_steinerleft;                 /// Number of Steiner points not yet used.
  //MemoryPool m_subsegs;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<Edge> m_subsegs;
  //MemoryPool m_triangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<boost::shared_ptr<Triangle>> m_triangles;
  int m_undeads;    /// Number of input vertices that don't appear in the mesh.
  //static const int m_vertex2triindex = 3; //TODO: REMOVE    /// Index to find a triangle adjacent to a vertex.
  //static const int m_vertexmarkindex = 1; //TODO: REMOVE        /// Index to find boundary marker of a vertex.
  //MemoryPool m_vertices;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<Vertex> m_vertices;
  //MemoryPool m_viri;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  std::vector<Vertex> m_viri;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  double m_xmax; /// x and y bounds
  double m_xmin; /// x and y bounds
  double m_xminextreme;      /// Nonexistent x value used as a flag in sweepline.
  double m_ymax; /// x and y bounds
  double m_ymin; /// x and y bounds
  */
};

//void triangleinit(Mesh& m);

//vertextraverse()   Traverse the vertices, skipping dead ones.
//Vertex vertextraverse(Mesh& m);

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPMESH_H
