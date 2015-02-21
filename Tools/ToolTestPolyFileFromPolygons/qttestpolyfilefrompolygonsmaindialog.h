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
#ifndef QTTRIANGLEMESHCREATORMAINDIALOG_H
#define QTTRIANGLEMESHCREATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
//#include <boost/units/quantity.hpp>
//#include <boost/units/systems/si/area.hpp>
//#include <boost/units/systems/si/length.hpp>
//#include <boost/units/systems/si/plane_angle.hpp>
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtTestPolyFileFromPolygonsMainDialog;
}

namespace ribi {

class QtTestPolyFileFromPolygonsMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:

  explicit QtTestPolyFileFromPolygonsMainDialog(QWidget *parent = 0) noexcept;
  QtTestPolyFileFromPolygonsMainDialog(const QtTestPolyFileFromPolygonsMainDialog&) = delete;
  QtTestPolyFileFromPolygonsMainDialog& operator=(const QtTestPolyFileFromPolygonsMainDialog&) = delete;
  ~QtTestPolyFileFromPolygonsMainDialog() noexcept;

  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;
  typedef boost::geometry::model::linestring<Coordinat2D> Linestring;
  typedef std::vector<Polygon> Polygons;
  typedef std::vector<Linestring> Linestrings;
  typedef std::pair<Polygons,Linestrings> Shapes;
  Shapes GetShapes() const noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtTestPolyFileFromPolygonsMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  //static std::vector<std::string> SeperateString(
  //  const std::string& input,
  //  const char seperator = '\n'
  //) noexcept;

private slots:

  void DisplayPolyFile() noexcept;
  void DisplayPolygons() noexcept;

  void on_edit_shapes_textChanged();
};

} //~namespace ribi

#endif // QTTRIANGLEMESHCREATORMAINDIALOG_H
