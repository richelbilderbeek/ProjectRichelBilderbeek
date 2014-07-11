//---------------------------------------------------------------------------
/*
    Reversi Console, a simple board game
    Copyright (C) 2008  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/GameReversi.htm
//---------------------------------------------------------------------------
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <iterator>
#include <memory>
#include <sstream>
#include "UnitReversi.h"

std::ostream& operator<<(std::ostream& os, const Square s)
{
  switch (s)
  {
    case empty  : os << "."; break;
    case player1: os << "1"; break;
    case player2: os << "2"; break;
    default: assert(!"Should not get here"); break;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Reversi& r)
{
  { //Show the indices horizontally
    const int size = r.GetSize();
    os << "  ";
    for (int i=0; i!=size; ++i)
    {
      os << (i%10);
    }
    os << std::endl;
    os << std::endl;
  }
  {
    int i = 0;
    const std::vector<std::vector<Square> >& board = r.GetBoard();
    const std::vector<std::vector<Square> >::const_iterator lastRow = board.end();
    for (std::vector<std::vector<Square> >::const_iterator row = board.begin();
      row!=lastRow;
      ++row, ++i)
    {
      os << (i%10) << " ";
      std::copy( (*row).begin(), (*row).end(),std::ostream_iterator<Square>(os,""));
      os << " " << (i%10) << '\n';
    }
  }

  { //Show the indices horizontally
    os << std::endl;
    os << "  ";
    const int size = r.GetSize();
    for (int i=0; i!=size; ++i)
    {
      os << i%10;
    }
    os << std::endl;
  }
  return os;
}

//From http://www.richelbilderbeek.nl/CppStrIsInt.htm
//Checks whether a std::string can be converted to an integer.
//Returns true if possible, also returning this integer by referencing.
//Returns false otherwise, setting the referenced integer to zero.
const bool IsInt(const std::string& s, int& rInt)
{
  std::istringstream i(s);
  if (!(i >> rInt))
  {
    rInt = 0;
    return false;
  }
  return true;
}

const std::string GetInput()
{
  std::string s;
  std::getline(std::cin,s,'\n');
  return s;
}

//From http://www.richelbilderbeek.nl/CppSeperateString.htm
const std::vector<std::string> SeperateString(std::string input, const char seperator)
{
  assert(input.empty()==false);
  assert(input[0]!=seperator);
  assert(input[input.size()-1]!=seperator);

  std::vector<std::string> result;
  int pos = 0;
  while(pos<static_cast<int>(input.size()))
  {
    if (input[pos]==seperator)
    {
      const std::string found = input.substr(0,pos);
      result.push_back(found);
      input = input.substr(pos+1,input.size()-pos);
      pos = 0;
    }
    ++pos;
  }
  result.push_back(input);
  return result;
}

const bool IsCoordinat(const std::string& input, std::pair<int,int>& coordinat)
{
  if ( std::count(input.begin(), input.end(), ',') != 1) return false;
  if ( *(input.begin()) == ',' || *(input.end() - 1) == ',') return false;
  const std::string::const_iterator i = std::find(input.begin(), input.end(), ',');
  assert(i != input.end() ); //Comma must be in! Checked above!

  const std::vector<std::string> v(SeperateString(input,','));
  if (v.size() != 2) return false;
  if (IsInt(v[0],coordinat.first)==false) return false;
  if (IsInt(v[1],coordinat.second)==false) return false;
 return true;

}

const int AskUserForBoardSize()
{
  //Get the board's size
  while (1)
  {
    std::cout << "Please enter the size of the reversi board" << std::endl;
    const std::string input = GetInput();
    int size = -1;
    if ( IsInt(input,size) == false)
    {
      std::cout << "Please enter an integer value. " << std::endl;
      continue;
    }
    if ( size < 4)
    {
      std::cout << "Please enter an integer value bigger then 4. " << std::endl;
      continue;
    }
    if ( size > 16)
    {
      std::cout << "Please enter an integer value less then 16. " << std::endl;
      continue;
    }
    return size;
  }
}

int main()
{
  std::cout
    << "***********" << std::endl
    << "* REVERSI *" << std::endl
    << "***********" << std::endl
    << std::endl;
    
  Reversi r(AskUserForBoardSize());
  Square player = player1;

  while (1)
  {
    std::cout
      << "\nThe board's current state: " << std::endl
      << r << std::endl
      << "It is player " << player << "'s turn."
      << "Please enter a coordinat, 'p' to pass or 'q' to quit"
      << std::endl;

    const std::string input = GetInput();

    if (input == "q")
    {
      //Quit
      return 0;
    }
    if (input == "p")
    {
      //Pass
      player = (player == player1? player2 : player1);
      continue;
    }


    std::pair<int,int> coordinat;
    const bool isValidCoordinat = IsCoordinat(input, coordinat);

    if (isValidCoordinat == false)
    {
      std::cout
        << "Please enter a correctly formatted coordinat."
        << "\nFor example:  1,2  " << std::endl;
      continue;
    }
    if (r.IsValidMove(coordinat.first, coordinat.second, player) == false)
    {
      std::cout
        << "Please enter a valid coordinat." << std::endl;
      continue;
    }
    //Actually do the move
    r.DoMove(coordinat.first, coordinat.second, player);

    //Check if the game has ended
    if (r.Count(empty) == 0)
    {
      //No empty squares
      const int n1 = r.Count(player1);
      const int n2 = r.Count(player2);
      std::cout << "The game has ended." << std::endl
        << "Player 1 conquered " << n1 << " squares." << std::endl
        << "Player 2 conquered " << n2 << " squares." << std::endl
        << "The winner is player " << (n1 > n2 ? "1" : "2") << std::endl
        << "Congratulations!" << std::endl
        << std::endl
        << "Press any key to quit. " << std::endl;

      std::cin.get();
      return 0; //Terminate the program
    }

    //Check if other player can actually do a move
    if (r.GetValidMoves(player).empty()==true)
    {
      std::cout << "Too bad! Player " << player << " is unabled to do a valid move!";
      player = (player == player1 ? player2 : player1);
      std::cout << "\nThe next turn again goes to player " << player << "!" << std::endl;
      continue;
    }

    player = (player == player1 ? player2 : player1);
  }
}

