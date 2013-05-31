//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2012 Richel Bilderbeek

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
#ifndef TESTQUESTIONMENUDIALOG_H
#define TESTQUESTIONMENUDIALOG_H

#include "about.h"

///The logic behind the menu dialog
struct TestQuestionMenuDialog
{
  ///Creates the resources needed
  TestQuestionMenuDialog();

  ///Obtain the about information
  ///
  ///\note
  ///This is a non-static method, to ensure users of this class
  ///call TestQuestionMenuDialog its constructor: this is where
  ///the resources needed are created
  const About GetAbout() const;

  ///Obtain the version
  static const std::string GetVersion();

  ///Obtain the version history
  static const std::vector<std::string> GetVersionHistory();
};

#endif // TESTQUESTIONMENUDIALOG_H
