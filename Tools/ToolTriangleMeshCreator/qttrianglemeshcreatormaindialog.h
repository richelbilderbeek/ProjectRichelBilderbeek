//---------------------------------------------------------------------------
/*
TriangleMeshCreator, creates a 3D mesh using Triangle,
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
//From http://www.richelbilderbeek.nl/ToolTriangleMeshCreator.htm
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
#include <boost/units/systems/si/area.hpp>
#include <boost/units/systems/si/length.hpp>
#include <boost/units/systems/si/plane_angle.hpp>
#include "qthideandshowdialog.h"
#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtTriangleMeshCreatorMainDialog;
}

namespace ribi {

class QtTriangleMeshCreatorMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTriangleMeshCreatorMainDialog(QWidget *parent = 0) noexcept;
  QtTriangleMeshCreatorMainDialog(const QtTriangleMeshCreatorMainDialog&) = delete;
  QtTriangleMeshCreatorMainDialog& operator=(const QtTriangleMeshCreatorMainDialog&) = delete;
  ~QtTriangleMeshCreatorMainDialog() noexcept;

  typedef boost::geometry::model::d2::point_xy<double> Coordinat2D;
  typedef boost::geometry::model::polygon<Coordinat2D> Polygon;
  typedef boost::units::quantity<boost::units::si::plane_angle> Angle;
  typedef boost::units::quantity<boost::units::si::area> Area;

  void CreateMesh() noexcept;
  void DisplayPolygons() noexcept;
  ribi::trim::CreateVerticalFacesStrategy GetCreateVerticalFacesStrategy() const noexcept;
  double GetFraction() const noexcept;
  boost::units::quantity<boost::units::si::length> GetLayerHeight() const noexcept;
  int GetNumberOfCellLayers() const noexcept;
  std::vector<Polygon> GetShapes() const noexcept;
  bool GetShowMesh() const noexcept;
  Area GetTriangleMaxArea() const noexcept;
  Angle GetTriangleMinAngle() const noexcept;
  bool GetVerbose() const noexcept;

  void SetShowMesh(const bool show_mesh) noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtTriangleMeshCreatorMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
  static std::vector<std::string> SeperateString(const std::string& input) noexcept;

private slots:

  void on_edit_shapes_textChanged();
  void on_button_create_clicked();
  void DisplayTriangleMesh() noexcept;
};

} //~namespace ribi

#endif // QTTRIANGLEMESHCREATORMAINDIALOG_H
