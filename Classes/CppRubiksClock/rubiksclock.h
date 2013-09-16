//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRubiksClock.htm
//---------------------------------------------------------------------------
#ifndef RUBIKSCLOCK_H
#define RUBIKSCLOCK_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct Rect;
struct RubiksClockDialWidget;
struct ToggleButtonWidget;

///RubiksClock is a Rubik's Clock
struct RubiksClock
{
  RubiksClock();

  struct Pegs
  {
    Pegs();
    boost::shared_ptr<ToggleButtonWidget> pegs[2][2]; //Is peg pressed?
    static Pegs CreatePegsFromIndex(const int index);
  };

  enum Side
  {
    topLeft, topRight, bottomLeft, bottomRight
  };

  struct Times
  {
    Times(const bool is_front);
    boost::shared_ptr<RubiksClockDialWidget> times[3][3];
  };

  ///Set the geometry of all Widgets
  void SetGeometry(const Rect& r);

  ///Change a peg, as seen from the front
  void TogglePeg(const Side side);

  ///Change a wheel, as seen from the front
  void TurnWheel(const Side side, const int nSteps);

  void Check();

  ///Get the time dials of the back side
  const Times& GetBackTimes() const;

  ///Get the time dials of the back side
  Times& GetBackTimes();

  ///Get the pegs of the back side
  const Pegs GetBackPegs() const;

  ///Get the time dials of the front side
  const Times& GetFrontTimes() const;

  ///Get the time dials of the front side
  Times& GetFrontTimes();

  ///Get the pegs of the front side
  const Pegs& GetFrontPegs() const;

  ///Get the pegs of the front side
  Pegs& GetFrontPegs();

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Respond to a change in the clock
  mutable boost::signals2::signal<void ()> m_signal_clock_changed;

  private:
  Times mFront;
  Times mBack;
  Pegs mPegs;

  ///Change the top-left wheel, as seen from the front
  void TurnWheelTopLeft(const int nSteps);

  ///Change the top-right wheel, as seen from the front
  void TurnWheelTopRight(const int nSteps);

  ///Change the bottom-left wheel, as seen from the front
  void TurnWheelBottomLeft(const int nSteps);

  ///Change the bottom-right wheel, as seen from the front
  void TurnWheelBottomRight(const int nSteps);

  friend std::ostream& operator<<(std::ostream& os, const RubiksClock& r);

};

RubiksClock::Pegs CreatePegsFromIndex(const int index);

std::ostream& operator<<(std::ostream& os, const RubiksClock& r);
std::ostream& operator<<(std::ostream& os, const RubiksClock::Times& t);
std::ostream& operator<<(std::ostream& os, const RubiksClock::Pegs& p);

bool operator==(const RubiksClock::Times& lhs, const RubiksClock::Times& rhs);
bool operator==(const RubiksClock::Pegs& lhs, const RubiksClock::Pegs& rhs);

} //~namespace ribi

#endif // RUBIKSCLOCK_H
