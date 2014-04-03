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
#include <boost/make_shared.hpp>
#include "trianglemeshfwd.h"

#ifdef TRIANGLEMESH_USE_BOOST_SIGNALS2
#include <boost/signals2.hpp>
#endif //#ifdef TRIANGLEMESH_USE_BOOST_SIGNALS2

#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///An OpenFOAM point, as in the file 'points'
struct Point
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;
  typedef std::set<boost::weak_ptr<Face>,std::function<bool(boost::weak_ptr<const Face>,boost::weak_ptr<const Face>)>> WeakFaceSet;

  const boost::shared_ptr<const Coordinat2D> GetCoordinat() const noexcept { return m_coordinat; }
  Coordinat3D GetCoordinat3D() const noexcept;

  bool CanGetZ() const noexcept;

  const WeakFaceSet& GetConnected() const noexcept { return m_connected; }

  int GetIndex() const noexcept { return m_index; }

  const boost::units::quantity<boost::units::si::length> GetZ() const noexcept;

  ///Let the Point know its Z coordinat itself
  ///Similar to SetLayer
  ///Can be done exactly once
  void SetZ(const boost::units::quantity<boost::units::si::length> z) const noexcept; //const due to mutable

  std::string ToStr() const noexcept;
  std::string ToXml() const noexcept;

  #ifdef TRIANGLEMESH_USE_BOOST_SIGNALS2
  boost::signals2::signal<void(const Point*)> m_signal_destroyed;
  #endif //#ifdef TRIANGLEMESH_USE_BOOST_SIGNALS2

  private:
  Point(const Point&) = delete;
  Point& operator=(const Point&) = delete;
  ~Point() noexcept;
  friend void boost::checked_delete<>(      Point* x);
  friend void boost::checked_delete<>(const Point* x);
  friend class boost::detail::sp_ms_deleter<      Point>;
  friend class boost::detail::sp_ms_deleter<const Point>;

  friend class PointFactory;
  Point(
    const boost::shared_ptr<const Coordinat2D> coordinat,
    const int index,
    const PointFactory& lock
  );

  /// m_connected must be mutable, because of the interdependent creation of
  /// Point and Face: a Point needs to know the Face it is connected to,
  /// a Face consists of Point objects
  WeakFaceSet m_connected;

  const boost::shared_ptr<const Coordinat2D> m_coordinat;

  ///The index of this Point in an TriangleMeshBuilder vector. It is determined at the end
  mutable int m_index;

  mutable boost::shared_ptr<boost::units::quantity<boost::units::si::length>> m_z;

  friend class FaceFactory;
  ///Points are connected to Faces in the Faces' construction
  void AddConnected(const boost::weak_ptr<Face>& face);


  std::function<
    bool(
      const boost::weak_ptr<const ribi::trim::Face>& lhs,
      const boost::weak_ptr<const ribi::trim::Face>& rhs
    )
  >
  OrderByIndex() const noexcept;

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

bool operator<(const boost::shared_ptr<const Point>& lhs, const boost::shared_ptr<      Point>& rhs) = delete;
bool operator<(const boost::shared_ptr<const Point>& lhs, const boost::shared_ptr<const Point>& rhs) = delete;
bool operator<(const boost::shared_ptr<      Point>& lhs, const boost::shared_ptr<      Point>& rhs) = delete;
bool operator<(const boost::shared_ptr<      Point>& lhs, const boost::shared_ptr<const Point>& rhs) = delete;

std::ostream& operator<<(std::ostream& os, const Point& n);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHPOINT_H
