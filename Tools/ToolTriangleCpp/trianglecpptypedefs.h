#ifndef TRIANGLECPPTYPEDEFS_H
#define TRIANGLECPPTYPEDEFS_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include <boost/units/quantity.hpp>
#pragma GCC diagnostic pop

namespace ribi {
namespace tricpp {

//Temporary
typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
typedef boost::units::quantity<boost::units::si::area> Area;
typedef boost::units::quantity<boost::units::si::length> Length;
typedef boost::geometry::model::d2::point_xy<double> Coordinat;
typedef boost::geometry::model::polygon<Coordinat> Polygon;
typedef std::vector<Polygon> Polygons;

using boost::units::si::meter;
using boost::units::si::radian;

} //~namespace tricpp
} //~namespace ribi

#endif // TRIANGLECPPTYPEDEFS_H
