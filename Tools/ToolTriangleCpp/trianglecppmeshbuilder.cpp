#include "trianglecppmeshbuilder.h"

#include <cassert>

#include <boost/make_shared.hpp>


boost::shared_ptr<ribi::tricpp::Mesh>
  ribi::tricpp::MeshBuilder::Create(const Arguments& arguments) const noexcept
{
  Vertices vertices = CreateVertices(polyfile);
  Edges edges = CreateEdges(polyfile,vertices);
  Triangles triangles = CreateTriangles(edges);
  const auto mesh
    = boost::make_shared<Mesh>(arguments,edges,triangles,vertices);
  assert(mesh);
  return mesh;
}

std::vector<boost::shared_ptr<ribi::tricpp::Edge>>
  ribi::tricpp::MeshBuilder::CreateEdges(
    const ribi::PolyFile& polyfile,
    std::vector<boost::shared_ptr<Vertex>>& vertices
  ) const noexcept
{
  std::vector<boost::shared_ptr<Edge>> edges;
  for (const auto vertex_indices: polyfile.GetEdges())
  {
    const int vertex_index = vertex_indices.first;
    const int next_vertex_index = vertex_indices.second;
    assert(vertex_index < static_cast<int>(vertices.size()));
    assert(next_vertex_index < static_cast<int>(vertices.size()));
    const auto edge = boost::make_shared<Edge>(
      vertices[vertex_index],vertices[next_vertex_index]
    );
    edges.push_back(edge);
  }
  return edges;
}

std::vector<boost::shared_ptr<ribi::tricpp::Triangle>>
  ribi::tricpp::MeshBuilder::CreateTriangles(
    std::vector<boost::shared_ptr<Edge>>& edges
  ) const noexcept
{
  std::vector<boost::shared_ptr<ribi::tricpp::Triangle>> triangles;
  for (auto edge: edges)
  {
    const auto from_edges = edge->GetFromEdges();
    const auto to_edges = edge->GetToEdges();
    for (auto from_edge: from_edges)
    {
      for (auto to_edge: to_edges)
      {
        if (AreConnected(*from_edge,*to_edge))
        {
          const auto triangle
            = boost::make_shared<Triangle>(
              make_array(edge,from_edge,to_edge)
            )
          ;
          triangles.push_back(triangle);
        }
      }
    }
  }
  return triangles;
}

std::vector<boost::shared_ptr<ribi::tricpp::Vertex>>
  ribi::tricpp::MeshBuilder::CreateVertices(
    const ribi::PolyFile& polyfile
  ) const noexcept
{
  std::vector<boost::shared_ptr<Vertex>> vertices;
  for (const auto coordinat: polyfile.GetVertices())
  {
    const int currentmarker = 1; //Appeared to always be true
    const auto vertex
      = boost::make_shared<Vertex>(coordinat.x(),coordinat.y(),currentmarker);
    vertices.push_back(vertex);
  }
  return vertices;
}
