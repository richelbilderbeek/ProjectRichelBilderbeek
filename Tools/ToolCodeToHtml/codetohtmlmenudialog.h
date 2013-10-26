//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef CODETOHTMLMENUDIALOG_H
#define CODETOHTMLMENUDIALOG_H

#include <string>
#include <vector>

#include "about.h"
#include "menudialog.h"

namespace ribi {

///GUI independent CodeToHtml menu dialog
struct CodeToHtmlMenuDialog : public MenuDialog
{
  ~CodeToHtmlMenuDialog() noexcept {}
  const ribi::About GetAbout() const noexcept;
  const std::string GetVersion() const noexcept;

  //Obtain the help information
  const Help GetHelp() const noexcept;
  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;
};

} //~namespace ribi

#endif // CODETOHTMLMENUDIALOG_H
