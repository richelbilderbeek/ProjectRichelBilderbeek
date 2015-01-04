//---------------------------------------------------------------------------
/*
StaircaseCardCreator, tool to generate staircase cards
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolStaircaseCardCreator.htm
//---------------------------------------------------------------------------
#ifndef STAIRCASECARDCOLUMN_H
#define STAIRCASECARDCOLUMN_H

#include <string>
#include <vector>
#include "staircasecardorientation.h"

namespace ribi {
namespace scc {

///A column in a staircase card
struct Column
{
  Column(const int n_vertical, const int n_horizontal);
  Column(const std::vector<int>& v);

  Orientation GetOrientation(const int row) const noexcept;

  int GetMax() const noexcept { return static_cast<int>(m_v.size()); }

  void Shuffle() noexcept;

  //Swap two orientations
  void Swap(const int a, const int b) noexcept;

  std::string ToStr() const noexcept;

  private:
  std::vector<Orientation> m_v;

  static std::vector<Orientation> Create(const int n_vertical, const int n_horizontal) noexcept;
  static std::vector<Orientation> Create(const std::vector<int>& v);
};

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARDCOLUMN_H
