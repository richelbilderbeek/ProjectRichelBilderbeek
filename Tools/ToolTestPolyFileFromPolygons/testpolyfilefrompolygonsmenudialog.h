//---------------------------------------------------------------------------
/*
TestPolyFileFromPolygons, tests the PolyFileFromPolygons class
Copyright (C) 2014-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPolyFileFromPolygons.htm
//---------------------------------------------------------------------------
#ifndef RIBI_TESTPOLYFILEFROMPOLYGONSMENUDIALOG_H
#define RIBI_TESTPOLYFILEFROMPOLYGONSMENUDIALOG_H

#include <string>
#include <vector>

#include "menudialog.h"

struct QRegExp;

namespace ribi {

///GUI independent TestPolyFileFromPolygons menu dialog
struct TestPolyFileFromPolygonsMenuDialog : public MenuDialog
{
  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  static std::string GetPolygonRegex();

  //static std::vector<std::string> GetRegexMatches(
  //  const std::string& s,
  //  const QRegExp& r_original
  //) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace ribi

#endif // RIBI_TESTPOLYFILEFROMPOLYGONSMENUDIALOG_H
