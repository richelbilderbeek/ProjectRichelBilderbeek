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
#include <cassert>

#pragma hdrstop

#include "UnitRubiksClock.h"

//---------------------------------------------------------------------------
RubiksClockTimes::RubiksClockTimes()
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      times[x][y] = 0;
    }
  }
}
//---------------------------------------------------------------------------
bool operator==(const RubiksClockTimes& lhs, const RubiksClockTimes& rhs)
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (lhs.times[x][y] != rhs.times[x][y]) return false;
    }
  }
  return true;
}
//---------------------------------------------------------------------------
RubiksClockPegs::RubiksClockPegs()
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      pegs[x][y] = 0;
    }
  }
}
//---------------------------------------------------------------------------
bool operator==(const RubiksClockPegs& lhs, const RubiksClockPegs& rhs)
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      if (lhs.pegs[x][y] != rhs.pegs[x][y]) return false;
    }
  }
  return true;
}
//---------------------------------------------------------------------------
RubiksClockPegs CreatePegsFromIndex(const int index)
{
  //Index 0: (p = pressed, u = unpressed)
  // u u
  // u u
  //Index 1: (p = pressed, u = unpressed)
  // p u
  // u u
  //Index 2: (p = pressed, u = unpressed)
  // u p
  // u u
  //Index 3: (p = pressed, u = unpressed)
  // p p
  // u u
  //Index 4: (p = pressed, u = unpressed)
  // u u
  // p u
  //Index 5: (p = pressed, u = unpressed)
  // p u
  // p u
  //Index 6: (p = pressed, u = unpressed)
  // u p
  // p u
  //Index 7: (p = pressed, u = unpressed)
  // p p
  // p u
  //Index 8: (p = pressed, u = unpressed)
  // u u
  // u p
  //Index 9: (p = pressed, u = unpressed)
  // p u
  // u p
  //Index 10: (p = pressed, u = unpressed)
  // u p
  // u p
  //Index 11: (p = pressed, u = unpressed)
  // p p
  // u p
  //Index 12: (p = pressed, u = unpressed)
  // u u
  // p p
  //Index 13: (p = pressed, u = unpressed)
  // p u
  // p p
  //Index 14: (p = pressed, u = unpressed)
  // u p
  // p p
  //Index 15: (p = pressed, u = unpressed)
  // p p
  // p p

  RubiksClockPegs pegs;
  pegs.pegs[0][0] = ( index & 1 == 1 ? true : false);
  pegs.pegs[1][0] = ( index & 2 == 2 ? true : false);
  pegs.pegs[0][1] = ( index & 4 == 4 ? true : false);
  pegs.pegs[1][1] = ( index & 8 == 8 ? true : false);
  return pegs;


}
//---------------------------------------------------------------------------
RubiksClock::RubiksClock()
{
  Check();
}
//---------------------------------------------------------------------------
void RubiksClock::ChangePeg(const RubiksClockSide side, const bool press)
{
  const int x = (side == topLeft || side == bottomLeft ? 0 : 1);
  const int y = (side == topLeft || side == topRight ? 0 : 1);
  mPegs.pegs[x][y] = press;
}
//---------------------------------------------------------------------------
void RubiksClock::TurnWheel(const RubiksClockSide side, const int nSteps)
{
  switch (side)
  {
    case topLeft: TurnWheelTopLeft(nSteps); break;
    case topRight: TurnWheelTopRight(nSteps); break;
    case bottomLeft: TurnWheelBottomLeft(nSteps); break;
    case bottomRight: TurnWheelBottomRight(nSteps); break;
  }
}
//---------------------------------------------------------------------------
void RubiksClock::TurnWheelTopLeft(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][0] = true;
  turnFront[1][0] = (mPegs.pegs[0][0] == false ? true: false);
  turnFront[2][0] = (mPegs.pegs[0][0] == mPegs.pegs[1][0] ? true: false);
  turnFront[0][1] = (mPegs.pegs[0][0] == false ? true: false);
  turnFront[1][1] = (mPegs.pegs[0][0] == false ? true: false);
  turnFront[2][1] = (
    mPegs.pegs[0][0] == false
    && (  mPegs.pegs[1][0] == false
       || mPegs.pegs[1][1] == false )
    ? true: false);
  turnFront[0][2] = (mPegs.pegs[0][0] == mPegs.pegs[0][1] ? true : false);
  turnFront[1][2] = (
    mPegs.pegs[0][0] == false
    && (  mPegs.pegs[0][1] == false
       || mPegs.pegs[1][1] == false )
    ? true: false);
  turnFront[2][2] = (mPegs.pegs[0][0] == mPegs.pegs[1][1] ? true : false);

  turnBack[0][0] = (mPegs.pegs[0][0] == mPegs.pegs[1][0] ? true: false);
  turnBack[1][0] = (mPegs.pegs[0][0] == true ? true: false);
  turnBack[2][0] = true;

  turnBack[0][1] = (
    mPegs.pegs[0][0] == true
    && (    mPegs.pegs[1][0] == true
       ||   mPegs.pegs[1][1] == true )
    ? true: false);
  turnBack[1][1] = (mPegs.pegs[0][0] == true ? true: false);
  turnBack[2][1] = (mPegs.pegs[0][0] == true ? true: false);

  turnBack[0][2] = (mPegs.pegs[0][0] == mPegs.pegs[1][1] ? true: false);
  turnBack[1][2] = (
    mPegs.pegs[0][0] == true
    && (  mPegs.pegs[0][1] == true
       || mPegs.pegs[1][1] == true )
    ? true: false);
  turnBack[2][2] = (mPegs.pegs[0][0] == mPegs.pegs[0][1] ? true: false);

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y] == true) { mFront.times[x][y] += nSteps     ; mFront.times[x][y]%=12; }
      if (turnBack[x][y]  == true) { mBack.times[x][y]  += (12-nSteps); mBack.times[x][y] %=12; }
    }
  }

}
//---------------------------------------------------------------------------
void RubiksClock::TurnWheelTopRight(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][0] = true;
  turnFront[1][0] = (mPegs.pegs[1][0] == false ? true: false);
  turnFront[0][0] = (mPegs.pegs[0][0] == mPegs.pegs[1][0] ? true: false);
  turnFront[2][1] = (mPegs.pegs[1][0] == false ? true: false);
  turnFront[1][1] = (mPegs.pegs[1][0] == false ? true: false);
  turnFront[0][1] = (
    mPegs.pegs[1][0] == false
    && (  mPegs.pegs[0][0] == false
       || mPegs.pegs[0][1] == false )
    ? true: false);
  turnFront[2][2] = (mPegs.pegs[1][0] == mPegs.pegs[1][1] ? true : false);
  turnFront[1][2] = (
    mPegs.pegs[1][0] == false
    && (  mPegs.pegs[1][1] == false
       || mPegs.pegs[0][1] == false )
    ? true: false);
  turnFront[0][2] = (mPegs.pegs[1][0] == mPegs.pegs[0][1] ? true : false);

  turnBack[2][0] = (mPegs.pegs[1][0] == mPegs.pegs[0][0] ? true: false);
  turnBack[1][0] = (mPegs.pegs[1][0] == true ? true: false);
  turnBack[0][0] = true;

  turnBack[2][1] = (
    mPegs.pegs[1][0] == true
    && (    mPegs.pegs[0][0] == true
       ||   mPegs.pegs[0][1] == true )
    ? true: false);
  turnBack[1][1] = (mPegs.pegs[1][0] == true ? true: false);
  turnBack[0][1] = (mPegs.pegs[1][0] == true ? true: false);

  turnBack[2][2] = (mPegs.pegs[1][0] == mPegs.pegs[0][1] ? true: false);
  turnBack[1][2] = (
    mPegs.pegs[1][0] == true
    && (  mPegs.pegs[1][1] == true
       || mPegs.pegs[0][1] == true )
    ? true: false);
  turnBack[0][2] = (mPegs.pegs[1][0] == mPegs.pegs[1][1] ? true: false);

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y] == true) { mFront.times[x][y] += nSteps     ; mFront.times[x][y]%=12; }
      if (turnBack[x][y]  == true) { mBack.times[x][y]  += (12-nSteps); mBack.times[x][y] %=12; }
    }
  }
}
//---------------------------------------------------------------------------
void RubiksClock::TurnWheelBottomLeft(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][2] = true;
  turnFront[1][2] = (mPegs.pegs[0][1] == false ? true: false);
  turnFront[2][2] = (mPegs.pegs[0][1] == mPegs.pegs[1][1] ? true: false);
  turnFront[0][1] = (mPegs.pegs[0][1] == false ? true: false);
  turnFront[1][1] = (mPegs.pegs[0][1] == false ? true: false);
  turnFront[2][1] = (
    mPegs.pegs[0][1] == false
    && (  mPegs.pegs[1][1] == false
       || mPegs.pegs[1][0] == false )
    ? true: false);
  turnFront[0][0] = (mPegs.pegs[0][1] == mPegs.pegs[0][0] ? true : false);
  turnFront[1][0] = (
    mPegs.pegs[0][1] == false
    && (  mPegs.pegs[0][0] == false
       || mPegs.pegs[1][0] == false )
    ? true: false);
  turnFront[2][0] = (mPegs.pegs[0][1] == mPegs.pegs[1][0] ? true : false);

  turnBack[0][2] = (mPegs.pegs[0][1] == mPegs.pegs[1][1] ? true: false);
  turnBack[1][2] = (mPegs.pegs[0][1] == true ? true: false);
  turnBack[2][2] = true;

  turnBack[0][1] = (
    mPegs.pegs[0][1] == true
    && (    mPegs.pegs[1][1] == true
       ||   mPegs.pegs[1][0] == true )
    ? true: false);
  turnBack[1][1] = (mPegs.pegs[0][1] == true ? true: false);
  turnBack[2][1] = (mPegs.pegs[0][1] == true ? true: false);

  turnBack[0][0] = (mPegs.pegs[0][1] == mPegs.pegs[1][0] ? true: false);
  turnBack[1][0] = (
    mPegs.pegs[0][1] == true
    && (  mPegs.pegs[0][0] == true
       || mPegs.pegs[1][0] == true )
    ? true: false);
  turnBack[2][0] = (mPegs.pegs[0][1] == mPegs.pegs[0][0] ? true: false);

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y] == true) { mFront.times[x][y] += nSteps     ; mFront.times[x][y]%=12; }
      if (turnBack[x][y]  == true) { mBack.times[x][y]  += (12-nSteps); mBack.times[x][y] %=12; }
    }
  }
}
//---------------------------------------------------------------------------
void RubiksClock::TurnWheelBottomRight(const int nSteps)
{


  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][2] = true;
  turnFront[1][2] = (mPegs.pegs[1][1] == false ? true: false);
  turnFront[0][2] = (mPegs.pegs[0][1] == mPegs.pegs[1][1] ? true: false);
  turnFront[2][1] = (mPegs.pegs[1][1] == false ? true: false);
  turnFront[1][1] = (mPegs.pegs[1][1] == false ? true: false);
  turnFront[0][1] = (
    mPegs.pegs[1][1] == false
    && (  mPegs.pegs[0][1] == false
       || mPegs.pegs[0][0] == false )
    ? true: false);
  turnFront[2][0] = (mPegs.pegs[1][1] == mPegs.pegs[1][0] ? true : false);
  turnFront[1][0] = (
    mPegs.pegs[1][1] == false
    && (  mPegs.pegs[1][0] == false
       || mPegs.pegs[0][0] == false )
    ? true: false);
  turnFront[0][0] = (mPegs.pegs[1][1] == mPegs.pegs[0][0] ? true : false);

  turnBack[2][2] = (mPegs.pegs[1][1] == mPegs.pegs[0][1] ? true: false);
  turnBack[1][2] = (mPegs.pegs[1][1] == true ? true: false);
  turnBack[0][2] = true;

  turnBack[2][1] = (
    mPegs.pegs[1][1] == true
    && (    mPegs.pegs[0][1] == true
       ||   mPegs.pegs[0][0] == true )
    ? true: false);
  turnBack[1][1] = (mPegs.pegs[1][1] == true ? true: false);
  turnBack[0][1] = (mPegs.pegs[1][1] == true ? true: false);

  turnBack[2][0] = (mPegs.pegs[1][1] == mPegs.pegs[0][0] ? true: false);
  turnBack[1][0] = (
    mPegs.pegs[1][1] == true
    && (  mPegs.pegs[1][0] == true
       || mPegs.pegs[0][0] == true )
    ? true: false);
  turnBack[0][0] = (mPegs.pegs[1][1] == mPegs.pegs[1][0] ? true: false);

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y] == true) { mFront.times[x][y] += nSteps     ; mFront.times[x][y]%=12; }
      if (turnBack[x][y]  == true) { mBack.times[x][y]  += (12-nSteps); mBack.times[x][y] %=12; }
    }
  }




}
//---------------------------------------------------------------------------
const RubiksClockTimes& RubiksClock::GetFrontTimes() const
{
  return mFront;
}
//---------------------------------------------------------------------------
const RubiksClockTimes& RubiksClock::GetBackTimes() const
{
  return mBack;
}
//---------------------------------------------------------------------------
const RubiksClockPegs& RubiksClock::GetFrontPegs() const
{
  return mPegs;
}
//---------------------------------------------------------------------------
const RubiksClockPegs RubiksClock::GetBackPegs() const
{
  RubiksClockPegs back;
  back.pegs[0][0] = !mPegs.pegs[1][0];
  back.pegs[1][0] = !mPegs.pegs[0][0];
  back.pegs[0][1] = !mPegs.pegs[1][1];
  back.pegs[1][1] = !mPegs.pegs[0][1];
  return back;
}
//---------------------------------------------------------------------------
void RubiksClock::Check()
{
  #ifndef NDEBUG
  const RubiksClockTimes originalFront = mFront;
  const RubiksClockTimes originalBack = mBack;
  const RubiksClockPegs originalPegs = mPegs;

  //Check the corner clocks
  assert( mFront.times[0][0] + mBack.times[2][0] == 0 || mFront.times[0][0] + mBack.times[2][0] == 12);
  assert( mFront.times[2][0] + mBack.times[0][0] == 0 || mFront.times[2][0] + mBack.times[0][0] == 12);
  assert( mFront.times[0][2] + mBack.times[2][2] == 0 || mFront.times[0][2] + mBack.times[2][2] == 12);
  assert( mFront.times[2][2] + mBack.times[0][2] == 0 || mFront.times[2][2] + mBack.times[0][2] == 12);
  //Check all peg combinations
  for (int i=0; i!=16; ++i)
  {
    mPegs = CreatePegsFromIndex(i);
    //Check all wheels
    for (int j=0; j!=4; ++j)
    {
      //Check if after turning around in two steps, everything stays the same
      const RubiksClockTimes front = mFront;
      const RubiksClockTimes back = mBack;

      const RubiksClockSide side = static_cast<RubiksClockSide>(j);
      const int nSteps = std::rand() % 12;
      //Turn 1
      this->TurnWheel(side,nSteps);
      //Turn 11
      this->TurnWheel(side,12-nSteps);
      assert( mFront == front);
      assert( mBack == back);
    }
  }

  #endif
}
//---------------------------------------------------------------------------



#pragma package(smart_init)
