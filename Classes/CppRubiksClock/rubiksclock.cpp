
/*
RubiksClock, class for Rubik's clock
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

//From http://www.richelbilderbeek.nl/CppRubiksClock.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "rubiksclock.h"

#include <cassert>
#include <cstdlib>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
#include "trace.h"

#pragma GCC diagnostic pop

RubiksClock::Times::Times(const bool is_front)
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      times[x][y].reset(new RubiksClockDialWidget(0,0,0,32,32,
        is_front ? 196 : 128,
        is_front ? 196 : 128,
        is_front ? 255 : 255));
    }
  }
}

bool operator==(const RubiksClock::Times& lhs, const RubiksClock::Times& rhs)
{
  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (lhs.times[x][y]->GetRubiksClockDial()->GetTime()
        != rhs.times[x][y]->GetRubiksClockDial()->GetTime()) return false;
    }
  }
  return true;
}

RubiksClock::Pegs::Pegs()
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      pegs[x][y].reset(new ToggleButtonWidget(false,255,255,0));
    }
  }
}

bool operator==(const RubiksClock::Pegs& lhs, const RubiksClock::Pegs& rhs)
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

RubiksClock::Pegs CreatePegsFromIndex(const int index)
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

  RubiksClock::Pegs pegs;
  pegs.pegs[0][0].reset(new ToggleButtonWidget(((index & 1) == 1),255,255,0));
  pegs.pegs[1][0].reset(new ToggleButtonWidget(((index & 2) == 2),255,255,0));
  pegs.pegs[0][1].reset(new ToggleButtonWidget(((index & 4) == 4),255,255,0));
  pegs.pegs[1][1].reset(new ToggleButtonWidget(((index & 8) == 8),255,255,0));
  return pegs;


}

RubiksClock::RubiksClock()
  : mFront(Times(true)),
    mBack(Times(false))
{
  Check();
}

void RubiksClock::SetGeometry(const Rect& r)
{
  const int left = r.GetX();
  const int top = r.GetY();
  const int width = r.GetWidth();
  const int height = r.GetHeight();

  const double w3 = boost::numeric_cast<double>(width) / 3.0;
  const double h3 = boost::numeric_cast<double>(height) / 3.0;
  for (int x=0; x!=3; ++x)
  {
    const double x_d = boost::numeric_cast<double>(x);
    for (int y=0; y!=3; ++y)
    {
      const double y_d = boost::numeric_cast<double>(y);
      mBack.times[x][y]->SetGeometry(
        Rect(
          left + (x_d*w3),
          top + (y_d*h3),
          w3,
          h3));
      mFront.times[x][y]->SetGeometry(
        Rect(
          left + (x_d*w3),
          top + (y_d*h3),
          w3,
          h3));
    }
  }
  for (int x=0; x!=2; ++x)
  {
    const double x_d = boost::numeric_cast<double>(x);
    for (int y=0; y!=2; ++y)
    {
      const double y_d = boost::numeric_cast<double>(y);
      mPegs.pegs[x][y]->SetGeometry(
        Rect(
          left + ((0.9+x_d)*w3),
          top + ((0.9+y_d)*h3),
          w3*0.2,
          h3*0.2));
    }
  }

}

void RubiksClock::TogglePeg(const Side side)
{
  const int x = (side == topLeft || side == bottomLeft ? 0 : 1);
  const int y = (side == topLeft || side == topRight ? 0 : 1);
  mPegs.pegs[x][y]->GetToggleButton()->Toggle();
  m_signal_clock_changed();
}

void RubiksClock::TurnWheel(const Side side, const int nSteps)
{
  switch (side)
  {
    case topLeft: TurnWheelTopLeft(nSteps); break;
    case topRight: TurnWheelTopRight(nSteps); break;
    case bottomLeft: TurnWheelBottomLeft(nSteps); break;
    case bottomRight: TurnWheelBottomRight(nSteps); break;
  }
  if (nSteps % 12 != 0)
  {
    m_signal_clock_changed();
  }
}

void RubiksClock::TurnWheelTopLeft(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][0] = true;
  turnFront[1][0] = !mPegs.pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][0] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !mPegs.pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[0][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());

  turnBack[0][0] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][0] = true;

  turnBack[0][1] = (
    mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
    && (    mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
       ||   mPegs.pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][1] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
    && (  mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
       || mPegs.pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[2][2] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[0][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }

}

void RubiksClock::TurnWheelTopRight(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][0] = true;
  turnFront[1][0] = !mPegs.pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][0] = (mPegs.pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !mPegs.pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (mPegs.pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (mPegs.pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.pegs[0][1]->GetToggleButton()->IsPressed());

  turnBack[2][0] = (mPegs.pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = mPegs.pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][0] = true;

  turnBack[2][1] = (
    mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
    && (    mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
       ||   mPegs.pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][1] = mPegs.pegs[1][0]->GetToggleButton()->IsPressed();

  turnBack[2][2] = (mPegs.pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
    && (  mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
       || mPegs.pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[0][2] = (mPegs.pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void RubiksClock::TurnWheelBottomLeft(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][2] = true;
  turnFront[1][2] = !mPegs.pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][2] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !mPegs.pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[0][0] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[0][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = mPegs.pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][2] = true;

  turnBack[0][1] = (
    mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
    && (    mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
       ||   mPegs.pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][1] = mPegs.pegs[0][1]->GetToggleButton()->IsPressed();

  turnBack[0][0] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
    && (  mPegs.pegs[0][0]->GetToggleButton()->IsPressed()
       || mPegs.pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[2][0] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[0][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void RubiksClock::TurnWheelBottomRight(const int nSteps)
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][2] = true;
  turnFront[1][2] = !mPegs.pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][2] = (mPegs.pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !mPegs.pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (mPegs.pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
       || !mPegs.pegs[0][0]->GetToggleButton()->IsPressed()  ) );
  turnFront[0][0] = (mPegs.pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[2][2] = (mPegs.pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = mPegs.pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][2] = true;

  turnBack[2][1] = (
    mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
    && (    mPegs.pegs[0][1]->GetToggleButton()->IsPressed()
       ||   mPegs.pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][1] = mPegs.pegs[1][1]->GetToggleButton()->IsPressed();

  turnBack[2][0] = (mPegs.pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    mPegs.pegs[1][1]->GetToggleButton()->IsPressed()
    && (  mPegs.pegs[1][0]->GetToggleButton()->IsPressed()
       || mPegs.pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[0][0] = (mPegs.pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.pegs[1][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

const RubiksClock::Times& RubiksClock::GetFrontTimes() const
{
  return mFront;
}

RubiksClock::Times& RubiksClock::GetFrontTimes()
{
  return mFront;
}

const RubiksClock::Times& RubiksClock::GetBackTimes() const
{
  return mBack;
}

RubiksClock::Times& RubiksClock::GetBackTimes()
{
  return mBack;
}

const RubiksClock::Pegs& RubiksClock::GetFrontPegs() const
{
  return mPegs;
}

RubiksClock::Pegs& RubiksClock::GetFrontPegs()
{
  return mPegs;
}

const RubiksClock::Pegs RubiksClock::GetBackPegs() const
{
  Pegs back;
  back.pegs[0][0].reset(new ToggleButtonWidget(!mPegs.pegs[1][0]->GetToggleButton()->IsPressed(),255,255,0));
  back.pegs[1][0].reset(new ToggleButtonWidget(!mPegs.pegs[0][0]->GetToggleButton()->IsPressed(),255,255,0));
  back.pegs[0][1].reset(new ToggleButtonWidget(!mPegs.pegs[1][1]->GetToggleButton()->IsPressed(),255,255,0));
  back.pegs[1][1].reset(new ToggleButtonWidget(!mPegs.pegs[0][1]->GetToggleButton()->IsPressed(),255,255,0));

  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      back.pegs[x][y]->SetGeometry(mPegs.pegs[1-x][y]->GetGeometry());
    }
  }

  return back;
}

void RubiksClock::Check()
{
  #ifndef NDEBUG
  const Times originalFront = mFront;
  const Times originalBack = mBack;
  const Pegs originalPegs = mPegs;

  //Check the corner clocks
  assert( (mFront.times[0][0]->GetRubiksClockDial()->GetTime()
    + mBack.times[2][0]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (mFront.times[2][0]->GetRubiksClockDial()->GetTime()
    + mBack.times[0][0]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (mFront.times[0][2]->GetRubiksClockDial()->GetTime()
    + mBack.times[2][2]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (mFront.times[2][2]->GetRubiksClockDial()->GetTime()
    + mBack.times[0][2]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  //Check all peg combinations
  for (int i=0; i!=16; ++i)
  {
    mPegs = CreatePegsFromIndex(i);
    //Check all wheels
    for (int j=0; j!=4; ++j)
    {
      //Check if after turning around in two steps, everything stays the same
      const Times front = mFront;
      const Times back = mBack;

      const Side side = static_cast<Side>(j);
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

const std::string RubiksClock::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> RubiksClock::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-08: Version 1.0: initial version");
  return v;
}

std::ostream& operator<<(std::ostream& os, const RubiksClock& r)
{
  os
    << "<rubiks_clock>"
    << "<front>"
    << r.mFront
    << "</front>"
    << "<back>"
    << r.mBack
    << "</back>"
    << "<pegs>"
    << r.mPegs
    << "</pegs>"
    << "</rubiks_clock>";
  return os;
}

std::ostream& operator<<(std::ostream& os, const RubiksClock::Times& t)
{
  os
    << "<rubiks_clock_times>";
  for (int x=0; x!=3; ++x)
  {
    for (int y=0; y!=3; ++y)
    {
      os
        << "<rubiks_clock_dial>"
        << "<x>"
        << x
        << "</x>"
        << "<y>"
        << y
        << "</y>"
        << t.times[x][y].get()
        << "</rubiks_clock_dial>";
    }
  }
  os
    << "</rubiks_clock_times>";
  return os;
}

std::ostream& operator<<(std::ostream& os, const RubiksClock::Pegs& p)
{
  os
    << "<rubiks_clock_pegs>";
  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      os
        << "<rubiks_clock_pegs>"
        << "<x>"
        << x
        << "</x>"
        << "<y>"
        << y
        << "</y>"
        << p.pegs[x][y].get()
        << "</rubiks_clock_dial>";
    }
  }
  os
    << "</rubiks_clock_pegs>";
  return os;
}


