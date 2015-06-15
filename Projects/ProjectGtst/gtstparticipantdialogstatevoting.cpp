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
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstatevoting.h"
#include "gtstvotingoption.h"
#include "wtserverpusher.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateVoting::ParticipantDialogStateVoting(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    m_ui{},
    m_voting_options{}
{

}

///Do something random with the UI, used by DebugDialog
void ribi::gtst::ParticipantDialogStateVoting::DoSomethingRandom()
{
  assert(m_ui.m_group);
  assert(m_ui.m_button_vote);

  switch (std::rand() % 2)
  {
    //Select a random button
    case 0:
      if (m_ui.m_group->buttons()[0]->isEnabled())
      {
        m_ui.m_group->setSelectedButtonIndex(
          -1 + (std::rand() % (m_ui.m_group->count() + 1)));
      }
      break;
    //Click to choose this action
    case 1:
      if (m_ui.m_button_vote->isEnabled())
      {
        OnVoteClick();
      }
      break;
    default: break; //No problem
  }
}

void ribi::gtst::ParticipantDialogStateVoting::RespondToTimedServerPush()
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
    assert(m_ui.m_label_time_left);
    m_ui.m_label_time_left->setText(text.c_str());
  }

  //Check if choice must be sent to the server

  //If no waiting for others, choose randomly for the Participant
  if (!m_server->GetParameters()->GetVoting()->GetWait()
    && time_left <= 0)
  {
    assert(GetDialog());
    assert(GetDialog()->CanGetParticipant());
    if (m_ui.m_button_vote->isEnabled())
    {
      m_ui.m_button_vote->setEnabled(false);
      assert(!m_ui.m_button_vote->isEnabled());
      const int selected = m_ui.m_group->selectedButtonIndex();
      assert(m_ui.m_group->count() > 0);
      const int vote_index
        = (selected == -1 //Did user select something?
        ? std::rand() % m_ui.m_group->count() //Take a random action
        : selected);
      m_ui.m_group->setSelectedButtonIndex(vote_index);
      OnVoteClick();
    }
  }

  if (!m_ui.m_button_vote->isEnabled())
  {
    assert(m_ui.m_group->selectedButtonIndex() != -1);
    const std::string vote_description
      = m_ui.m_group->selectedButton()->text().toUTF8();
    const std::string text
      = std::string("You have voted \'")
      + vote_description
      + std::string("\', waiting for the others...");
    m_ui.m_button_vote->setEnabled(false);
    m_ui.m_label_status->setText(text.c_str());
  }
  else
  {
    m_ui.m_label_status->setText("Waiting for your vote");
  }


  ///Follow the server its tempo
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateVoting::OnVoteClick()
{

  const int vote = m_ui.m_group->selectedButtonIndex();

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

  m_ui.m_button_vote->setEnabled(false);

  auto buttons = m_ui.m_group->buttons();
  std::for_each(buttons.begin(),buttons.end(),
    [](Wt::WRadioButton * const r) { r->setEnabled(false); } );
}

void ribi::gtst::ParticipantDialogStateVoting::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  m_voting_options = m_server->GetParameters()->GetVoting()->GetOptions();

  m_ui.m_button_vote = new Wt::WPushButton("Submit");
  m_ui.m_group = new Wt::WButtonGroup(dialog);
  m_ui.m_label_time_left = new Wt::WLabel("Time left: ... seconds");
  m_ui.m_label_status = new Wt::WLabel("Waiting for your vote");

  assert(m_ui.m_button_vote);
  assert(m_ui.m_group);
  assert(m_ui.m_label_time_left);
  assert(m_ui.m_label_status);

  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_label_status);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_label_time_left);
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
      m_ui.m_group->addButton(button,i);
    }
  }
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_ui.m_button_vote);

  m_ui.m_button_vote->clicked().connect(
    this,
    &ribi::gtst::ParticipantDialogStateVoting::OnVoteClick);
}

