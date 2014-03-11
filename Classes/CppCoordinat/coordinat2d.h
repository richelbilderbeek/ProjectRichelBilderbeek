#ifndef COORDINAT2D_H
#define COORDINAT2D_H

//typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;

#ifdef USE_CUSTOM_RIBI_COORDINAT2D

#include <array>
#include <iosfwd>
#include <vector>

namespace ribi {

///An X-Y coordinat
//Note: I dislike to write this class: I wish there was a library (STL, Boost)
//with an alternative.
struct Coordinat2D
{
  Coordinat2D(
    const double x = 0.0,
    const double y = 0.0
  ) noexcept;

  void ChangeX(const double dx) noexcept { m_co[0] += dx; }
  void ChangeY(const double dy) noexcept { m_co[1] += dy; }

  double GetX() const noexcept { return m_co[0]; }
  double GetY() const noexcept { return m_co[1]; }

  void SetX(const double x) noexcept { m_co[0] = x; }
  void SetY(const double y) noexcept { m_co[1] = y; }

  Coordinat2D& operator+=(const Coordinat2D& rhs) noexcept;
  Coordinat2D& operator-=(const Coordinat2D& rhs) noexcept;

  private:
  static const int dimensionality = 2;
  std::array<double,dimensionality> m_co;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Coordinat2D& lhs, const Coordinat2D& rhs) noexcept;
bool operator<(const Coordinat2D& lhs, const Coordinat2D& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Coordinat2D& n) noexcept;

///The dot product
double operator*(const Coordinat2D& v1,const Coordinat2D& v2) noexcept;

///Calculate the point in the center of the collection of points
Coordinat2D CalcCenter(const std::vector<Coordinat2D>& points) noexcept;

double Distance(const Coordinat2D& lhs,const Coordinat2D& rhs) noexcept;

///Distance to origin
double Length(const Coordinat2D& v) noexcept;

Coordinat2D Scale(
  const double scalar,
  const Coordinat2D& v
) noexcept;

Coordinat2D operator+(
  const Coordinat2D& v1,
  const Coordinat2D& v2) noexcept;

Coordinat2D operator*(
  const double scalar,
  const Coordinat2D& v) noexcept;

Coordinat2D operator-(
  const Coordinat2D& v1,
  const Coordinat2D& v2) noexcept;

} //~namespace ribi

#endif

#endif // COORDINAT2D_H
