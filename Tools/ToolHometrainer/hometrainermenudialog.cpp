//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "hometrainermenudialog.h"

#include <boost/foreach.hpp>

#include "exercise.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "question.h"
#include "questiondialog.h"
//#include "trace.h"

#include <QFile>

const ribi::About ribi::HometrainerMenuDialog::GetAbout() const
{
  About a(
    "Richel Bilderbeek",
    "Hometrainer",
    "exercise and survey suite",
    "the 16th of October 2011",
    "2011",
    "http://www.richelbilderbeek.nl/ToolHometrainer.htm",
    GetVersion(),
    GetVersionHistory());
  a.AddLibrary("Exercise version: " + Exercise::GetVersion());
  a.AddLibrary("Hometrainer version: " + ribi::HometrainerMenuDialog::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  //a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string ribi::HometrainerMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> ribi::HometrainerMenuDialog::GetVersionHistory()
{
  return {
    "2009-xx-xx: Version 0.9: initial version (called HomeTrainer)",
    "2009-04-28: Version 1.0: renamed 'HomeTrainer' to 'Hometrainer 2'",
    "2009-05-09: Version 1.1",
    "2009-08-23: Version 1.2",
    "2009-08-29: Version 1.3",
    "2009-09-20: Version 1.4",
    "2009-10-29: Version 1.5",
    "2009-11-03: Version 1.6",
    "2010-01-07: Version 1.7",
    "2010-01-28: Version 1.8",
    "2011-10-16: Version 2.0: initial website version, renamed 'Hometrainer 2' to 'Hometrainer'"
  };
}

