//---------------------------------------------------------------------------
/*
Project Richel Bilderbeek, Richel Bilderbeek's work
Copyright (C) 2010-2013 Richel Bilderbeek

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
struct ProjectRichelBilderbeekMenuDialog : public MenuDialog
{
  ProjectRichelBilderbeekMenuDialog();
  ~ProjectRichelBilderbeekMenuDialog() noexcept {}

  ///Start the command line version
  ///Returns the error code to give back to the operatings system
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  const About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;

  ///Get every Program by Richel Bilderbeek
  //const std::vector<boost::shared_ptr<Program> >& GetPrograms() const noexcept { return m_programs; }

  const std::string GetVersion() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;


  private:

  ///Created by lazy initialization
  static boost::bimap<ProgramType,boost::shared_ptr<MenuDialog>> sm_map_to_menu;

  ///Every Program by Richel Bilderbeek
  //const std::vector<boost::shared_ptr<Program> > m_programs;

  ///Create all menus
  static const boost::bimap<ProgramType,boost::shared_ptr<MenuDialog> > GetEnumMenuMap() noexcept;

  ///Shows all programs' statuses
  void ShowStatus() const noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RICHELBILDERBEEKMENUDIALOG_H

