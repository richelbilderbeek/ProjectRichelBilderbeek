//---------------------------------------------------------------------------
/*
ConnectThree. A connect-three game.
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/GameConnectThree.htm
//---------------------------------------------------------------------------
#include <iostream>
//---------------------------------------------------------------------------
#include "../../Classes/CppConnectThree/connectthree.h"
//---------------------------------------------------------------------------
void PlayRandomMatch()
{
  ConnectThree c(std::bitset<3>(),15,5);
  while (c.GetWinner() == ConnectThree::no_player)
  {
    c.DoMove(c.SuggestMove());
  }
}
//---------------------------------------------------------------------------
void TestConnectThree()
{
  for (int i=0; i!=1000; ++i)
  {
    PlayRandomMatch();
  }
}
//---------------------------------------------------------------------------
///main only tests the ConnectThree class.
int main()
{
  TestConnectThree();
}
//---------------------------------------------------------------------------
