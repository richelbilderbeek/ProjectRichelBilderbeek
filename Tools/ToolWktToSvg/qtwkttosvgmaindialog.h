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
#ifndef QTWKTTOSVGMAINDIALOG_H
#define QTWKTTOSVGMAINDIALOG_H

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
//#include "trianglemeshcreateverticalfacesstrategy.h"
#pragma GCC diagnostic pop

struct QPlainTextEdit;

namespace Ui {
  class QtWktToSvgMainDialog;
}

namespace ribi {

class QtWktToSvgMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtWktToSvgMainDialog(QWidget *parent = 0) noexcept;
  QtWktToSvgMainDialog(const QtWktToSvgMainDialog&) = delete;
  QtWktToSvgMainDialog& operator=(const QtWktToSvgMainDialog&) = delete;
  ~QtWktToSvgMainDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *) noexcept;

private:
  Ui::QtWktToSvgMainDialog *ui;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

private slots:
  void on_text_svg_textChanged();
  void OnInputChanged();
};

} //~namespace ribi

#endif // QTWKTTOSVGMAINDIALOG_H
