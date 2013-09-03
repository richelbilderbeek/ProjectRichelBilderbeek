#ifndef POLARCOORDINAT_H
#define POLARCOORDINAT_H

#include <cassert>
#include <cmath>
#include "coordinat.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/math/constants/constants.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/prefixes.hpp>
#include "is_about_equal.h"
#include "trace.h"
#pragma GCC diagnostic pop

template <class Angle, class Length>
struct PolarCoordinat
{
  PolarCoordinat(const Angle& angle, const Length& length);
  PolarCoordinat(const Length& x, const Length& y);

  ///Add a polar coordinat
  PolarCoordinat& operator+=(const PolarCoordinat& pc);

  static const Angle CalcAngle(const Length& dx, const Length& dy);

  static const Length CalcLength(const Length& dx, const Length& dy);

  const Angle& GetAngle() const { return m_angle; }

  const Length& GetLength() const { return m_length; }

  void SetAngle(const Angle& angle) { m_angle = angle; }

  ///Test this class
  static void Test();


  ///Translate with a coordinat
  void Translate(const Coordinat<Length>& c);

  private:
  ///The angle
  ///0.0 pi rad = 12 o'clock
  ///0.5 pi rad =  3 o'clock
  ///1.0 pi rad =  6 o'clock
  ///1.5 pi rad =  9 o'clock
  Angle m_angle;

  Length m_length;

};

template <class T, class U>
T CalculateSqrt(const U& x);

template <class Angle,class Length>
Coordinat<Length> ToCoordinat(const PolarCoordinat<Angle,Length>& c)
{
  return Coordinat<Length>(
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
    * boost::units::si::radian);
}


template <class Angle, class Length>
const Length PolarCoordinat<Angle,Length>::CalcLength(const Length& dx, const Length& dy)
{
  //return Length(std::sqrt(((dx*dx)+(dy*dy)).value()) * meter);
  return Length(
    CalculateSqrt<boost::units::quantity<boost::units::si::length> >(
      (dx*dx)+(dy*dy)
    )
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
  {
    const PolarCoordinat<Angle,Length> p(
      Angle(0.0 * boost::math::constants::pi<double>() * radian),
      Length(1.0 * meter)
    );
    const Coordinat<Length> c(ToCoordinat(p));
    assert(c.GetX() > Length(-1.0 * micro * meter));
    assert(c.GetX() < Length( 1.0 * micro * meter));
    assert(c.GetY() > Length(-1.00001 * meter));
    assert(c.GetY() < Length(-0.99999 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(0.5 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat<Length> c(ToCoordinat(p));
    assert(c.GetY() > Length(-1.0 * micro * meter));
    assert(c.GetY() < Length( 1.0 * micro * meter));
    assert(c.GetX() > Length(0.99999 * meter));
    assert(c.GetX() < Length(1.00001 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(1.0 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat<Length> c(ToCoordinat(p));
    assert(c.GetX() > Length(-1.0 * micro * meter));
    assert(c.GetX() < Length( 1.0 * micro * meter));
    assert(c.GetY() > Length(0.99999 * meter));
    assert(c.GetY() < Length(1.00001 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(1.5 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat<Length> c(ToCoordinat(p));
    assert(c.GetY() > Length(-1.0 * micro * meter));
    assert(c.GetY() < Length( 1.0 * micro * meter));
    assert(c.GetX() > Length(-1.00001 * meter));
    assert(c.GetX() < Length(-0.99999 * meter));
  }
  {
    const PolarCoordinat<Angle,Length> p(Angle(2.0 * boost::math::constants::pi<double>() * radian),Length(1.0 * meter));
    const Coordinat<Length> c(ToCoordinat(p));
    assert(c.GetX() > Length(-1.0 * micro * meter));
    assert(c.GetX() < Length( 1.0 * micro * meter));
    assert(c.GetY() > Length(-1.00001 * meter));
    assert(c.GetY() < Length(-0.99999 * meter));
  }
  //Translate
  {
    const PolarCoordinat<Angle,Length> c(Length(1.0 * meter),Length(1.0 * meter));
    PolarCoordinat<Angle,Length> d(c);
    d.Translate(Coordinat<Length>(Length(2.0 * meter),Length(2.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),d.GetAngle(),Angle(1.0 * nano * radian)));
  }
  {
    const PolarCoordinat<Angle,Length> c(Length(-1.0 * meter),Length(1.0 * meter));
    PolarCoordinat<Angle,Length> d(c);
    d.Translate(Coordinat<Length>(Length(-2.0 * meter),Length(2.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),d.GetAngle(),Angle(1.0 * nano * radian)));
  }
  {
    const PolarCoordinat<Angle,Length> c(Length( 3.0 * meter),Length( 4.0 * meter));
    const PolarCoordinat<Angle,Length> d(Length(-3.0 * meter),Length(-4.0 * meter));
    PolarCoordinat<Angle,Length> e(d);
    e.Translate(Coordinat<Length>(Length(6.0 * meter),Length(8.0 * meter)));
    assert(IsAboutEqual(c.GetAngle(),e.GetAngle(),Angle(1.0 * nano * radian)));
    assert(IsAboutEqual(c.GetLength(),e.GetLength(),Length(1.0 * nano * meter)));
  }
}

template <class Angle, class Length>
void PolarCoordinat<Angle,Length>::Translate(const Coordinat<Length>& c)
{
  Coordinat<Length> old_coordinat(ToCoordinat(*this));
  old_coordinat.Translate(c);
  const PolarCoordinat<Angle,Length> new_coordinat(old_coordinat.GetX(),old_coordinat.GetY());
  m_angle = new_coordinat.GetAngle();
  m_length = new_coordinat.GetLength();
}

#endif // POLARCOORDINAT_H
