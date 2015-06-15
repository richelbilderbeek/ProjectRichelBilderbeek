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
#include <thread>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WCheckBox>
#include <Wt/WLabel>

#include "gtstall_groups.h"
#include "gtstall_serverstates.h"
#include "gtstgroups.h"
#include "gtststate.h"
#include "gtstlogfile.h"
#include "gtstparticipant.h"
#include "stopwatch.h"
#include "gtstserver.h"
#include "gtstparticipantdialog.h"
#include "gtstparticipantdialogstategroupassign.h"
#include "gtstparticipantdialogstategroupreassign.h"
#include "gtstparticipantdialogstatenotloggedin.h"
//#include "trace.h"
#include "wtserverpusher.h"
#pragma GCC diagnostic pop

ribi::gtst::ParticipantDialogStateNotLoggedIn::ParticipantDialogStateNotLoggedIn(
  ParticipantDialog * const dialog,Server * const server)
  : ParticipantDialogState(dialog,server),
    ui{}
{

}

///Do something random with the UI, used by DebugDialog
void ribi::gtst::ParticipantDialogStateNotLoggedIn::DoSomethingRandom()
{
  //switch (std::rand() % 1)
  //{
  //  //Select a random button
  //  case 0:
      ui.m_check_participate->setChecked(std::rand() % 2);
  //  default: break; //No problem
  //}
}

void ribi::gtst::ParticipantDialogStateNotLoggedIn::Login()
{
  //Keep trying forever to log in!
  while (ui.m_check_participate->isChecked()
    && !GetDialog()->CanGetParticipant())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    //The Participant is acknowledged to be logged in
    GetDialog()->SetParticipant(
      m_server->LetLogin(GetDialog()->GetIpAddress()));

    //WtServerPusher::GetInstance()->Post();
  }

  assert(GetDialog()->CanGetParticipant()
    && "Assume a logged in participant");

  assert(!m_server->GetGroups()->GetGroupNotLoggedIn()->IsMember(
    GetDialog()->GetParticipant())
    && "Assume Participant is not in GroupNotLoggedIn anymore");

  assert(m_server->GetGroups()->GetGroupLoggedIn()->IsMember(
    GetDialog()->GetParticipant())
    && "Assume Participant is in GroupLoggedIn");

  ui.m_check_participate->hide();
  ui.m_label_status->setText("Logged in... waiting for the experiment to start");
}

void ribi::gtst::ParticipantDialogStateNotLoggedIn::RespondToTimedServerPush()
{
  if(!GetDialog()->CanGetParticipant())
  {
    //Check if participant may log in...
    if (ui.m_check_participate->isChecked()
      && m_server->GetGroups()->CanLetLogin(
        GetDialog()->GetIpAddress()))
    {
      Login();
    }
  }
  else
  {
    //Participant is logged in
    ///Follow the server its tempo
    RespondToParticipant();
  }
}

void ribi::gtst::ParticipantDialogStateNotLoggedIn::ShowPage(ParticipantDialog * const dialog)
{
  assert(dialog);

  ui.m_check_participate = new Wt::WCheckBox("I want to participate");
  ui.m_label_status = new Wt::WLabel("Welcome participant");

  dialog->addWidget(new Wt::WBreak);
  dialog->addWidget(ui.m_label_status);

  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(ui.m_check_participate);
}

