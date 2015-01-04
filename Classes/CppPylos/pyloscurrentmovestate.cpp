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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "pyloscurrentmovestate.h"

#include <cassert>

#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::pylos::CurrentMoveState::CurrentMoveState() noexcept
  : m_current_move{},
    m_must_remove(MustRemoveState::no)
{
  #ifndef NDEBUG
  Test();
  #endif

  assert(IsMoveUnknown());
  //assert(IsRemoveUnknown());
}

std::string ribi::pylos::CurrentMoveState::GetVersion() noexcept
{
  return "2.0";
}

std::vector<std::string> ribi::pylos::CurrentMoveState::GetVersionHistory() noexcept
{
  return {
    "2012-05-05: version 2.0: initial release version"
  };
}

bool ribi::pylos::CurrentMoveState::IsMoveMove() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 2;
}

bool ribi::pylos::CurrentMoveState::IsMovePlace() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 1;
}

bool ribi::pylos::CurrentMoveState::IsMoveUnknown() const
{
  assert(m_current_move.m_move.size() < 3);
  return m_current_move.m_move.size() == 0;
}

ribi::pylos::MustRemoveState ribi::pylos::CurrentMoveState::GetMustRemove() const noexcept
{
  return m_must_remove;
}

void ribi::pylos::CurrentMoveState::Restart() noexcept
{
  m_must_remove = MustRemoveState::no;
  m_current_move = Move();
  assert(IsMoveUnknown());
}

void ribi::pylos::CurrentMoveState::SetMove(const Move& move)
{
  assert(m_current_move.m_move.empty());
  assert(m_current_move.m_remove.empty());
  m_current_move = move;
  m_must_remove = MustRemoveState::no;
}

void ribi::pylos::CurrentMoveState::SetMoveTransfer(const Coordinat& from, const Coordinat& to)
{
  assert(IsMoveUnknown());
  assert(m_current_move.m_move.empty());
  m_current_move.m_move.push_back(from);
  m_current_move.m_move.push_back(to);
}

void ribi::pylos::CurrentMoveState::SetMoveSet(const Coordinat& c)
{
  assert(IsMoveUnknown());
  assert(m_current_move.m_move.empty());
  m_current_move.m_move.push_back(c);
}

void ribi::pylos::CurrentMoveState::SetMustRemove(const MustRemoveState must_remove)
{
  assert(!(must_remove == MustRemoveState::player2
    &&   m_must_remove == MustRemoveState::player1)
    && "Cannot set duty to remove from player 1 to player 2");
  assert(!(must_remove == MustRemoveState::player1
    &&   m_must_remove == MustRemoveState::player2)
    && "Cannot set duty to remove from player 2 to player 1");
  m_must_remove = must_remove;
}

void ribi::pylos::CurrentMoveState::SetRemove(const std::vector<Coordinat>& v)
{
  assert(m_must_remove != MustRemoveState::no);
  m_current_move.m_remove = v;
}

#ifndef NDEBUG
void ribi::pylos::CurrentMoveState::Test() noexcept
{
  {
    static bool tested = false;
    if (tested) return;
    tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};

  if (verbose) { TRACE("Test PylosCurrentMoveState"); }
  {
    const Coordinat c(0,1,1);
    pylos::CurrentMoveState s;
    assert(s.IsMoveUnknown());
    assert(!s.GetMustRemove());
    s.SetMoveSet(c);
    assert(!s.IsMoveUnknown());
    const pylos::Move m = s.GetMove();
    assert(m.m_move.size() == 1);
    assert(m.m_move[0] == c);
    assert(m.m_remove.empty());
    s.Restart();
    pylos::CurrentMoveState t;
    assert(s == t);
  }
}
#endif

bool ribi::pylos::operator==(const CurrentMoveState& lhs, const CurrentMoveState& rhs) noexcept
{
  return lhs.GetMustRemove() == rhs.GetMustRemove()
    && lhs.GetMove() == rhs.GetMove();
}
