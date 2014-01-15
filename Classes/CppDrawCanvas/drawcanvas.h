//---------------------------------------------------------------------------
/*
DrawCanvas, ASCII art painting surface class
Copyright (C) 2008-2014 Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppDrawCanvas.htm
//---------------------------------------------------------------------------
#ifndef DRAWCANVAS_H
#define DRAWCANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvas.h"
#include "canvascolorsystem.h"
#include "canvascoordinatsystem.h"
#pragma GCC diagnostic pop

struct QRegExp;

namespace ribi {

///The DrawCanvas is an ASCII art tool to draw on
///The DrawCanvas has a coordinat system of (0,0)-(width,height)
///similar to the possible character position on a screen.
///Everything drawn beyond the range of DrawCanvas is not stored.
///Yet, if for example a line is drawn between two off-screen coordinats,
///the part that goes through the DrawCanvas is drawn and stored
struct DrawCanvas : public Canvas
{
  ///The number of characters the DrawCanvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0.0 and 0.0
  DrawCanvas(
    const int width  = 1,
    const int height = 1,
    const CanvasColorSystem color_system = CanvasColorSystem::normal,
    const CanvasCoordinatSystem coordinat_system = CanvasCoordinatSystem::screen);

  ///Create a DrawCanvas from its raw internals
  DrawCanvas(
    const std::vector<std::vector<double>>& canvas,
    const CanvasColorSystem color_system = CanvasColorSystem::normal,
    const CanvasCoordinatSystem coordinat_system = CanvasCoordinatSystem::screen);

  ///Load a DrawCanvas from file
  DrawCanvas(const std::string& filename);

  ~DrawCanvas() noexcept {}

  ///Clears the canvas
  void Clear() noexcept;

  ///Draw (or actually: add) a circle on the canvas at (xMid,yMid),
  ///with radius ray
  void DrawCircle(const double xMid, const double yMid, const double ray) noexcept;

  ///Draw (or actually: add) a dot on the canvas at (x,y), where
  ///(x,y) is the center of a dot with radius 1.0. It is not checked that
  ///(x,y) is in ( [0.0,GetWidth()>, [0.0,GetHeight()> )
  void DrawDot(const double x, const double y) noexcept;

  ///Draw (or actually: add) a line on the canvas from (x1,y1) to (x2,y2),
  ///where (x1,y1) and (x2,y2) are the centers of a dot with radius 1.0 at
  ///the edges of the line
  void DrawLine(const double x1, const double y1, const double x2, const double y2) noexcept;

  ///Draw (or actually: add) text to the DrawCanvas, where (top,left) is the topleft coordinat
  ///of the text. The text will end up as dots drawn for each character its pixel.
  ///The DotMatrix font is used, with a spacing of two pixel, as the letters tend to
  ///overlap otherwise.
  //
  //  DrawCanvas::DrawText(1,1,"Hello world") results in:
  //
  //  M   M          MM     MM                                        MM        M
  //  M   M           M      M                                         M        M
  //  M   M   MMM     M      M     MMM          M   M   MMM   M MM     M     MM M
  //  MMMMM  M   M    M      M    M   M         M   M  M   M  MM  M    M    M  MM
  //  M   M  MMMMM    M      M    M   M         M M M  M   M  M        M    M   M
  //  M   M  M        M      M    M   M         M M M  M   M  M        M    M   M
  //  M   M   MMM    MMM    MMM    MMM           M M    MMM   M       MMM    MMMM
  //
  void DrawText(const double top, const double left, const std::string& text) noexcept;

  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  CanvasColorSystem GetColorSystem() const noexcept { return m_color_system; }

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CanvasCoordinatSystem GetCoordinatSystem() const noexcept { return m_coordinat_system; }

  ///The DrawCanvas its internal data: a 2D y-x-ordered std::vector
  ///of doubles, where 0.0 denotes empty/non-drawn
  ///and 1.0 denotes full/drawn.
  const std::vector<std::vector<double> >& GetGreynesses() const noexcept { return m_canvas; }

  ///Obtain the height of the canvas is characters
  int GetHeight() const noexcept { return m_canvas.size(); }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  int GetWidth() const noexcept { return (GetHeight()==0 ? 0 : m_canvas[0].size() ); }

  void Load(const std::vector<std::string>& v);

  ///Save to file
  void Save(const std::string& filename) const noexcept;

  ///Set the color system used
  void SetColorSystem(const CanvasColorSystem color_system) noexcept;

  ///Set the coordinat system used
  void SetCoordinatSystem(const CanvasCoordinatSystem coordinat_system) noexcept;

  const std::vector<std::string> ToStrings() const noexcept;

  ///This signal is emitted when any member variable changes
  boost::signals2::signal<void(DrawCanvas*)> m_signal_changed;

  private:
  ///The DrawCanvas its internal data: a 2D y-x-ordered std::vector
  ///of doubles, where 0.0 denotes empty/non-drawn
  ///and 1.0 denotes full/drawn.
  std::vector<std::vector<double> > m_canvas;

  ///The color system used:
  ///- normal: full/drawn is displayed by M
  ///- invert: empty/non-drawn is displayed by M
  CanvasColorSystem m_color_system;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  CanvasCoordinatSystem m_coordinat_system;

  ///From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static const std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const QRegExp& r);

  ///Check if a coordinat is in the range of the DrawCanvas
  bool IsInRange(const int x, const int y) const;

  //Obtains the minimum element of a 2D container
  //From http://www.richelbilderbeek.nl/CppMinElement.htm
  template <class Container>
  static const typename Container::value_type::value_type MinElement(const Container& v);

  //Obtains the maximal element of a 2D container
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

  static const std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const DrawCanvas& canvas);
  friend bool operator==(const DrawCanvas& lhs, const DrawCanvas& rhs) noexcept;

};

std::ostream& operator<<(std::ostream& os, const DrawCanvas& canvas);

///Useful for exact comparison
bool operator==(const DrawCanvas& lhs, const DrawCanvas& rhs) noexcept;
bool operator!=(const DrawCanvas& lhs, const DrawCanvas& rhs) noexcept;

///Useful for fuzzy comparison, like (1) Save (2) Load (3) Compare original
///with loaded version
bool IsAboutEqual(const DrawCanvas& lhs, const DrawCanvas& rhs) noexcept;

} //~namespace ribi

#endif
