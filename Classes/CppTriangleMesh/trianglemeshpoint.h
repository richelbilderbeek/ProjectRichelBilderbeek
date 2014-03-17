#ifndef TRIANGLEMESHPOINT_H
#define TRIANGLEMESHPOINT_H

#include <iosfwd>
#include <set>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
//
#include "trianglemeshfwd.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///An OpenFOAM point, as in the file 'points'
struct Point
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  const boost::shared_ptr<const Coordinat2D> GetCoordinat() const noexcept { return m_coordinat; }
  Coordinat3D GetCoordinat3D() const noexcept;

  bool CanGetZ() const noexcept;

  #ifdef USE_TRIANGLEMESHEDGE
  const std::set<boost::weak_ptr<Edge>>& GetBelongsTo() const noexcept { return m_belongs_to; }
  #endif
  const std::set<boost::weak_ptr<Face>>& GetConnected() const noexcept { return m_connected; }

  int GetIndex() const noexcept { return m_index; }

  const boost::units::quantity<boost::units::si::length> GetZ() const noexcept;

  ///Let the Point know its Z coordinat itself
  ///Similar to SetLayer
  ///Can be done exactly once
  void SetZ(const boost::units::quantity<boost::units::si::length> z) const noexcept; //const due to mutable

  std::string ToStr() const noexcept;
  std::string ToXml() const noexcept;

  private:
  Point(const Point&) = delete;
  Point& operator=(const Point&) = delete;
  ~Point() noexcept {}
  friend void boost::checked_delete<>(Point* x);

  friend class PointFactory;
  Point(
    const boost::shared_ptr<const Coordinat2D> coordinat,
    const int index,
    const PointFactory& lock
  );

  /// m_belongs_to must be mutable, because of the interdependent creation of
  /// Point and Edge: a Point needs to know the Edge it belongs to,
  /// an Edge consists of Point objects
  #ifdef USE_TRIANGLEMESHEDGE
  std::set<boost::weak_ptr<Edge>> m_belongs_to;
  #endif

  /// m_connected must be mutable, because of the interdependent creation of
  /// Point and Face: a Point needs to know the Face it is connected to,
  /// a Face consists of Point objects
  std::set<boost::weak_ptr<Face>> m_connected;

  const boost::shared_ptr<const Coordinat2D> m_coordinat;

  ///The index of this Point in an TriangleMeshBuilder vector. It is determined at the end
  mutable int m_index;

  mutable boost::shared_ptr<boost::units::quantity<boost::units::si::length>> m_z;

  #ifdef USE_TRIANGLEMESHEDGE
  friend class EdgeFactory;
  ///Points are connected to Edge in the Edge's construction
  void AddBelongsTo(const boost::weak_ptr<Edge> edge);
  #endif

  friend class FaceFactory;
  ///Points are connected to Faces in the Faces' construction
  void AddConnected(const boost::weak_ptr<Face> face);

  friend class TriangleMeshBuilder;
  ///Determined in the end
  void SetIndex(const int index) const noexcept { m_index = index; }

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Point& n);
};

bool operator==(const Point& lhs, const Point& rhs);
bool operator!=(const Point& lhs, const Point& rhs);
std::ostream& operator<<(std::ostream& os, const Point& n);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHPOINT_H
