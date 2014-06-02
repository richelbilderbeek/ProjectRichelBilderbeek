#include "polyfile.h"

#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <QFile>

#include "fileio.h"
#include "geometry.h"
#include "trace.h"

//#include "triangle.h"

//#define TODO_ISSUE_207
#ifdef  TODO_ISSUE_207
#include "trianglecppmain.h"
#endif

#pragma GCC diagnostic pop

ribi::PolyFile::PolyFile(
  const Vertices& vertices,
  const Edges& edges
) : m_edges(edges),
    m_vertices(vertices)
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
ribi::PolyFile::PolyFile(
  const Polygons& shapes
  //const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& holes
) : m_holes(holes),
    m_shapes(shapes)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(holes.empty() && "Adding holes is not implemented yet");
}
*/

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::PolyFile::CreateShapeHeart(const double scale) noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 1.0 * scale}, //0
    { 1.0 * scale, 2.0 * scale}, //1
    { 2.0 * scale, 1.0 * scale}, //2
    { 2.0 * scale, 0.0 * scale}, //3
    { 0.0 * scale,-2.0 * scale}, //4
    {-2.0 * scale, 0.0 * scale}, //5
    {-2.0 * scale, 1.0 * scale}, //6
    {-1.0 * scale, 2.0 * scale}  //7
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::PolyFile::CreateShapeHouse(const double scale) noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 2.0 * scale}, //0
    { 1.0 * scale, 1.0 * scale}, //1
    { 1.0 * scale,-1.0 * scale}, //2
    {-1.0 * scale,-1.0 * scale}, //3
    {-1.0 * scale, 1.0 * scale}  //4
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::PolyFile::CreateShapePolygon(
  const int n,
  const double rotation,
  const double scale
) noexcept
{
  assert(n >= 3 && "A polygon has at least three edges");
  const double tau { boost::math::constants::two_pi<double>() };
  std::vector<boost::geometry::model::d2::point_xy<double>> points;
  for (int i=0; i!=n; ++i)
  {
    const double angle { tau * static_cast<double>(i) / static_cast<double>(n) };
    const double x {  std::sin(angle + rotation) };
    const double y { -std::cos(angle + rotation) };
    boost::geometry::model::d2::point_xy<double> point(x * scale, y * scale);
    points.push_back(point);
  }

  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::PolyFile::CreateShapeTriangle(const double scale) noexcept
{
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    { 0.0 * scale, 0.0 * scale}, //0
    { 1.0 * scale, 0.0 * scale}, //1
    { 0.0 * scale, 1.0 * scale}  //2
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  return v;
}

std::vector<std::string> ribi::PolyFile::FileToNoCommentVector(const std::string& filename) noexcept
{
  //From http://people.sc.fsu.edu/~jburkardt/data/poly/poly.html:
  //
  //  Comments are prefixed by the character '#'. Everything from the comment character to the end of the line is ignored.
  //
  std::vector<std::string> v = fileio::FileIo().FileToVector(filename);
  v.erase(
    std::remove_if(v.begin(),v.end(),
      [](std::string s)
      {
        boost::algorithm::trim_left(s);
        if (s.empty()) return true;
        if (s[0]=='#') return true;
        return false;
      }
    ),
    v.end()
  );
  return v;
}

std::string ribi::PolyFile::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::PolyFile::GetVersionHistory() noexcept
{
  return {
    "2014-05-27: Version 1.0: initial version, split off from TriangleFile"
  };
}

std::pair<ribi::PolyFile::Vertices,ribi::PolyFile::Edges> ribi::PolyFile::Parse(const std::string& filename)
{
  //Collect all indices
  const auto v = FileToNoCommentVector(filename);
  if (v.empty())
  {
    std::stringstream s;
    s
      << "ribi::PolyFile::Parse: " << filename
      << " does not contain any vertices"
    ;
    throw std::logic_error(s.str().c_str());
  }
  int n_vertices = -1;
  {
    const std::string& first_line = v[0];
    const auto w = SeperateString(first_line,' ');
    if (w.empty())
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its first line does not indicate the number of vertices"
      ;
      throw std::logic_error(s.str().c_str());
    }
    n_vertices = boost::lexical_cast<int>(w[0]);
  }
  assert(n_vertices >= 0);
  const int first_vertex_index = 1;
  const int beyond_last_vertex_index = first_vertex_index + n_vertices;
  const int edges_header_index = beyond_last_vertex_index;
  int n_edges = -1;
  {
    assert(edges_header_index < static_cast<int>(v.size()));
    const std::string& line = v[edges_header_index];
    const auto w = SeperateString(line,' ');
    if (w.empty())
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its edge header does not indicate the number of edges"
      ;
      throw std::logic_error(s.str().c_str());
    }
    n_edges = boost::lexical_cast<int>(w[0]);
  }
  assert(n_edges >= 0);
  const int first_edge_index = edges_header_index + 1;
  const int beyond_last_edge_index = first_edge_index + n_edges;
  //Create actual data
  Vertices vertices;
  for (int i=first_vertex_index; i!=beyond_last_vertex_index; ++i)
  {
    const std::string& line = v[i];
    const auto w = SeperateString(line,' ');
    assert(w.size() == 4);
    const double x = boost::lexical_cast<double>(w[1]);
    const double y = boost::lexical_cast<double>(w[2]);
    const Vertex vertex(x,y);
    vertices.push_back(vertex);
  }
  Edges edges;
  for (int i=first_edge_index; i!=beyond_last_edge_index; ++i)
  {
    const std::string& line = v[i];
    const auto w = SeperateString(line,' ');
    assert(w.size() >= 3);
    const int from_index = boost::lexical_cast<int>(w[1]);
    const int to_index = boost::lexical_cast<int>(w[1]);
    Edge edge(from_index,to_index);
    edges.push_back(edge);
  }
  return std::make_pair(vertices,edges);
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
std::vector<std::string> ribi::PolyFile::SeperateString(
  const std::string& input,
  const char seperator) noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

