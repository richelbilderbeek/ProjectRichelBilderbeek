//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestShape.htm
//---------------------------------------------------------------------------
#ifndef TESTSHAPEMENUDIALOG_H
#define TESTSHAPEMENUDIALOG_H

#include "menudialog.h"

namespace ribi {

///The logic behind the menu dialog
struct TestShapeMenuDialog : public MenuDialog
{
  ///Creates the resources needed
  TestShapeMenuDialog();

  About GetAbout() const noexcept;
  Help GetHelp() const noexcept;
  ///\brief
  ///Get the filename of the image shown at the welcome screen
  ///
  ///This is a non-static method to force this class its constructor being
  ///called, creating the file from the application its resource file
  std::string GetFilenameImageWelcome() const { return "ToolTestShapeWelcome.png"; }
  boost::shared_ptr<const Program> GetProgram() const noexcept;
  std::string GetVersion() const noexcept;
  std::vector<std::string> GetVersionHistory() const noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // TESTSHAPEMENUDIALOG_H
