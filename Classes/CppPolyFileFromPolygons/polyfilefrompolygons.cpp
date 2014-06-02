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


ribi::PolyFileFromPolygons::PolyFileFromPolygons(const Polygons& polygons)
  : m_polyfile(PolyFile(ToVertices(polygons),ToEdges(polygons))),
    m_polygons(polygons)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::PolyFileFromPolygons::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::PolyFileFromPolygons::GetVersionHistory() noexcept
{
  return {
    "2014-06-02: Version 1.0: split off from PolyFile"
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
ribi::PolyFile::Edges ribi::PolyFileFromPolygons::ToEdges(const Polygons& polygons) noexcept
{
  ribi::PolyFile::Edges edges;
  int vertex_index = 0;
  int shape_first_vertex_index = 0;
  for (const auto shape: polygons)
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
  return edges;
}

std::string ribi::PolyFileFromPolygons::ToStr() const noexcept
{
  return m_polyfile.ToStr();
}

ribi::PolyFile::Vertices ribi::PolyFileFromPolygons::ToVertices(const Polygons& polygons) noexcept
{
  ribi::PolyFile::Vertices v;
  for (const auto shape: polygons)
  {
    for (const auto vertex: shape.outer())
    {
      v.push_back(vertex);
    }
  }
  return v;
}

/*
std::ostream& ribi::operator<<(std::ostream& os, const PolyFileFromPolygons& polyfile) noexcept
{
  os << polyfile.GetPolyFile();
  return os;
}
*/
