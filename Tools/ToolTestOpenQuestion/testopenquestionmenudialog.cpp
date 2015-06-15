//---------------------------------------------------------------------------
/*
TestOpenQuestion, tool to test the OpenQuestion and OpenQuestionDialog classes
Copyright (C) 2013-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testopenquestionmenudialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "fileio.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "testtimer.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::TestOpenQuestionMenuDialog::TestOpenQuestionMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
  const std::vector<std::string> files = { "Question.png" };
  for(const std::string& filename: files)
  {
    if (!fileio::FileIo().IsRegularFile(filename))
    {
      QFile f( (":/images/" + filename).c_str() );
      f.copy(filename.c_str());
    }
    assert(fileio::FileIo().IsRegularFile(filename));
    if (!fileio::FileIo().IsRegularFile(filename))
    {
      const std::string s = "TestOpenQuestionMenuDialog: file not found: " + filename;
      throw std::logic_error(s.c_str());
    }
  }
}

int ribi::TestOpenQuestionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  assert(!"TODO");
  return 1;
}

ribi::About ribi::TestOpenQuestionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestOpenQuestion",
    "tool to test the OpenQuestion and OpenQuestionDialog classes",
    "the 20th of August 2013",
    "2013-2015",
    "http://www.richelbilderbeek.nl/ToolTestOpenQuestion.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestOpenQuestionMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestOpenQuestionMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestOpenQuestion
  };
  assert(p);
  return p;
}
std::string ribi::TestOpenQuestionMenuDialog::GetVersion() const noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::TestOpenQuestionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2013-08-20: Version 1.0: initial version"
    "2013-11-05: version 2.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestOpenQuestionMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
