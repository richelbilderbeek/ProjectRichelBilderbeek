#include "polyfile.h"

#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#include <QFile>

#include "container.h"
#include "fileio.h"
//#include "geometry.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::PolyFile::PolyFile(
  const Vertices& vertices,
  const Edges& edges
) noexcept
  : m_edges(edges),
    m_vertices(vertices)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::PolyFile::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::PolyFile::GetVersionHistory() noexcept
{
  return {
    "2014-05-27: Version 1.0: initial version, split off from TriangleFile"
    "2014-06-02: Version 1.1: removed contruction from polygons, start counting from zero, added testing broken files"
  };
}

std::pair<ribi::PolyFile::Vertices,ribi::PolyFile::Edges> ribi::PolyFile::Parse(const std::string& filename)
{
  const bool verbose{false};
  //Collect all indices
  const auto v = RemoveComments(fileio::FileIo().FileToVector(filename));
  if (v.empty())
  {
    if (verbose)
    {
      TRACE(Container().ToStr(v));
    }
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
    const auto w = Container().SeperateString(first_line,' ');
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
    if (edges_header_index >= static_cast<int>(v.size()))
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its edges header is missing"
      ;
      throw std::logic_error(s.str().c_str());
    }

    assert(edges_header_index < static_cast<int>(v.size()));
    const std::string& line = v[edges_header_index];
    const auto w = Container().SeperateString(line,' ');
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
  const int holes_header_index = beyond_last_edge_index;
  int n_holes = -1;
  {
    if (holes_header_index >= static_cast<int>(v.size()))
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its holes header is missing"
      ;
      throw std::logic_error(s.str().c_str());
    }
    assert(holes_header_index < static_cast<int>(v.size()));
    const std::string& line = v[holes_header_index];
    const auto w = Container().SeperateString(line,' ');
    if (w.empty())
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its holes header does not indicate the number of holes"
      ;
      throw std::logic_error(s.str().c_str());
    }
    if (w.size() != 1)
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " its holes header contains too much element"
      ;
      throw std::logic_error(s.str().c_str());
    }
    n_holes = boost::lexical_cast<int>(w[0]);
    if (n_holes != 0)
    {
      std::stringstream s;
      s
        << "ribi::PolyFile::Parse: " << filename
        << " no support for holes"
      ;
      throw std::logic_error(s.str().c_str());
    }
  }
  assert(n_holes == 0 && "Holes are not supported");

  //Allow the indices to start at 1,
  //because, from http://people.sc.fsu.edu/~jburkardt/data/poly/poly.html :
  //
  //  Vertices, segments, holes, and regions must be numbered and listed consecutively, starting from either 1 or 0.
  //
  const int first_index = boost::lexical_cast<int>(Container().SeperateString(v[1],' ')[0]);
  //Create actual data
  Vertices vertices;
  for (int i=first_vertex_index; i!=beyond_last_vertex_index; ++i)
  {
    const std::string& line = v[i];
    const auto w = Container().SeperateString(line,' ');
    if (w.size() != 4)
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "vertex line does not contain four strings. "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
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
    const auto w = Container().SeperateString(line,' ');
    if (w.size() != 3)
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line does not contain three strings. "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    assert(w.size() == 3);
    const int from_index = boost::lexical_cast<int>(w[1]) - first_index;
    const int to_index = boost::lexical_cast<int>(w[2]) - first_index;
    if (from_index == to_index)
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line 'from' is equal to 'to'. "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    if (from_index < 0)
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line 'from' is an invalid index (" << from_index
        << "), as it is lower than zero. "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    if (from_index >= static_cast<int>(vertices.size()))
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line 'from' is an invalid index (" << from_index
        << "), as it is height than the number of vertices ("
        << vertices.size() << "). "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    if (to_index < 0)
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line 'to' is an invalid index (" << to_index
        << "), as it is lower than zero. "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    if (to_index >= static_cast<int>(vertices.size()))
    {
      std::stringstream s;
      s << "File '" << filename << "' cannot be parsed: "
        << "edge line 'to' is an invalid index (" << to_index
        << "), as it is height than the number of vertices ("
        << vertices.size() << "). "
        << "line #" << i << ": '"
        << line << "'"
      ;
      TRACE(s.str());
      throw std::runtime_error(s.str());
    }
    assert(from_index != to_index);
    assert(from_index < static_cast<int>(vertices.size()));
    assert(from_index >= 0);
    assert(to_index < static_cast<int>(vertices.size()));
    assert(to_index >= 0);
    Edge edge(from_index,to_index);
    edges.push_back(edge);
  }
  return std::make_pair(vertices,edges);
}

std::vector<std::string> ribi::PolyFile::RemoveComments(const std::vector<std::string>& v) noexcept
{
  std::vector<std::string> w;
  std::copy_if(v.begin(),v.end(),std::back_inserter(w),
    [](std::string s)
    {
      boost::algorithm::trim_left(s);
      if (s.empty()) return false;
      if (s[0]=='#') return false;
      return true;
    }
  );
  assert(w.size() <= v.size());
  return w;
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
  const bool verbose{false};
  if (verbose) { TRACE("RemoveComments"); }
  {
    std::vector<std::string> v
      = { "#At beginning", " #At second spot", "Keep me", "  #At third spot"  } ;
    const auto w = RemoveComments(v);
    assert(w.size() == 1);
  }
  if (verbose) { TRACE("Load a .poly file"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      const std::string qtfilename = ":/polyfile/polyfile1.poly";
      QFile qfile(qtfilename.c_str());
      if (qfile.size() == 0)
      {
        std::stringstream s;
        s << "PolyFile::Test: "
          << "resource file '" << qtfilename << "' not found. "
          << "Solutions: "
          << "(1) Add the resource file Classes/CppPolyFile/CppPolyFile.qrc to your project "
          << "(2) Check that in that resource file, " << qtfilename << " is present"
        ;
        TRACE(s.str());
      }
      assert(qfile.size() > 0);
      qfile.copy(filename.c_str());
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    PolyFile polyfile(filename);
    assert(!polyfile.GetVertices().empty());
    assert(!polyfile.GetEdges().empty());
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a .poly file from vertices and edges, save to file and load again"); }
  {
    const Vertices vertices = { {0.0,0.0},{0.0,1.0},{1.0,0.0} };
    const int n_vertices = static_cast<int>(vertices.size());
    const Edges edges = { {0,1},{1,2},{2,0} };
    const int n_edges = static_cast<int>(edges.size());
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    //Save to file
    {
      const PolyFile polyfile(vertices,edges);
      std::ofstream f(filename.c_str());
      f << polyfile.ToStr();
    }
    //Load from file
    const PolyFile polyfile(filename);
    assert(polyfile.GetVertices().size() == vertices.size());
    for (int i=0; i!=n_vertices; ++i)
    {
      assert(std::abs(polyfile.GetVertices()[i].x() - vertices[i].x()) < 0.00001);
      assert(std::abs(polyfile.GetVertices()[i].y() - vertices[i].y()) < 0.00001);
    }
    assert(polyfile.GetEdges().size() == edges.size());
    for (int i=0; i!=n_edges; ++i)
    {
      assert(polyfile.GetEdges()[i].first  == edges[i].first );
      assert(polyfile.GetEdges()[i].second == edges[i].second);
    }
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a .poly file starting at index 0"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "3 2 0 1" << '\n'
        << "# Vertices " << '\n'
        << "0 0.0 0.0 1" << '\n'
        << "1 0.0 1.0 1" << '\n'
        << "2 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "3 0" << '\n'
        << "# Edges " << '\n'
        << "0 0 1" << '\n'
        << "1 1 2" << '\n'
        << "2 2 0" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    const PolyFile polyfile(filename);
    assert(polyfile.GetEdges().size() == 3);
    assert(polyfile.GetVertices().size() == 3);
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a .poly file starting at index 1"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "3 2 0 1" << '\n'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "3 0" << '\n'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 1" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    const PolyFile polyfile(filename);
    assert(polyfile.GetEdges().size() == 3);
    assert(polyfile.GetVertices().size() == 3);
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a broken .poly file: number of vertices is more than supplied"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "4 2 0 1" << '\n' //Changed first number '3' to '4'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "3 0" << '\n'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 1" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    try
    {
      const PolyFile polyfile(filename);
      assert(!"Should have detected error");
      assert(!polyfile.GetVertices().empty()); //To silence the compiler
    }
    catch (std::exception&)
    {
      //OK
    }
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a broken .poly file: number of vertices is less than supplied"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "2 2 0 1" << '\n' //Changed first number '3' to '2'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "3 0" << '\n'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 1" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    try
    {
      const PolyFile polyfile(filename);
      assert(!"Should have detected error");
      assert(!polyfile.GetVertices().empty()); //To silence the compiler
    }
    catch (std::exception&)
    {
      //OK
    }
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a broken .poly file: number of edges is more than supplied"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "3 2 0 1" << '\n'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "4 0" << '\n' //Changed first number '3' to '4'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 1" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    try
    {
      const PolyFile polyfile(filename);
      assert(!"Should have detected error");
      assert(!polyfile.GetVertices().empty()); //To silence the compiler
    }
    catch (std::exception&)
    {
      //OK
    }
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a broken .poly file: number of edges is less than supplied"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "3 2 0 1" << '\n'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "2 0" << '\n' //Changed first number '3' to '2'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 1" << '\n'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    try
    {
      const PolyFile polyfile(filename);
      assert(!"Should have detected error");
      assert(!polyfile.GetVertices().empty()); //To silence the compiler
    }
    catch (std::exception&)
    {
      //OK
    }
    fileio::FileIo().DeleteFile(filename);
  }
  if (verbose) { TRACE("Create a broken .poly file starting at index 1, but has an edge pointing to index 0"); }
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      std::ofstream f(filename);
      f
        << "# Vertices header" << '\n'
        << "3 2 0 1" << '\n'
        << "# Vertices " << '\n'
        << "1 0.0 0.0 1" << '\n'
        << "2 0.0 1.0 1" << '\n'
        << "3 1.0 0.0 1" << '\n'
        << "# Edges header" << '\n'
        << "3 0" << '\n'
        << "# Edges " << '\n'
        << "1 1 2" << '\n'
        << "2 2 3" << '\n'
        << "3 3 0" << '\n' //Changed last digit '1' to '0'
        << "# Holes header" << '\n'
        << "0" << '\n'
        << "# Holes (unsupported)" << '\n'
      ;
    }
    try
    {
      const PolyFile polyfile(filename);
      assert(!"Should have detected error");
      assert(!polyfile.GetVertices().empty()); //To silence the compiler
    }
    catch (std::exception&)
    {
      //OK
    }
    fileio::FileIo().DeleteFile(filename);
  }
}
#endif


std::string ribi::PolyFile::ToStr() const noexcept
{
  std::stringstream s;
  s << *this;
  return s.str();
}

std::ostream& ribi::operator<<(std::ostream& s,const PolyFile& file) noexcept
{
  //Write vertices
  {
    {
      const int n_vertices = static_cast<int>(file.GetVertices().size());
      const int dimensionality = 2; //All m_vertices are 2 dimensional
      const int n_extras = 0; //Points have zero extras
      const int n_node_markers = 1;
      s << "# Vertex header: n_vertices - dimensionality - n_extras - n_node_markers\n";
      s << n_vertices << " " << dimensionality << " " << n_extras << " " << n_node_markers << '\n';
      s << "# Vertices\n";
      s << "# index - x - y\n";

      for(int n=0; n !=n_vertices; ++n)
      {
        const auto point = file.GetVertices()[n];
        s
          << n
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
    const int n_edges = static_cast<int>(file.GetEdges().size());
    {
      const int n_extras = 0;
      s << "# Edge header: n_edges - n_extras\n";
      s << n_edges << " " << n_extras << '\n';
      s << "# Edges\n";
      s << "# index - from vertex index - to vertex index\n";
    }
    for(int i=0; i!=n_edges; ++i)
    {
      s
        << i
        << " "
        << file.GetEdges()[i].first
        << " "
        << file.GetEdges()[i].second
        << "\n";
    }
  }
  //Write holes: unsupported
  {
    s << "# Holes header: n_holes\n";
    const int n_holes = 0;
    s << n_holes << '\n';
  }
  return s;
}
