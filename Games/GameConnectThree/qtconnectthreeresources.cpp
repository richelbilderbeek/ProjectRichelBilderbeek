//---------------------------------------------------------------------------
/*
GameConnectThree, connect-three game
Copyright (C) 2010-2015 Richel Bilderbeek

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
#include "qtconnectthreeresources.h"

#include <cassert>

ribi::con3::QtConnectThreeResources::QtConnectThreeResources()
  : ConnectThreeResources(
    {
      "ConnectThreeComputer1.png",
      "ConnectThreeComputer2.png",
      "ConnectThreeComputer3.png"
    },
    "ConnectThreeComputerGrey.png",
    "GameConnectThree.css",
    "ConnectThreeEmpty.png",
    "ConnectThreeIcon.png",
    {
      "ConnectThreeGood1.png",
      "ConnectThreeGood2.png"
    },
    "ConnectThreeWrong.png",
    {
      "ConnectThreePlayer1.png",
      "ConnectThreePlayer2.png",
      "ConnectThreePlayer3.png"
    },
    {
      "ConnectThreePlayer1Grey.png",
      "ConnectThreePlayer2Grey.png",
      "ConnectThreePlayer3Grey.png"
    },
    "Quit",
    "Winner"
  )
{

}
