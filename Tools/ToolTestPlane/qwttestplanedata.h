#ifndef QWTTESTPLANEDATA_H
#define QWTTESTPLANEDATA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#include "qwt_matrix_raster_data.h"
#pragma GCC diagnostic pop


namespace ribi {

struct Plane;

///The spectrogram data
struct QwtTestPlaneData: public QwtRasterData
{
  typedef boost::geometry::model::point<double,3,boost::geometry::cs::cartesian> Coordinat3D;

  //f converts the x and y of the plot to the X,Y and Z coordinat of the X/Y/Z cut of the plane
  QwtTestPlaneData(
    const boost::shared_ptr<Plane>& plane,
    const std::function<Coordinat3D(const double, const double)>& f,
    const double minx = -1.0, const double maxx = 1.0,
    const double miny = -1.0, const double maxy = 1.0
  );
  double value(const double x, const double y) const noexcept;

  private:
  const std::function<Coordinat3D(const double, const double)> m_f;
  const boost::shared_ptr<Plane> m_plane;
};

} //~namespace ribi


#endif // QWTTESTPLANEDATA_H