#ifndef NDEBUG
void ribi::PolyFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::PolyFile::Test");
  //Load a .poly file
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      const std::string qtfilename = ":/polyfile/polyfile1.poly";
      QFile qfile(qtfilename.c_str());
      assert(qfile.size() > 0);
      qfile.copy(filename.c_str());
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    PolyFile polyfile(filename);
    assert(!polyfile.GetVertices().empty());
    assert(!polyfile.GetEdges().empty());
  }

  //Create PolyFile from shapes, save to file, load PolyFile from file,
  //shapes before should match those loaded from file
  /*
  {
    boost::shared_ptr<PolyFile> triangle_file;
    {
      const std::vector<Coordinat> points {
        {0.5, 2.0}, //0
        {1.0, 1.0}, //1
        {1.0, 0.0}, //2
        {0.0, 0.0}, //3
        {0.0, 1.0}  //4
      };
      Polygon shape;
      boost::geometry::append(shape, points);
      const Polygons shapes = {shape};
      triangle_file = boost::make_shared<PolyFile>(shapes);
    }
    const Polygons shapes = triangle_file->GetShapes();
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename.c_str());
      f << triangle_file->ToStr();
    }
    {
      triangle_file = boost::make_shared<PolyFile>(filename);
      assert(shapes.size() == triangle_file->GetShapes().size()
        && "The number of shapes is expected to be equal");
      const int n_shapes = static_cast<int>(shapes.size());
      for (int i=0; i!=n_shapes; ++i)
      {
        assert(shapes[i].outer().size() == triangle_file->GetShapes()[i].outer().size()
          && "The number of vertices per shape is expected to be equal");
        const int n_vertices = static_cast<int>(shapes[i].outer().size());
        for (int j=0; j!=n_vertices; ++j)
        {
          assert(
            Geometry().IsEqual2d(
              shapes[i].outer()[j],
              triangle_file->GetShapes()[i].outer()[j]
            )
          && "Vertices must be about equal"
          );
        }
      }
    }

  }
  */
}
#endif

