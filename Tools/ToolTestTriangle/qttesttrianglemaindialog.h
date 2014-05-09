//---------------------------------------------------------------------------
/*
TestTriangle, compare Triangle to its C++ equivalent
Copyright (C) 2014-2014 Richel Bilderbeek

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
#ifndef QTTRIANGLEMESHCREATORMAINDIALOG_H
#define QTTRIANGLEMESHCREATORMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si/length.hpp>
#include "qthideandshowdialog.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtTestTriangleMainDialog;
}

namespace ribi {

class QtTestTriangleMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestTriangleMainDialog(QWidget *parent = 0) noexcept;
  QtTestTriangleMainDialog(const QtTestTriangleMainDialog&) = delete;
  QtTestTriangleMainDialog& operator=(const QtTestTriangleMainDialog&) = delete;
  ~QtTestTriangleMainDialog() noexcept;

  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;

  void DisplayPolygons() noexcept;
  std::vector<Polygon> GetShapes() const noexcept;
  double GetTriangleArea() const noexcept;
  double GetTriangleQuality() const noexcept;
  bool GetVerbose() const noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtTestTriangleMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  static std::vector<std::string> SeperateString(const std::string& input) noexcept;

private slots:

  void on_edit_shapes_textChanged();
  void DisplayTriangleMesh() noexcept;
};

} //~namespace ribi

#endif // QTTRIANGLEMESHCREATORMAINDIALOG_H
