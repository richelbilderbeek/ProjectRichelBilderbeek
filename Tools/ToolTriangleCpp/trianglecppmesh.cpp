#include "trianglecppmesh.h"

#include "trianglecppglobals.h"
#include "trianglecppdefines.h"

tricpp::Mesh::Mesh()
  :
    badsubsegs{},
    badtriangles{},
    checkquality{0},
    checksegments{0},
    circletopcount{0},
    circumcentercount{0},
    counterclockcount{0},
    firstnonemptyq{0},
    flipstackers{},
    hyperbolacount{0},
    incirclecount{0},
    lastflip{nullptr},
    orient3dcount{0},
    samples{1}, //Point location should take at least one sample
    splaynodes{},
    subsegs{},
    triangles{},
    undeads{0},
    vertices{},
    viri{},
    xmax{0.0},
    xmin{0.0},
    xminextreme{0.0},
    ymax{0.0},
    ymin{0.0}
{
  recenttri.tri = nullptr; //(Triangle *) NULL; /* No triangle has been visited yet. */
}

tricpp::Vertex tricpp::vertextraverse(Mesh& m)
{
  Vertex newvertex;

  do {
    newvertex = (Vertex) traverse(&m.vertices);
    if (newvertex == nullptr) {
      return nullptr;
    }
  } while (vertextype(newvertex,m) == DEADVERTEX);          /* Skip dead ones. */
  return newvertex;
}

