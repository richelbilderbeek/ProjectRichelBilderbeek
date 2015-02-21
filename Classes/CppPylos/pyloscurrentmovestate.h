//---------------------------------------------------------------------------
/*
pylos::CurrentMoveState, Pylos/Phyraos current move state class
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPylos.htm
//---------------------------------------------------------------------------
#ifndef PYLOSCURRENTMOVESTATE_H
#define PYLOSCURRENTMOVESTATE_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/checked_delete.hpp>

#include "pyloscoordinat.h"
#include "pylosmove.h"
#include "pylosmustremovestate.h"
#pragma GCC diagnostic pop

namespace ribi {

namespace pylos {

///CurrentMoveState contains the state of the current Move.
///CurrentMoveState is used by pylos::Game, to incrementally keep track of the
///ongoing move
struct CurrentMoveState
{
  CurrentMoveState() noexcept;

  ///Obtain the current Move in process
  const Move& GetMove() const noexcept { return m_current_move; }

  ///Obtain if the first part of the move has taken place and
  ///if the current player must remove one or two marbles
  MustRemoveState GetMustRemove() const noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;


  ///Is it unknown what kind of Move this is?
  bool IsMoveUnknown() const;
  bool IsMoveMove() const;
  bool IsMovePlace() const;

  void Restart() noexcept;

  ///Set a complete Move directly
  void SetMove(const Move& move);

  ///Set the transfer part of a move,enabling
  void SetMoveTransfer(const Coordinat& from, const Coordinat& to);

  void SetMoveSet(const Coordinat& c);

  ///Set the duty of one or none of the players
  void SetMustRemove(const MustRemoveState must_remove);
  void SetRemove(const std::vector<Coordinat>& v);


  private:
  ~CurrentMoveState() noexcept {}
  friend void boost::checked_delete<>(      CurrentMoveState*);
  friend void boost::checked_delete<>(const CurrentMoveState*);

  Move m_current_move;
  MustRemoveState m_must_remove;

  #ifndef NDEBUG
  ///Test this class
  static void Test() noexcept;
  #endif
};

bool operator==(const CurrentMoveState& lhs, const CurrentMoveState& rhs) noexcept;

} //~namespace Pylos

} //~namespace ribi

#endif // PYLOSCURRENTMOVESTATE_H
