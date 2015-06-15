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
#include "gtstadministratordialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WGroupBox>
#include <Wt/WLabel>

#include "gtstall_serverstates.h"
#include "gtstadministratordialogstateloggedin.h"
#include "gtstadministratordialogstatenotloggedin.h"
#include "led.h"
#include "ledwidget.h"
#include "gtstlogfile.h"
#include "gtstserver.h"
#include "stopwatch.h"
#include "wtledwidget.h"
#include "wtselectfiledialog.h"
#pragma GCC diagnostic pop

ribi::gtst::AdministratorDialog::AdministratorDialog(Server * const server)
  : m_administrator{},
    m_state(0),
    m_state_logged_in(new AdministratorDialogStateLoggedIn(server,this)),
    m_state_not_logged_in(new AdministratorDialogStateNotLoggedIn(server,this))
    #ifndef NDEBUG
    ,ui{}
    #endif
{
  assert(!m_state);
  assert(m_state_logged_in);
  assert(m_state_not_logged_in);
  SetState(GetStateNotLoggedIn());
}

ribi::gtst::AdministratorDialog::~AdministratorDialog()
{

}

bool ribi::gtst::AdministratorDialog::CanGetAdministrator() const
{
  assert(m_administrator.empty() || m_administrator.size() == 1);
  return !m_administrator.empty();
}

ribi::gtst::AdministratorDialog * ribi::gtst::AdministratorDialog::CreateDialogHeading()
{
  AdministratorDialog * const dialog = this->m_state->GetDialog();
  assert(dialog);

  dialog->clear();
  dialog->setContentAlignment(Wt::AlignCenter);

  #ifndef NDEBUG
  ui.m_led = new WtLedWidget(1.0);
  ui.m_led->GetWidget()->SetGeometry(0,0,24,24);
  dialog->addWidget(ui.m_led);
  #endif

  return dialog;
}

boost::weak_ptr<ribi::gtst::Administrator> ribi::gtst::AdministratorDialog::GetAdministrator() const
{
  assert(CanGetAdministrator());
  assert(m_administrator.size() == 1);
  return m_administrator[0];
}

ribi::gtst::AdministratorDialogStateLoggedIn * ribi::gtst::AdministratorDialog::GetStateLoggedIn() const
{
  assert(m_state_logged_in);
  return m_state_logged_in.get();
}

ribi::gtst::AdministratorDialogStateNotLoggedIn * ribi::gtst::AdministratorDialog::GetStateNotLoggedIn() const
{
  assert(m_state_not_logged_in);
  return m_state_not_logged_in.get();
}

void ribi::gtst::AdministratorDialog::SetState(AdministratorDialogState * const state)
{
  assert(state);
  m_state = state;
  assert(m_state);
  m_state->ShowPage(CreateDialogHeading());
}

void ribi::gtst::AdministratorDialog::OnServerPush()
{
  //OnServerTimer();
  this->m_state->OnTimer();
}

void ribi::gtst::AdministratorDialog::SetAdministrator(boost::weak_ptr<Administrator> administrator)
{
  assert(m_administrator.empty());
  m_administrator.push_back(administrator);
}




