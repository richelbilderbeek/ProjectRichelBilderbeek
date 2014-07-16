#include "polyfilefrompolygons.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/make_shared.hpp>

#include "fileio.h"
#include "geometry.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::PolyFileFromPolygons::PolyFileFromPolygons(
  const Polygons& polygons,
  const Linestrings& linestrings
)
  : m_linestrings(linestrings),
    m_polyfile(
      PolyFile(
        ToVertices(polygons,linestrings),
        ToEdges(polygons,linestrings)
      )
    ),
    m_polygons(polygons)
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::PolyFileFromPolygons::GetNedges() const noexcept
{
  return static_cast<int>(m_polyfile.GetEdges().size());
}

int ribi::PolyFileFromPolygons::GetNvertices() const noexcept
{
  return static_cast<int>(m_polyfile.GetVertices().size());
}

std::string ribi::PolyFileFromPolygons::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::PolyFileFromPolygons::GetVersionHistory() noexcept
{
  return {
    "2014-06-02: Version 1.0: split off from PolyFile",
    "2014-06-10: Version 1.1: added support for linestrings",
    "2014-06-26: Version 1.2: added GetNvertices and GetNedges"
  };
}

#ifndef NDEBUG
void ribi::PolyFileFromPolygons::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PolyFileFromPolygons::Test");
  //Create PolyFileFromPolygon, save to file, load PolyFile from file,
  //shapes before should match those loaded from file
  {
    //Create polygon
    const std::vector<Coordinat> points {
      {0.0, 0.0}, //0
      {0.0, 1.0}, //1
      {1.0, 0.0}  //2
    };
    //Write polygon to file
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      Polygon shape;
      boost::geometry::append(shape, points);
      const Polygons shapes = {shape};
      const auto polyfile_from_polygons = boost::make_shared<PolyFileFromPolygons>(shapes);
      std::ofstream f(filename.c_str());
      f << std::setprecision(20) << polyfile_from_polygons->GetPolyFile().ToStr();
    }
    //Load file
    {
      const auto polyfile = boost::make_shared<PolyFile>(filename);
      assert(points.size() == polyfile->GetVertices().size()
        && "The number of points is expected to be equal");
      const int n_vertices = static_cast<int>(polyfile->GetVertices().size());
      for (int i=0; i!=n_vertices; ++i)
      {
        assert(
          Geometry().IsEqual2d(
            points[i],
            polyfile->GetVertices()[i]
          )
        );
      }
    }
  }
  TRACE("Successfully finished ribi::PolyFileFromPolygons::Test");
}
#endif
ribi::PolyFile::Edges ribi::PolyFileFromPolygons::ToEdges(
  const Polygons& polygons,
  const Linestrings& linestrings
) noexcept
{
  ribi::PolyFile::Edges edges;
  int vertex_index = 0;
  int shape_first_vertex_index = 0;
  for (const auto& shape: polygons)
  {
    const int n = static_cast<int>(shape.outer().size());

    for (int i=0; i!=n; ++i)
    {
      const int from_index = vertex_index;
      const int to_index
        = i != n-1
        ? vertex_index+1           //Go to next
        : shape_first_vertex_index //Go to first of shape
      ;
      edges.push_back(std::make_pair(from_index,to_index));
      ++vertex_index;
    }
    shape_first_vertex_index += n;
  }

  for (const auto& linestring: linestrings)
  {
    const int n = static_cast<int>(linestring.size());

    for (int i=0; i!=n-1; ++i) //Always go to the next point
    {
      const int from_index = vertex_index;
      const int to_index = vertex_index+1; //Go to next
      edges.push_back(std::make_pair(from_index,to_index));
      ++vertex_index;
    }
    shape_first_vertex_index += n;
  }

  return edges;
}

std::string ribi::PolyFileFromPolygons::ToStr() const noexcept
{
  std::stringstream s;
  s << (*this);
  return s.str();
  //return m_polyfile.ToStr();
}

ribi::PolyFile::Vertices ribi::PolyFileFromPolygons::ToVertices(
  const Polygons& polygons,
  const Linestrings& linestrings
) noexcept
{
  ribi::PolyFile::Vertices v;
  for (const auto& polygon: polygons)
  {
    for (const auto& vertex: polygon.outer())
    {
      v.push_back(vertex);
    }
  }
  for (const auto& linestring: linestrings)
  {
    for (const auto& vertex: linestring)
    {
      v.push_back(vertex);
    }
  }
  return v;
}

std::ostream& ribi::operator<<(std::ostream& os, const PolyFileFromPolygons& polyfile) noexcept
{
  os << polyfile.m_polyfile;
  return os;
}
