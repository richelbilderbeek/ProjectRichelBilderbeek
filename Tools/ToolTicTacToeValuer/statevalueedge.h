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
#ifndef STATEVALUEEDGE_H
#define STATEVALUEEDGE_H
//---------------------------------------------------------------------------
#include <cstdlib>
//---------------------------------------------------------------------------
struct StateValueEdge
{
  StateValueEdge() : m_move(std::rand() % 100) {}
  StateValueEdge(const int move) : m_move(move) {}
  int m_move;
};
//---------------------------------------------------------------------------
#endif // STATEVALUEEDGE_H
