//---------------------------------------------------------------------------
/*
PicToCode, tool to convert a picture to C++ code
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
//From http://www.richelbilderbeek.nl/ToolPicToCode.htm
//---------------------------------------------------------------------------
#include "pictocodemenudialog.h"

#include <cassert>
#include <iostream>

#include <QFile>
#include <QImage>

#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"
#include "pictocodemaindialog.h"

int ribi::p2c::PicToCodeMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::p2c::PicToCodeMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "PicToCode",
    "tool to convert a picture to C++ code",
    "the 20th of August 2015",
    "2010-2015",
    "http://www.richelbilderbeek.nl/ToolPicToCode.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::p2c::PicToCodeMenuDialog::GetHelp() const noexcept
{
  return Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('f',"image_file","input image filename"),
      Help::Option('h',"header_file","C++ header file name"),
      Help::Option('c',"implementation_file","C++ implementation file name"),
      Help::Option('t',"type","NDS or Qt"),
    },
    {
      GetAbout().GetFileTitle() + " -f pic.png -t nds -c pic.cpp -h pic.h",
      GetAbout().GetFileTitle() + " -f pic.png -t qt",
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::p2c::PicToCodeMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const ribi::Program> p {
    new ProgramPicToCode
  };
  assert(p);
  return p;
}

std::string ribi::p2c::PicToCodeMenuDialog::GetVersion() const noexcept
{
  return "1.6";
}

std::vector<std::string> ribi::p2c::PicToCodeMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2010-10-10: version 1.0: initial version",
    "2010-10-11: version 1.1: added tranparency support",
    "2011-04-18: version 1.2: added support for QPixmap",
    "2011-04-18: version 1.3: added menu, added web application",
    "2013-11-04: version 1.4: conformized to ProjectRichelBilderbeekConsole",
    "2015-08-20: version 1.5: NDS code has seperate header and implementation file",
    "2015-08-26: version 1.6: created command-line version",
  };
}

#ifndef NDEBUG
void ribi::p2c::PicToCodeMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  PicToCodeMainDialog();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  PicToCodeMenuDialog d;
  const std::string temp_png{"temp.png"};
  const std::string temp_h{"temp.h"};
  const std::string temp_cpp{"temp.cpp"};
  QImage image(":/p2c/images/R.png");
  image.save(temp_png.c_str());
  assert(QFile::exists(temp_png));
  d.Execute( { "PicToCode", "-f", temp_png, "-t", "nds", "-c", temp_cpp, "-h", temp_h } );
  assert(QFile::exists(temp_cpp));
  assert(QFile::exists(temp_h));
}
#endif
