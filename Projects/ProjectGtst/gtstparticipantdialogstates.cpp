//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectGtst.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "gtstall_participantdialogstates.h"
#include "gtstparticipantdialogstates.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStates::ParticipantDialogStates(
  ParticipantDialog* const dialog,Server * const server)
  : m_state(0),
    m_state_assign_payoff(new ParticipantDialogStateAssignPayoff(dialog,server)),
    m_state_chat(new ParticipantDialogStateChat(dialog,server)),
    m_state_choose_action(new ParticipantDialogStateChooseAction(dialog,server)),
    m_state_finished(new ParticipantDialogStateFinished(dialog,server)),
    m_state_group_assign(new ParticipantDialogStateGroupAssign(dialog,server)),
    m_state_group_reassign(new ParticipantDialogStateGroupReAssign(dialog,server)),
    m_state_logged_in(new ParticipantDialogStateLoggedIn(dialog,server)),
    m_state_not_logged_in(new ParticipantDialogStateNotLoggedIn(dialog,server)),
    m_state_quiz(new ParticipantDialogStateQuiz(dialog,server)),
    m_state_view_results_group(new ParticipantDialogStateViewResultsGroup(dialog,server)),
    m_state_view_results_voting(new ParticipantDialogStateViewResultsVoting(dialog,server)),
    m_state_voting(new ParticipantDialogStateVoting(dialog,server))
{
  m_state = m_state_not_logged_in.get();
}

ribi::gtst::ParticipantDialogState * ribi::gtst::ParticipantDialogStates::GetCurrentState() const
{
  assert(m_state);
  return m_state;
}

ribi::gtst::ParticipantDialogStateChat * ribi::gtst::ParticipantDialogStates::GetStateChat() const
{
  assert(m_state_chat);
  return m_state_chat.get();
}

ribi::gtst::ParticipantDialogStateAssignPayoff * ribi::gtst::ParticipantDialogStates::GetStateAssignPayoff() const
{
  assert(m_state_assign_payoff);
  return m_state_assign_payoff.get();
}

ribi::gtst::ParticipantDialogStateChooseAction * ribi::gtst::ParticipantDialogStates::GetStateChooseAction() const
{
  assert(m_state_choose_action);
  return m_state_choose_action.get();
}

ribi::gtst::ParticipantDialogStateFinished * ribi::gtst::ParticipantDialogStates::GetStateFinished() const
{
  assert(m_state_finished);
  return m_state_finished.get();
}

ribi::gtst::ParticipantDialogStateGroupAssign * ribi::gtst::ParticipantDialogStates::GetStateGroupAssign() const
{
  assert(m_state_group_assign);
  return m_state_group_assign.get();
}

ribi::gtst::ParticipantDialogStateGroupReAssign * ribi::gtst::ParticipantDialogStates::GetStateGroupReAssign() const
{
  assert(m_state_group_reassign);
  return m_state_group_reassign.get();
}

ribi::gtst::ParticipantDialogStateLoggedIn * ribi::gtst::ParticipantDialogStates::GetStateLoggedIn() const
{
  assert(m_state_logged_in);
  return m_state_logged_in.get();
}

ribi::gtst::ParticipantDialogStateQuiz * ribi::gtst::ParticipantDialogStates::GetStateQuiz() const
{
  assert(m_state_quiz);
  return m_state_quiz.get();
}

/*
ribi::gtst::ParticipantDialogStateViewResultsAll * ribi::gtst::ParticipantDialogStates::GetStateViewResultsAll() const
{
  assert(m_state_view_results_all);
  return m_state_view_results_all.get();
}
*/

ribi::gtst::ParticipantDialogStateViewResultsGroup * ribi::gtst::ParticipantDialogStates::GetStateViewResultsGroup() const
{
  assert(m_state_view_results_group);
  return m_state_view_results_group.get();
}

ribi::gtst::ParticipantDialogStateViewResultsVoting * ribi::gtst::ParticipantDialogStates::GetStateViewResultsVoting() const
{
  assert(m_state_view_results_voting);
  return m_state_view_results_voting.get();
}

ribi::gtst::ParticipantDialogStateVoting * ribi::gtst::ParticipantDialogStates::GetStateVoting() const
{
  assert(m_state_voting);
  return m_state_voting.get();
}

ribi::gtst::ParticipantDialogStateNotLoggedIn * ribi::gtst::ParticipantDialogStates::GetStateNotLoggedIn() const
{
  assert(m_state_not_logged_in);
  return m_state_not_logged_in.get();
}

void ribi::gtst::ParticipantDialogStates::SetState(ParticipantDialogState * const state)
{
  if (state == m_state) return;
  m_state = state;
  assert(m_state);
}

