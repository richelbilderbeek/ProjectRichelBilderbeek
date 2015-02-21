//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#ifndef RIBI_TESTPOLYFILEFROMPOLYGONSMAINDIALOG_H
#define RIBI_TESTPOLYFILEFROMPOLYGONSMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/units/quantity.hpp>
//#include <boost/units/systems/si/area.hpp>
//#include <boost/units/systems/si/length.hpp>
//#include <boost/units/systems/si/plane_angle.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Converts shapes to a .poly file its content (using operator<<
struct TestPolyFileFromPolygonsMainDialog
{
  typedef boost::geometry::model::d2::point_xy<double> Point;
  typedef boost::geometry::model::polygon<Point> Polygon;
  typedef std::vector<Polygon> Polygons;


  TestPolyFileFromPolygonsMainDialog(const Polygons& polygons);
  const Polygons& GetPolygons() const noexcept { return m_polygons; }

  private:
  const Polygons m_polygons;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

std::ostream& operator<<(std::ostream& os, const TestPolyFileFromPolygonsMainDialog& dialog) noexcept;

} //~namespace ribi

#endif // RIBI_TESTPOLYFILEFROMPOLYGONSMAINDIALOG_H
