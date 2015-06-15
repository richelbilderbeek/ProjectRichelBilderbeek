//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testshapemenudialog.h"

#include <cassert>
#include <iostream>

#include "richelbilderbeekprogram.h"
#include "shape.h"
#include "shapewidget.h"
#include "trace.h"
#include "testtimer.h"

#include <QFile>

#pragma GCC diagnostic pop

int ribi::TestShapeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::TestShapeMenuDialog::TestShapeMenuDialog()
{
  const std::vector<std::string> files =
  {
    GetFilenameImageWelcome()
  };
  for(const std::string& filename: files)
  {
    if (!QFile::exists(filename.c_str()))
    {
      QFile f( (":/images/" + filename).c_str() );
        f.copy(filename.c_str());
    }
    assert(QFile::exists(filename.c_str()));
  }
}

ribi::About ribi::TestShapeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestShape",
    "tool to test the Shape and ShapeWidget classes",
    "the 8th of August 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestShape.htm",
    GetVersion(),
    GetVersionHistory());
  //a.AddLibrary("Rectangle version: " + Rect::GetVersion());
  a.AddLibrary("Shape version: " + Shape::GetVersion());
  a.AddLibrary("ShapeWidget version: " + ShapeWidget::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  a.AddLibrary("Widget version: " + Widget::GetVersion());
  return a;
}

ribi::Help ribi::TestShapeMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {

    },
    {

    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestShapeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestShape
  };
  assert(p);
  return p;
}

std::string ribi::TestShapeMenuDialog::GetVersion() const noexcept
{
  return "2.1";
}

std::vector<std::string> ribi::TestShapeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-28: Version 1.0: initial version",
    "2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget",
    "2013-11-05: version 2.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestShapeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
