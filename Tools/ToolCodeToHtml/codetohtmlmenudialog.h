//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifndef CODETOHTMLMENUDIALOG_H
#define CODETOHTMLMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"
#include "codetohtmlfwd.h"

namespace ribi {
namespace c2h {

///GUI independent CodeToHtml menu dialog
struct CodeToHtmlMenuDialog final : public MenuDialog
{
  CodeToHtmlMenuDialog();
  ~CodeToHtmlMenuDialog() noexcept {}
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  boost::shared_ptr<const Program> GetProgram() const noexcept override;
  std::string GetVersion() const noexcept override;

  std::vector<std::string> GetVersionHistory() const noexcept override;

  static void TestAllProgramsHaveInfo() noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLMENUDIALOG_H
