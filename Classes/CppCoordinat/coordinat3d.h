#ifndef COORDINAT3D_H
#define COORDINAT3D_H

#include <array>
#include <iosfwd>
#include <vector>

namespace ribi {

///An X-Y-Z coordinat
//Note: I dislike to write this class: I wish there was a library (STL, Boost)
//with an alternative.
struct Coordinat3D
{
  explicit Coordinat3D(
    const double x = 0.0,
    const double y = 0.0,
    const double z = 0.0
  );
  void ChangeX(const double dx) noexcept { m_co[0] += dx; }
  void ChangeY(const double dy) noexcept { m_co[1] += dy; }
  void ChangeZ(const double dz) noexcept { m_co[2] += dz; }

  double GetX() const noexcept { return m_co[0]; }
  double GetY() const noexcept { return m_co[1]; }
  double GetZ() const noexcept { return m_co[2]; }

  void SetX(const double x) noexcept { m_co[0] = x; }
  void SetY(const double y) noexcept { m_co[1] = y; }
  void SetZ(const double z) noexcept { m_co[2] = z; }

  Coordinat3D& operator+=(const Coordinat3D& rhs) noexcept;
  Coordinat3D& operator-=(const Coordinat3D& rhs) noexcept;

  Coordinat3D& operator/=(const double f);
  Coordinat3D& operator*=(const double f) noexcept;

  private:
  static const int dimensionality = 3;
  std::array<double,dimensionality> m_co;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Coordinat3D& lhs, const Coordinat3D& rhs);
bool operator<(const Coordinat3D& lhs, const Coordinat3D& rhs);
std::ostream& operator<<(std::ostream& os, const Coordinat3D& n);

const Coordinat3D operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2);

const Coordinat3D operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2);

///Divide all components of the coordinat by f
const Coordinat3D operator/(
  const Coordinat3D& c,
  const double f);

///Multiply all components of the coordinat by f
const Coordinat3D operator*(
  const Coordinat3D& c,
  const double f) noexcept;

///Calculate the point in the center of the collection of points
const Coordinat3D CalcCenter(const std::vector<Coordinat3D>& points) noexcept;

///Calculate the cross product
const ribi::Coordinat3D CalcCrossProduct(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b
) noexcept;

///Calculate the cross product
double CalcDotProduct(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b
) noexcept;

///Calculate the normal of a triangle
///The normal will be (0,0,-1) if a,b and c lie in the XY plane and ordered clockwise (when viewed from above)
///The normal will be (0,0, 1) if a,b and c lie in the XY plane and ordered counter-clockwise (when viewed from above)
///I use this convention as it appears to be used most extensively
const ribi::Coordinat3D CalcNormal(
  const ribi::Coordinat3D& a,
  const ribi::Coordinat3D& b,
  const ribi::Coordinat3D& c
) noexcept;

///Calculate the distance between two coordinats
double Distance(const Coordinat3D& lhs,const Coordinat3D& rhs);

///When viewing a coordinat as a vector from origin, calculate its length
double Length(const Coordinat3D& v);

} //~namespace ribi

#endif // COORDINAT3D_H
