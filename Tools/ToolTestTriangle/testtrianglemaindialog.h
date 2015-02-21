//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
Copyright (C) 2014-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestTriangle.htm
//---------------------------------------------------------------------------
#ifndef RIBI_TESTTRIANGLEMAINDIALOG_H
#define RIBI_TESTTRIANGLEMAINDIALOG_H

#ifdef DO_I_REALLY_USE_THIS_20140626

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/area.hpp>
//#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct TestTriangleMainDialog
{
  typedef boost::geometry::model::d2::point_xy<double> Coordinat;
  typedef boost::geometry::model::linestring<Coordinat> Linestring;
  typedef boost::geometry::model::polygon<Coordinat> Polygon;
  typedef std::vector<Linestring> Linestrings;
  typedef std::vector<Polygon> Polygons;
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;
  typedef std::pair<Polygons,Linestrings> Shapes;

  TestTriangleMainDialog(
    const Shapes& shapes,
    const Area triangle_max_area,
    const Angle triangle_min_angle,
    const bool verbose
  );

  ///Obtain the filename of the created mesh
  //std::string GetFilename() const noexcept { return m_filename_result_mesh; }

  private:
  //const std::string m_filename_result_mesh;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // DO_I_REALLY_USE_THIS_20140626

#endif // RIBI_TESTTRIANGLEMAINDIALOG_H
