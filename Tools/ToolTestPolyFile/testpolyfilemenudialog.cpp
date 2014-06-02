//---------------------------------------------------------------------------
/*
TestPolyFile, tool to test the PolyFile class
Copyright (C) 2014-2014 Richel Bilderbeek

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

#include "fileio.h"
#include "polyfile.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::TestPolyFileMenuDialog::TestPolyFileMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
}

int ribi::TestPolyFileMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 3 && (argv[1] == "-f" || argv[1] == "--filename"))
  {
    const std::string filename = argv[2];
    if (filename.empty())
    {
      std::cout << "Please specify a filename.\n";
    }
    else if (filename.size() < 5)
    {
      std::cout << "Please specify a full poly (.poly) filename.\n";
    }
    else if (filename.substr(filename.size() - 5,5) != ".poly")
    {
      std::cout << "Please specify a filename ending on .poly.\n";
    }
    else if (!fileio::FileIo().IsRegularFile(filename))
    {
      std::cout << "Please specify a poly (.poly) filename that exists.\n";
    }
    else
    {
      PolyFile p(filename);
      std::cout << p << '\n';
      return 0;
    }
    return 1;
  }
  std::cout << GetHelp() << '\n';
  return 1;
}

ribi::About ribi::TestPolyFileMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestPolyFile",
    "tool to test the PolyFile class",
    "the 2nd of June 2014",
    "2014-2014",
    "http://www.richelbilderbeek.nl/ToolTestPolyFile.htm",
    GetVersion(),
    GetVersionHistory());
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
      Help::Option('f',"filename","filename of the poly (.poly) file")
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
  return "1.0";
}

std::vector<std::string> ribi::TestPolyFileMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2016-06-02: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::TestPolyFileMenuDialog::Test() noexcept
{
  //Test exactly once
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
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
    const PolyFile polyfile(filename);
    assert(!polyfile.GetVertices().empty());
    assert(!polyfile.GetEdges().empty());
  }
}
#endif

