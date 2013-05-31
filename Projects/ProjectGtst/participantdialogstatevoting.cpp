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
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
//---------------------------------------------------------------------------
#include "all_groups.h"
#include "all_parameters.h"
#include "all_serverstates.h"
#include "groups.h"
#include "state.h"
#include "logfile.h"
#include "participant.h"
#include "stopwatch.h"
#include "server.h"
#include "participantdialog.h"
#include "participantdialogstatevoting.h"
#include "votingoption.h"
#include "wtserverpusher.h"
//---------------------------------------------------------------------------
ParticipantDialogStateVoting::ParticipantDialogStateVoting(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server)
{

}
//---------------------------------------------------------------------------
///Do something random with the UI, used by DebugDialog
void ParticipantDialogStateVoting::DoSomethingRandom()
{
  assert(ui.m_group);
  assert(ui.m_button_vote);

  switch (std::rand() % 2)
  {
    //Select a random button
    case 0:
      if (ui.m_group->buttons()[0]->isEnabled())
      {
        ui.m_group->setSelectedButtonIndex(
          -1 + (std::rand() % (ui.m_group->count() + 1)));
      }
      break;
    //Click to choose this action
    case 1:
      if (ui.m_button_vote->isEnabled())
      {
        OnVoteClick();
      }
      break;
    default: break; //No problem
  }
}
//---------------------------------------------------------------------------
void ParticipantDialogStateVoting::RespondToTimedServerPush()
{
  const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();

  //Update label_time_left
  {
    std::string text = std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds ");
    if (m_server->GetParameters()->GetVoting()->GetWait())
    {
      //Infinite time
      text+=std::string(" (waiting for others)");
    }
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
  }

  //Check if choice must be sent to the server

  //If no waiting for others, choose randomly for the Participant
  if (!m_server->GetParameters()->GetVoting()->GetWait()
    && time_left <= 0)
  {
    assert(GetDialog());
    assert(GetDialog()->CanGetParticipant());
    if (ui.m_button_vote->isEnabled())
    {
      ui.m_button_vote->setEnabled(false);
      assert(!ui.m_button_vote->isEnabled());
      const int selected = ui.m_group->selectedButtonIndex();
      assert(ui.m_group->count() > 0);
      const int vote_index
        = (selected == -1 //Did user select something?
        ? std::rand() % ui.m_group->count() //Take a random action
        : selected);
      ui.m_group->setSelectedButtonIndex(vote_index);
      OnVoteClick();
    }
  }

  if (!ui.m_button_vote->isEnabled())
  {
    assert(ui.m_group->selectedButtonIndex() != -1);
    const std::string vote_description
      = ui.m_group->selectedButton()->text().toUTF8();
    const std::string text
      = std::string("You have voted \'")
      + vote_description
      + std::string("\', waiting for the others...");
    ui.m_button_vote->setEnabled(false);
    ui.m_label_status->setText(text.c_str());
  }
  else
  {
    ui.m_label_status->setText("Waiting for your vote");
  }


  ///Follow the server its tempo
  RespondToParticipant();
}
//---------------------------------------------------------------------------
void ParticipantDialogStateVoting::OnVoteClick()
{

  const int vote = ui.m_group->selectedButtonIndex();

  ///Check if user did not click vote, without selecting a radiobutton
  if (vote == -1) return;

  assert(vote >= 0);
  assert(vote < boost::numeric_cast<int>(m_voting_options.size()));

  {
    ServerStateVoting * const server_state
      = dynamic_cast<ServerStateVoting*>(m_server->GetStates()->GetCurrentState());
    if (!server_state)
    {
      std::clog << __func__ << ": warning: no ServerStateVoting\n";
      return;
    }

    //Do really vote
    server_state->NotifyVote(
      GetDialog()->GetParticipant(),
      m_voting_options[vote]);

    //WtServerPusher::GetInstance()->Post();
  }

  ui.m_button_vote->setEnabled(false);

  auto buttons = ui.m_group->buttons();
  std::for_each(buttons.begin(),buttons.end(),
    [](Wt::WRadioButton * const r) { r->setEnabled(false); } );
}
//---------------------------------------------------------------------------
void ParticipantDialogStateVoting::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  m_voting_options = m_server->GetParameters()->GetVoting()->GetOptions();

  ui.m_button_vote = new Wt::WPushButton("Submit");
  ui.m_group = new Wt::WButtonGroup(dialog);
  ui.m_label_time_left = new Wt::WLabel("Time left: ... seconds");
  ui.m_label_status = new Wt::WLabel("Waiting for your vote");

  assert(ui.m_button_vote);
  assert(ui.m_group);
  assert(ui.m_label_time_left);
  assert(ui.m_label_status);

  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_status);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_time_left);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Possible voting options",dialog);

    const int n_options
      = boost::numeric_cast<int>(m_voting_options.size());
    //Add the RadioButtons
    for (int i=0; i!=n_options; ++i)
    {
      Wt::WRadioButton * const button
        = new Wt::WRadioButton(m_voting_options[i]->GetDescription().c_str(), container);
      new Wt::WBreak(container);
      ui.m_group->addButton(button,i);
    }
  }
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_button_vote);

  ui.m_button_vote->clicked().connect(
    this,
    &ParticipantDialogStateVoting::OnVoteClick);
}
//---------------------------------------------------------------------------
