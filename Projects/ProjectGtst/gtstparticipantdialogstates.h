
/*
GTST, Game Theory Server
Copyright (C) 2011-2015 Richel Bilderbeek

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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PARTICIPANTDIALOGSTATES_H
#define PARTICIPANTDIALOGSTATES_H

#include <boost/checked_delete.hpp>
#include <boost/scoped_ptr.hpp>


namespace ribi {
namespace gtst {

///ParticipantDialogStates manages all ParticipantDialogState instances
struct ParticipantDialogStates
{
  ParticipantDialogStates(
    ParticipantDialog* const dialog,
    Server * const server);
  ParticipantDialogStates(const ParticipantDialogStates&) = delete;
  ParticipantDialogStates& operator=(const ParticipantDialogStates&) = delete;

  ///Get the ParticipantDialog its current ParticipantDialogState
  ParticipantDialogState * GetCurrentState() const;
  ///Get the ParticipantDialog its ParticipantDialogStateAssignPayoff
  ParticipantDialogStateAssignPayoff * GetStateAssignPayoff() const;
  ///Get the ParticipantDialog its ParticipantDialogStateChat
  ParticipantDialogStateChat * GetStateChat() const;
  ///Get the ParticipantDialog its ParticipantDialogStateChooseAction
  ParticipantDialogStateChooseAction * GetStateChooseAction() const;
  ///Get the ParticipantDialog its ParticipantDialogStateFinished
  ParticipantDialogStateFinished * GetStateFinished() const;
  ///Get the ParticipantDialog its ParticipantDialogStateGroupAssign
  ParticipantDialogStateGroupAssign * GetStateGroupAssign() const;
  ///Get the ParticipantDialog its ParticipantDialogStateGroupReAssign
  ParticipantDialogStateGroupReAssign * GetStateGroupReAssign() const;
  ///Get the ParticipantDialog its ParticipantDialogStateLoggedIn
  ParticipantDialogStateLoggedIn * GetStateLoggedIn() const;
  ///Get the ParticipantDialog its ParticipantDialogStateViewResultsAll
  ParticipantDialogStateNotLoggedIn * GetStateNotLoggedIn() const;
  ///Get the ParticipantDialog its ParticipantDialogStateQuiz
  ParticipantDialogStateQuiz * GetStateQuiz() const;
  ///Get the ParticipantDialog its ParticipantDialogStateViewResultsAll
  //ParticipantDialogStateViewResultsAll * GetStateViewResultsAll() const;
  ///Get the ParticipantDialog its ParticipantDialogStateViewResultsGroup
  ParticipantDialogStateViewResultsGroup * GetStateViewResultsGroup() const;
  ///Get the ParticipantDialog its ParticipantDialogStateViewResultsVoting
  ParticipantDialogStateViewResultsVoting * GetStateViewResultsVoting() const;
  ///Get the ParticipantDialog its ParticipantDialogStateVoting
  ParticipantDialogStateVoting * GetStateVoting() const;

  ///Set the ParticipantDialogState of this ParticipantDialog
  void SetState(ParticipantDialogState * const state);

  private:
  ~ParticipantDialogStates() {}
  friend void boost::checked_delete<>(ParticipantDialogStates*);

  ///The ParticipantDialog its current ParticipantDialogState
  ParticipantDialogState * m_state;
  ///The ParticipantDialog its ParticipantDialogStateAssignPayoff
  boost::scoped_ptr<ParticipantDialogStateAssignPayoff> m_state_assign_payoff;
  ///The ParticipantDialog its ParticipantDialogStateChat
  boost::scoped_ptr<ParticipantDialogStateChat> m_state_chat;
  ///The ParticipantDialog its ParticipantDialogStateChooseAction
  boost::scoped_ptr<ParticipantDialogStateChooseAction> m_state_choose_action;
  ///The ParticipantDialog its ParticipantDialogStateFinished
  boost::scoped_ptr<ParticipantDialogStateFinished> m_state_finished;
  ///The ParticipantDialog its ParticipantDialogStateGroupAssign
  boost::scoped_ptr<ParticipantDialogStateGroupAssign> m_state_group_assign;
  ///The ParticipantDialog its ParticipantDialogStateGroupAssign
  boost::scoped_ptr<ParticipantDialogStateGroupReAssign> m_state_group_reassign;
  ///The ParticipantDialog its ParticipantDialogStateLoggedIn
  boost::scoped_ptr<ParticipantDialogStateLoggedIn> m_state_logged_in;
  ///The ParticipantDialog its ParticipantDialogStateNotLoggedIn
  boost::scoped_ptr<ParticipantDialogStateNotLoggedIn> m_state_not_logged_in;
  ///The ParticipantDialog its ParticipantDialogStateQuiz
  boost::scoped_ptr<ParticipantDialogStateQuiz> m_state_quiz;
  ///The ParticipantDialog its ParticipantDialogStateViewResultsAll
  //boost::scoped_ptr<ParticipantDialogStateViewResultsAll> m_state_view_results_all;
  ///The ParticipantDialog its ParticipantDialogStateViewResultsGroup
  boost::scoped_ptr<ParticipantDialogStateViewResultsGroup> m_state_view_results_group;
  ///The ParticipantDialog its ParticipantDialogStateViewResultsVoting
  boost::scoped_ptr<ParticipantDialogStateViewResultsVoting> m_state_view_results_voting;
  ///The ParticipantDialog its ParticipantDialogStateVoting
  boost::scoped_ptr<ParticipantDialogStateVoting> m_state_voting;
};

} //~namespace gtst
} //~namespace ribi

#endif // PARTICIPANTDIALOGSTATES_H
