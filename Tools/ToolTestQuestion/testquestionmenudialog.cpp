//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
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
//From http://www.richelbilderbeek.nl/ToolTestQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testquestionmenudialog.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "question.h"
#include "questiondialog.h"
#include "richelbilderbeekprogram.h"
#include "testtimer.h"
#include "trace.h"

#include <QFile>

#pragma GCC diagnostic pop

ribi::TestQuestionMenuDialog::TestQuestionMenuDialog()
{
  #ifndef NDEBUG
  Test();
  #endif
  const std::vector<std::string> files = { "question.png" };
  for(const std::string& filename: files)
  {
    if (!QFile::exists(filename.c_str()))
    {
      QFile f( (":/images/" + filename).c_str() );
        f.copy(filename.c_str());
    }
    assert(QFile::exists(filename.c_str()));
    if (!QFile::exists(filename.c_str()))
    {
      const std::string s = "TestQuestionMenuDialog: file not found: " + filename;
      throw std::logic_error(s.c_str());
    }
  }
}

int ribi::TestQuestionMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestQuestionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestQuestion",
    "tool to test the Question and QuestionDialog classes",
    "the 20th of August 2013",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestQuestion.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestQuestionMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestQuestionMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestQuestion
  };
  assert(p);
  return p;
}

std::string ribi::TestQuestionMenuDialog::GetVersion() const noexcept
{
  return "3.1";
}

std::vector<std::string> ribi::TestQuestionMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-06-28: Version 1.0: initial version",
    "2011-09-16: Version 2.0: show QuestionDialog from std::string in website version",
    "2012-12-23: Version 2.1: finished desktop application",
    "2013-08-20: Version 3.0: major architectural rewrite",
    "2013-11-05: version 3.1: conformized for ProjectRichelBilderbeekConsole"
  };
}
#ifndef NDEBUG
void ribi::TestQuestionMenuDialog::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
