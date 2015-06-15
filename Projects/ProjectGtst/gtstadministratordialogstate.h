
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

//From http://www.richelbilderbeek.nl/ProjectGtst.htm

#ifndef PROJECTGTSTADMINISTRATORDIALOGSTATE_H
#define PROJECTGTSTADMINISTRATORDIALOGSTATE_H

#include <string>
#include <vector>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/checked_delete.hpp>
//#include <boost/shared_ptr.hpp>

#include <Wt/WObject>

#include "gtstforward_declarations.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace gtst {

///\brief
///The WtAdministratorDialog its state.
struct AdministratorDialogState : public Wt::WObject
{
  ///An AdministratorDialogState needs its AdministratorDialog
  AdministratorDialogState(
    Server * const server,
    AdministratorDialog * const dialog
  );

  AdministratorDialogState(const AdministratorDialogState&) = delete;
  AdministratorDialogState& operator=(const AdministratorDialogState&) = delete;

  ///Obtain if the Administrator is logged in
  bool IsLoggedIn() const;

  ///Respond to a timer
  virtual void OnTimer() = 0;

  ///Show the web page
  virtual void ShowPage(AdministratorDialog * const base_dialog) = 0;

  ///Obtain the AdministratorDialogState its AdministratorDialog
  AdministratorDialog * GetDialog() const noexcept { return m_dialog; }

  protected:
  virtual ~AdministratorDialogState() {}
  friend void boost::checked_delete<>(AdministratorDialogState*);

  private:
  ///The dialog this state works on
  AdministratorDialog * const m_dialog;

  protected:
  ///The Server instance
  Server * const m_server;

  public:
  ///Get all .txt files in a folder
  static std::vector<std::string> GetTextFilesInFolder(const std::string& folder) noexcept;
};

} //~namespace gtst
} //~namespace ribi

#endif // PROJECTGTSTADMINISTRATORDIALOGSTATE_H
