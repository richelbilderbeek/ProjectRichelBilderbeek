#ifndef COORDINAT3D_H
#define COORDINAT3D_H

#include <array>
#include <iosfwd>

namespace ribi {

///An X-Y-Z coordinat
//Note: I dislike to write this class: I wish there was a library (STL, Boost)
//with an alternative.
struct Coordinat3D
{
  Coordinat3D(
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

  private:
  static const int dimensionality = 3;
  std::array<double,dimensionality> m_co;
};

bool operator==(const Coordinat3D& lhs, const Coordinat3D& rhs);
std::ostream& operator<<(std::ostream& os, const Coordinat3D& n);

const Coordinat3D operator-(
  const Coordinat3D& v1,
  const Coordinat3D& v2);

const Coordinat3D operator+(
  const Coordinat3D& v1,
  const Coordinat3D& v2);

double Length(const Coordinat3D& v);

} //~namespace ribi

#endif // COORDINAT3D_H
