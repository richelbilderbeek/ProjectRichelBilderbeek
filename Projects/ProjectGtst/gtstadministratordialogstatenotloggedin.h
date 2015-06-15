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
#ifndef PROJECTGTSTADMINISTRATORDIALOGSTATENOTLOGGEDIN_H
#define PROJECTGTSTADMINISTRATORDIALOGSTATENOTLOGGEDIN_H

#include "gtstadministratordialogstate.h"


namespace ribi {
namespace gtst {

///\brief
///The WtAdministratorDialog its state for a not-(yet-)logged in Administrator
struct AdministratorDialogStateNotLoggedIn : public AdministratorDialogState
{
  ///AdministratorDialogStateNotLoggedIn is a AdministratorDialogState
  AdministratorDialogStateNotLoggedIn(
    Server * const server,
    AdministratorDialog * const dialog);
  AdministratorDialogStateNotLoggedIn(const AdministratorDialogStateNotLoggedIn&) = delete;
  AdministratorDialogStateNotLoggedIn& operator=(const AdministratorDialogStateNotLoggedIn&) = delete;

  ///Respond to timer
  void OnTimer();

  ///Show this AdministratorDialogState its page
  void ShowPage(AdministratorDialog * const dialog);

  private:
  ~AdministratorDialogStateNotLoggedIn() {}
  friend void boost::checked_delete<>(AdministratorDialogStateNotLoggedIn* x);

  ///LineEdit for password
  Wt::WLineEdit * m_edit_password;

  ///Label for password
  Wt::WLabel * m_label_password;

  ///Respond to entering a password
  void OnPassword();
};

} //~namespace gtst
} //~namespace ribi

#endif // ADMINISTRATORDIALOGSTATENOTLOGGEDIN_H
