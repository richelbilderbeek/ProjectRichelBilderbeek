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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <Wt/WBreak>
#include <Wt/WLabel>
#include <Wt/WLineEdit>

#include "gtstadministratordialog.h"
#include "gtstadministratordialogstateloggedin.h"
#include "gtstadministratordialogstatenotloggedin.h"
#include "gtstall_groups.h"
#include "gtstall_serverstates.h"
#include "gtstlogfile.h"
#include "gtstserver.h"
#include "stopwatch.h"
#include "wtserverpusher.h"
#include "wtselectfiledialog.h"
#pragma GCC diagnostic pop

ribi::gtst::AdministratorDialogStateNotLoggedIn::AdministratorDialogStateNotLoggedIn(
  Server * const server,
  AdministratorDialog * const dialog)
  : AdministratorDialogState(server,dialog),
    m_edit_password(0),
    m_label_password(0)
{

}

void ribi::gtst::AdministratorDialogStateNotLoggedIn::OnPassword()
{
  assert(!GetDialog()->CanGetAdministrator() && "Assume no administrator yet");
  //Theoretical Biology beats COCON
  //at a Pub Quiz 4 ever
  const std::string password = "TBbCaaPQ4e";
  if (m_edit_password->text().toUTF8() == password)
  {
     
    //Add the Administrator
    GetDialog()->SetAdministrator(m_server->LoginAdministrator());
    assert(GetDialog()->CanGetAdministrator() && "Assume one administrator");
    GetDialog()->SetState(GetDialog()->GetStateLoggedIn());
    WtServerPusher::GetInstance()->Post();
  }
}

void ribi::gtst::AdministratorDialogStateNotLoggedIn::OnTimer()
{
  //Do exactly nothing...
}

void ribi::gtst::AdministratorDialogStateNotLoggedIn::ShowPage(AdministratorDialog * const dialog)
{
  assert(dialog);

  m_edit_password = new Wt::WLineEdit;
  m_label_password = new Wt::WLabel("Password");

  dialog->addWidget(new Wt::WBreak);

  new Wt::WLabel("Welcome potential administrator",dialog);
  new Wt::WBreak(dialog);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_label_password);
  new Wt::WBreak(dialog);
  dialog->addWidget(m_edit_password);

  m_edit_password->setMinimumSize(300,Wt::WLength::Auto);
  m_edit_password->setEchoMode(Wt::WLineEdit::Password);
  #ifndef NDEBUG
  m_edit_password->setText("TBbCaaPQ4e");
  #endif
  m_edit_password->enterPressed().connect(
    this,&ribi::gtst::AdministratorDialogStateNotLoggedIn::OnPassword);

}

