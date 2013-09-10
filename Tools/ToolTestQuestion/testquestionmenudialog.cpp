//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2013 Richel Bilderbeek

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

#include <boost/foreach.hpp>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "question.h"
#include "questiondialog.h"
#include "trace.h"

#include <QFile>

#pragma GCC diagnostic pop

ribi::TestQuestionMenuDialog::TestQuestionMenuDialog()
{
  const std::vector<std::string> files = { "question.png" };
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

const ribi::About ribi::TestQuestionMenuDialog::GetAbout() const
{
  About a(
    "Richel Bilderbeek",
    "TestQuestion",
    "tool to test the Question and QuestionDialog classes",
    "the 20th of August 2013",
    "2011-2013",
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

const std::string ribi::TestQuestionMenuDialog::GetVersion()
{
  return "3.0";
}

const std::vector<std::string> ribi::TestQuestionMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-28: Version 1.0: initial version");
  v.push_back("2011-09-16: Version 2.0: show QuestionDialog from std::string in website version");
  v.push_back("2012-12-23: Version 2.1: finished desktop application");
  v.push_back("2013-08-20: Version 3.0: major architectural rewrite");
  return v;
}
