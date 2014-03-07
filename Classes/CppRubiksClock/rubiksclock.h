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
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include "rubiksclockfwd.h"
#include "rubiksclockside.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace ruco {

///Clock is a Rubik's Clock
struct Clock
{
  Clock() noexcept;

  ///Set the geometry of all Widgets
  void SetGeometry(const Rect& r) noexcept;

  ///Change a peg, as seen from the front
  void TogglePeg(const Side side) noexcept;

  ///Change a wheel, as seen from the front
  void TurnWheel(const Side side, const int nSteps) noexcept;

  void Check() noexcept;

  ///Get the time dials of the back side
  const boost::shared_ptr<const Times> GetBackTimes() const noexcept { return m_back; }
  //const boost::shared_ptr<      Times> GetBackTimes()       noexcept { return m_back; }

  ///Get the time dials of the back side
  //Times& GetBackTimes() noexcept;

  ///Get the pegs of the back side
  const boost::shared_ptr<const Pegs> GetBackPegs() const noexcept;
  //const boost::shared_ptr<      Pegs> GetBackPegs()       noexcept;

  ///Get the time dials of the front side
  const boost::shared_ptr<const Times> GetFrontTimes() const noexcept { return m_front; }
  //const boost::shared_ptr<      Times> GetFrontTimes()       noexcept { return m_front; }

  ///Get the time dials of the front side
  //Times& GetFrontTimes() noexcept;

  ///Get the pegs of the front side
  const boost::shared_ptr<const Pegs> GetFrontPegs() const noexcept { return m_pegs; }

  ///Get the pegs of the front side
  //Pegs& GetFrontPegs() noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Convert to a Canvas
  const boost::shared_ptr<TextCanvas> ToCanvas(const int radius) const noexcept;

  ///Convert to XML
  std::string ToXml() const noexcept;

  ///Respond to a change in the clock
  mutable boost::signals2::signal<void ()> m_signal_clock_changed;

  private:
  ~Clock() noexcept {}
  friend void boost::checked_delete<>(Clock*);
  friend void boost::checked_delete<>(const Clock*);

  boost::shared_ptr<Times> m_back;
  boost::shared_ptr<Times> m_front;
  boost::shared_ptr<Pegs > m_pegs;

  static const boost::shared_ptr<Pegs> CreatePegsFromIndex(const int index) noexcept;

  ///Change the top-left wheel, as seen from the front
  void TurnWheelTopLeft(const int nSteps) noexcept;

  ///Change the top-right wheel, as seen from the front
  void TurnWheelTopRight(const int nSteps) noexcept;

  ///Change the bottom-left wheel, as seen from the front
  void TurnWheelBottomLeft(const int nSteps) noexcept;

  ///Change the bottom-right wheel, as seen from the front
  void TurnWheelBottomRight(const int nSteps) noexcept;

  friend std::ostream& operator<<(std::ostream& os, const Clock& r) noexcept;

};

std::ostream& operator<<(std::ostream& os, const Clock& r) noexcept;

} //~namespace ruco
} //~namespace ribi

#endif // RUBIKSCLOCK_H
