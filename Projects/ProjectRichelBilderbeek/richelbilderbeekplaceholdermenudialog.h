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
#ifndef RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H
#define RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H

/*

#include "about.h"
#include "menudialog.h"

namespace ribi {

struct PlaceholderMenuDialog : public MenuDialog
{
  PlaceholderMenuDialog(
    const About& about,
    const boost::shared_ptr<const Program> program,
    const std::string& version,
    const std::vector<std::string> version_history);
  ~PlaceholderMenuDialog() noexcept {}
  About GetAbout() const noexcept { return m_about; }
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept { return m_program; }
  std::string GetVersion() const noexcept { return m_version; }
  std::vector<std::string> GetVersionHistory() const noexcept { return m_version_history; }

  private:
  const About m_about;
  const boost::shared_ptr<const Program> m_program;
  const std::string m_version;
  const std::vector<std::string> m_version_history;

  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

*/

#endif // RICHELBILDERBEEKPLACEHOLDERMENUDIALOG_H
