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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "testqrcfilemenudialog.h"

#include <cassert>

#include <boost/filesystem.hpp>

#include "trace.h"
#include "qrcfile.h"

const About TestQrcFileMenuDialog::GetAbout()
{
  About a(
    "Richel Bilderbeek",
    "TestQrcFile",
    "tool to test the QrcFile class",
    "the 20th of May 2013",
    "2012-2013",
    "http://www.richelbilderbeek.nl/ToolTestQrcFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("QrcFile version: " + QrcFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

const std::string TestQrcFileMenuDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> TestQrcFileMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-06-13: version 1.0: initial version");
  v.push_back("2013-05-20: version 1.1: some GUI modifications");
  return v;
}

void TestQrcFileMenuDialog::Test()
{
  //Test exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }

  QrcFile::Test();

  assert(boost::filesystem::exists("../ToolTestQrcFile/ToolTestQrcFile.qrc"));
  {
    QrcFile f("../ToolTestQrcFile/ToolTestQrcFile.qrc");
    assert(f.GetFiles().count("R.png"));
  }
}

