//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ProjectRichelBilderbeek.htm
//---------------------------------------------------------------------------
#ifndef RICHELBILDERBEEKMENUDIALOG_H
#define RICHELBILDERBEEKMENUDIALOG_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#include <boost/bimap.hpp>
#include "about.h"
#include "help.h"
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {

struct Program;

///The GUI independent version of Project Richel Bilderbeek its menu dialog
struct ProjectRichelBilderbeekMenuDialog final : public ::ribi::MenuDialog
{
  ProjectRichelBilderbeekMenuDialog();
  ~ProjectRichelBilderbeekMenuDialog() noexcept {}
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
  About GetAbout() const noexcept override { return GetAboutStatic(); }
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;

  ///Get every Program by Richel Bilderbeek
  //const std::vector<boost::shared_ptr<Program> >& GetPrograms() const noexcept { return m_programs; }
  std::string GetVersion() const noexcept override { return GetVersionStatic(); }
  std::vector<std::string> GetVersionHistory() const noexcept override { return GetVersionHistoryStatic(); }

  private:
  ///All program menus
  const std::vector<boost::shared_ptr<MenuDialog>> m_menus;

  ///Create all menus
  static std::vector<boost::shared_ptr<MenuDialog>> CreateMenus() noexcept;

  static About GetAboutStatic() noexcept;
  static std::string GetVersionStatic() noexcept;
  static std::vector<std::string> GetVersionHistoryStatic() noexcept;

  ///Shows all programs' statuses
  void ShowStatus() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RICHELBILDERBEEKMENUDIALOG_H

