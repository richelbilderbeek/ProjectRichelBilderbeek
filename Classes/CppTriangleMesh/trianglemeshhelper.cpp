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
#include "coordinat2d.h"
#include "coordinat3d.h"
#include "geometry.h"
#include "trace.h"
#include "trianglemeshpoint.h"
#include "trianglemeshface.h"

#pragma GCC diagnostic pop

double ribi::trim::GetAngle(const boost::shared_ptr<const Point> point) noexcept
{
  return Geometry().GetAngle(point->GetCoordinat()->GetX(),point->GetCoordinat()->GetY());
}

bool ribi::trim::IsClockwiseHorizontal(const std::vector<boost::shared_ptr<Point>>& points) noexcept
{
  assert(points.size() == 3);
  double center_x = 0.0;
  double center_y = 0.0;
  for (const auto point: points)
  {
    center_x += point->GetCoordinat()->GetX();
    center_y += point->GetCoordinat()->GetY();
  }
  center_x /= static_cast<double>(points.size());
  center_y /= static_cast<double>(points.size());

  //const double pi  = boost::math::constants::pi<double>();
  //const double tau = boost::math::constants::two_pi<double>();
  const bool a {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        points[0]->GetCoordinat()->GetX() - center_x,
        points[0]->GetCoordinat()->GetY() - center_y
      ),
      Geometry().GetAngle(
        points[1]->GetCoordinat()->GetX() - center_x,
        points[1]->GetCoordinat()->GetY() - center_y
      )
    )
  };
  const bool b {
    Geometry().IsClockwise(
      Geometry().GetAngle(
        points[1]->GetCoordinat()->GetX() - center_x,
        points[1]->GetCoordinat()->GetY() - center_y
      ),
      Geometry().GetAngle(
        points[2]->GetCoordinat()->GetX() - center_x,
        points[2]->GetCoordinat()->GetY() - center_y
      )
    )
  };
  //TRACE(a);
  //TRACE(b);
  const bool is_clockwise { a && b };
  //TRACE(is_clockwise);
  return is_clockwise;
}
