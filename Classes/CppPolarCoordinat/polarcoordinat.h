#ifndef POLARCOORDINAT_H
#define POLARCOORDINAT_H

#include <cassert>
#include <cmath>

//#include "coordinat.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/units/base_units/angle/radian.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include "trace.h"
#pragma GCC diagnostic pop

namespace ribi {

template <class Angle, class Length>
struct PolarCoordinat
{
  typedef boost::geometry::model::d2::point_xy<Length> Coordinat;
  explicit PolarCoordinat(const Angle& angle, const Length& length);
  explicit PolarCoordinat(const Length& x, const Length& y);

  ///Add a polar coordinat by putting the second's tail on the
  ///head of this PolarCoordinat
  PolarCoordinat& operator+=(const PolarCoordinat& pc);

  static const Angle CalcAngle(const Length& dx, const Length& dy);

  static const Length CalcLength(const Length& dx, const Length& dy);

  ///Get the angle of this polar coordinat
  ///0.0 pi rad = 12 o'clock
  ///0.5 pi rad =  3 o'clock
  ///1.0 pi rad =  6 o'clock
  ///1.5 pi rad =  9 o'clock
  const Angle& GetAngle() const { return m_angle; }

  ///Get the length of this coordinat, which equals its distance to the origin
  const Length& GetLength() const { return m_length; }

  void SetAngle(const Angle& angle) { m_angle = angle; }

  ///Test this class
  static void Test();


  ///Translate with a coordinat
  void Translate(const Coordinat& c);

  private:
  ///The angle
  ///0.0 pi rad = 12 o'clock
  ///0.5 pi rad =  3 o'clock
  ///1.0 pi rad =  6 o'clock
  ///1.5 pi rad =  9 o'clock
  Angle m_angle;

