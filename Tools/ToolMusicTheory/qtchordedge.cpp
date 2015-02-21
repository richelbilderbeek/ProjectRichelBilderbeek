//---------------------------------------------------------------------------
/*
MusicTheory, tool for visualizing my music theory
Copyright (C) 2012-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolMusicTheory.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "qtchordedge.h"
#pragma GCC diagnostic pop

QtChordEdge::QtChordEdge(QGraphicsItem *parent)
  : QGraphicsLineItem(parent)
{

}

std::string QtChordEdge::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> QtChordEdge::GetVersionHistory() noexcept
{
  return {
    "2012-08-10: version 1.0: initial version",
    "2013-07-25: version 1.1: transition to Qt5"
  };
}
