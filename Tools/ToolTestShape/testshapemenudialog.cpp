//---------------------------------------------------------------------------
/*
TestShape, tool to test the Shape and ShapeWidget classes
Copyright (C) 2011 Richel Bilderbeek

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


#include "testshapemenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#pragma GCC diagnostic pop

#include "shape.h"
#include "shapewidget.h"
#include "trace.h"

#include <QFile>

TestShapeMenuDialog::TestShapeMenuDialog()
{
  const std::vector<std::string> files =
  {
    GetFilenameImageWelcome()
  };
  BOOST_FOREACH(const std::string& filename,files)
  {
    if (!QFile::exists(filename.c_str()))
    {
      QFile f( (std::string(":/images/") + filename).c_str() );
        f.copy(filename.c_str());
    }
    assert(QFile::exists(filename.c_str()));
  }
}

const About TestShapeMenuDialog::GetAbout() const
{
  About a(
    "Richel Bilderbeek",
    "TestShape",
    "tool to test the Shape and ShapeWidget classes",
    "the 8th of August 2011",
    "2011",
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

const std::string TestShapeMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> TestShapeMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-28: Version 1.0: initial version");
  v.push_back("2011-08-08: Version 2.0: conformized architecture to MysteryMachineWidget");
  return v;
}

