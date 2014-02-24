#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshhelper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>

#include "Shiny.h"

#include "constcoordinat2d.h"
#include "coordinat3d.h"
#include "trace.h"
#include "trianglemeshpoint.h"
#include "trianglemeshface.h"

#pragma GCC diagnostic pop

/*
double ribi::trim::DotProduct(const ribi::Coordinat3D& v1,const ribi::Coordinat3D& v2)
{
  PROFILE_FUNC();
  //Don't use v1.GetZ() and v2.GetZ() as the original code didn't as well
  return
      ( v1.GetX() * v2.GetX())
    + ( v1.GetY() * v2.GetY())
  ;
}
*/

/*
const std::string ribi::trim::FormatDigitsBehindTheComma(const double x, const int n)
{
  PROFILE_FUNC();
  std::stringstream s;
  s << std::setprecision(n) << std::fixed << x;
  const std::string t = s.str();
  return t;
}
*/
/*
const ribi::Coordinat3D ribi::trim::vOut(
  const ribi::Coordinat3D& v1,
  const ribi::Coordinat3D& v2)
{
  PROFILE_FUNC();
  return ribi::Coordinat3D(
    (v1.GetY()*v2.GetZ())-(v1.GetZ()*v2.GetY()),
    (v1.GetZ()*v2.GetX())-(v1.GetX()*v2.GetZ()),
    (v1.GetX()*v2.GetY())-(v1.GetY()*v2.GetX())
  );
}
*/

double ribi::trim::Fmod(const double x, const double mod) noexcept
{
  assert(mod != 0.0); //Cannot divide by zero
  return x - (mod * static_cast<int>(x / mod));
}

double ribi::trim::GetAngle(const double dx, const double dy) noexcept
{
  const double pi = boost::math::constants::pi<double>();
  const double tau = boost::math::constants::two_pi<double>();
  double angle = pi - (std::atan2(dx,dy));
  assert(angle < tau);
  if (angle < 0.0) angle += tau;
  if (angle >= tau) angle -= tau;
  assert(angle >= 0.0);
  assert(angle < tau);
  return angle;
}

double ribi::trim::GetAngle(const boost::shared_ptr<const Point> point) noexcept
{
  return GetAngle(point->GetCoordinat()->GetX(),point->GetCoordinat()->GetY());
}

bool ribi::trim::IsClockwise(const std::vector<boost::shared_ptr<Point>>& points) noexcept
{
  assert(points.size() == 3);
  const double tau = boost::math::constants::two_pi<double>();
  assert(GetAngle(points[0]) >= 0.0);
  assert(GetAngle(points[0]) <= tau);
  assert(GetAngle(points[1]) >= 0.0);
  assert(GetAngle(points[1]) <= tau);
  assert(GetAngle(points[2]) >= 0.0);
  assert(GetAngle(points[2]) <= tau);
  TRACE(GetAngle(points[0]));
  TRACE(GetAngle(points[1]));
  TRACE(GetAngle(points[2]));

  const bool is_clockwise {
       GetAngle(points[0]) < GetAngle(points[1])
    && GetAngle(points[1]) < GetAngle(points[2])
  };
  TRACE(is_clockwise);
  return is_clockwise;
}
