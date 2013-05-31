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
#ifndef STAIRCASECARD_H
#define STAIRCASECARD_H
//---------------------------------------------------------------------------
#include <vector>
#include <boost/dynamic_bitset.hpp>
//---------------------------------------------------------------------------
struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);

  const std::vector<boost::dynamic_bitset<> > Get() const { return m_grid; }
  int GetCols() const { return m_grid.size(); }
  int GetRows() const { return m_grid[0].size(); }
  bool GetValue(const int col, const int row) const { return m_grid[col][row]; }
  void ResizeCols(const int n_cols);
  void ResizeRows(const int n_rows);
  void Swap(const int col, const int row1, const int row2);

  private:
  std::vector<boost::dynamic_bitset<> > m_grid;
};
//---------------------------------------------------------------------------
#endif // STAIRCASECARD_H
