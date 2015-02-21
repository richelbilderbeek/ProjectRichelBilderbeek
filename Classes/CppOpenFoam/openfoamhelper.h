#ifndef RIBI_OPENFOAMHELPER_H
#define RIBI_OPENFOAMHELPER_H

//#include <iosfwd>
//#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/shared_ptr.hpp>
#ifndef _WIN32
#include <boost/geometry/geometries/polygon.hpp>
#endif
#include "openfoamfwd.h"
#pragma GCC diagnostic pop


namespace ribi {
namespace foam {



///Help adding constness a bit
template <class T>
std::vector<boost::shared_ptr<const T>> AddConst(
  const std::vector<boost::shared_ptr<T>> v)
{
  return std::vector<boost::shared_ptr<const T>>(std::begin(v),std::end(v));
}

std::string ToStr(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept;
std::string ToXml(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept;

bool operator==(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept;

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> operator+(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept;

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> operator/(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const double factor
) noexcept;

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& operator+=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept;

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& operator/=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p,
  const double factor
) noexcept;

//Name of operator+
boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Add(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept;

} //~namespace foam
} //~namespace ribi

#endif // RIBI_OPENFOAMHELPER_H
