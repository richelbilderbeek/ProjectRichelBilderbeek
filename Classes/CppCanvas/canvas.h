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



struct Canvas
{
  ///The color system used:
  ///- normal: black is displayed by M (assumes white background, black characters)
  ///- invert: white is displayed by M
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

  void DrawDot(const double x, const double y);
  void DrawLine(const double x1, const double y1, const double x2, const double y2);
  void DrawCircle(const double xMid, const double yMid, const double ray);

  int GetHeight() const { return mCanvas.size(); }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  int GetWidth() const { return (GetHeight()==0 ? 0 : mCanvas[0].size() ); }

  private:
  bool IsInRange(const int x, const int y) const;

  std::vector<std::vector<double> > mCanvas;

  ///The color system used:
  ///- normal: black is displayed by M (assumes white background, black characters)
  ///- invert: white is displayed by M
  const ColorSystem mColorSystem;

  ///The coordinat system used in displayal:
  ///- screen: origin is at top-left of the screen
  ///- graph: origin is at bottom-left of the screen
  const CoordinatSystem mCoordinatSystem;

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

  //From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
  static const std::vector<char> GetAsciiArtGradient();

  friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas);

};

std::ostream& operator<<(std::ostream& os, const Canvas& canvas);


#endif
