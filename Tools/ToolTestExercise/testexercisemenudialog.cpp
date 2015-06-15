//---------------------------------------------------------------------------
/*
TestExercise, tool to test the Exercise class
Copyright (C) 2011-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestExercise.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testexercisemenudialog.h"

#include <cassert>
#include <iostream>

#include "exercise.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "testtimer.h"
#include "question.h"
#include "questiondialog.h"
#include "richelbilderbeekprogram.h"
#include "trace.h"
#pragma GCC diagnostic pop

int ribi::TestExerciseMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
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

ribi::About ribi::TestExerciseMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestExercise",
    "tool to test the Exercise class",
    "the 2nd of October 2011",
    "2011-2015",
    "http://www.richelbilderbeek.nl/ToolTestExercise.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Exercise version: " + Exercise::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::TestExerciseMenuDialog::GetHelp() const noexcept
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

boost::shared_ptr<const ribi::Program> ribi::TestExerciseMenuDialog::GetProgram() const noexcept
{
  const boost::shared_ptr<const Program> p {
    new ProgramTestExercise
  };
  assert(p);
  return p;
}
std::string ribi::TestExerciseMenuDialog::GetVersion() const noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::TestExerciseMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2011-09-26: Version 1.0: initial version",
    "2013-11-05: version 1.1: conformized for ProjectRichelBilderbeekConsole"
  };
}

#ifndef NDEBUG
void ribi::TestExerciseMenuDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
