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
#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/numeric/conversion/cast.hpp>
#include <boost/signals2.hpp>

#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroups.h"
#include "gtststate.h"
#include "gtstlogfile.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "gtstparticipant.h"
#include "questiondialog.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstatequiz.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtserverpusher.h"
#include "wtquestiondialog.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateQuiz::ParticipantDialogStateQuiz(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{
}

///Do something random with the UI, used by DebugDialog
void ribi::gtst::ParticipantDialogStateQuiz::DoSomethingRandom()
{
  /*
  switch (std::rand() % 5)
  {
    //Select a random button
    case 0:
      if (m_group->buttons()[0]->isEnabled())
      {
        m_group->setSelectedButtonIndex(
          -1 + (std::rand() % (m_group->count() + 1)));
      }
      break;
    //Click to choose this action
    case 1:
      if (m_button_vote->isEnabled())
      {
        OnVoteClick();
      }
      break;
    default: break; //No problem
  }
  */
}

void ribi::gtst::ParticipantDialogStateQuiz::RespondToTimedServerPush()
{
  const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();

  //Update label_time_left
  {
    std::string text = std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds ");
    if (m_server->GetParameters()->GetQuiz()->GetWait())
    {
      //Infinite time
      text+=std::string(" (waiting for others)");
    }
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
  }

  //Check if choice must be sent to the server

  //If no waiting for others, choose randomly for the Participant
  if (!m_server->GetParameters()->GetQuiz()->GetWait()
    && time_left <= 0)
  {
    assert(GetDialog());
    assert(GetDialog()->CanGetParticipant());
    /*
    if (ui.m_button_vote->isEnabled())
    {
      m_button_vote->setEnabled(false);
      assert(!m_button_vote->isEnabled());
      const int selected = m_group->selectedButtonIndex();
      assert(m_group->count() > 0);
      const int vote_index
        = (selected == -1 //Did user select something?
        ? std::rand() % m_group->count() //Take a random action
        : selected);
      m_group->setSelectedButtonIndex(vote_index);
      OnVoteClick();
    }
    */
  }

  /*
  if (!m_button_vote->isEnabled())
  {
    assert(m_group->selectedButtonIndex() != -1);
    const std::string vote_description
      = m_group->selectedButton()->text().toUTF8();
    const std::string text
      = std::string("You have voted \'")
      + vote_description
      + std::string("\', waiting for the others...");
    m_button_vote->setEnabled(false);
    m_label_status->setText(text.c_str());
  }
  else
  {
    m_label_status->setText("Waiting for your vote");
  }
  */

  ///Follow the server its tempo
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateQuiz::OnSubmitClick()
{
  /*
  ui.m_mc_dialog->GetDialog()->IsAnswerCorrect
  const int vote = m_group->selectedButtonIndex();

  ///Check if user did not click vote, without selecting a radiobutton
  if (vote == -1) return;

  //Do really vote
  server.GetStateQuiz()->NotifyVote(
    GetDialog()->GetParticipant(),
    vote);

  m_button_vote->setEnabled(false);

  for(Wt::WRadioButton * const r: m_group->buttons())
  {
    r->setEnabled(false);
  }
  */
}

void ribi::gtst::ParticipantDialogStateQuiz::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);

  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  ui.m_label_time_left = new Wt::WLabel("Time left: ... seconds");
  ui.m_label_status = new Wt::WLabel("Waiting for your vote");

  ui.m_mc_dialog = new WtMultipleChoiceQuestionDialog("*,Test,Good,Wrong1,Wrong2");
  assert(ui.m_label_time_left);
  assert(ui.m_label_status);
  assert(ui.m_mc_dialog);

  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_status);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_time_left);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_mc_dialog);

  //ui.m_mc_dialog->m_signal_submitted.connect(
  //  this,&ribi::gtst::ParticipantDialogStateQuiz::OnSubmitClick);
}

