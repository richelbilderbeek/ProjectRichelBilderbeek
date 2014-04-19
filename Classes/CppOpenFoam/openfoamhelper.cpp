#include "openfoamhelper.h"

#include <sstream>
#include "xml.h"

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::foam::Add(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  return lhs + rhs;
}

std::string ribi::foam::ToStr(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept
{
  std::stringstream s;
  s
    << "(" << boost::geometry::get<0>(p)
    << "," << boost::geometry::get<1>(p)
    << "," << boost::geometry::get<2>(p)
    << ")"
  ;

  return s.str();
}

std::string ribi::foam::ToXml(const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p) noexcept
{
  std::stringstream s;
  s
    << ribi::xml::ToXml("x",boost::geometry::get<0>(p))
    << ribi::xml::ToXml("y",boost::geometry::get<1>(p))
    << ribi::xml::ToXml("z",boost::geometry::get<2>(p));

  std::stringstream t;
  t << ribi::xml::ToXml("coordinat3d",s.str());
  return t.str();
}

bool ribi::foam::operator==(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  return
       boost::geometry::get<0>(lhs) == boost::geometry::get<0>(rhs)
    && boost::geometry::get<1>(lhs) == boost::geometry::get<1>(rhs)
    && boost::geometry::get<2>(lhs) == boost::geometry::get<2>(rhs)
  ;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::foam::operator+(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  typedef std::remove_const<std::remove_reference<decltype(lhs)>::type>::type ReturnType;
  return ReturnType(
    boost::geometry::get<0>(lhs) + boost::geometry::get<0>(rhs),
    boost::geometry::get<1>(lhs) + boost::geometry::get<1>(rhs),
    boost::geometry::get<2>(lhs) + boost::geometry::get<2>(rhs)
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& ribi::foam::operator+=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& lhs,
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& rhs
) noexcept
{
  lhs = lhs + rhs;
  return lhs;
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> ribi::foam::operator/(
  const boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p,
  const double factor
) noexcept
{
  typedef std::remove_const<std::remove_reference<decltype(p)>::type>::type ReturnType;
  return ReturnType(
    boost::geometry::get<0>(p) / factor,
    boost::geometry::get<1>(p) / factor,
    boost::geometry::get<2>(p) / factor
  );
}

boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& ribi::foam::operator/=(
  boost::geometry::model::point<double,3,boost::geometry::cs::cartesian>& p,
  const double factor
) noexcept
{
  p = p / factor;
  return p;
}
