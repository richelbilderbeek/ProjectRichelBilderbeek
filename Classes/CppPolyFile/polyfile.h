#ifndef RIBI_POLYFILE_H
#define RIBI_POLYFILE_H

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

///PolyFile allows for conversion between
///multiple polygons to a .poly file
///
///Does not allow holes
struct PolyFile
{
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef boost::units::quantity<boost::units::si::length> Length;
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Polygon> Polygons;

  PolyFile(
    const std::vector<Coordinat> vertices,
    const std::vector<std::pair<int,int>> edges
  );

  ///Start from polygons
  PolyFile(
    const Polygons& shapes
    //const Polygons& holes = {}
  ) : PolyFile(ToVertices(shapes),ToEdges(shapes)) { }


  ///Start from polygons
  PolyFile(
    const std::string& poly_filename
  );

  //int CountSegments() const noexcept { return CountVertices(); } //A polygon has as much vertices as segments
  //int CountShapes() const noexcept { return static_cast<int>(m_shapes.size()); }
  //int CountVertices() const noexcept;

  static Polygon CreateShapeHeart(const double scale = 1.0) noexcept;
  static Polygon CreateShapeHouse(const double scale = 1.0) noexcept;
  static Polygon CreateShapePolygon(const int n, const double rotation = 0.0, const double scale = 0.0) noexcept;
  static Polygon CreateShapeTriangle(const double scale = 1.0) noexcept;

  //const Polygons& GetHoles()  const noexcept { return m_holes; }
  //const Polygons& GetShapes() const noexcept { return m_shapes; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Convert the vertices and edges to a .poly file its content
  std::string ToStr() const noexcept;

  private:
  //const Polygons m_holes;
  //const Polygons m_shapes;
  const std::vector<std::pair<int,int>> m_edges;
  const std::vector<Coordinat> m_vertices;



  static std::vector<std::pair<int,int>> ToEdges(const Polygons& polygons) noexcept;
  static std::vector<Coordinat> ToVertices(const Polygons& polygons) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_POLYFILE_H
