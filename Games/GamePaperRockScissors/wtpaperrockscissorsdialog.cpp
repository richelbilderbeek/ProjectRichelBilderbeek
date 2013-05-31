//---------------------------------------------------------------------------
/*
PaperRockScissors, time polling server
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
//From http://www.richelbilderbeek.nl/ToolPaperRockScissors.htm
//---------------------------------------------------------------------------
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WContainerWidget>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WRadioButton>
#include <Wt/WPushButton>
//---------------------------------------------------------------------------
#include "about.h"
#include "wtaboutdialog.h"
#include "wtpaperrockscissorsdialog.h"
#include "wtpaperrockscissorsserver.h"
#include "wtpaperrockscissorsdialogstate.h"
//---------------------------------------------------------------------------
WtPaperRockScissorsDialog::WtPaperRockScissorsDialog(Wt::WContainerWidget *parent)
  : WContainerWidget(parent),
    m_application(Wt::WApplication::instance()),
    m_server(WtPaperRockScissorsServer::GetInstance()),
    m_state_about(new WtPaperRockScissorsDialogStateAbout(this,WtPaperRockScissorsServer::GetInstance(),0)),
    m_state_connect(new WtPaperRockScissorsDialogStateConnect(this,WtPaperRockScissorsServer::GetInstance())),
    m_state_login(new WtPaperRockScissorsDialogStateLogin(this,WtPaperRockScissorsServer::GetInstance())),
    m_state_game(new WtPaperRockScissorsDialogStateGame(this,WtPaperRockScissorsServer::GetInstance()))
{
  //Need to have Wt::WApplication::instance() at the
  //constructor of the class, to have it directly
  //accessible in WtPaperRockScissorsDialog::PollChangedEvent

  this->setContentAlignment(Wt::AlignCenter);
  this->SetState(this->GetStateLogin());
  Show();

  // this widget supports server-side updates its PollChangedEvent()
  // method is connected to a slot that is triggered from outside this
  // session's event loop when another user selects another option.
  m_application->enableUpdates();
}
//---------------------------------------------------------------------------
 WtPaperRockScissorsDialog::~WtPaperRockScissorsDialog()
{
  m_state->Disconnect();
  m_signal_close();
}
//---------------------------------------------------------------------------
const About WtPaperRockScissorsDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "PaperRockScissors",
    "time poll web application",
    "the 13th of April 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolPaperRockScissors.htm",
    GetVersion(),
    GetVersionHistory());
  return a;
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState * WtPaperRockScissorsDialog::GetStateAbout() const
{
  assert(m_state_about);
  return this->m_state_about.get();
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState * WtPaperRockScissorsDialog::GetStateConnect() const
{
  assert(m_state_connect);
  return this->m_state_connect.get();
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState * WtPaperRockScissorsDialog::GetStateGame() const
{
  assert(m_state_game);
  return this->m_state_game.get();
}
//---------------------------------------------------------------------------
WtPaperRockScissorsDialogState * WtPaperRockScissorsDialog::GetStateLogin() const
{
  assert(m_state_login);
  return this->m_state_login.get();
}
//---------------------------------------------------------------------------
const std::string WtPaperRockScissorsDialog::GetVersion()
{
  return "1.0";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtPaperRockScissorsDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-04-15: Version 1.0: initial version");
  return v;
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialog::OnClose()
{
  m_state->Disconnect();
  m_signal_close();
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialog::SetState(State * const state)
{
  assert(state);
  m_state = state;
  Show();
}
//---------------------------------------------------------------------------
void WtPaperRockScissorsDialog::Show()
{
  m_state->Show();
}
//---------------------------------------------------------------------------
///Called by server triggered from other session
void WtPaperRockScissorsDialog::ServerEvent(const WtPaperRockScissorsEvent& event)
{
  Wt::WApplication::UpdateLock lock = m_application->getUpdateLock();

  m_state->ProcessEvent(event);

  m_application->triggerUpdate();
}
//---------------------------------------------------------------------------
