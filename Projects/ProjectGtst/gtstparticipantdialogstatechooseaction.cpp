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
#include "gtstchooseactionoption.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstate.h"
#include "gtstparticipantdialogstatechooseaction.h"
#include "wtserverpusher.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateChooseAction::ParticipantDialogStateChooseAction(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

///Do something random with the UI, used by DebugDialog
void ribi::gtst::ParticipantDialogStateChooseAction::DoSomethingRandom()
{
  switch (std::rand() % 2)
  {
    //Select a random button
    case 0:
      if (ui.m_button_choose_action->isEnabled())
      {

        ui.m_group->setSelectedButtonIndex(
          -1 + (std::rand() % (ui.m_group->count() + 1)));
      }
      break;
    //Click to choose this action
    case 1:
      if (ui.m_button_choose_action->isEnabled())
      {
        OnChooseActionClick();
      }
      break;
    default: break; //No problem
  }
}

void ribi::gtst::ParticipantDialogStateChooseAction::OnChooseActionClick()
{
  const int action_index = ui.m_group->selectedButtonIndex();

  ///Check if user did not click vote, without selecting a radiobutton
  if (action_index == -1) return;

  {
    assert(action_index < boost::numeric_cast<int>(
      m_server->GetParameters()->GetChooseAction()->GetOptions().size()));

    ServerStateChooseAction * const server_state
      = dynamic_cast<ServerStateChooseAction*>(m_server->GetStates()->GetCurrentState());
    if (!server_state)
    {
      std::clog << __func__ << ": warning: no ServerStateChooseAction\n";
      return;
    }

    server_state->NotifyChosenAction(
      GetDialog()->GetParticipant(),
      m_server->GetParameters()->GetChooseAction()->GetOptions()[action_index].get());

  }

  ///Log the action
  ui.m_button_choose_action->setEnabled(false);
  assert(ui.m_group->selectedButtonIndex() != -1
    && "m_button_choose_action should only disable when an action is selected");
  const auto buttons = ui.m_group->buttons();
  std::for_each(buttons.begin(),buttons.end(),
    [](Wt::WRadioButton * const r) { r->setEnabled(false); } );
}

void ribi::gtst::ParticipantDialogStateChooseAction::RespondToTimedServerPush()
{
  const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();

  //Update label_time_left
  {
    std::string text
    =  std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds");
    if (m_server->GetParameters()->GetChooseAction()->GetWait())
    {
      //Infinite time
      text+=std::string(" (waiting for others)");
    }
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
  }

  //Check if choice must be sent to the server
  if (!m_server->GetParameters()->GetChooseAction()->GetWait()
    && time_left <= 0)
  {
    assert(GetDialog());
    assert(GetDialog()->CanGetParticipant());
    if (ui.m_button_choose_action->isEnabled())
    {
      //Let Participant choose a random action by time
      const int selected = ui.m_group->selectedButtonIndex();
      assert(ui.m_group->count() > 0);
      const int action_index
        = (selected == -1 //Did user select something?
        ? std::rand() % ui.m_group->count() //Take a random action
        : selected);
      assert(action_index > -1 && action_index < ui.m_group->count());
      ui.m_group->setSelectedButtonIndex(action_index);
      OnChooseActionClick();
    }
  }


  if (!ui.m_button_choose_action->isEnabled())
  {
    assert(ui.m_group->selectedButtonIndex() != -1
      && "m_button_choose_action should only disable when an action is selected");

    const std::vector<boost::shared_ptr<ChooseActionOption> >& options
      = m_server->GetParameters()->GetChooseAction()->GetOptions();

    assert(ui.m_group->selectedButtonIndex() < static_cast<int>(options.size()));

    const boost::shared_ptr<ChooseActionOption> option
      = options[ ui.m_group->selectedButtonIndex() ];

    const std::string text
      = option->GetMessageChoice()
      + std::string("\', waiting for the others...");

    ui.m_label_status->setText(text.c_str());
  }
  else
  {
    ui.m_label_status->setText("Please choose an action.");
  }

  ///Follow the server its tempo
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateChooseAction::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  ui.m_button_choose_action = new Wt::WPushButton("Submit");
  ui.m_group = new Wt::WButtonGroup(dialog);
  ui.m_label_status = new Wt::WLabel("Please choose an action.");
  ui.m_label_time_left = new Wt::WLabel("Time left: ... seconds");

  assert(ui.m_button_choose_action);
  assert(ui.m_group);
  assert(ui.m_label_status);
  assert(ui.m_label_time_left);

  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_status);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_time_left);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  //ButtonGroup
  {
    Wt::WGroupBox * const container = new Wt::WGroupBox("Possible actions",dialog);

    const std::vector<boost::shared_ptr<ChooseActionOption> >& options
      = m_server->GetParameters()->GetChooseAction()->GetOptions();
    const int n_options
      = boost::numeric_cast<int>(options.size());
    //Add the RadioButtons
    for (int i=0; i!=n_options; ++i)
    {
      Wt::WRadioButton * const button = new Wt::WRadioButton(
        options[i]->GetDescription().c_str(), container);
      new Wt::WBreak(container);
      ui.m_group->addButton(button,i);
    }
  }
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_button_choose_action);

  ui.m_button_choose_action->clicked().connect(
    this,
    &ribi::gtst::ParticipantDialogStateChooseAction::OnChooseActionClick);
}

