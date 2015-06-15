//---------------------------------------------------------------------------
/*
TestPolyFile, tool to test the PolyFile class
Copyright (C) 2014-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestPolyFile.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "testpolyfilemenudialog.h"

#include <cassert>
#include <iostream>

#include <QFile>

#include "container.h"
#include "fileio.h"
#include "polyfile.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::TestPolyFileMenuDialog::TestPolyFileMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestPolyFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& args) noexcept
{
  const int argc = static_cast<int>(args.size());

  bool silent{false};
  if (std::count(args.begin(),args.end(),"-s") || std::count(args.begin(),args.end(),"--silent"))
  {
    silent = true;
  }

  std::stringstream s;
  if (argc >= 3 && (args[1] == "-f" || args[1] == "--filename"))
  {
    const std::string filename = args[2];
    if (filename.empty())
    {
      s << "Please specify a filename.\n";
    }
    else if (filename.size() < 5)
    {
      s << "Please specify a full poly (.poly) filename.\n";
    }
    else if (filename.substr(filename.size() - 5,5) != ".poly")
    {
      s << "Please specify a filename ending on .poly.\n";
    }
    else if (!fileio::FileIo().IsRegularFile(filename))
    {
      s << "Please specify a poly (.poly) filename that exists.\n";
    }
    else
    {
      PolyFile p(filename);
      s << p << '\n';
      if (!silent) { std::cout << s.str(); }
      return 0;
    }
    if (!silent) { std::cout << s.str(); }
    return 1;
  }
  if (!silent) { std::cout << GetHelp() << '\n'; }
  return 1;
}

ribi::About ribi::TestPolyFileMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestPolyFile",
    "tool to test the PolyFile class",
    "the 2nd of June 2014",
    "2014-2015",
    "http://www.richelbilderbeek.nl/ToolTestPolyFile.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Container version: " + Container().GetVersion());
  a.AddLibrary("ribi::fileio::FileIo version: " + fileio::FileIo().GetVersion());
  a.AddLibrary("PolyFile version: " + PolyFile::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());

  return a;
}

ribi::Help ribi::TestPolyFileMenuDialog::GetHelp() const noexcept
{
  return Help(
    GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
      Help::Option('f',"filename","filename of the poly (.poly) file"),
      Help::Option('s',"silent","produce no output")
    },
    {
      GetAbout().GetFileTitle() + " -f somefile.poly",
      GetAbout().GetFileTitle() + " --filename somefile.poly"
    }
  );
}

boost::shared_ptr<const ribi::Program> ribi::TestPolyFileMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestPolyFile
  };
  assert(p);
  return p;
}

std::string ribi::TestPolyFileMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TestPolyFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2014-06-02: version 1.0: initial version"
    "2014-08-08: version 1.1: added silent flag to console version"
  };
}

#ifndef NDEBUG
void ribi::TestPolyFileMenuDialog::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Container();
    fileio::FileIo();
    PolyFile( {}, {} );
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Load a .poly file
  {
    const std::string filename = fileio::FileIo().GetTempFileName(".poly");
    {
      const std::string qtfilename = ":/polyfile/polyfile1.poly";
      QFile qfile(qtfilename.c_str());
      assert(qfile.size() > 0);
      qfile.copy(filename.c_str());
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    TestPolyFileMenuDialog d;
    d.ExecuteSpecific(
      {
        "TestPolyFile", "-f", filename, "--silent"
      }
    );
    fileio::FileIo().DeleteFile(filename);
  }
}
#endif

