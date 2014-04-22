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

#include <Wt/WBreak>
#include <Wt/WLabel>

#include "all_parameters.h"
#include "all_serverstates.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groups.h"
#include "logfile.h"
#include "participant.h"
#include "participantstate.h"
#include "state.h"
#include "stopwatch.h"
#include "participantdialog.h"
#include "participantdialogstate.h"
#include "participantdialogstateassignpayoff.h"
#include "server.h"
#include "wtserverpusher.h"

ribi::gtst::ParticipantDialogStateAssignPayoff::ParticipantDialogStateAssignPayoff(
  ParticipantDialog * const dialog,
  Server * const server)
  : ParticipantDialogState(dialog,server),
    m_ui{}
{

}

void ribi::gtst::ParticipantDialogStateAssignPayoff::RespondToTimedServerPush()
{
  assert(GetDialog()->CanGetParticipant()
    && "Assume that only existing participants can have their payoffs assigned");
  //Do nothing...

  //Display the Participant
  RespondToParticipant();

}

void ribi::gtst::ParticipantDialogStateAssignPayoff::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);

  m_ui.m_label_status
    = new Wt::WLabel(
      m_server->GetParameters()->GetAssignPayoff()->GetMessage().c_str());

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(m_ui.m_label_status);
}

