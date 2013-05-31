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
#include <Wt/WApplication>
//#include <Wt/WTimer>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
//---------------------------------------------------------------------------
#include "all_serverstates.h"
#include "all_participantdialogstates.h"
#include "groupfinished.h"
#include "grouploggedin.h"
#include "groupnotloggedin.h"
#include "groups.h"
#include "ipaddress.h"
#include "led.h"
#include "ledwidget.h"
#include "logfile.h"
#include "participant.h"
#include "participantdialog.h"
#include "participantdialogstates.h"
#include "rainbow.h"
#include "server.h"
#include "state.h"
#include "stopwatch.h"
//#include "trace.h"
#include "wtledwidget.h"
#include "wtserverpusher.h"
//---------------------------------------------------------------------------
///\note
///Do not make m_timer a child of this,
///to prevent it being delete by Wt classes
ParticipantDialog::ParticipantDialog(
  Server * const server,
  const SafeIpAddress * const ip_address)
  : m_ip_address(new SafeIpAddress(ip_address->Get())),
    m_server(server),
    m_states(new ParticipantDialogStates(this,server))
{
  assert(m_server);
  assert(!m_participant && "Participant is obtained from Server");

  m_states->GetCurrentState()->ShowPage(CreateDialogHeading());
}
//---------------------------------------------------------------------------
ParticipantDialog::~ParticipantDialog()
{

}
//---------------------------------------------------------------------------
bool ParticipantDialog::CanGetParticipant() const
{
  return m_participant;
}
//---------------------------------------------------------------------------
ParticipantDialog * ParticipantDialog::CreateDialogHeading()
{
  ParticipantDialog * const dialog = GetStates()->GetCurrentState()->GetDialog();
  dialog->clear();

  dialog->setContentAlignment(Wt::AlignRight);

  #ifndef NDEBUG
  ui.m_led = new WtLedWidget(1.0);
  ui.m_led->GetWidget()->SetGeometry(Rect(0,0,24,24));
  dialog->addWidget(ui.m_led);
  #endif

  dialog->setContentAlignment(Wt::AlignCenter);

  return dialog;
}
//---------------------------------------------------------------------------
void ParticipantDialog::DoSomethingRandom()
{
  m_states->GetCurrentState()->DoSomethingRandom();
}
//---------------------------------------------------------------------------
const boost::shared_ptr<const SafeIpAddress> ParticipantDialog::GetIpAddress() const
{
  return m_ip_address;
}
//---------------------------------------------------------------------------
const boost::shared_ptr<const Participant>& ParticipantDialog::GetParticipant() const
{
  assert(CanGetParticipant());
  return m_participant;
}
//---------------------------------------------------------------------------
const boost::shared_ptr<const ParticipantDialogStates> ParticipantDialog::GetStates() const
{
  return m_states;
}
//---------------------------------------------------------------------------
void ParticipantDialog::OnServerPush()
{
  //If the participant is logged out, throw him/her back to the login screen
  if (!CanGetParticipant())
  {
    this->m_states->SetState(m_states->GetStateNotLoggedIn());
  }

  m_states->GetCurrentState()->RespondToParticipant();

  m_states->GetCurrentState()->RespondToServerPush();
}
//---------------------------------------------------------------------------
void ParticipantDialog::OnTimedServerPush()
{
  //If the participant is logged out, throw him/her back to the login screen
  if (!CanGetParticipant())
  {
    this->m_states->SetState(m_states->GetStateNotLoggedIn());
  }

  //Update label_time_left
  {
    #ifndef NDEBUG
    /*
    const int time_left = m_server->GetStates()->GetCurrentState()->GetTimeLeft();
    const std::string text
    =  std::string("Time left: ")
    + std::to_string(time_left)
    + std::string(" seconds ");
    assert(ui.m_label_time_left);
    ui.m_label_time_left->setText(text.c_str());
    */
    //Update the Led
    const double f = static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
    double r,g,b;
    Rainbow::GetRgb(f,r,g,b);
    ui.m_led->GetWidget()->GetLed()->SetColor(
      r * 255.0,
      g * 255.0,
      b * 255.0);
    ui.m_led->refresh();
    #endif
  }

  m_states->GetCurrentState()->RespondToParticipant();

  m_states->GetCurrentState()->RespondToTimedServerPush();
}
//---------------------------------------------------------------------------
void ParticipantDialog::SetParticipant(const boost::shared_ptr<const Participant>& participant)
{
  assert(participant);
  m_participant = participant;
}
//---------------------------------------------------------------------------
///Let a State perform a transition that is logged and lets the new State be drawn to screen.
void ParticipantDialog::SetState(ParticipantDialogState * const state)
{
  if (state == m_states->GetCurrentState()) return;

  m_states->SetState(state);

  //Log the change in state
  m_server->GetLog()->LogParticipantDialogStateChanged(m_states->GetCurrentState());

  //Show the new page
  m_states->GetCurrentState()->ShowPage(CreateDialogHeading());
}
//---------------------------------------------------------------------------
