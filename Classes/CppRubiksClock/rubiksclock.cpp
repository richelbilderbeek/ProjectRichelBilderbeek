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
#include <sstream>

#include <boost/numeric/conversion/cast.hpp>

#include "dial.h"
#include "dialwidget.h"
#include "geometry.h"
#include "rubiksclockdial.h"
#include "rubiksclockdialwidget.h"
#include "rubiksclockpegs.h"
#include "rubiksclocktimes.h"
#include "togglebutton.h"
#include "togglebuttonwidget.h"
//#include "trace.h"

#pragma GCC diagnostic pop

ribi::ruco::Clock::Clock() noexcept
  : m_signal_clock_changed{},
    m_back{new Times{false}},
    m_front{new Times{true}},
    m_pegs{new Pegs}
{
  Check();
}

void ribi::ruco::Clock::SetGeometry(const Rect& r) noexcept
{
  const int left   = Geometry().GetLeft(r);
  const int top    = Geometry().GetTop(r);
  const int width  = Geometry().GetWidth(r);
  const int height = Geometry().GetHeight(r);

  const double w3 = boost::numeric_cast<double>(width) / 3.0;
  const double h3 = boost::numeric_cast<double>(height) / 3.0;
  for (int x=0; x!=3; ++x)
  {
    const double x_d = boost::numeric_cast<double>(x);
    for (int y=0; y!=3; ++y)
    {
      const double y_d = boost::numeric_cast<double>(y);
      m_back->times[x][y]->SetGeometry(
        left + (x_d*w3),
        top + (y_d*h3),
        w3,
        h3
      );
      m_front->times[x][y]->SetGeometry(
        left + (x_d*w3),
        top + (y_d*h3),
        w3,
        h3
      );
    }
  }
  for (int x=0; x!=2; ++x)
  {
    const double x_d = boost::numeric_cast<double>(x);
    for (int y=0; y!=2; ++y)
    {
      const double y_d = boost::numeric_cast<double>(y);
      m_pegs->m_pegs[x][y]->SetGeometry(
        left + ((0.9+x_d)*w3),
        top + ((0.9+y_d)*h3),
        w3*0.2,
        h3*0.2
      );
    }
  }

}

void ribi::ruco::Clock::TogglePeg(const Side side) noexcept
{
  const int x = (side == Side::topLeft || side == Side::bottomLeft ? 0 : 1);
  const int y = (side == Side::topLeft || side == Side::topRight ? 0 : 1);
  m_pegs->m_pegs[x][y]->GetToggleButton()->Toggle();
  m_signal_clock_changed();
}

void ribi::ruco::Clock::TurnWheel(const Side side, const int nSteps) noexcept
{
  switch (side)
  {
    case Side::topLeft    : TurnWheelTopLeft(nSteps);     break;
    case Side::topRight   : TurnWheelTopRight(nSteps);    break;
    case Side::bottomLeft : TurnWheelBottomLeft(nSteps);  break;
    case Side::bottomRight: TurnWheelBottomRight(nSteps); break;
  }
  if (nSteps % 12 != 0)
  {
    m_signal_clock_changed();
  }
}

