//---------------------------------------------------------------------------
/*
GTST, Game Theory Server
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
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#include <cassert>
//---------------------------------------------------------------------------
#include <boost/scoped_ptr.hpp>
//---------------------------------------------------------------------------
#include "state.h"
#include "test.h"
//---------------------------------------------------------------------------
///TestStates test State
void Test::TestState()
{

  {
    boost::scoped_ptr<State> s(new StateAssignPayoff);
    assert(s->ToStr() == "assign_payoff");
  }
  {
    boost::scoped_ptr<State> s(new StateChat);
    assert(s->ToStr() == "chat");
  }
  {
    boost::scoped_ptr<State> s(new StateChooseAction);
    assert(s->ToStr() == "choose_action");
  }
  {
    boost::scoped_ptr<State> s(new StateFinished);
    assert(s->ToStr() == "finished");
  }
  {
    boost::scoped_ptr<State> s(new StateGroupAssign);
    assert(s->ToStr() == "group_assign");
  }
  {
    boost::scoped_ptr<State> s(new StateGroupReAssign);
    assert(s->ToStr() == "group_reassign");
  }
  {
    boost::scoped_ptr<State> s(new StateLoggedIn);
    assert(s->ToStr() == "logged_in");
  }
  {
    boost::scoped_ptr<State> s(new StateNotLoggedIn);
    assert(s->ToStr() == "not_logged_in");
  }
  //{
  //  boost::scoped_ptr<State> s(new StateViewResultsAll);
  //  assert(s->ToStr() == "view_results_all");
  //}
  {
    boost::scoped_ptr<State> s(new StateViewResultsGroup);
    assert(s->ToStr() == "view_results_group");
  }
  {
    boost::scoped_ptr<State> s(new StateViewResultsVoting);
    assert(s->ToStr() == "view_results_voting");
  }
  {
    boost::scoped_ptr<State> s(new StateVoting);
    assert(s->ToStr() == "voting");
  }
  {
    boost::scoped_ptr<State> s(new StateWaiting);
    assert(s->ToStr() == "waiting");
  }
}
//---------------------------------------------------------------------------


