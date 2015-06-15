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
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WLabel>

#include "gtstall_groups.h"
#include "gtstall_parameters.h"
#include "gtstall_serverstates.h"
#include "gtstgroup.h"
#include "gtstgroups.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstate.h"
#include "gtstparticipantdialogstatechat.h"
#include "gtstparticipantdialogstategroupassign.h"
#include "gtstparticipantdialogstategroupreassign.h"
#include "gtstparticipantstate.h"
#include "gtstparticipantstategroupassign.h"
#include "gtstserver.h"
#include "gtststate.h"
#include "stopwatch.h"
#include "wtserverpusher.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateGroupAssign::ParticipantDialogStateGroupAssign(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

void ribi::gtst::ParticipantDialogStateGroupAssign::RespondToTimedServerPush()
{
   

  assert(GetDialog()->CanGetParticipant()
    && "Assume that only existing participants can have their payoffs assigned");

  const auto participant = GetDialog()->GetParticipant();
  assert(participant);

  ServerStateGroupAssign * const server_state
    = dynamic_cast<ServerStateGroupAssign*>(m_server->GetStates()->GetCurrentState());
  if (!server_state)
  {
    std::clog << __func__ << ": warning: no ServerStateGroupAssign\n";
    return;
  }

  //Is the Participant waiting to be assigned to a group?
  if (m_server->GetGroups()->FindMyGroup(participant)
    == m_server->GetGroups()->GetGroupLoggedIn())
  {
    //Can the server assign the Participant to a group?
    if (server_state->CanAssignGroup(participant))
    {
      //Assign the Participant to a group
      server_state->AssignGroup(participant);

      assert(m_server->GetGroups()->FindMyGroup(participant)
        != m_server->GetGroups()->GetGroupLoggedIn());
    }
  }

  //Display the group the Participant is in
  {
    const Group * const group
      = m_server->GetGroups()->FindMyGroup(participant);
    //Update the status label
    const std::string message
      = m_server->GetParameters()->GetGroupAssign()->GetMessageAssigned()
      + std::to_string(group->GetId())
      + (dynamic_cast<const GroupNotLoggedIn *>(group)
        ? std::string(" (not participating)")
        : std::string(" (participating)"));

    assert(ui.m_label_group);
    ui.m_label_group->setText(message.c_str());
  }

  //const boost::shared_ptr<const Participant> participant = GetDialog()->GetParticipant();
  assert(participant);

  //if (dynamic_cast<const ParticipantStateGroupAssign*>(participant->GetState()))
  //{
  //  const ParticipantStateGroupAssign* const state
  //    = dynamic_cast<const ParticipantStateGroupAssign*>(participant->GetState());
  //  ui.m_label_status->setText(state->GetMessage().c_str());
  //}

  ///Follow the server its tempo
  RespondToParticipant();
}

void ribi::gtst::ParticipantDialogStateGroupAssign::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->CanGetParticipant()
    && "A Participant must be logged in in this state");

  assert(GetDialog()->GetParticipant()->CanGetId()
    && "A Participant must be assigned an ID before entering this state");

  const auto participant = dialog->GetParticipant();

  //Create the widget(s)
  ui.m_label_group = new Wt::WLabel;
  ui.m_label_status = new Wt::WLabel;

  //Check the widget(s)
  assert(ui.m_label_status);
  assert(ui.m_label_group);

  //Add the widgets to the
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  {
    const std::string id
      = "You have been assigned ID "
      + std::to_string(participant->GetId());
    dialog->addWidget(new Wt::WLabel(id.c_str()));
  }
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_group);

  const Group * const group = m_server->GetGroups()->FindMyGroup(participant);

  ui.m_label_group->setText(
       (dynamic_cast<const GroupParticipating*>(group)
      ? m_server->GetParameters()->GetGroupAssign()->GetMessageAssigned()
        + std::to_string(dynamic_cast<const GroupParticipating*>(group)->GetId())
      : m_server->GetParameters()->GetGroupAssign()->GetMessageUnassigned() ).c_str() );
}

