//---------------------------------------------------------------------------
/*
Shape, shape class
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
//From http://www.richelbilderbeek.nl/CppShape.htm
//---------------------------------------------------------------------------
#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///Shape is a class for a regular polygonal shape
///
///A Shape can be a circle, ellipse, triange, square, rhombus, rectangle
///A Shape cannot yet be a minus, plus, star
struct Shape
{
  explicit Shape(
    const int n_corners,
    const double rotation,
    const unsigned char red = 255,
    const unsigned char green = 255,
    const unsigned char blue = 255);

  ///Get the blueness of the Shape its color
  unsigned char GetBlue() const noexcept { return m_blue; }

  ///Get the greenness of the Shape its color
  unsigned char GetGreen() const noexcept { return m_green; }

  ///Get the number of corners of the Shape
  double GetNumberOfCorners() const noexcept { return m_n_corners; }

  ///Get the redness of the Shape its color
  unsigned char GetRed() const noexcept { return m_red; }

  ///Get the rotation of the Shape
  double GetRotation() const noexcept { return m_rotation; }

  ///Set the number of corners of the Shape
  void SetNumberOfCorners(const int n_corners);

  ///Set the rotation of the Shape
  void SetRotation(const double rotation) noexcept;

  ///The signal emitted when the Shape position is changed
  mutable boost::signals2::signal<void ()> m_signal_changed;

  private:
  //Shape can only be deleted by Boost smart pointers
  virtual ~Shape() noexcept {}
  friend void boost::checked_delete<>(Shape*);

  friend bool operator==(const Shape& lhs, const Shape& rhs) noexcept;

  ///The shape its blueness
  unsigned char m_blue;

  ///The shape its greenness
  unsigned char m_green;

  ///The number of corners
  int m_n_corners;

  ///The shape its redness
  unsigned char m_red;

  ///The rotation
  ///
  ///The rotation is a value between 0.0 and 2.0 * M_PI,
  ///in which  0.0 * M_PI is the equivalent to 12:00 o'clock
  ///and which 0.5 * M_PI is the equivalent to  3:00 o'clock
  ///Values not in this range are accepted nonetheless
  double m_rotation;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

  public:
  ///Obtain the angle in radians between two deltas
  ///12 o'clock is 0.0 * pi
  /// 3 o'clock is 0.5 * pi
  /// 6 o'clock is 1.0 * pi
  /// 9 o'clock is 1.5 * pi
  //From www.richelbilderbeek.nl/CppGetAngle.htm
  static double GetAngle(const double dx, const double dy) noexcept;

  //From www.richelbilderbeek.nl/CppGetDistance.htm
  static double GetDistance(const double dX, const double dY) noexcept;
  static const std::string GetVersion() noexcept;
  static const std::vector<std::string> GetVersionHistory() noexcept;

};

bool operator==(const Shape& lhs, const Shape& rhs) noexcept;

} //~namespace ribi

#endif // SHAPE_H