ribi::PolyFile::Edges ribi::PolyFile::ToEdges(const Polygons& polygons) noexcept
{
  Edges edges;
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

std::string ribi::PolyFile::ToStr() const noexcept
{
  std::stringstream s;
  s << *this;
  return s.str();
  /*
  s << std::setprecision(6) << std::fixed;

  //Write vertices
  {
    {
      const int sz = static_cast<int>(m_vertices.size());
      const int dimensionality = 2; //All m_vertices are 2 dimensional
      const int n_extras = 0; //Points have zero extras
      const int n_node_markers = 1;
      s << sz << " " << dimensionality << " " << n_extras << " " << n_node_markers << '\n';

      for(int n=0; n !=sz; ++n)
      {
        const auto point = m_vertices[n];
        s
          << (n + 1) //Human based index counting
          << " "
          << point.x()
          << " "
          << point.y()
          << " 1\n";
      }
    }
  }

  //Write segments
  {

    const int n_edges = static_cast<int>(m_edges.size());
    {
      const int n_extras = 0;
      s << n_edges << " " << n_extras << '\n';
    }
    for(int i=0; i!=n_edges; ++i)
    {
      s
        << (i + 1) //Human based index counting
        << " "
        << (m_edges[i].first  + 1) //Human based index counting
        << " "
        << (m_edges[i].second + 1) //Human based index counting
        << "\n";
    }
  }
  //Write holes
  {
    #ifdef SUPPORT_HOLES_20140527
    std::vector<boost::geometry::model::d2::point_xy<double>> holes;
    for (auto hole: m_holes)
    {
      boost::geometry::model::ring<boost::geometry::model::d2::point_xy<double>> v;
      boost::geometry::convert(hole,v);
      std::copy(std::begin(v),std::end(v),std::back_inserter(holes));
    }

    {
      const int sz = static_cast<int>(holes.size());
      s << sz << '\n';

      for(int n=0; n !=sz; ++n)
      {
        const auto hole = holes[n];
        s
          << (n + 1) //Human based index counting
          << " "
          << hole.x()
          << " "
          << hole.y()
          << '\n';
      }
    }
    #else
    const int n_holes = 0;
    s << n_holes << '\n';
    #endif
  }
  return s.str();
  */
}

std::vector<ribi::PolyFile::Coordinat> ribi::PolyFile::ToVertices(const Polygons& polygons) noexcept
{
  std::vector<Coordinat> v;
  for (const auto shape: polygons)
  {
    for (const auto vertex: shape.outer())
    {
      v.push_back(vertex);
    }
  }
  return v;
}

std::ostream& ribi::operator<<(std::ostream& s,const PolyFile& file) noexcept
{
  //std::stringstream s;
  s << std::setprecision(6) << std::fixed;

  //Write vertices
  {
    /*
    std::vector<boost::geometry::model::d2::point_xy<double>> points;
    for (auto shape: m_shapes)
    {
      boost::geometry::model::ring<boost::geometry::model::d2::point_xy<double>> v;
      boost::geometry::convert(shape,v);
      std::copy(std::begin(v),std::end(v),std::back_inserter(points));
    }
    */
    {
      const int sz = static_cast<int>(file.GetVertices().size());
      const int dimensionality = 2; //All m_vertices are 2 dimensional
      const int n_extras = 0; //Points have zero extras
      const int n_node_markers = 1;
      s << sz << " " << dimensionality << " " << n_extras << " " << n_node_markers << '\n';

      for(int n=0; n !=sz; ++n)
      {
        const auto point = file.GetVertices()[n];
        s
          << (n + 1) //Human based index counting
          << " "
          << point.x()
          << " "
          << point.y()
          << " 1\n";
      }
    }
  }

  //Write segments
  {
    /*
    std::vector<std::pair<int,int>> segments;
    const int n_segments = CountSegments();
    s << n_segments << " 0\n";

    const int n_shapes = CountShapes();
    int cnt = 0;
    for (int i=0; i!=n_shapes; ++i)
    {
      const int n_vertices = boost::geometry::num_points(m_shapes[i]);
      //A polygon has segments from a point to the next...
      for (int j=0; j!=n_vertices-1; ++j)
      {
        segments.push_back(std::make_pair(cnt,cnt+1));
        ++cnt;
      }
      //...or from the last to the first
      segments.push_back(std::make_pair(cnt,cnt-n_vertices+1));
      ++cnt;
    }
    */
    const int n_edges = static_cast<int>(file.GetEdges().size());
    {
      const int n_extras = 0;
      s << n_edges << " " << n_extras << '\n';
    }
    for(int i=0; i!=n_edges; ++i)
    {
      s
        << (i + 1) //Human based index counting
        << " "
        << (file.GetEdges()[i].first  + 1) //Human based index counting
        << " "
        << (file.GetEdges()[i].second + 1) //Human based index counting
        << "\n";
    }
  }
  //Write holes
  {
    #ifdef SUPPORT_HOLES_20140527
    std::vector<boost::geometry::model::d2::point_xy<double>> holes;
    for (auto hole: m_holes)
    {
      boost::geometry::model::ring<boost::geometry::model::d2::point_xy<double>> v;
      boost::geometry::convert(hole,v);
      std::copy(std::begin(v),std::end(v),std::back_inserter(holes));
    }

    {
      const int sz = static_cast<int>(holes.size());
      s << sz << '\n';

      for(int n=0; n !=sz; ++n)
      {
        const auto hole = holes[n];
        s
          << (n + 1) //Human based index counting
          << " "
          << hole.x()
          << " "
          << hole.y()
          << '\n';
      }
    }
    #else
    const int n_holes = 0;
    s << n_holes << '\n';
    #endif
  }
  return s;
}
