//---------------------------------------------------------------------------
/*
pylos::Winner, Pylos enum class for the winner
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


#include "pyloswinner.h"

#include <cassert>
#include <stdexcept>

std::string ribi::pylos::ToStr(const Winner winner)
{
  switch (winner)
  {
    case Winner::player1: return "player1";
    case Winner::player2: return "player2";
    case Winner::none: return "none";
  }
  assert(!"Cannot convert this Winner to a std::string");
  throw std::logic_error("Cannot convert this Winner to a std::string");
}
