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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testpolyfilefrompolygonsmaindialog.h"

#include <fstream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

#include "fileio.h"
#include "geometry.h"
#include "polyfilefrompolygons.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::TestPolyFileFromPolygonsMainDialog::TestPolyFileFromPolygonsMainDialog(
  const Polygons& polygons
) : m_polygons(polygons)
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void ribi::TestPolyFileFromPolygonsMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    PolyFile( {}, {} );
    PolyFileFromPolygons( {}, {} );
    Geometry();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const auto polygon = Geometry().CreateShapeTriangle();
  const Polygons polygons = { polygon };
  TestPolyFileFromPolygonsMainDialog d(polygons);
  std::stringstream s;
  s << d;
  assert(!s.str().empty());
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const TestPolyFileFromPolygonsMainDialog& dialog) noexcept
{
  PolyFileFromPolygons file(dialog.GetPolygons());
  os << file.ToStr();
  return os;

}
