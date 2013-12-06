#ifndef OPENFOAMPOINTSFILEITEM_H
#define OPENFOAMPOINTSFILEITEM_H

#include <array>
#include <vector>
#include <iosfwd>

namespace ribi {
namespace foam {

///An item in an OpenFOAM boundary file
struct PointsFileItem
{
  explicit PointsFileItem(
    const std::array<double,3>& coordinat = { 0.0, 0.0, 0.0}
  );

  const std::array<double,3>& GetCoordinat() const noexcept { return m_coordinat; }

  private:

  std::array<double,3> m_coordinat;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend class OpenFoamPointsFile;
  friend std::istream& operator>>(std::istream& is, PointsFileItem& f);
};

bool operator==(const PointsFileItem& lhs, const PointsFileItem& rhs);
bool operator!=(const PointsFileItem& lhs, const PointsFileItem& rhs);
std::ostream& operator<<(std::ostream& os, const PointsFileItem& f);
std::istream& operator>>(std::istream& is, PointsFileItem& f);

} //~namespace foam
} //~namespace ribi



#endif // OPENFOAMPOINTSFILEITEM_H
