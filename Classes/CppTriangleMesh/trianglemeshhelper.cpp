#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "trianglemeshhelper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Shiny.h"

#include "constcoordinat2d.h"
#include "coordinat3d.h"
#include <boost/lexical_cast.hpp>
#pragma GCC diagnostic pop

const std::string ribi::trim::formatDigitsBehindTheComma(const double x, const int n)
{
  PROFILE_FUNC();
  std::stringstream s;
  s << std::setprecision(n) << std::fixed << x;
  const std::string t = s.str();
  return t;
}

double ribi::trim::DotProduct(const ribi::Coordinat3D& v1,const ribi::Coordinat3D& v2)
{
  PROFILE_FUNC();
  //Don't use v1.GetZ() and v2.GetZ() as the original code didn't as well
  return
      ( v1.GetX() * v2.GetX())
    + ( v1.GetY() * v2.GetY())
  ;
}

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
