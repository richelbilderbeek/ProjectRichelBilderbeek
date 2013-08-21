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
  Canvas(const int width = 0, const int height = 0);
  int GetHeight() const { return mCanvas.size(); }
  int GetWidth() const { return (GetHeight()==0 ? 0 : mCanvas[0].size() ); }
  void DrawDot(const double x, const double y);
  void DrawLine(const double x1, const double y1, const double x2, const double y2);
  void DrawCircle(const double xMid, const double yMid, const double ray);

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  void Cout() const; //operator<< is not used, as PlotSurface only writes to std::cout
  private:
  bool IsInRange(const int x, const int y) const;
  std::vector<std::vector<double> > mCanvas;

};

//From http://www.richelbilderbeek.nl/CppMinElement.htm
template <class Container>
const typename Container::value_type::value_type MinElement(const Container& v);

//From http://www.richelbilderbeek.nl/CppMaxElement.htm
template <class Container>
const typename Container::value_type::value_type MaxElement(const Container& v);

//From http://www.richelbilderbeek.nl/CppPlotSurface.htm
void PlotSurface(const std::vector<std::vector<double> >& v);

//From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
const std::vector<char> GetAsciiArtGradient();

#endif
