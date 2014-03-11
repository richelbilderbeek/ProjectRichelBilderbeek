#ifndef CONSTCOORDINAT2D_H
#define CONSTCOORDINAT2D_H

//typedef boost::geometry::model::d2::point_xy<double> ConstCoordinat2D;

#ifdef USE_CUSTOM_RIBI_CONSTCOORDINAT2D

#include <array>
#include <iosfwd>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///An immutable X-Y coordinat
//Note: I dislike to write this class: I wish there was a library (STL, Boost)
//with an alternative.
struct ConstCoordinat2D
{
  ConstCoordinat2D(
    const double x = 0.0,
    const double y = 0.0
  ) noexcept;


  double GetX() const noexcept { return m_co[0]; }
  double GetY() const noexcept { return m_co[1]; }

  private:
  ConstCoordinat2D(const ConstCoordinat2D&) = delete;
  ConstCoordinat2D& operator=(const ConstCoordinat2D&) = delete;
  virtual ~ConstCoordinat2D() noexcept {}
  friend void boost::checked_delete<>(ConstCoordinat2D*);
  friend void boost::checked_delete<>(const ConstCoordinat2D*);

  static const int dimensionality = 2;
  const std::array<double,dimensionality> m_co;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

double Distance(const ConstCoordinat2D& lhs,const ConstCoordinat2D& rhs) noexcept;

double DotProduct(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2) noexcept;

///Distance to origin
double Length(const boost::shared_ptr<const ConstCoordinat2D> v) noexcept;

boost::shared_ptr<const ConstCoordinat2D> Scale(
  const double scalar,
  const boost::shared_ptr<const ConstCoordinat2D> v
) noexcept;

bool operator==(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept;
bool operator<(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const ConstCoordinat2D& n) noexcept;


boost::shared_ptr<const ConstCoordinat2D> operator+(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2
) noexcept;

boost::shared_ptr<const ConstCoordinat2D> operator-(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2
) noexcept;

} //~namespace ribi

#endif

#endif // CONSTCOORDINAT2D_H

