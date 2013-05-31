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
#include "all_participantdialogstates.h"
#include "participantdialogstates.h"
//---------------------------------------------------------------------------
ParticipantDialogStates::ParticipantDialogStates(
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
//---------------------------------------------------------------------------
ParticipantDialogState * ParticipantDialogStates::GetCurrentState() const
{
  assert(m_state);
  return m_state;
}
//---------------------------------------------------------------------------
ParticipantDialogStateChat * ParticipantDialogStates::GetStateChat() const
{
  assert(m_state_chat);
  return m_state_chat.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateAssignPayoff * ParticipantDialogStates::GetStateAssignPayoff() const
{
  assert(m_state_assign_payoff);
  return m_state_assign_payoff.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateChooseAction * ParticipantDialogStates::GetStateChooseAction() const
{
  assert(m_state_choose_action);
  return m_state_choose_action.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateFinished * ParticipantDialogStates::GetStateFinished() const
{
  assert(m_state_finished);
  return m_state_finished.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateGroupAssign * ParticipantDialogStates::GetStateGroupAssign() const
{
  assert(m_state_group_assign);
  return m_state_group_assign.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateGroupReAssign * ParticipantDialogStates::GetStateGroupReAssign() const
{
  assert(m_state_group_reassign);
  return m_state_group_reassign.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateLoggedIn * ParticipantDialogStates::GetStateLoggedIn() const
{
  assert(m_state_logged_in);
  return m_state_logged_in.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateQuiz * ParticipantDialogStates::GetStateQuiz() const
{
  assert(m_state_quiz);
  return m_state_quiz.get();
}
//---------------------------------------------------------------------------
/*
ParticipantDialogStateViewResultsAll * ParticipantDialogStates::GetStateViewResultsAll() const
{
  assert(m_state_view_results_all);
  return m_state_view_results_all.get();
}
*/
//---------------------------------------------------------------------------
ParticipantDialogStateViewResultsGroup * ParticipantDialogStates::GetStateViewResultsGroup() const
{
  assert(m_state_view_results_group);
  return m_state_view_results_group.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateViewResultsVoting * ParticipantDialogStates::GetStateViewResultsVoting() const
{
  assert(m_state_view_results_voting);
  return m_state_view_results_voting.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateVoting * ParticipantDialogStates::GetStateVoting() const
{
  assert(m_state_voting);
  return m_state_voting.get();
}
//---------------------------------------------------------------------------
ParticipantDialogStateNotLoggedIn * ParticipantDialogStates::GetStateNotLoggedIn() const
{
  assert(m_state_not_logged_in);
  return m_state_not_logged_in.get();
}
//---------------------------------------------------------------------------
void ParticipantDialogStates::SetState(ParticipantDialogState * const state)
{
  if (state == m_state) return;
  m_state = state;
  assert(m_state);
}
//---------------------------------------------------------------------------
