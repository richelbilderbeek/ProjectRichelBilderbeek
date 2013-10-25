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
#include <boost/shared_ptr.hpp>
#include "about.h"
#include "menudialog.h"
#pragma GCC diagnostic pop

namespace ribi {
namespace RichelBilderbeek {

struct Program;

///The GUI independent version of Project Richel Bilderbeek its menu dialog
struct ProjectRichelBilderbeekMenuDialog : public MenuDialog
{
  ProjectRichelBilderbeekMenuDialog();
  ~ProjectRichelBilderbeekMenuDialog() noexcept {}

  ///Start the command line version
  ///Returns the error code to give back to the operatings system
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  const std::vector<std::string> GetHelp() const noexcept;

  ///Get every Program by Richel Bilderbeek
  const std::vector<boost::shared_ptr<Program> >& GetPrograms() const noexcept { return m_programs; }

  ///Obtain the version of this class
  const std::string GetVersion() const noexcept;

  ///Obtain the version history of this class
  const std::vector<std::string> GetVersionHistory() const noexcept;

  ///Obtain the About information of this class
  const About GetAbout() const noexcept;

  ///Every Program by Richel Bilderbeek
  const std::vector<boost::shared_ptr<Program> > m_programs;

  private:
  ///Create all menus
  const std::vector<boost::shared_ptr<MenuDialog> > CreateMenus() const;

};

} //~namespace RichelBilderbeek
} //~namespace ribi

#endif // RICHELBILDERBEEKMENUDIALOG_H

