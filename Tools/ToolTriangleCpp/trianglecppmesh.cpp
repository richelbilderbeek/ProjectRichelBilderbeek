#include "trianglecppmesh.h"

#include "trianglecppglobals.h"
#include "trianglecppdefines.h"

tricpp::Mesh::Mesh()
  :
    m_areaboundindex{0},
    m_badsubsegs{},
    m_badtriangles{},
    m_checkquality{0},
    m_checksegments{0},
    m_circletopcount{0},
    m_circumcentercount{0},
    m_counterclockcount{0},
    //m_do_readnodefile{false},
    m_dummysub{nullptr},
    m_dummysubbase{nullptr},
    m_dummytri{nullptr},
    m_dummytribase{nullptr},
    m_edges{0},
    m_eextras{0},
    m_elemattribindex{0},
    m_firstnonemptyq{0},
    m_flipstackers{},
    m_highorderindex{0},
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
    m_lastflip{nullptr},
    m_orient3dcount{0},
    m_recenttri{},
    m_regions{0},
    m_samples{1}, //Point location should take at least one sample
    m_splaynodes{},
    m_steinerleft{0},
    m_subsegs{},
    m_triangles{},
    m_undeads{0},
    m_vertex2triindex{0},
    m_vertices{},
    m_viri{},
    m_xmax{0.0},
    m_xmin{0.0},
    m_xminextreme{0.0},
    m_ymax{0.0},
    m_ymin{0.0}
{

}

tricpp::Vertex tricpp::vertextraverse(Mesh& m)
{
  Vertex newvertex;

  do
  {
    newvertex = (Vertex) Traverse(&m.m_vertices);
    if (newvertex == nullptr)
    {
      return nullptr;
    }
  } while (vertextype(newvertex,m) == DEADVERTEX);          /* Skip dead ones. */
  return newvertex;
}

