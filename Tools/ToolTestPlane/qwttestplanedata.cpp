#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qwttestplanedata.h"

#include <cassert>

#include <boost/make_shared.hpp>

#include "geometry.h"
#include "plane.h"

#pragma GCC diagnostic pop


ribi::QwtTestPlaneData::QwtTestPlaneData(
  const boost::shared_ptr<Plane>& plane,
  const std::function<Coordinat3D(const double, const double)>& f,
  const double minx, const double maxx,
  const double miny, const double maxy
  )
  : m_f(f),
    m_plane(plane)
{
  assert(m_plane);

  setInterval(Qt::XAxis,QwtInterval(minx,maxx));
  setInterval(Qt::YAxis,QwtInterval(miny,maxy));
  setInterval(Qt::ZAxis,QwtInterval(0.0,1.0)); //Yes (1.0) or no (0.0) in plane
}

double ribi::QwtTestPlaneData::value(const double x, const double y) const noexcept
{
  assert(m_plane);
  try
  {
    const auto co_double = m_f(x,y);
    const Plane::Coordinat3D co_apfloat(
      apfloat(boost::geometry::get<0>(co_double)),
      apfloat(boost::geometry::get<1>(co_double)),
      apfloat(boost::geometry::get<2>(co_double))
    );
    const auto error_apfloat = m_plane->CalcError(co_apfloat);
    return Geometry().ToDoubleSafe(error_apfloat);
    //return m_plane->CalcDistanceFromPlane(m_f(x,y));
  }
  catch (std::exception&)
  {
    assert(!"Should not get here");
    return 0.0;
  }
  /*
  const double c = 0.842;

  const double v1 = x * x + ( y - c ) * ( y + c );
  const double v2 = x * ( y + c ) + x * ( y + c );

  return 1.0 / ( v1 * v1 + v2 * v2 );
  */
}
