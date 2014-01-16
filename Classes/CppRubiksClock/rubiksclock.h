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
  RubiksClock() noexcept;

  struct Pegs
  {
    Pegs() noexcept;
    boost::shared_ptr<ToggleButtonWidget> pegs[2][2]; //Is peg pressed?
    static Pegs CreatePegsFromIndex(const int index) noexcept;
  };

  enum class Side
  {
    topLeft, topRight, bottomLeft, bottomRight
  };

  struct Times
  {
    Times(const bool is_front) noexcept;
    boost::shared_ptr<RubiksClockDialWidget> times[3][3];
  };

  ///Set the geometry of all Widgets
  void SetGeometry(const Rect& r) noexcept;

  ///Change a peg, as seen from the front
  void TogglePeg(const Side side) noexcept;

  ///Change a wheel, as seen from the front
  void TurnWheel(const Side side, const int nSteps) noexcept;

  void Check() noexcept;

  ///Get the time dials of the back side
  const Times& GetBackTimes() const noexcept;

  ///Get the time dials of the back side
  Times& GetBackTimes() noexcept;

  ///Get the pegs of the back side
  const Pegs GetBackPegs() const noexcept;

  ///Get the time dials of the front side
  const Times& GetFrontTimes() const noexcept;

  ///Get the time dials of the front side
  Times& GetFrontTimes() noexcept;

  ///Get the pegs of the front side
  const Pegs& GetFrontPegs() const noexcept;

  ///Get the pegs of the front side
  Pegs& GetFrontPegs() noexcept;

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
  void TurnWheelTopLeft(const int nSteps) noexcept;

  ///Change the top-right wheel, as seen from the front
  void TurnWheelTopRight(const int nSteps) noexcept;

  ///Change the bottom-left wheel, as seen from the front
  void TurnWheelBottomLeft(const int nSteps) noexcept;

  ///Change the bottom-right wheel, as seen from the front
  void TurnWheelBottomRight(const int nSteps) noexcept;

  friend std::ostream& operator<<(std::ostream& os, const RubiksClock& r) noexcept;

};

RubiksClock::Pegs CreatePegsFromIndex(const int index) noexcept;

std::ostream& operator<<(std::ostream& os, const RubiksClock& r) noexcept;
std::ostream& operator<<(std::ostream& os, const RubiksClock::Times& t) noexcept;
std::ostream& operator<<(std::ostream& os, const RubiksClock::Pegs& p) noexcept;

bool operator==(const RubiksClock::Times& lhs, const RubiksClock::Times& rhs) noexcept;
bool operator==(const RubiksClock::Pegs& lhs, const RubiksClock::Pegs& rhs) noexcept;

} //~namespace ribi

#endif // RUBIKSCLOCK_H
