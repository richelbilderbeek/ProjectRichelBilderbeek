
/*
OpenQuestionDialog, dialog for OpenQuestion
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

//From http://www.richelbilderbeek.nl/CppOpenQuestionDialog.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "openquestiondialog.h"


#include "openquestion.h"
//#include "trace.h"

OpenQuestionDialog::OpenQuestionDialog(const std::string& question)
  : QuestionDialog(boost::shared_ptr<Question>(new OpenQuestion(question)))
{
  assert(CanSubmit());
  assert(!HasSubmitted());
  assert(GetQuestion());
}

OpenQuestionDialog::OpenQuestionDialog(const boost::shared_ptr<Question>& question)
  : QuestionDialog(question)
{
  assert(CanSubmit());
  assert(!HasSubmitted());
  assert(GetQuestion());
}

const std::string OpenQuestionDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> OpenQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-29: version 1.0: initial version");
  return v;
}

