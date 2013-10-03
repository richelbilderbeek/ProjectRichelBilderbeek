//---------------------------------------------------------------------------
/*
TestMultipleChoiceQuestion, tests multiple choice question classes
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "testmultiplechoicequestionmenudialog.h"

#include <stdexcept>

#include <boost/foreach.hpp>

#include <QFile>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::TestMultipleChoiceQuestionMenuDialog::TestMultipleChoiceQuestionMenuDialog()
{
  const std::vector<std::string> files = { "Question.png" };
  BOOST_FOREACH(const std::string& filename,files)
  {
    if (!QFile::exists(filename.c_str()))
    {
      QFile f( (std::string(":/images/") + filename).c_str() );
        f.copy(filename.c_str());
    }
    assert(QFile::exists(filename.c_str()));
    if (QFile::exists(filename.c_str()))
    {
      const std::string s = "TestMultipleChoiceQuestionMenuDialog: file not found: " + filename;
      throw std::logic_error(s.c_str());
    }
  }
}

const ribi::About ribi::TestMultipleChoiceQuestionMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "TestMultipleChoiceQuestion",
    "tool to test the MultipleChoiceQuestion and MultipleChoiceQuestionDialog classes",
    "the 20th of August 2013",
    "2013",
    "http://www.richelbilderbeek.nl/ToolTestMultipleChoiceQuestion.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::TestMultipleChoiceQuestionMenuDialog::GetVersion() noexcept
{
  return "1.0";
}

const std::vector<std::string> ribi::TestMultipleChoiceQuestionMenuDialog::GetVersionHistory() noexcept
{
  return {
    "2013-08-20: Version 1.0: initial version"
  };
}

