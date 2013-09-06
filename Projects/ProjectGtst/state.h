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
#ifndef PROJECTGTSTSTATE_H
#define PROJECTGTSTSTATE_H
//---------------------------------------------------------------------------
//#include <iosfwd>
#include <string>
//---------------------------------------------------------------------------
#include <boost/checked_delete.hpp>
//---------------------------------------------------------------------------
namespace ribi {
namespace gtst {

///\brief
///State is a state and serves as a base class for all states.
///
///State is used by ParticipantState, ParticipantDialogState,
///ServerState and Parameters.
struct State
{
  ///Represent the State as a std::string
  virtual const std::string ToStr() const = 0;

  protected:
  ///\brief Only allow a Boost smart pointer to delete State
  ///
  ///This prevents the following trouble,
  ///cited from http://www.boost.org/libs/utility/checked_delete.html:
  ///The C++ Standard allows, in 5.3.5/5, pointers to incomplete
  ///class types to be deleted with a delete-expression.
  ///When the class has a non-trivial destructor, or a class-specific operator
  ///delete, the behavior is undefined. Some compilers issue a warning when an
  ///incomplete type is deleted, but unfortunately, not all do, and programmers
  ///sometimes ignore or disable warnings.
  virtual ~State() {}
  ///Only allow a Boost smart pointer to delete State
  //Template syntax from Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(State*);
};
//---------------------------------------------------------------------------
///Assigning-payoff State
struct StateAssignPayoff : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "assign_payoff"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateAssignPayoff() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateAssignPayoff*);
};
//---------------------------------------------------------------------------
///Chat State
struct StateChat : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "chat"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateChat() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateChat*);
};
//---------------------------------------------------------------------------
///Choose-action State
struct StateChooseAction : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "choose_action"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateChooseAction() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateChooseAction*);
};
//---------------------------------------------------------------------------
///Experiment/Participant-is-finished State
struct StateFinished : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "finished"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateFinished() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateFinished*);
};
//---------------------------------------------------------------------------
///Group assignment State
struct StateGroupAssign : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "group_assign"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateGroupAssign() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateGroupAssign*);
};
//---------------------------------------------------------------------------
///Group re-assignment State
struct StateGroupReAssign : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "group_reassign"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateGroupReAssign() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateGroupReAssign*);
};
//---------------------------------------------------------------------------
///Participant-is-logged-in State
struct StateLoggedIn : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "logged_in"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateLoggedIn() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateLoggedIn*);
};
//---------------------------------------------------------------------------
///Participant-is-not-logged-in State
///Server does not have this State.
struct StateNotLoggedIn : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "not_logged_in"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateNotLoggedIn() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateNotLoggedIn*);
};
//---------------------------------------------------------------------------
///Participant is doing a quiz
struct StateQuiz : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "quiz"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateQuiz() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateQuiz*);
};
//---------------------------------------------------------------------------
///View-the-results-within-own-group State
struct StateViewResultsGroup : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "view_results_group"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateViewResultsGroup() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateViewResultsGroup*);
};
//---------------------------------------------------------------------------
///View-the-results-of-voting State
struct StateViewResultsVoting : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "view_results_voting"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateViewResultsVoting() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateViewResultsVoting*);
};
//---------------------------------------------------------------------------
///Voting State
struct StateVoting : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "voting"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateVoting() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateVoting*);
};
//---------------------------------------------------------------------------
///Server-is-waiting-for-Parameters State
struct StateWaiting : public State
{
  ///Represent this State as a std::string
  const std::string ToStr() const { return "waiting"; }
  protected:
  ///Only allow a Boost smart pointer to delete this State
  virtual ~StateWaiting() {}
  ///Only allow a Boost smart pointer to delete this State
  friend void boost::checked_delete<>(StateWaiting*);
};

} //~namespace gtst
} //~namespace ribi

#endif // STATE_H
