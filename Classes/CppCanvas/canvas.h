//---------------------------------------------------------------------------
/*
Canvas, ASCII art painting surface class
Copyright (C) 2008-2013  Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppCanvas.htm
//---------------------------------------------------------------------------
#ifndef CANVAS_H
#define CANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct Canvas
{
  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  enum class ColorSystem { normal, invert };

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  enum class CoordinatSystem { screen, graph };

  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0.0 and 0.0
  Canvas(
    const int width = 0,
    const int height = 0,
    const ColorSystem colorSystem = ColorSystem::normal,
    const CoordinatSystem coordinatSystem = CoordinatSystem::screen);

  ///Clears the canvas
  void Clear() noexcept;

  ///Draw (or actually: add) a dot on the canvas at (x,y), where
  ///(x,y) is the center of a dot with radius 1.0. It is not checked that
  ///(x,y) is in ( [0.0,GetWidth()>, [0.0,GetHeight()> )
  void DrawDot(const double x, const double y) noexcept;

  ///Draw (or actually: add) a line on the canvas from (x1,y1) to (x2,y2),
  ///where (x1,y1) and (x2,y2) are the centers of a dot with radius 1.0 at
  ///the edges of the line
  void DrawLine(const double x1, const double y1, const double x2, const double y2) noexcept;

  ///Draw (or actually: add) a circle on the canvas at (xMid,yMid),
  ///with radius ray
  void DrawCircle(const double xMid, const double yMid, const double ray) noexcept;

  ///Obtain the height of the canvas is characters
  int GetHeight() const noexcept { return mCanvas.size(); }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  int GetWidth() const noexcept { return (GetHeight()==0 ? 0 : mCanvas[0].size() ); }

  ///Set the color system used
  void SetColorSystem(const ColorSystem colorSystem) noexcept;

  ///Set the coordinat system used
  void SetCoordinatSystem(const CoordinatSystem coordinatSystem) noexcept;

  ///This signal is emitted when any member variable changes
  boost::signals2::signal<void(Canvas*)> m_signal_changed;

  private:
  ///The Canvas its internal data: a 2D y-x-ordered std::vector
  ///of doubles, where 0.0 denotes empty/non-drawn
  ///and 1.0 denotes full/drawn.
  std::vector<std::vector<double> > mCanvas;

  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  ColorSystem mColorSystem;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CoordinatSystem mCoordinatSystem;

  ///Check if a coordinat is in the range of the Canvas
  bool IsInRange(const int x, const int y) const;

  //From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
  static const std::vector<char> GetAsciiArtGradient();

  //From http://www.richelbilderbeek.nl/CppMinElement.htm
  template <class Container>
  static const typename Container::value_type::value_type MinElement(const Container& v);

  //From http://www.richelbilderbeek.nl/CppMaxElement.htm
  template <class Container>
  static const typename Container::value_type::value_type MaxElement(const Container& v);

  ///Plot a surface on screen
  ///if as_screen_coordinat_system is true, the origin is in the top left
  ///corner of the screen, else it is in the bottom left of the screen,
  ///as is usual in graphs
  //From http://www.richelbilderbeek.nl/CppPlotSurface.htm
  static void PlotSurface(
    std::ostream& os,
    const std::vector<std::vector<double> >& v,
    const bool use_normal_color_system,
    const bool as_screen_coordinat_system);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas);

};

std::ostream& operator<<(std::ostream& os, const Canvas& canvas);

} //~namespace ribi

#endif
