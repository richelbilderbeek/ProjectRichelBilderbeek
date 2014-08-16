#ifndef RIBI_OPENFOAMPOINTSFILEITEM_H
#define RIBI_OPENFOAMPOINTSFILEITEM_H

#include <array>
#include <vector>
#include <iosfwd>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace foam {

///An item in an OpenFOAM 'points' file
struct PointsFileItem
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  explicit PointsFileItem(
    const Coordinat3D& coordinat = Coordinat3D(0.0, 0.0, 0.0)
  );

  const Coordinat3D& GetCoordinat() const noexcept { return m_coordinat; }
        Coordinat3D& GetCoordinat()       noexcept { return m_coordinat; }

  private:

  Coordinat3D m_coordinat;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamPointsFile;
  friend std::istream& operator>>(std::istream& is, PointsFileItem& f);
};

bool operator==(const PointsFileItem& lhs, const PointsFileItem& rhs) noexcept;
bool operator!=(const PointsFileItem& lhs, const PointsFileItem& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const PointsFileItem& f) noexcept;
std::istream& operator>>(std::istream& is, PointsFileItem& f);

} //~namespace foam
} //~namespace ribi



#endif // RIBI_OPENFOAMPOINTSFILEITEM_H
