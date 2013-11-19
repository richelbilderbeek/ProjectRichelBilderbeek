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
  CodeToHtmlMenuDialog();
  ~CodeToHtmlMenuDialog() noexcept {}
  const ribi::About GetAbout() const noexcept;
  const Help GetHelp() const noexcept;
  const boost::shared_ptr<const Program> GetProgram() const noexcept;
  const std::string GetVersion() const noexcept;

  const std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  /// Source type: folder, content type: C++   -> C++ webpage with tech info
  /// Source type: folder, content type: foam  -> OpenFOAM webpage
  /// Source type: text  , content type: C++   -> C++ code snippet without tech info
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // CODETOHTMLMENUDIALOG_H
