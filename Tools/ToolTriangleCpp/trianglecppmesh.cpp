#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "trianglecppmesh.h"

#include <cassert>

#include "trianglecppbadsubseg.h"
#include "trianglecppdefines.h"
#include "trianglecppglobals.h"
#include "trianglecppsubseg.h"
#pragma GCC diagnostic pop

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
