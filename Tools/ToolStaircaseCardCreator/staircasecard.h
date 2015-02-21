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
#ifndef STAIRCASECARD_H
#define STAIRCASECARD_H

#include <iosfwd>
#include <vector>
#include "staircasecardcolumn.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct TextCanvas;

namespace scc {

struct StaircaseCard
{
  StaircaseCard(const int n_cols, const int n_rows);
  StaircaseCard(const std::vector<Column>& v) noexcept : m_v{v} {}

  static boost::shared_ptr<StaircaseCard> GetTest(const int i) noexcept;

  ///Give a measurement of aesthetics
  int RateAesthetics() const noexcept;

  ///Create a random card
  void Shuffle() noexcept;

  ///Create a random card with an aesthetic algorithm
  void ShuffleAesthetic() noexcept;

  boost::shared_ptr<QImage> ToImage() const noexcept;
  boost::shared_ptr<TextCanvas> ToTextCanvas() const noexcept;
  boost::shared_ptr<TextCanvas> ToTextCanvasCompact() const noexcept;

  private:
  std::vector<Column> m_v;

  static std::vector<int> ColumnToMap(const Column& c) noexcept;
  static std::vector<Column> CreateGrid(const int n_cols, const int n_rows) noexcept;
};

std::ostream& operator<<(std::ostream& os, const StaircaseCard& c);

} //~namespace scc
} //~namespace ribi

#endif // STAIRCASECARD_H
