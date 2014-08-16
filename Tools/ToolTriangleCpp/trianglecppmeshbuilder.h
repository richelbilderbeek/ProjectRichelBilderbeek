#ifndef TRIANGLECPPMESHBUILDER_H
#define TRIANGLECPPMESHBUILDER_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <vector>

#include <boost/shared_ptr.hpp>

#include "trianglecppfwd.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace tricpp {

///Creates a Mesh
struct MeshBuilder
{
  typedef boost::shared_ptr<const Arguments> ArgumentsPtr;
  typedef boost::shared_ptr<Edge> EdgePtr;
  typedef boost::shared_ptr<Triangle> TrianglePtr;
  typedef boost::shared_ptr<Vertex> VertexPtr;
  typedef std::vector<EdgePtr> Edges;
  typedef std::vector<TrianglePtr> Triangles;
  typedef std::vector<VertexPtr> Vertices;

  MeshBuilder();
  boost::shared_ptr<Mesh> Create(const Arguments& arguments) const noexcept;

  private:

  std::vector<boost::shared_ptr<ribi::tricpp::Edge>> CreateEdges(
    const ribi::PolyFile& polyfile,
    std::vector<boost::shared_ptr<Vertex>>& vertices
  ) const noexcept;

  //Assembles Triangles from edges
  std::vector<boost::shared_ptr<ribi::tricpp::Triangle>> CreateTriangles(
    std::vector<boost::shared_ptr<Edge>>& edges
  ) const noexcept;

  ///Converts raw .poly file its contents
  ///to Vertex instances
  std::vector<boost::shared_ptr<Vertex>> CreateVertices(
    const ribi::PolyFile& polyfile
  ) const noexcept;

};

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPMESHBUILDER_H
