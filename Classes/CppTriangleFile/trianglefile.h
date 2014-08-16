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

struct PolyFileFromPolygons;

///TriangleFile allows for conversion between multiple polygons
///  and Triangle output files
///The following steps are taken:
/// - Convert the shapes to WKT
///
///TriangleFile can then call ExecuteTriangle on itself
///to create a triangulated 2D mesh in the form of a .ele, .node and poly file
///
///Triangle.exe is written by Jonathan Shewchuk, http://people.sc.fsu.edu/~jburkardt/c_src/triangle/triangle.html
struct TriangleFile
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::linestring<Coordinat> Linestring;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Linestring> Linestrings;
  typedef std::vector<Polygon> Polygons;
  typedef std::pair<Polygons,Linestrings> Shapes;

  ///Start from polygons
  explicit TriangleFile(const Polygons& polygons, const Linestrings& linestrings);
  explicit TriangleFile(const Shapes& shapes) : TriangleFile(shapes.first,shapes.second) {}

  ///Call Triangle
  //#define TODO_ISSUE_207
  #ifdef  TODO_ISSUE_207
  void ExecuteTriangle(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose
  ) const;

  ///Call Triangle its C++ equivalent
  void ExecuteTriangleCpp(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose
  ) const;
  #endif
  ///Executes Triangle.exe from a Windows command line
  ///Creates three output files:
  ///- ele_filename: the .ele file
  ///- node_filename: the .node file
  ///- poly_filename: the .poly file
  void ExecuteTriangleExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose
  ) const;

  ///Executes TriangleCpp.exe from command line
  ///Creates three output files:
  ///- ele_filename: the .ele file
  ///- node_filename: the .node file
  ///- poly_filename: the .poly file
  void ExecuteTriangleCppExe(
    std::string& node_filename,
    std::string& ele_filename,
    std::string& poly_filename,
    const Angle triangle_min_angle,
    const Area triangle_max_area,
    const bool verbose
  ) const;

  ///Count the number of input edges
  int GetTriangleInputNedges() const noexcept;

  ///Count the number of input vertices
  int GetTriangleInputNvertices() const noexcept;

  const Polygons& GetShapes() const noexcept;

  ///Obtain the Triangle.exe input .poly file
  std::string GetTriangleInputPoly() const noexcept { return ToStr(); }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the Triangle.exe input .poly file
  std::string ToStr() const noexcept;

  private:
  boost::shared_ptr<PolyFileFromPolygons> m_polyfile;

  static std::pair<int,char **> CreateArgv(const std::vector<std::string>& v) noexcept;
  static void DeleteArgv(const std::pair<int,char **>& p) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const TriangleFile& f) noexcept;
};

std::ostream& operator<<(std::ostream& os, const TriangleFile& f) noexcept;

} //~namespace ribi

#endif // RIBI_TRIANGLEFILE_H
