#include "geometry.h"

template <class T>
boost::geometry::model::point<T,3,boost::geometry::cs::cartesian>
CalcCrossProductImpl(
  const boost::geometry::model::point<T,3,boost::geometry::cs::cartesian>& a,
  const boost::geometry::model::point<T,3,boost::geometry::cs::cartesian>& b)
{
  using boost::geometry::get;
  return boost::geometry::model::point<T,3,boost::geometry::cs::cartesian>(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
}

ribi::Geometry::Coordinat3D ribi::Geometry::CalcCrossProduct(
  const Coordinat3D& a,
  const Coordinat3D& b
) const noexcept
{
  return CalcCrossProductImpl<double>(a,b);
  /*
  using boost::geometry::get;
  return Coordinat3D(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
  */
}

ribi::Geometry::ApCoordinat3D ribi::Geometry::CalcCrossProduct(
  const ApCoordinat3D& a,
  const ApCoordinat3D& b
) const noexcept
{
  return CalcCrossProductImpl<apfloat>(a,b);
  /*
  using boost::geometry::get;
  return ApCoordinat3D(
    (get<1>(a) * get<2>(b)) - (get<2>(a) * get<1>(b)),
    (get<2>(a) * get<0>(b)) - (get<0>(a) * get<2>(b)),
    (get<0>(a) * get<1>(b)) - (get<1>(a) * get<0>(b))
  );
  */
}
