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
#ifndef RIBI_WKTTOSVGMAINDIALOG_H
#define RIBI_WKTTOSVGMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <iosfwd>
#include <string>
#include <vector>
#pragma GCC diagnostic pop

namespace ribi {

struct WktToSvgMainDialog
{
  explicit WktToSvgMainDialog(
    const std::string& wkt,
    const double stroke_width
  );

  const std::string& GetSvg() const noexcept { return m_svg; }
  const std::string& GetWkt() const noexcept { return m_wkt; }


  private:
  const std::string m_svg;
  const std::string m_wkt;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  static std::string ToSvg(
    const std::string& wkt,
    const double stroke_width
  );
};

} //~namespace ribi

#endif // RIBI_WKTTOSVGMAINDIALOG_H
