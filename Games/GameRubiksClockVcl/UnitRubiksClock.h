//---------------------------------------------------------------------------
/*
  Rubik's Clock Simulator. Simulates Rubik's Clock.
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
#ifndef UnitRubiksClockH
#define UnitRubiksClockH
//---------------------------------------------------------------------------
#include <vector>
//---------------------------------------------------------------------------
struct RubiksClockTimes
{
  RubiksClockTimes();
  int times[3][3];
};

bool operator==(const RubiksClockTimes& lhs, const RubiksClockTimes& rhs);

struct RubiksClockPegs
{
  RubiksClockPegs();
  bool pegs[2][2]; //Is peg pressed?
};

bool operator==(const RubiksClockPegs& lhs, const RubiksClockPegs& rhs);

RubiksClockPegs CreatePegsFromIndex(const int index);

enum RubiksClockSide
{
  topLeft, topRight, bottomLeft, bottomRight
};


struct RubiksClock
{
  RubiksClock();

  void ChangePeg(const RubiksClockSide side, const bool press); //Seen from front
  void TurnWheel(const RubiksClockSide side, const int nSteps); //Seen from front
  void TurnWheelTopLeft(const int nSteps); //Seen from front
  void TurnWheelTopRight(const int nSteps); //Seen from front
  void TurnWheelBottomLeft(const int nSteps); //Seen from front
  void TurnWheelBottomRight(const int nSteps); //Seen from front

  void Check();

  const RubiksClockTimes& GetFrontTimes() const;
  const RubiksClockTimes& GetBackTimes() const;
  const RubiksClockPegs& GetFrontPegs() const;
  const RubiksClockPegs GetBackPegs() const;

  private:
  RubiksClockTimes mFront;
  RubiksClockTimes mBack;
  RubiksClockPegs mPegs;
};


#endif
