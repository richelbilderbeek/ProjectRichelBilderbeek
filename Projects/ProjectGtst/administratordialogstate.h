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
#ifndef PROJECTGTSTADMINISTRATORDIALOGSTATE_H
#define PROJECTGTSTADMINISTRATORDIALOGSTATE_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
#include <boost/noncopyable.hpp>
#include <boost/checked_delete.hpp>
//#include <boost/shared_ptr.hpp>
//---------------------------------------------------------------------------
#include <Wt/WObject>
//---------------------------------------------------------------------------
#include "forward_declarations.h"
//---------------------------------------------------------------------------
///\brief
///The WtAdministratorDialog its state.
struct AdministratorDialogState : public boost::noncopyable, Wt::WObject
{
  ///An AdministratorDialogState needs its AdministratorDialog
  AdministratorDialogState(
    Server * const server,
    AdministratorDialog * const dialog);

  ///Obtain if the Administrator is logged in
  bool IsLoggedIn() const;

  ///Respond to a timer
  virtual void OnTimer() = 0;

  ///Show the web page
  virtual void ShowPage(AdministratorDialog * const base_dialog) = 0;

  ///Obtain the AdministratorDialogState its AdministratorDialog
  AdministratorDialog * GetDialog() const { return m_dialog; }

  protected:
  ///Only let smart pointers delete AdministratorDialogState
  virtual ~AdministratorDialogState() {}
  ///Only let smart pointers delete AdministratorDialogState
  //Do not forget the template brackets, as stated in
  //Herb Sutter. Exceptional C++ style. 2005. ISBN: 0-201-76042-8. Item 8: 'Befriending templates'.
  friend void boost::checked_delete<>(AdministratorDialogState*);

  private:
  ///The dialog this state works on
  AdministratorDialog * const m_dialog;

  protected:
  ///The Server instance
  Server * const m_server;

  public:
  ///Convert a file to std::vector<std::string>
  static const std::vector<std::string> FileToVector(const std::string& filename);
  ///Get all files in a folder
  static const std::vector<std::string> GetFilesInFolder(const std::string& folder);
  ///Get all .txt files in a folder
  static const std::vector<std::string> GetTextFilesInFolder(const std::string& folder);
};
//---------------------------------------------------------------------------
#endif // PROJECTGTSTADMINISTRATORDIALOGSTATE_H
