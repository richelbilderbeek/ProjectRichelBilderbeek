//---------------------------------------------------------------------------
/*
TestExercise, tool to test the Exercise class
Copyright (C) 2011 Richel Bilderbeek

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
#include "testexercisemenudialog.h"

#include "exercise.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "question.h"
#include "questiondialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

const ribi::About ribi::TestExerciseMenuDialog::GetAbout() const
{
  About a(
    "Richel Bilderbeek",
    "TestExercise",
    "tool to test the Exercise class",
    "the 2nd of October 2011",
    "2011",
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

const std::string ribi::TestExerciseMenuDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::TestExerciseMenuDialog::GetVersionHistory()
{
  return {
    "2011-09-26: Version 1.0: initial version"
  };
}
