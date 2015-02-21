//---------------------------------------------------------------------------
/*
pylos::Coordinat, Pylos/Phyraos coordinat class
Copyright (C) 2010-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------
#ifndef PYLOSCOORDINAT_H
#define PYLOSCOORDINAT_H

#include <iosfwd>
#include <string>
#include <vector>

namespace ribi {

namespace pylos {

struct Coordinat
{
  Coordinat(const int layer, const int x, const int y);

  ///Construct a Coordinat from a std::string.
  ///For example, (0,1,2) is the coordinat Z=0=bottom,X=1=leftmost-but-one,Y=2=frontmost-but-two
  Coordinat(const std::string& s);

  ///Obtain the layer or Z-coordinat
  ///0: bottom 4x4 layer, 3: top 1x1 layer
  int GetLayer() const noexcept { return m_layer; }

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Obtain this coordinat its X coordinat
  ///0: Left
  int GetX() const noexcept { return m_x; }

  ///Obtain this coordinat its Y coordinat
  ///0: Top
  int GetY() const noexcept { return m_y; }

  ///IsValid returns if the proposed coordinat is a valid Pylos coordinat
  static bool IsValid(const int layer, const int x, const int y) noexcept;

  ///IsValid returns if this coordinat is a valid Pylos coordinat
  bool IsValid() const noexcept;

  ///ToStr() converts the coordinat to a std::string
  ///of the form '(layer,x,y)'.
  std::string ToStr() const noexcept;

  private:
  ///Not const, so that copying is possible
  int m_layer;
  int m_x;
  int m_y;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

};

bool operator==(const Coordinat& lhs, const Coordinat& rhs) noexcept;
bool operator!=(const Coordinat& lhs, const Coordinat& rhs) noexcept;
std::ostream& operator<<(std::ostream& os,const Coordinat& c) noexcept;

///GetAbove returns the coordinats physically
///above the entered coordinat
const std::vector<Coordinat> GetAbove(
  const Coordinat& c);

///GetAllPylosCoordinats returns all possible PylosCoordinats
const std::vector<Coordinat> GetAllCoordinats() noexcept;

///GetBelow returns the four coordinats physically
///below the entered coordinat
const std::vector<Coordinat> GetBelow(
  const Coordinat& c);

///GetLines returns the possible 2x2 squares around the coordinat
const std::vector<std::vector<Coordinat> > GetLines(
  const Coordinat& c);

///GetRandomPylosCoordinat returns a random valid PylosCoordinat
const Coordinat GetRandomCoordinat() noexcept;

///GetSquares returns the possible 2x2 squares around the coordinat
const std::vector<std::vector<Coordinat> > GetSquares(
  const Coordinat& c);

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSCOORDINAT_H
