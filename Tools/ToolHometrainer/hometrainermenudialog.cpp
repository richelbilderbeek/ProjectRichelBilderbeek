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
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

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

HometrainerMenuDialog::HometrainerMenuDialog()
{

}

const About HometrainerMenuDialog::GetAbout() const
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
  a.AddLibrary("Hometrainer version: " + HometrainerMenuDialog::GetVersion());
  a.AddLibrary("MultipleChoiceQuestion version: " + MultipleChoiceQuestion::GetVersion());
  a.AddLibrary("MultipleChoiceQuestionDialog version: " + MultipleChoiceQuestionDialog::GetVersion());
  a.AddLibrary("OpenQuestion version: " + OpenQuestion::GetVersion());
  a.AddLibrary("OpenQuestionDialog version: " + OpenQuestionDialog::GetVersion());
  a.AddLibrary("Question version: " + Question::GetVersion());
  a.AddLibrary("QuestionDialog version: " + QuestionDialog::GetVersion());
  //a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

const std::string HometrainerMenuDialog::GetVersion()
{
  return "2.0";
}

const std::vector<std::string> HometrainerMenuDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2009-xx-xx: Version 0.9: initial version (called HomeTrainer)");
  v.push_back("2009-04-28: Version 1.0: renamed 'HomeTrainer' to 'Hometrainer 2'");
  v.push_back("09-05-2009: Version 1.1");
  v.push_back("23-08-2009: Version 1.2");
  v.push_back("29-08-2009: Version 1.3");
  v.push_back("20-09-2009: Version 1.4");
  v.push_back("29-10-2009: Version 1.5");
  v.push_back("03-11-2009: Version 1.6");
  v.push_back("07-01-2010: Version 1.7");
  v.push_back("28-01-2010: Version 1.8");
  v.push_back("16-10-2011: Version 2.0: initial website version, renamed 'Hometrainer 2' to 'Hometrainer'");
  return v;
}

