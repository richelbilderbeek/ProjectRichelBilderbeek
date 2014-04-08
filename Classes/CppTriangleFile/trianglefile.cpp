#include "trianglefile.h"

#include <cassert>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <QFile>

#include "fileio.h"
#include "trace.h"

//#ifndef _WIN32
#include "triangle.h"
//#endif

#pragma GCC diagnostic pop

ribi::TriangleFile::TriangleFile(
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& holes
) : m_holes(holes),
    m_shapes(shapes)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(holes.empty() && "Adding holes is not implemented yet");
}

int ribi::TriangleFile::CountVertices() const noexcept
{
  int sum = 0;
  for (auto shape: m_shapes)
  {
    sum += boost::geometry::num_points(shape);
  }
  return sum;
}

std::pair<int,char **> ribi::TriangleFile::CreateArgv(const std::vector<std::string>& v) noexcept
{
  typedef char* String;
  typedef String* Strings;
  const int argc = static_cast<int>(v.size());
  Strings argv = new String[argc];
  for (int i=0; i!=argc; ++i)
  {
    argv[i] = new char[v[i].size() + 1];
    std::strcpy(argv[i],&v[i][0]);
    TRACE(argv[i]);
  }
  std::pair<int,char **> p = std::make_pair(argc,argv);
  return p;
}

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::TriangleFile::CreateShapeHeart(const double scale) noexcept
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

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::TriangleFile::CreateShapeHouse(const double scale) noexcept
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

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::TriangleFile::CreateShapePolygon(
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

boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> ribi::TriangleFile::CreateShapeTriangle(const double scale) noexcept
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

void ribi::TriangleFile::DeleteArgv(const std::pair<int,char **>& p) noexcept
{
  const int argc = p.first;
  for(int i = 0; i != argc; ++i)
  {
    delete[] p.second[i];
  }
  delete[] p.second;
}

void ribi::TriangleFile::ExecuteTriangle(
  std::string& node_filename,
  std::string& ele_filename,
  std::string& poly_filename,
  const double quality,
  const double area,
  const bool verbose) const noexcept
{
  const std::string filename { fileio::FileIo().GetTempFileName(".poly") };
  node_filename = "";
  ele_filename = "";
  poly_filename = "";

  {
    std::ofstream f(filename.c_str());
    f << this->ToStr();
  }

  assert(fileio::FileIo().IsRegularFile(filename));
  const std::string exe_filename { "triangle.exe" };

  //#define USE_TRIANGLE_EXE
  #ifdef  USE_TRIANGLE_EXE
  if (!fileio::FileIo().IsRegularFile(exe_filename))
  {
    QFile file( (":/trianglefile/files/" + exe_filename).c_str() );
    file.copy(exe_filename.c_str());
  }
  assert(fileio::FileIo().IsRegularFile(exe_filename));

  std::stringstream s;
  s
    << exe_filename
    << " -j -z -q"
    << quality
    << " -a"
    << area
    << (verbose ? "" : " -Q")
    << " "
    << filename;
  const bool error = std::system(s.str().c_str());
  if (error)
  {
    fileio::FileIo().DeleteFile(filename);
    throw std::runtime_error(s.str().c_str());
  }
  #else
  std::vector<std::string> cmd {
    exe_filename,
    "-j",
    "-z",
    "-q",
    boost::lexical_cast<std::string>(quality),
    "-a",
    boost::lexical_cast<std::string>(area),
    filename
  };
  if (!verbose)
  {
    cmd.push_back("-Q");
    std::swap(cmd[cmd.size() - 1], cmd[cmd.size() - 2]);
  }
  const std::pair<int,char **> p = CreateArgv(cmd);
  triangle_main(p.first,p.second);
  DeleteArgv(p);
  #endif
  const std::string filename_base(fileio::FileIo().GetFileBasename(filename));
  node_filename = filename_base + ".1.node";
  ele_filename = filename_base + ".1.ele";
  poly_filename = filename_base + ".1.poly";
  assert(fileio::FileIo().IsRegularFile(node_filename));
  assert(fileio::FileIo().IsRegularFile(ele_filename));
  assert(fileio::FileIo().IsRegularFile(poly_filename));
  fileio::FileIo().DeleteFile(filename);
}

std::string ribi::TriangleFile::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TriangleFile::GetVersionHistory() noexcept
{
  return {
    "2014-02-07: Version 1.0: initial version",
    "2014-04-04: Version 1.1: allow to call Triangle its code directly"
  };
}


#ifndef NDEBUG
void ribi::TriangleFile::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::TriangleFile::Test");
  const std::vector<boost::geometry::model::d2::point_xy<double>> points {
    {0.5, 2.0}, //0
    {1.0, 1.0}, //1
    {1.0, 0.0}, //2
    {0.0, 0.0}, //3
    {0.0, 1.0}  //4
  };
  boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> v;
  boost::geometry::append(v, points);
  TriangleFile f( {v} );
  //TRACE(f.ToStr());
  std::string filename_node;
  std::string filename_ele;
  std::string filename_poly;
  f.ExecuteTriangle(filename_node,filename_ele,filename_poly);
  assert(fileio::FileIo().IsRegularFile(filename_node));
  assert(fileio::FileIo().IsRegularFile(filename_ele));
  assert(fileio::FileIo().IsRegularFile(filename_poly));
  TRACE("Finished ribi::TriangleFile::Test successfully");
}
#endif

std::string ribi::TriangleFile::ToStr() const noexcept
{
  std::stringstream s;
  s << std::setprecision(6) << std::fixed;

  //Write vertices
  {
    std::vector<boost::geometry::model::d2::point_xy<double>> points;
    for (auto shape: m_shapes)
    {
      boost::geometry::model::ring<boost::geometry::model::d2::point_xy<double>> v;
      boost::geometry::convert(shape,v);
      std::copy(std::begin(v),std::end(v),std::back_inserter(points));
    }

    {
      const int sz = static_cast<int>(points.size());
      s << sz << " 2 0 1" << '\n';

      for(int n=0; n !=sz; ++n)
      {
        const auto point = points[n];
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

    for(int i=0; i!=n_segments; ++i)
    {
      s
        << (i + 1) //Human based index counting
        << " "
        << (segments[i].first  + 1) //Human based index counting
        << " "
        << (segments[i].second + 1) //Human based index counting
        << "\n";
    }
  }
  //Write holes
  {
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
  }
  return s.str();
}
