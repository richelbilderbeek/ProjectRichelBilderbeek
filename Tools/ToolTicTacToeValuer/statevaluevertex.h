//---------------------------------------------------------------------------
/*
TicTacToeValuer, tool to solve TicTacToe
Copyright (C) 2010 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTicTacToeValuer.htm
//---------------------------------------------------------------------------
#ifndef STATEVALUEVERTEX_H
#define STATEVALUEVERTEX_H
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
struct StateValueVertex
{
  StateValueVertex(const int state = 0, const double value = 0.0)
    : m_state(state), m_value(value) {}
  int m_state;
  double m_value;
  const std::string ToStr() const;
};
//---------------------------------------------------------------------------
#endif // STATEVALUEVERTEX_H
