//---------------------------------------------------------------------------
/*
  Maze Creater, creates a maze and displays it on screen
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
#include <cassert>
#pragma hdrstop

#include "UnitMazeCreater.h"
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCreateMaze.htm
std::vector<std::vector<int> > CreateMaze(const int size)
{
  //Size must be odd
  assert( size % 2 == 1);

  std::vector<std::vector<int> > maze(size, std::vector<int>(size,0));

  //Draw outer walls
  for (int i=0; i!=size; ++i)
  {
    maze[0]     [i     ] = 1;
    maze[size-1][i     ] = 1;
    maze[i]     [0     ] = 1;
    maze[i]     [size-1] = 1;
  }

  //Draw pillars
  for (int y=2; y!=size-1; y+=2)
  {
    for (int x=2; x!=size-1; x+=2)
    {
      maze[y][x] = 1;
    }
  }

  //Check around pillars
  const int nWallsToAdd = ((size / 2) - 1) * ((size / 2) - 1);
  for (int i=0; i!=nWallsToAdd; )
  {

    for (int y=2; y!=size-1; y+=2)
    {
      for (int x=2; x!=size-1; x+=2)
      {
        const int nWalls
          = (maze[y-1][x] == 0 ? 0 : 1)
          + (maze[y+1][x] == 0 ? 0 : 1)
          + (maze[y][x+1] == 0 ? 0 : 1)
          + (maze[y][x-1] == 0 ? 0 : 1);
        if ( nWalls == 0)
        {
          switch(std::rand() % 4)
          {
            case 0: maze[y-1][x] = 1; break;
            case 1: maze[y+1][x] = 1; break;
            case 2: maze[y][x+1] = 1; break;
            case 3: maze[y][x-1] = 1; break;
          }
          ++i;
        }
        else if (nWalls == 1)
        {
          switch(std::rand() % 6)
          {
            case 0: std::swap(maze[y-1][x], maze[y+1][x]); break;
            case 1: std::swap(maze[y-1][x], maze[y][x+1]); break;
            case 2: std::swap(maze[y-1][x], maze[y][x-1]); break;
            case 3: std::swap(maze[y+1][x], maze[y][x+1]); break;
            case 4: std::swap(maze[y+1][x], maze[y][x-1]); break;
            case 5: std::swap(maze[y][x+1], maze[y][x-1]); break;
          }
        }
      }
    }
  }
  return maze;
}

#pragma package(smart_init)
