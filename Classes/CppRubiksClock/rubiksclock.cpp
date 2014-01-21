//---------------------------------------------------------------------------
/*
RubiksClock, class for Rubik's clock
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppRubiksClock.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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

ribi::RubiksClock::Times::Times(const bool is_front) noexcept
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

bool ribi::operator==(const ribi::RubiksClock::Times& lhs, const ribi::RubiksClock::Times& rhs) noexcept
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

ribi::RubiksClock::Pegs::Pegs() noexcept
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      m_pegs[x][y].reset(new ToggleButtonWidget(false,255,255,0));
    }
  }
}

const boost::shared_ptr<const ribi::ToggleButtonWidget> ribi::RubiksClock::Pegs::GetPeg(const Side side) const noexcept
{
  switch (side)
  {
    case Side::topLeft    : return m_pegs[0][0];
    case Side::bottomLeft : return m_pegs[1][0];
    case Side::topRight   : return m_pegs[0][1];
    case Side::bottomRight: return m_pegs[1][1];
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::RubiksClock::Pegs::GetPeg");
}

bool operator==(const ribi::RubiksClock::Pegs& lhs, const ribi::RubiksClock::Pegs& rhs) noexcept
{
  for (int y=0; y!=2; ++y)
  {
    for (int x=0; x!=2; ++x)
    {
      if (lhs.m_pegs[x][y] != rhs.m_pegs[x][y]) return false;
    }
  }
  return true;
}

ribi::RubiksClock::Pegs ribi::CreatePegsFromIndex(const int index) noexcept
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

  ribi::RubiksClock::Pegs pegs;
  pegs.m_pegs[0][0].reset(new ToggleButtonWidget(((index & 1) == 1),255,255,0));
  pegs.m_pegs[1][0].reset(new ToggleButtonWidget(((index & 2) == 2),255,255,0));
  pegs.m_pegs[0][1].reset(new ToggleButtonWidget(((index & 4) == 4),255,255,0));
  pegs.m_pegs[1][1].reset(new ToggleButtonWidget(((index & 8) == 8),255,255,0));
  return pegs;


}

ribi::RubiksClock::RubiksClock() noexcept
  : m_signal_clock_changed{},
    mFront{Times{true}},
    mBack{Times{false}},
    mPegs{}
{
  Check();
}

void ribi::RubiksClock::SetGeometry(const Rect& r) noexcept
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
      mPegs.m_pegs[x][y]->SetGeometry(
        Rect(
          left + ((0.9+x_d)*w3),
          top + ((0.9+y_d)*h3),
          w3*0.2,
          h3*0.2));
    }
  }

}

void ribi::RubiksClock::TogglePeg(const Side side) noexcept
{
  const int x = (side == Side::topLeft || side == Side::bottomLeft ? 0 : 1);
  const int y = (side == Side::topLeft || side == Side::topRight ? 0 : 1);
  mPegs.m_pegs[x][y]->GetToggleButton()->Toggle();
  m_signal_clock_changed();
}

void ribi::RubiksClock::TurnWheel(const Side side, const int nSteps) noexcept
{
  switch (side)
  {
    case Side::topLeft: TurnWheelTopLeft(nSteps); break;
    case Side::topRight: TurnWheelTopRight(nSteps); break;
    case Side::bottomLeft: TurnWheelBottomLeft(nSteps); break;
    case Side::bottomRight: TurnWheelBottomRight(nSteps); break;
  }
  if (nSteps % 12 != 0)
  {
    m_signal_clock_changed();
  }
}

void ribi::RubiksClock::TurnWheelTopLeft(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][0] = true;
  turnFront[1][0] = !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][0] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());

  turnBack[0][0] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][0] = true;

  turnBack[0][1] = (
    mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (    mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
       ||   mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][1] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
       || mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[2][2] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }

}

void ribi::RubiksClock::TurnWheelTopRight(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][0] = true;
  turnFront[1][0] = !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][0] = (mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed());

  turnBack[2][0] = (mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][0] = true;

  turnBack[2][1] = (
    mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (    mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
       ||   mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][1] = mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed();

  turnBack[2][2] = (mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
       || mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[0][2] = (mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void ribi::RubiksClock::TurnWheelBottomLeft(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][2] = true;
  turnFront[1][2] = !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][2] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[0][0] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][2] = true;

  turnBack[0][1] = (
    mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (    mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
       ||   mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][1] = mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed();

  turnBack[0][0] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()
       || mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[2][0] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void ribi::RubiksClock::TurnWheelBottomRight(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][2] = true;
  turnFront[1][2] = !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][2] = (mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
       || !mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed()  ) );
  turnFront[0][0] = (mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[2][2] = (mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][2] = true;

  turnBack[2][1] = (
    mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (    mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed()
       ||   mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][1] = mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed();

  turnBack[2][0] = (mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed()
       || mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[0][0] = (mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed() == mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { mFront.times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { mBack.times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

const ribi::RubiksClock::Times& ribi::RubiksClock::GetFrontTimes() const noexcept
{
  return mFront;
}

ribi::RubiksClock::Times& ribi::RubiksClock::GetFrontTimes() noexcept
{
  return mFront;
}

const ribi::RubiksClock::Times& ribi::RubiksClock::GetBackTimes() const noexcept
{
  return mBack;
}

ribi::RubiksClock::Times& ribi::RubiksClock::GetBackTimes() noexcept
{
  return mBack;
}

const ribi::RubiksClock::Pegs& ribi::RubiksClock::GetFrontPegs() const noexcept
{
  return mPegs;
}

ribi::RubiksClock::Pegs& ribi::RubiksClock::GetFrontPegs() noexcept
{
  return mPegs;
}

const ribi::RubiksClock::Pegs ribi::RubiksClock::GetBackPegs() const noexcept
{
  Pegs back;
  back.m_pegs[0][0].reset(new ToggleButtonWidget(!mPegs.m_pegs[1][0]->GetToggleButton()->IsPressed(),255,255,0));
  back.m_pegs[1][0].reset(new ToggleButtonWidget(!mPegs.m_pegs[0][0]->GetToggleButton()->IsPressed(),255,255,0));
  back.m_pegs[0][1].reset(new ToggleButtonWidget(!mPegs.m_pegs[1][1]->GetToggleButton()->IsPressed(),255,255,0));
  back.m_pegs[1][1].reset(new ToggleButtonWidget(!mPegs.m_pegs[0][1]->GetToggleButton()->IsPressed(),255,255,0));

  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      back.m_pegs[x][y]->SetGeometry(mPegs.m_pegs[1-x][y]->GetGeometry());
    }
  }

  return back;
}

void ribi::RubiksClock::Check() noexcept
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

const std::string ribi::RubiksClock::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::RubiksClock::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2011-09-08: Version 1.0: initial version");
  return v;
}

std::ostream& ribi::operator<<(std::ostream& os, const RubiksClock& r) noexcept
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

std::ostream& ribi::operator<<(std::ostream& os, const ribi::RubiksClock::Times& t) noexcept
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

std::ostream& ribi::operator<<(std::ostream& os, const ribi::RubiksClock::Pegs& p) noexcept
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
        << p.m_pegs[x][y].get()
        << "</rubiks_clock_dial>";
    }
  }
  os
    << "</rubiks_clock_pegs>";
  return os;
}


