#ifndef TRIANGLEMESHHELPER_H
#define TRIANGLEMESHHELPER_H

#include <algorithm>
#include <cassert>
#include <map>
#include <set>
#include <string>
#include <vector>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lexical_cast.hpp>

#include "trianglemeshfwd.h"
#include "constcoordinat2d.h"
#include "coordinat3d.h"

#pragma GCC diagnostic pop

namespace ribi {
namespace trim {

///Help adding constness a bit
template <class T>
const std::vector<boost::shared_ptr<const T> > AddConst(
  const std::vector<boost::shared_ptr<T> > v)
{
  return std::vector<boost::shared_ptr<const T> >(v.begin(),v.end());
}

//From http://www.richelbilderbeek.nl/CppCanLexicalCast.htm
template <class TargetType>
bool CanLexicalCast(const std::string& from)
{
  try
  {
    boost::lexical_cast<TargetType>(from);
  }
  catch (boost::bad_lexical_cast&)
  {
    return false;
  }
  catch (...)
  {
    assert(!"Something unexpected happened");
    throw;
  }
  return true;
}
const std::string FormatDigitsBehindTheComma(const double x, const int n);

double DotProduct(const ribi::Coordinat3D& v1,const ribi::Coordinat3D& v2);

///Obtain the angle in radians between two deltas
///12 o'clock is 0.0 * pi
/// 3 o'clock is 0.5 * pi
/// 6 o'clock is 1.0 * pi
/// 9 o'clock is 1.5 * pi
//From www.richelbilderbeek.nl/CppGetAngle.htm
double GetAngle(const double dx, const double dy) noexcept;

///Obtain the angle in radians between two deltas
///12 o'clock is 0.0 * pi
/// 3 o'clock is 0.5 * pi
/// 6 o'clock is 1.0 * pi
/// 9 o'clock is 1.5 * pi
double GetAngle(const boost::shared_ptr<const Point> point) noexcept;

bool IsClockwise(const std::vector<boost::shared_ptr<Point>>& points) noexcept;

const ribi::Coordinat3D vOut(
  const ribi::Coordinat3D& v1,
  const ribi::Coordinat3D& v2);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHHELPER_H
