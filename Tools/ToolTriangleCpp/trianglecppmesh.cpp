#include "trianglecppmesh.h"

#include "trianglecppglobals.h"
#include "trianglecppdefines.h"

tricpp::Mesh::Mesh()
  :
    areaboundindex{0},
    badsubsegs{},
    badtriangles{},
    checkquality{0},
    checksegments{0},
    circletopcount{0},
    circumcentercount{0},
    counterclockcount{0},
    dummysub{nullptr},
    dummysubbase{nullptr},
    dummytri{nullptr},
    dummytribase{nullptr},
    edges{0},
    eextras{0},
    elemattribindex{0},
    firstnonemptyq{0},
    flipstackers{},
    highorderindex{0},
    holes{0},
    hullsize{0},
    hyperbolacount{0},
    incirclecount{0},
    inelements{0},
    infvertex1{},
    infvertex2{},
    infvertex3{},
    insegments{0},
    invertices{0},
    lastflip{nullptr},
    mesh_dim{0},
    nextras{0},
    orient3dcount{0},
    readnodefile{0},
    recenttri{},
    regions{0},
    samples{1}, //Point location should take at least one sample
    splaynodes{},
    steinerleft{0},
    subsegs{},
    triangles{},
    undeads{0},
    vertex2triindex{0},
    vertexmarkindex{0},
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

