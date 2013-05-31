//---------------------------------------------------------------------------
/*
Staircase Card Creator, tool to create staircase cards
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
//From http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
#include "staircasecard.h"
//---------------------------------------------------------------------------
StaircaseCard::StaircaseCard(const int n_cols, const int n_rows)
  : m_grid(n_cols,boost::dynamic_bitset<>(n_rows))
{
  assert(GetCols() == n_cols);
  assert(GetRows() == n_rows);
}
//---------------------------------------------------------------------------
