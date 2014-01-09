//---------------------------------------------------------------------------
/*
ImageCanvas, class to convert an image to ASCII art
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppImageCanvas.htm
//---------------------------------------------------------------------------
#ifndef IMAGECANVAS_H
#define IMAGECANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvas.h"
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

///ImageCanvas converts an image to a Canvas
struct ImageCanvas
{
  ///The number of characters the Canvas is heigh and wide
  ///but also the maximum x and y coordinat. The minimum
  ///x and y coordinats are 0.0 and 0.0
  ImageCanvas(
    const std::string& filename,
    const int n_cols,
    const CanvasColorSystem colorSystem         = CanvasColorSystem::normal,
    const CanvasCoordinatSystem coordinatSystem = CanvasCoordinatSystem::screen);

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  const boost::shared_ptr<Canvas> ToCanvas() const noexcept;

  private:
  const CanvasColorSystem mColorSystem;
  const CanvasCoordinatSystem mCoordinatSystem;
  const std::string m_filename;
  const int m_n_cols;

  ///Returns a Y-X-ordered std::vector of greynesses.
  static const std::vector<std::vector<double> >
    ConvertToGreyYx(const QImage * const i);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

  friend std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas);
};

std::ostream& operator<<(std::ostream& os, const ImageCanvas& canvas);

} //~namespace ribi

#endif
