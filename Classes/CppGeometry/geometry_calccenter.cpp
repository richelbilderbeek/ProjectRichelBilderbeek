#include "geometry.h"

ribi::Geometry::ApCoordinat2D ribi::Geometry::CalcCenter(const ApCoordinats2D& points) const noexcept
{
  ApCoordinat2D sum(0.0,0.0);
  for (const auto& point: points)
  {
    sum.x(sum.x() + point.x());
    sum.y(sum.y() + point.y());
  }
  const double n { static_cast<double>(points.size()) };
  const ApCoordinat2D center(
    sum.x() / n,
    sum.y() / n
  );
  return center;

}

ribi::Geometry::ApCoordinat3D ribi::Geometry::CalcCenter(const ApCoordinats3D& points) const noexcept
{
  Apfloat sum_x = 0.0;
  Apfloat sum_y = 0.0;
  Apfloat sum_z = 0.0;
  for (const auto& point: points)
  {
    sum_x += boost::geometry::get<0>(point);
    sum_y += boost::geometry::get<1>(point);
    sum_z += boost::geometry::get<2>(point);
  }
  const Apfloat n { static_cast<double>(points.size()) };
  const ApCoordinat3D center(
    sum_x / n,
    sum_y / n,
    sum_z / n
  );
  return center;
}
