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
#ifndef PROJECTGTSTADMINISTRATORDIALOG_H
#define PROJECTGTSTADMINISTRATORDIALOG_H

#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <Wt/WContainerWidget>

#include "gtstforward_declarations.h"
#include "wtserverpusherclient.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///WtAdministratorDialog contains the user interface of the administrator's dialog.
///
///The logic of it is in the Administrator class
struct AdministratorDialog : public Wt::WContainerWidget, WtServerPusherClient
{
  ///The GUI of an Administrator
  AdministratorDialog(Server * const server);
  AdministratorDialog(const AdministratorDialog&) = delete;
  AdministratorDialog& operator=(const AdministratorDialog&) = delete;

  ///Check if there is a logged-in Administrator
  bool CanGetAdministrator() const;

  ///Obtain a logged-in Administrator
  boost::weak_ptr<Administrator> GetAdministrator() const;

  ///Set a logged-in Administrator
  void SetAdministrator(boost::weak_ptr<Administrator> administrator);

  ///Get the AdministratorDialogStateLoggedIn
  AdministratorDialogStateLoggedIn * GetStateLoggedIn() const;

  ///Get the AdministratorDialogStateNotLoggedIn
  AdministratorDialogStateNotLoggedIn * GetStateNotLoggedIn() const;

  ///Set this AdministratorDialog its AdministratorDialogState
  void SetState(AdministratorDialogState * const state);

  private:
  ~AdministratorDialog();
  friend void boost::checked_delete<>(AdministratorDialog*);

  ///m_administrator contains either nothing or one logged in Administrator
  std::vector<boost::weak_ptr<Administrator> > m_administrator;

  ///The current AdministratorDialogState
  AdministratorDialogState * m_state;

  ///The AdministratorDialogStateLoggedIn state
  boost::scoped_ptr<AdministratorDialogStateLoggedIn> m_state_logged_in;

  ///The AdministratorDialogStateNotLoggedIn state
  boost::scoped_ptr<AdministratorDialogStateNotLoggedIn> m_state_not_logged_in;

  ///Create the start/heading/beginning of all AdministratorDialog instances
  AdministratorDialog * CreateDialogHeading();

  ///OnServerPush is called by WtServerPusher
  void OnServerPush();

  #ifndef NDEBUG
  struct Ui
  {
    Ui() : m_led(0) {}
    WtLedWidget * m_led;
  } ui;
  #endif
};

} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTADMINISTRATORDIALOG_H
