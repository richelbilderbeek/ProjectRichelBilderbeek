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

  int areaboundindex;             /// Index to find area bound of a triangle.
  MemoryPool badsubsegs; /// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool badtriangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int checkquality;                  /// Has quality triangulation begun yet?
  int checksegments;         /// Are there segments in the triangulation yet?
  long circletopcount;       /// Number of circle top calculations performed.
  long circumcentercount;  /// Number of circumcenter calculations performed.
  long counterclockcount;     /// Number of counterclockwise tests performed.
  SubSeg *dummysub; /// Pointer to the omnipresent subsegment.  Referenced by any triangle or ///   subsegment that isn't really connected to a subsegment at that ///   location.
  SubSeg *dummysubbase;      /// Keep base address so we can free() it later.
  Triangle *dummytri; /// Pointer to the `triangle' that occupies all of "outer space."
  Triangle *dummytribase;    /// Keep base address so we can free() it later.
  long edges;                                     /// Number of output edges.
  int eextras;                         /// Number of attributes per triangle.
  int elemattribindex;            /// Index to find attributes of a triangle.
  int firstnonemptyq; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  MemoryPool flipstackers;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int highorderindex;  /// Index to find extra nodes for high-order elements.
  int holes;                                       /// Number of input holes.
  long hullsize;                          /// Number of edges in convex hull.
  long hyperbolacount;      /// Number of right-of-hyperbola tests performed.
  long incirclecount;                 /// Number of incircle tests performed.
  int inelements;                              /// Number of input triangles.
  Vertex infvertex1; /// Triangular bounding box vertices.
  Vertex infvertex2; /// Triangular bounding box vertices.
  Vertex infvertex3; /// Triangular bounding box vertices.
  int insegments;                               /// Number of input segments.
  int invertices;                               /// Number of input vertices.
  FlipStacker *lastflip; /// Variable that maintains the stack of recently flipped triangles.
  int mesh_dim;                                /// Dimension (ought to be 2).
  int nextnonemptyq[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  int nextras;                           /// Number of attributes per vertex.
  long orient3dcount;           /// Number of 3D orientation tests performed.
  BadTriang *queuefront[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  BadTriang *queuetail[4096]; /// bad triangle queues.  The queues are ordered from 4095 (highest priority) to 0 (lowest priority).
  int readnodefile;          /// Has a .node file been read?
  Otri recenttri; /// Pointer to a recently visited triangle.  Improves point location if proximate vertices are inserted sequentially.
  int regions;                                   /// Number of input regions.
  long samples;              /// Number of random samples for point location.
  MemoryPool splaynodes;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int steinerleft;                 /// Number of Steiner points not yet used.
  MemoryPool subsegs;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool triangles;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  int undeads;    /// Number of input vertices that don't appear in the mesh.
  int vertex2triindex;     /// Index to find a triangle adjacent to a vertex.
  int vertexmarkindex;         /// Index to find boundary marker of a vertex.
  MemoryPool vertices;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  MemoryPool viri;/// Variables used to allocate memory for triangles, subsegments, vertices, viri (triangles being eaten), encroached segments, bad (skinny or too large) triangles, and splay tree nodes.
  double xmax; /// x and y bounds
  double xmin; /// x and y bounds
  double xminextreme;      /// Nonexistent x value used as a flag in sweepline.
  double ymax; /// x and y bounds
  double ymin; /// x and y bounds

};

//void triangleinit(Mesh& m);

/*  vertextraverse()   Traverse the vertices, skipping dead ones.            */
Vertex vertextraverse(Mesh& m);

} //~namespace tricpp

#endif // TRIANGLECPPMESH_H
