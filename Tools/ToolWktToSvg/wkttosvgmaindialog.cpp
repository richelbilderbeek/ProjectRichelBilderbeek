//---------------------------------------------------------------------------
/*
WktToSvg, tool to convert WKT to SVG
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
//From http://www.richelbilderbeek.nl/ToolWktToSvg.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "wkttosvgmaindialog.h"

#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/io/svg/svg_mapper.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/xpressive/xpressive.hpp>

#include "geometry.h"
#include "trace.h"
#include "testtimer.h"

#pragma GCC diagnostic pop

ribi::WktToSvgMainDialog::WktToSvgMainDialog(
  const std::string& wkt,
  const double stroke_width
) : m_svg(ToSvg(wkt,stroke_width)),
    m_wkt(wkt)
{
  #ifndef NDEBUG
  Test();
  #endif
}

#ifndef NDEBUG
void ribi::WktToSvgMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif

std::string ribi::WktToSvgMainDialog::ToSvg(
  const std::string& wkt,
  const double stroke_width
)
{
  return Geometry().WktToSvg(wkt,stroke_width);
}
