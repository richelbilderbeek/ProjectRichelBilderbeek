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
#include <Wt/WBreak>
#include <Wt/WCheckBox>
#include <Wt/WLabel>
//---------------------------------------------------------------------------
#include "all_groups.h"
#include "all_serverstates.h"
#include "groups.h"
#include "state.h"
#include "logfile.h"
#include "participant.h"
#include "stopwatch.h"
#include "server.h"
#include "participantdialog.h"
#include "participantdialogstategroupassign.h"
#include "participantdialogstategroupreassign.h"
#include "participantdialogstateloggedin.h"
#include "participantstate.h"
#include "participantstateloggedin.h"
//---------------------------------------------------------------------------
ribi::gtst::ParticipantDialogStateLoggedIn::ParticipantDialogStateLoggedIn(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}
//---------------------------------------------------------------------------
void ribi::gtst::ParticipantDialogStateLoggedIn::RespondToTimedServerPush()
{
  const auto participant = GetDialog()->GetParticipant();
  if (dynamic_cast<const ParticipantStateLoggedIn*>(participant->GetState()))
  {
    const ParticipantStateLoggedIn* const state
      = dynamic_cast<const ParticipantStateLoggedIn*>(participant->GetState());
    ui.m_label_status->setText(state->GetMessage().c_str());
  }

  RespondToParticipant();
}
//---------------------------------------------------------------------------
void ribi::gtst::ParticipantDialogStateLoggedIn::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);
  assert(GetDialog()->GetParticipant());
  assert(GetDialog()->GetParticipant()->CanGetId()
    && "A Participant must have became an ID before being logged in");
  assert(GetDialog()->GetParticipant()->CanGetIpAddress()
    && "A Participant must have became an IP address before being logged in");

  //Create the GUI widgets
  ui.m_label_status = new Wt::WLabel;

  new Wt::WBreak(dialog);
  new Wt::WLabel("Welcome",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  new Wt::WLabel("Please wait for the experiment to begin",dialog);
  //new Wt::WLabel(
  //    (std::string("You have been assigned an ID of ")
  //  + std::to_string(GetDialog()->GetParticipant()->GetId())).c_str()
  //  ,dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_label_status);
}
//---------------------------------------------------------------------------
