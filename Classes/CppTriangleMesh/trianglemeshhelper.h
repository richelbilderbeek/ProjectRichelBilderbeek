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

#include "constcoordinat2d.h"
#include "coordinat3d.h"
#include "trianglemeshfwd.h"
#include "trianglemeshwinding.h"

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

///Calculate the point in the center of the collection of edges
const Coordinat3D CalcCenter(const std::vector<boost::shared_ptr<Edge>>& edges) noexcept;

///Find out the Winding of the edges
///knowing that all edges are in the same XY plane
///when viewed from above (at an infinite Z coordinat)
Winding CalcWindingHorizontal(const std::vector<boost::shared_ptr<const Edge>>& edges);

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
bool IsClockwiseHorizontal(
  const boost::shared_ptr<const Edge> edge,
  const Coordinat3D& center
) noexcept;

///Are the points ordered clockwise in the XY plane seen from above
/// (e.g. from coordinat {0,0,1} )
bool IsClockwiseHorizontal(const std::vector<boost::shared_ptr<Point>>& points) noexcept;

///Are the points ordered clockwise in the XY plane seen from above
/// (e.g. from coordinat {0,0,1} )
bool IsClockwiseVertical(
  const std::vector<boost::shared_ptr<Point>>& points,
  const boost::shared_ptr<const Point>& observer
) noexcept;

///Set the edges to get a certain Winding,
///knowing that all edges are in the same XY plane
///when viewed from above (at an infinite Z coordinat)
void SetWindingHorizontal(std::vector<boost::shared_ptr<Edge>>& edges,const Winding winding);

} //~namespace trim
} //~namespace ribi

#endif // TRIANGLEMESHHELPER_H
