//---------------------------------------------------------------------------
/*
Canvas, ASCII art painting surface class
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
// From http://www.richelbilderbeek.nl/CppCanvas.htm
//---------------------------------------------------------------------------
#ifndef RIBI_CANVAS_H
#define RIBI_CANVAS_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/signals2.hpp>
#include "canvascolorsystem.h"
#include "canvascoordinatsystem.h"
#pragma GCC diagnostic pop

struct QRegExp;

namespace ribi {

///A Canvas is an ASCII art class for drawing (DrawCanvas),
///displaying images (ImageCanvas) and displaying text (TextCanvas)
struct Canvas
{
  Canvas();
  virtual ~Canvas() noexcept {}

  //From http://www.richelbilderbeek.nl/CppGetAsciiArtGradient.htm
  static std::vector<char> GetAsciiArtGradient() noexcept;

  ///Obtain the height of the canvas is characters
  virtual int GetHeight() const noexcept = 0;

  ///Obtain the version of this class
  static std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain the width of the canvas is characters
  virtual int GetWidth() const noexcept = 0;

  ///Load a Canvas from std::strings
  ///DON'T: make it a constructor instead
  ///virtual void Load(const std::vector<std::string>& v) = 0;

  ///Convert the Canvas to std::strings
  virtual std::vector<std::string> ToStrings() const noexcept = 0;

  ///This signal is emitted when any member variable changes
  boost::signals2::signal<void(Canvas*)> m_signal_changed;

  private:
  ///From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  static std::vector<std::string> GetRegexMatches(
    const std::string& s,
    const QRegExp& r
  ) noexcept;

  ///Check if a coordinat is in the range of the Canvas
  bool IsInRange(const int x, const int y) const;

  //Obtains the minimum element of a 2D container
  //From http://www.richelbilderbeek.nl/CppMinElement.htm
  template <class Container>
  static typename Container::value_type::value_type MinElement(const Container& v);

  //Obtains the maximal element of a 2D container
  //From http://www.richelbilderbeek.nl/CppMaxElement.htm
  template <class Container>
  static typename Container::value_type::value_type MaxElement(const Container& v);

  static std::vector<std::string> SeperateString(
    const std::string& input,
    const char seperator) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_CANVAS_H
