#ifndef POLYFILEFROMPOLYGONS_H
#define POLYFILEFROMPOLYGONS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/polygon.hpp>

#include "polyfile.h"
#pragma GCC diagnostic pop

namespace ribi {

///Class to contruct a PolyFile from Polygons
struct PolyFileFromPolygons
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Polygon> Polygons;

  PolyFileFromPolygons(const Polygons& shapes);

  const PolyFile& GetPolyFile() const noexcept { return m_polyfile; }
  const Polygons& GetPolygons() const noexcept { return m_polygons; }

  static std::string GetVersion() noexcept;
  static std::vector<std::string> GetVersionHistory() noexcept;

  std::string ToStr() const noexcept;

  private:
  const PolyFile m_polyfile;
  const Polygons m_polygons;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static PolyFile::Edges ToEdges(const Polygons& polygons) noexcept;
  static PolyFile::Vertices ToVertices(const Polygons& polygons) noexcept;
};

//std::ostream& operator<<(std::ostream& os, const PolyFileFromPolygons& polyfile) noexcept;
std::ostream& operator<<(std::ostream& os, const boost::shared_ptr<PolyFileFromPolygons>& polyfile) = delete;
std::ostream& operator<<(std::ostream& os, const boost::shared_ptr<const PolyFileFromPolygons>& polyfile) = delete;

} //~namespace ribi

#endif // POLYFILEFROMPOLYGONS_H
