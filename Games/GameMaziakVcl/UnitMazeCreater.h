/*
  Maziak, a simple maze game
  Copyright (C) 2007  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#ifndef UnitMazeCreaterH
#define UnitMazeCreaterH
//---------------------------------------------------------------------------
#include <vector>

//From http://www.richelbilderbeek.nl/GetMazeDistances.htm
const std::vector<std::vector<int> > GetMazeDistances(
  const std::vector<std::vector<int> >& maze,
  const int x,
  const int y);

//From http://www.richelbilderbeek.nl/GetDistancesPath.htm
const std::vector<std::vector<int> > GetDistancesPath(
  const std::vector<std::vector<int> >& distances,
  const int playerX,
  const int playerY);

//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
const std::vector<std::vector<int> > CreateMaze(const int sz);

//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
const std::vector<std::vector<int> > CreateMazeOld(const int size);

//From http://www.richelbilderbeek.nl/CppCreateSloppyMaze.htm
const std::vector<std::vector<int> > CreateSloppyMazeOld(const int size, const double fractionPerfect);

//From http://www.richelbilderbeek.nl/CppGetDeadEnds.htm
const std::vector<std::pair<int,int> > GetDeadEnds(const std::vector<std::vector<int> >& maze);

//From http://www.richelbilderbeek.nl/CppGetNonDeadEnds.htm
const std::vector<std::pair<int,int> > GetNonDeadEnds(const std::vector<std::vector<int> >& maze);

//From http://www.richelbilderbeek.nl/CppCountDeadEnds.htm
const int CountDeadEnds(const std::vector<std::vector<int> >& maze);

//From http://www.richelbilderbeek.nl/CppSolveMaze.htm
const std::vector<std::vector<int> > SolveMaze(
  const std::vector<std::vector<int> >& maze,
  const int x1,
  const int y1,
  const int x2,
  const int y2);

//From http://www.richelbilderbeek.nl/CppCountNonDeadEnds.htm
const int CountNonDeadEnds(const std::vector<std::vector<int> >& maze);


#endif
