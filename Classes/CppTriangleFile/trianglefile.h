#ifndef RIBI_TRIANGLEFILE_H
#define RIBI_TRIANGLEFILE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Create a two-dimensional shape in a format usable by Triangle.exe
///Triangle.exe is written by Jonathan Shewchuk, http://people.sc.fsu.edu/~jburkardt/c_src/triangle/triangle.html
struct TriangleFile
{
  TriangleFile(
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& shapes,
    const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>>& holes = {}
  );

  int CountSegments() const noexcept { return CountVertices(); } //A polygon has as much vertices as segments
  int CountShapes() const noexcept { return static_cast<int>(m_shapes.size()); }
  int CountVertices() const noexcept;

  static boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> CreateShapeHeart(const double scale = 1.0) noexcept;
  static boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> CreateShapeHouse(const double scale = 1.0) noexcept;
  static boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> CreateShapePolygon(const int n, const double rotation = 0.0, const double scale = 0.0) noexcept;
  static boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> CreateShapeTriangle(const double scale = 1.0) noexcept;

  ///Call Triangle
  //#define TODO_ISSUE_207
  #ifdef  TODO_ISSUE_207
  void ExecuteTriangle(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const double quality = 30.0,
    const double area = 2.0,
    const bool verbose = false
  ) const noexcept;

  ///Call Triangle its C++ equivalent
  void ExecuteTriangleCpp(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const double quality = 30.0,
    const double area = 2.0,
    const bool verbose = false
  ) const noexcept;
  #endif
  ///Executes Triangle.exe from a Windows command line
  void ExecuteTriangleExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const double quality = 30.0,
    const double area = 2.0,
    const bool verbose = false
  ) const noexcept;

  ///Executes TriangleCpp.exe from command line
  void ExecuteTriangleCppExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const double quality = 30.0,
    const double area = 2.0,
    const bool verbose = false
  ) const noexcept;

  ///Convert the file to a string in a format usable by Triangle.exe
  std::string ToStr() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>> m_holes;
  const std::vector<boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>>> m_shapes;

  static std::pair<int,char **> CreateArgv(const std::vector<std::string>& v) noexcept;
  static void DeleteArgv(const std::pair<int,char **>& p) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_TRIANGLEFILE_H