  Length m_length;

};

/*
template <class T, class U>
T CalculateSqrt(const U& x);
*/

template <class Angle,class Length>
boost::geometry::model::d2::point_xy<Length> ToCoordinat(const PolarCoordinat<Angle,Length>& c)
{
  return boost::geometry::model::d2::point_xy<Length>(
     std::sin(c.GetAngle().value()) * c.GetLength(),
    -std::cos(c.GetAngle().value()) * c.GetLength()
  );
}

template <class Angle, class Length>
PolarCoordinat<Angle,Length>::PolarCoordinat(const Angle& angle, const Length& length)
  : m_angle(angle), m_length(length)
{
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Angle, class Length>
PolarCoordinat<Angle,Length>::PolarCoordinat(const Length& x, const Length& y)
  : m_angle(CalcAngle(x,y)), m_length(CalcLength(x,y))
{
  #ifndef NDEBUG
  Test();
  #endif
}

template <class Angle, class Length>
const Angle PolarCoordinat<Angle,Length>::CalcAngle(const Length& dx, const Length& dy)
{
  const double half_pi = boost::math::constants::half_pi<double>();
  return Angle(
    (half_pi + std::atan2(dy.value(),dx.value()))
    * boost::units::si::radians);
}


template <class Angle, class Length>
const Length PolarCoordinat<Angle,Length>::CalcLength(const Length& dx, const Length& dy)
{
  const double a { dx.value() };
  const double b { dy.value() };
  return std::sqrt((a*a)+(b*b)) * boost::units::si::meter;
}

template <class T>
bool IsAboutEqual(
  const boost::units::quantity<T>& lhs,
  const boost::units::quantity<T>& rhs,
  const boost::units::quantity<T>& max_error)
{
  return lhs < rhs
    ? lhs + max_error > rhs
    : rhs + max_error > lhs;
}

template <class Angle,class Length>
PolarCoordinat<Angle,Length> operator+(
  const PolarCoordinat<Angle,Length>& a,
  const PolarCoordinat<Angle,Length>& b
  )
{
  return PolarCoordinat<Angle,Length>(
    boost::geometry::get<0>(ToCoordinat(a)) + boost::geometry::get<0>(ToCoordinat(b)),
    boost::geometry::get<1>(ToCoordinat(a)) + boost::geometry::get<1>(ToCoordinat(b))
  );
}

template <class Angle, class Length>
void PolarCoordinat<Angle,Length>::Test()
{
  {
    static bool is_tested { false };
    if (is_tested) return;
    is_tested = true;
  }
  #ifdef SHOW_CALCANGLE_SERIES
  TRACE(CalcAngle(Length( 1.0 * meter),Length(-1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length( 1.0 * meter),Length( 0.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length( 1.0 * meter),Length( 1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length( 0.0 * meter),Length( 1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length(-1.0 * meter),Length( 1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length(-1.0 * meter),Length( 0.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length(-1.0 * meter),Length(-1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  TRACE(CalcAngle(Length( 0.0 * meter),Length(-1.0 * meter)) / Angle(boost::math::constants::pi<double>() * radian));
  #endif
  using boost::units::si::meter;
  using boost::units::si::micro;
  using boost::units::si::nano;
  using boost::units::si::radian;
  assert(IsAboutEqual(CalcAngle(Length( 1.0 * meter),Length(-1.0 * meter)),Angle( 0.25 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length( 1.0 * meter),Length( 0.0 * meter)),Angle( 0.50 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length( 1.0 * meter),Length( 1.0 * meter)),Angle( 0.75 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length( 0.0 * meter),Length( 1.0 * meter)),Angle( 1.00 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length(-1.0 * meter),Length( 1.0 * meter)),Angle( 1.25 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length(-1.0 * meter),Length( 0.0 * meter)),Angle( 1.50 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  assert(IsAboutEqual(CalcAngle(Length(-1.0 * meter),Length(-1.0 * meter)),Angle(-0.25 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
  {
    PolarCoordinat c(Length(1.0 * nano * meter),Length(-1.0 * meter));
    assert(IsAboutEqual(c.GetAngle(),Angle(1.0 * nano * radian),Angle(1.0 * nano * radian)));
    assert(IsAboutEqual(c.GetLength(),Length(1.0 * meter),Length(1.0 * nano * meter)));
  }
  {
    PolarCoordinat c(Length(1.0 * meter),Length(1.0 * meter));
    assert(IsAboutEqual(c.GetAngle(),Angle(0.75 * boost::math::constants::pi<double>() * radian),Angle(1.0 * nano * radian)));
    assert(IsAboutEqual(c.GetLength(),Length(std::sqrt(2.0) * meter),Length(1.0 * nano * meter)));
  }
  //Conversion to Coordinat
  using boost::geometry::get;
  {
    const PolarCoordinat<Angle,Length> p(
      Angle(0.0 * boost::math::constants::pi<double>() * radian),
      Length(1.0 * meter)
    );
    const Coordinat c(ToCoordinat(p));
    assert(get<0>(c) > Length(-1.0 * micro * meter));
    assert(get<0>(c) < Length( 1.0 * micro * meter));
    assert(get<1>(c) > Length(-1.00001 * meter));
    assert(get<1>(c) < Length(-0.99999 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(0.5 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat c(ToCoordinat(p));
    assert(get<1>(c) > Length(-1.0 * micro * meter));
    assert(get<1>(c) < Length( 1.0 * micro * meter));
    assert(get<0>(c) > Length(0.99999 * meter));
    assert(get<0>(c) < Length(1.00001 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(1.0 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat c(ToCoordinat(p));
    assert(get<0>(c) > Length(-1.0 * micro * meter));
    assert(get<0>(c) < Length( 1.0 * micro * meter));
    assert(get<1>(c) > Length(0.99999 * meter));
    assert(get<1>(c) < Length(1.00001 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(1.5 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat c(ToCoordinat(p));
    assert(get<1>(c) > Length(-1.0 * micro * meter));
    assert(get<1>(c) < Length( 1.0 * micro * meter));
    assert(get<0>(c) > Length(-1.00001 * meter));
    assert(get<0>(c) < Length(-0.99999 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(2.0 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat c(ToCoordinat(p));
    assert(get<0>(c) > Length(-1.0 * micro * meter));
    assert(get<0>(c) < Length( 1.0 * micro * meter));
    assert(get<1>(c) > Length(-1.00001 * meter));
    assert(get<1>(c) < Length(-0.99999 * meter));
  }
  //Translate
  {
    const PolarCoordinat<Angle,Length> c(Length(1.0 * meter),Length(1.0 * meter));
    PolarCoordinat<Angle,Length> d(c);
    d.Translate(Coordinat(Length(2.0 * meter),Length(2.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),d.GetAngle(),Angle(1.0 * nano * radian)));
  }
  {
    const PolarCoordinat<Angle,Length> c(Length(-1.0 * meter),Length(1.0 * meter));
    PolarCoordinat<Angle,Length> d(c);
    d.Translate(Coordinat(Length(-2.0 * meter),Length(2.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),d.GetAngle(),Angle(1.0 * nano * radian)));
  }
  {
    const PolarCoordinat<Angle,Length> c(Length( 3.0 * meter),Length( 4.0 * meter));
    const PolarCoordinat<Angle,Length> d(Length(-3.0 * meter),Length(-4.0 * meter));
    PolarCoordinat<Angle,Length> e(d);
    e.Translate(Coordinat(Length(6.0 * meter),Length(8.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),e.GetAngle(),Angle(1.0 * nano * radian)));
    assert(IsAboutEqual(c.GetLength(),e.GetLength(),Length(1.0 * nano * meter)));
  }
}

template <class Angle, class Length>
void PolarCoordinat<Angle,Length>::Translate(const Coordinat& c)
{
  using boost::geometry::get;
  const Coordinat this_coordinat(ToCoordinat(*this));
  const Coordinat delta_coordinat(
    get<0>(this_coordinat) + get<0>(c),
    get<1>(this_coordinat) + get<1>(c)
  );
  const PolarCoordinat<Angle,Length> new_coordinat(
    get<0>(delta_coordinat),
    get<1>(delta_coordinat)
  );
  m_angle = new_coordinat.GetAngle();
  m_length = new_coordinat.GetLength();
}

} //~namespace ribi

#endif // POLARCOORDINAT_H
