#ifndef TRIANGLECPPMESH_H
#define TRIANGLECPPMESH_H

#include "trianglecppmemorypool.h"
#include "trianglecppbadtriang.h"
#include "trianglecppflipstacker.h"
#include "trianglecppsubseg.h"
#include "trianglecppotri.h"

namespace tricpp {

/// Mesh data structure.  Triangle operates on only one mesh, but the mesh
///   structure is used (instead of global variables) to allow reentrancy.

struct Mesh
{
  Mesh();

  int m_areaboundindex; //REPLACE BY CONST            /// Index to find area bound of a triangle.
  MemoryPool m_badsubsegs; /// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool m_badtriangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int m_checkquality;                  /// Has quality triangulation begun yet?
  int m_checksegments;         /// Are there segments in the triangulation yet?
  long m_circletopcount;       /// Number of circle top calculations performed.
  long m_circumcentercount;  /// Number of circumcenter calculations performed.
  long m_counterclockcount;     /// Number of counterclockwise tests performed.
  static const bool m_do_readnodefile = false;          /// Has a .node file been read?
  SubSeg * m_dummysub; /// Pointer to the omnipresent subsegment.  Referenced by any triangle or ///   subsegment that isn't really connected to a subsegment at that ///   location.
  SubSeg * m_dummysubbase;      /// Keep base address so we can free() it later.
  Triangle *m_dummytri; /// Pointer to the `triangle' that occupies all of "outer space."
  Triangle *m_dummytribase;    /// Keep base address so we can free() it later.
  long m_edges;                                     /// Number of output edges.
  int m_eextras;                         /// Number of attributes per triangle.
  int m_elemattribindex;            /// Index to find attributes of a triangle.
  int m_firstnonemptyq; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  MemoryPool m_flipstackers;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int m_highorderindex;  /// Index to find extra nodes for high-order elements.
  int m_holes;                                       /// Number of input holes.
  long m_hullsize;                          /// Number of edges in convex hull.
  long m_hyperbolacount;      /// Number of right-of-hyperbola tests performed.
  long m_incirclecount;                 /// Number of incircle tests performed.
  int m_inelements;                              /// Number of input triangles.
  Vertex m_infvertex1; /// Triangular bounding box vertices.
  Vertex m_infvertex2; /// Triangular bounding box vertices.
  Vertex m_infvertex3; /// Triangular bounding box vertices.
  int m_insegments;                               /// Number of input segments.
  int m_invertices;                               /// Number of input vertices.
  FlipStacker *m_lastflip; /// Variable that maintains the stack of recently flipped triangles.
  static const int m_mesh_dim = 2;                                /// Dimension (ought to be 2).
  int m_nextnonemptyq[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  static const int m_nextras = 0; /// Number of attributes per vertex.
  long m_orient3dcount;           /// Number of 3D orientation tests performed.
  BadTriang *m_queuefront[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  BadTriang *m_queuetail[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  Otri m_recenttri; /// Pointer to a recently visited triangle.  Improves point location if proximate vertices are inserted sequentially.
  int m_regions;                                   /// Number of input regions.
  long m_samples;              /// Number of random samples for point location.
  MemoryPool m_splaynodes;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int m_steinerleft;                 /// Number of Steiner points not yet used.
  MemoryPool m_subsegs;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool m_triangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int m_undeads;    /// Number of input vertices that don't appear in the mesh.
  static const int m_vertex2triindex = 3; //TODO: REMOVE    /// Index to find a triangle adjacent to a vertex.
  static const int m_vertexmarkindex = 1; //TODO: REMOVE        /// Index to find boundary marker of a vertex.
  MemoryPool m_vertices;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool m_viri;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  double m_xmax; /// x and y bounds
  double m_xmin; /// x and y bounds
  double m_xminextreme;      /// Nonexistent x value used as a flag in sweepline.
  double m_ymax; /// x and y bounds
  double m_ymin; /// x and y bounds

};

//void triangleinit(Mesh& m);

/*  vertextraverse()   Traverse the vertices, skipping dead ones.            */
Vertex vertextraverse(Mesh& m);

} //~namespace tricpp

#endif // TRIANGLECPPMESH_H
