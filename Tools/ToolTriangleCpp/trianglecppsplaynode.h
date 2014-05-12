#ifndef TRIANGLECPPSPLAYNODE_H
#define TRIANGLECPPSPLAYNODE_H

#include "trianglecppvertex.h"
#include "trianglecppotri.h"

namespace tricpp {

/// A node in the splay tree.  Each node holds an oriented ghost triangle
///   that represents a boundary edge of the growing triangulation.  When a
///   circle event covers two boundary edges with a triangle, so that they
///   are no longer boundary edges, those edges are not immediately deleted
///   from the tree; rather, they are lazily deleted when they are next
///   encountered.  (Since only a random sample of boundary edges are kept
///   in the tree, lazy deletion is faster.)  `keydest' is used to verify
///   that a triangle is still the same as when it entered the splay tree; if
///   it has been rotated (due to a circle event), it no longer represents a
///   boundary edge and should be deleted.
struct SplayNode
{
  /// Lprev of an edge on the front.
  Otri keyedge;
  /// Used to verify that splay node is still live.
  Vertex keydest;
  /// Children in splay tree.
  SplayNode *lchild, *rchild;
};

} //~namespace tricpp

#endif // TRIANGLECPPSPLAYNODE_H