void ribi::ruco::Clock::TurnWheelTopLeft(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][0] = true;
  turnFront[1][0] = !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][0] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());

  turnBack[0][0] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][0] = true;

  turnBack[0][1] = (
    m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (    m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
       ||   m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[2][1] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
    && (  m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
       || m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() ) );
  turnBack[2][2] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { m_front->times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { m_back->times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }

}

void ribi::ruco::Clock::TurnWheelTopRight(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][0] = true;
  turnFront[1][0] = !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][0] = (m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[2][2] = (m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[1][2] = (
    !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnFront[0][2] = (m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed());

  turnBack[2][0] = (m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][0] = true;

  turnBack[2][1] = (
    m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (    m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
       ||   m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();
  turnBack[0][1] = m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed();

  turnBack[2][2] = (m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = (
    m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
    && (  m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
       || m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() ) );
  turnBack[0][2] = (m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { m_front->times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { m_back->times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void ribi::ruco::Clock::TurnWheelBottomLeft(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[0][2] = true;
  turnFront[1][2] = !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][2] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[0][1] = !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnFront[2][1] = (
    !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[0][0] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());

  turnBack[0][2] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][2] = true;

  turnBack[0][1] = (
    m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (    m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
       ||   m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();
  turnBack[2][1] = m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed();

  turnBack[0][0] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
    && (  m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()
       || m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed() ) );
  turnBack[2][0] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { m_front->times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { m_back->times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}

void ribi::ruco::Clock::TurnWheelBottomRight(const int nSteps) noexcept
{
  bool turnFront[3][3];
  bool turnBack[3][3];

  turnFront[2][2] = true;
  turnFront[1][2] = !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][2] = (m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed());
  turnFront[2][1] = !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[1][1] = !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnFront[0][1] = (
    !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnFront[2][0] = (m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());
  turnFront[1][0] = (
    !m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  !m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
       || !m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed()  ) );
  turnFront[0][0] = (m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());

  turnBack[2][2] = (m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed());
  turnBack[1][2] = m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][2] = true;

  turnBack[2][1] = (
    m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (    m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed()
       ||   m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[1][1] = m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();
  turnBack[0][1] = m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed();

  turnBack[2][0] = (m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed());
  turnBack[1][0] = (
    m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed()
    && (  m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed()
       || m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed() ) );
  turnBack[0][0] = (m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed() == m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed());

  for (int y=0; y!=3; ++y)
  {
    for (int x=0; x!=3; ++x)
    {
      if (turnFront[x][y]) { m_front->times[x][y]->GetRubiksClockDial()->Turn(nSteps); }
      if (turnBack[x][y]) { m_back->times[x][y]->GetRubiksClockDial()->Turn(-nSteps); }
    }
  }
}



const boost::shared_ptr<const ribi::ruco::Pegs> ribi::ruco::Clock::GetBackPegs() const noexcept
{
  const boost::shared_ptr<Pegs> back(new Pegs);
  back->m_pegs[0][0].reset(new ToggleButtonWidget(!m_pegs->m_pegs[1][0]->GetToggleButton()->IsPressed(),255,255,0));
  back->m_pegs[1][0].reset(new ToggleButtonWidget(!m_pegs->m_pegs[0][0]->GetToggleButton()->IsPressed(),255,255,0));
  back->m_pegs[0][1].reset(new ToggleButtonWidget(!m_pegs->m_pegs[1][1]->GetToggleButton()->IsPressed(),255,255,0));
  back->m_pegs[1][1].reset(new ToggleButtonWidget(!m_pegs->m_pegs[0][1]->GetToggleButton()->IsPressed(),255,255,0));

  for (int x=0; x!=2; ++x)
  {
    for (int y=0; y!=2; ++y)
    {
      back->m_pegs[x][y]->SetGeometry(m_pegs->m_pegs[1-x][y]->GetGeometry());
    }
  }

  return back;
}

void ribi::ruco::Clock::Check() noexcept
{
  #ifndef NDEBUG
  const auto originalFront = m_front;
  const auto originalBack = m_back;
  const auto originalPegs = m_pegs;

  //Check the corner clocks
  assert( (m_front->times[0][0]->GetRubiksClockDial()->GetTime()
    + m_back->times[2][0]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (m_front->times[2][0]->GetRubiksClockDial()->GetTime()
    + m_back->times[0][0]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (m_front->times[0][2]->GetRubiksClockDial()->GetTime()
    + m_back->times[2][2]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  assert( (m_front->times[2][2]->GetRubiksClockDial()->GetTime()
    + m_back->times[0][2]->GetRubiksClockDial()->GetTime()) % 12 == 0);
  //Check all peg combinations
  for (int i=0; i!=16; ++i)
  {
    m_pegs = CreatePegsFromIndex(i);
    //Check all wheels
    for (int j=0; j!=4; ++j)
    {
      //Check if after turning around in two steps, everything stays the same
      const auto front = m_front;
      const auto back = m_back;

      const Side side = static_cast<Side>(j);
      const int nSteps = std::rand() % 12;
      //Turn 1
      this->TurnWheel(side,nSteps);
      //Turn 11
      this->TurnWheel(side,12-nSteps);
      assert( m_front == front);
      assert( m_back == back);
    }
  }

  #endif
}

const boost::shared_ptr<ribi::ruco::Pegs> ribi::ruco::Clock::CreatePegsFromIndex(const int index) noexcept
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

  const boost::shared_ptr<Pegs> pegs {
    new Pegs
  };
  if ((index & 1) == 1) { pegs->m_pegs[0][0]->GetToggleButton()->Toggle(); }
  if ((index & 2) == 2) { pegs->m_pegs[0][1]->GetToggleButton()->Toggle(); }
  if ((index & 4) == 4) { pegs->m_pegs[1][0]->GetToggleButton()->Toggle(); }
  if ((index & 8) == 8) { pegs->m_pegs[1][1]->GetToggleButton()->Toggle(); }
  return pegs;
}

std::string ribi::ruco::Clock::GetVersion() noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::ruco::Clock::GetVersionHistory() noexcept
{
  return {
    "2011-09-08: Version 1.0: initial version",
    "2014-01-23: Version 2.0: put into namespace ruco, forward declarations, use of smart pointers, use of multiple files",
    "2014-03-28: version 2.1: replaced Rect by Boost.Geometry its box class"
  };
}

std::string ribi::ruco::Clock::ToXml() const noexcept
{
  std::stringstream s;
  s
    << "<rubiks_clock>"
    << "<front>"
    << (*m_front)
    << "</front>"
    << "<back>"
    << (*m_back)
    << "</back>"
    << "<pegs>"
    << (*m_pegs)
    << "</pegs>"
    << "</rubiks_clock>";
  return s.str()
  ;
}

std::ostream& ribi::ruco::operator<<(std::ostream& os, const ribi::ruco::Clock& r) noexcept
{
  os
    << "<rubiks_clock>"
    << "<front>"
    << r.m_front
    << "</front>"
    << "<back>"
    << r.m_back
    << "</back>"
    << "<pegs>"
    << r.m_pegs
    << "</pegs>"
    << "</rubiks_clock>";
  return os;
}




