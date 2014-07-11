//---------------------------------------------------------------------------
/*
  Super Tron, a simple game
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
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#pragma hdrstop

#include <cmath>
#include "UnitSuperTronPlayer.h"

//---------------------------------------------------------------------------
double SuperTronPlayer::deltaAngle = 0.1 * M_PI;
const double SuperTronPlayer::speed = 1.0;
//---------------------------------------------------------------------------
SuperTronPlayer::SuperTronPlayer()
  : x(0.0),
    y(0.0),
    angle(0.0),
    nWins(0),
    nLose(0),
    color(static_cast<TColor>(0)),
    keyLeft(0),
    keyRight(0)
{

}

#pragma package(smart_init)
