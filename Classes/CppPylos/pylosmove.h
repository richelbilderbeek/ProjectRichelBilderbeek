//---------------------------------------------------------------------------
/*
pylos::Move, class for a Pylos/Phyraos move
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
#ifndef PYLOSMOVE_H
#define PYLOSMOVE_H

#include <iosfwd>
#include <string>
#include <vector>

#include "pyloscoordinat.h"

namespace ribi {

namespace pylos {

///PylosMove encapsulates a Pylos move.
///A Pylos move starts with either
/// - placing (Set) a new marble or
/// - moving (Transfer) an existing marble to a higher location
///Both a Set and a Transfer can results in that the player must
///remove either one or two marbles.
struct Move
{
  Move();

  ///Move is constructed from all the members it will hold
  Move(
    const std::vector<Coordinat>& moving,
    const std::vector<Coordinat>& removing);

  ///Move is constructed from Pylos notation
  Move(const std::string& s);

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Test if this Move is valid
  bool IsValid() const noexcept;

  std::string ToStr() const noexcept;

  ///What m_move is, depends on its size:
  ///m_move.size() == 1: placement at m_move[0]
  ///m_move.size() == 2: move from m_move[0] to m_move[1]
  std::vector<Coordinat> m_move;
  std::vector<Coordinat> m_remove;

  private:
  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif

};

bool operator==(const Move& lhs, const Move& rhs) noexcept;
std::ostream& operator<<(std::ostream& os, const Move& m) noexcept;

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSMOVE_H
