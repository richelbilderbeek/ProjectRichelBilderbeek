#ifndef CONSTCOORDINAT2D_H
#define CONSTCOORDINAT2D_H

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

  //void SetX(const double x) noexcept { m_co[0] = x; }
  //void SetY(const double y) noexcept { m_co[1] = y; }

  //ConstCoordinat2D& operator+=(const ConstCoordinat2D& rhs) noexcept;
  //ConstCoordinat2D& operator-=(const ConstCoordinat2D& rhs) noexcept;

  private:
  ConstCoordinat2D(const ConstCoordinat2D&) = delete;
  ConstCoordinat2D& operator=(const ConstCoordinat2D&) = delete;
  virtual ~ConstCoordinat2D() noexcept {}
  friend void boost::checked_delete<>(ConstCoordinat2D*);
  friend void boost::checked_delete<>(const ConstCoordinat2D*);

  static const int dimensionality = 2;
  const std::array<double,dimensionality> m_co;

  //friend const ConstCoordinat2D operator*(
  //  const double scalar,
  //  const ConstCoordinat2D& v) noexcept;
};

double Distance(const ConstCoordinat2D& lhs,const ConstCoordinat2D& rhs) noexcept;

double DotProduct(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2) noexcept;

///Distance to origin
double Length(const boost::shared_ptr<const ConstCoordinat2D> v) noexcept;

const boost::shared_ptr<const ConstCoordinat2D> Scale(
  const double scalar,
  const boost::shared_ptr<const ConstCoordinat2D> v
) noexcept;

bool operator==(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept;
bool operator<(const ConstCoordinat2D& lhs, const ConstCoordinat2D& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const ConstCoordinat2D& n) noexcept;


const boost::shared_ptr<const ConstCoordinat2D> operator+(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2
) noexcept;

const boost::shared_ptr<const ConstCoordinat2D> operator-(
  const boost::shared_ptr<const ConstCoordinat2D> v1,
  const boost::shared_ptr<const ConstCoordinat2D> v2
) noexcept;

} //~namespace ribi

#endif // CONSTCOORDINAT2D_H
