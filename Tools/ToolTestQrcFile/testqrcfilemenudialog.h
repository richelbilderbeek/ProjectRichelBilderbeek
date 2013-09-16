//---------------------------------------------------------------------------
/*
TestQrcFile, tool to test the QrcFile class
Copyright (C) 2012-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestQrcFile.htm
//---------------------------------------------------------------------------
#ifndef TESTQRCFILEMENUDIALOG_H
#define TESTQRCFILEMENUDIALOG_H

#include "about.h"

namespace ribi {

struct TestQrcFileMenuDialog
{

  ///Obtain this class its About information
  static const About GetAbout() noexcept;

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  #ifndef NDEBUG
  ///Test the QrcFile
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTQRCFILEMENUDIALOG_H
