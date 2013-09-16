//---------------------------------------------------------------------------
/*
Rectangle, rectangle class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppRectangle.htm
//---------------------------------------------------------------------------
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <string>
#include <vector>

namespace ribi {

///RectanglePolicyUseSize stores a rectangle by its topleft coordinats and its size
/*
template <class T>
struct RectanglePolicyUseSize
{
  RectanglePolicyUseSize(
    const T& any_x = 0,
    const T& any_y = 0,
    const T& any_w = 0,
    const T& any_h = 0)
  : x(any_x), y(any_y), w(any_w), h(any_h) {}

  ///Obtain the x coordinat of the rectangle its bottom side
  const T GetBottom() const { return y + h; }

  ///Obtain the y coordinat of the rectangle its right side
  const T GetRight() const { return x + w; }

  ///Obtain the rectangle its height
  const T GetHeight() const { return h; }

  ///Obtain the rectangle its width
  const T GetWidth() const { return w; }

  bool IsIn(const T& any_x, const T& any_y) const
  {
    return any_x > x && any_y > y && x < GetRight() && y < GetBottom();
  }

  private:
  T x;
  T y;
  T w;
  T h;
};
*/

///RectanglePolicyUseBottomRight stores a rectangle by its topleft
///and bottomright coordinats

template <class T>
struct RectanglePolicyUseBottomRight
{
  RectanglePolicyUseBottomRight(
    const T& any_x1 = 0,
    const T& any_y1 = 0,
    const T& any_x2 = 0,
    const T& any_y2 = 0)
  : x1(any_x1), y1(any_y1), x2(any_x2), y2(any_y2) {}

  const T GetBottom() const { return y2; }
  const T GetRight() const { return x2; }
  const T GetHeight() const { return y2 - y1; }
  const T GetWidth() const { return x2 - x1; }

  private:
  T x1;
  T y1;
  T x2;
  T y2;
};

///IntRectanglePolicyUseSize stores a rectangle by its topleft coordinats and its size
struct Rect
{
  Rect(
    const int any_x = 0,
    const int any_y = 0,
    const int any_w = 0,
    const int any_h = 0);

  ///Obtain the x coordinat of the rectangle its bottom side
  int GetBottom() const noexcept { return y + h; }

  ///Obtain the y coordinat of the rectangle its right side
  int GetRight() const noexcept { return x + w; }

  ///Obtain the rectangle its height
  int GetHeight() const noexcept { return h; }

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the rectangle its width
  int GetWidth() const noexcept { return w; }


  ///Obtain the x coordinat of the rectangle its left side
  int GetX() const noexcept { return x; }

  ///Obtain the y coordinat of the rectangle its top side
  int GetY() const noexcept { return y; }

  bool IsIn(const int any_x, const int any_y) const noexcept
  {
    return any_x > x && any_y > y && any_x < GetRight() && any_y < GetBottom();
  }

  private:
  int x;
  int y;
  int w;
  int h;

  friend bool operator==(const Rect& lhs, const Rect& rhs) noexcept;
  friend std::ostream& operator<<(std::ostream& os,const Rect& rect) noexcept;
};

std::ostream& operator<<(std::ostream& os,const Rect& rect) noexcept;
bool operator==(const Rect& lhs, const Rect& rhs) noexcept;
bool operator!=(const Rect& lhs, const Rect& rhs) noexcept;

} //~namespace ribi

#endif // RECTANGLE_H
