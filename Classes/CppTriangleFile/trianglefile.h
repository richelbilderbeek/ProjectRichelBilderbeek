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
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/quantity.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Create a two-dimensional shape in a format usable by Triangle.exe
///Triangle.exe is written by Jonathan Shewchuk, http://people.sc.fsu.edu/~jburkardt/c_src/triangle/triangle.html
struct TriangleFile
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Polygon> Polygons;

  TriangleFile(
    const Polygons& shapes,
    const Polygons& holes = {}
  );

  int CountSegments() const noexcept { return CountVertices(); } //A polygon has as much vertices as segments
  int CountShapes() const noexcept { return static_cast<int>(m_shapes.size()); }
  int CountVertices() const noexcept;

  static Polygon CreateShapeHeart(const double scale = 1.0) noexcept;
  static Polygon CreateShapeHouse(const double scale = 1.0) noexcept;
  static Polygon CreateShapePolygon(const int n, const double rotation = 0.0, const double scale = 0.0) noexcept;
  static Polygon CreateShapeTriangle(const double scale = 1.0) noexcept;

  ///Call Triangle
  //#define TODO_ISSUE_207
  #ifdef  TODO_ISSUE_207
  void ExecuteTriangle(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose = false
  ) const;

  ///Call Triangle its C++ equivalent
  void ExecuteTriangleCpp(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose = false
  ) const;
  #endif
  ///Executes Triangle.exe from a Windows command line
  void ExecuteTriangleExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose = false
  ) const;

  ///Executes TriangleCpp.exe from command line
  void ExecuteTriangleCppExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose = false
  ) const;

  ///Convert the file to a string in a format usable by Triangle.exe
  std::string ToStr() const noexcept;

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  private:
  const Polygons m_holes;
  const Polygons m_shapes;

  static std::pair<int,char **> CreateArgv(const std::vector<std::string>& v) noexcept;
  static void DeleteArgv(const std::pair<int,char **>& p) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_TRIANGLEFILE_H
