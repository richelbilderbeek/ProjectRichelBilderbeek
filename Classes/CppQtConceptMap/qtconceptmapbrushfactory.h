//---------------------------------------------------------------------------
/*
QtConceptMap, Qt classes for display and interaction with ConceptMap
Copyright (C) 2013-2014 The Brainweaver Team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtConceptMap.htm
//---------------------------------------------------------------------------
#ifndef QTCONCEPTMAPBRUSHFACTORY_H
#define QTCONCEPTMAPBRUSHFACTORY_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <QBrush>
#pragma GCC diagnostic pop

namespace ribi {
namespace cmap {

///Class for holding some QBrush instances
struct QtBrushFactory
{
  ///Obtain a brush its name
  static std::string BrushToStr(const QBrush& brush);

  ///Blue brush, to be used in all derived classes for uniform coloring
  static QBrush CreateBlueGradientBrush() noexcept;

  ///Gold brush, to be used in all derived classes for uniform coloring
  static QBrush CreateGoldGradientBrush() noexcept;

  ///Gray brush, to be used in all derived classes for uniform coloring
  static QBrush CreateGrayGradientBrush() noexcept;

  ///Green brush, to be used in all derived classes for uniform coloring
  static QBrush CreateGreenGradientBrush() noexcept;

  ///Red brush, to be used in all derived classes for uniform coloring
  static QBrush CreateRedGradientBrush() noexcept;

  ///Yellow brush, to be used in all derived classes for uniform coloring
  static QBrush CreateYellowGradientBrush() noexcept;

  ///Near-white brush, to be used in all derived classes for uniform coloring
  static QBrush CreateWhiteGradientBrush() noexcept;

  private:
  ///The bottom coordinat of a gradient
  static const int sm_bottom;
  ///The left coordinat of a gradient
  static const int sm_left;
  ///The right coordinat of a gradient
  static const int sm_right;
  ///The top coordinat of a gradient
  static const int sm_top;
  ///The low color value: low values return in darker brushes
  static const int sm_color_low_value;
  ///The middle color value: higher values return in lighter brushes
  static const int sm_color_mid_value;
};

} //~namespace cmap
} //~namespace ribi

#endif // QTCONCEPTMAPBRUSHFACTORY_H
