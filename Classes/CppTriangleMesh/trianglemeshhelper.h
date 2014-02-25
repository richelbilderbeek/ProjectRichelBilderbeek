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

///Obtain the angle in radians between two deltas
///12 o'clock is 0.0 * pi
/// 3 o'clock is 0.5 * pi
/// 6 o'clock is 1.0 * pi
/// 9 o'clock is 1.5 * pi
double GetAngle(const boost::shared_ptr<const Point> point) noexcept;

///Are the points ordered clockwise in the XY plane seen from above
/// (e.g. from coordinat {0,0,1} )
bool IsClockwiseHorizontal(const std::vector<boost::shared_ptr<Point>>& points) noexcept;

///Are the points ordered clockwise in the XY plane seen from above
/// (e.g. from coordinat {0,0,1} )
bool IsClockwiseVertical(
  const std::vector<boost::shared_ptr<Point>>& points,
  const boost::shared_ptr<const Point>& observer
) noexcept;

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHHELPER_H
