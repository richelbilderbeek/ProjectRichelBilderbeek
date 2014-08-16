//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
  Copyright (C) 2009  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <algorithm>
#include <boost/shared_ptr.hpp>

#include "UnitFormQuestion.h"
#include "UnitFormImage.h"
#include "UnitFormCorrect.h"
#include "UnitFormIncorrect.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormQuestion *FormQuestion;
//---------------------------------------------------------------------------
__fastcall TFormQuestion::TFormQuestion(
  TComponent* Owner,
  const boost::shared_ptr<Question>& question,
  const bool is_test)
  : TForm(Owner),
    m_question(question),
    m_is_test(is_test)
{
  m_state = unanswered;
}
//---------------------------------------------------------------------------
const std::string TFormQuestion::Get_question_string() const
{
  //Use '-' instead of comma, because of SeperateString in UnitFormScoreTests
  return (RemovePath(m_question->m_filename) + "-" + m_question->m_question);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRemovePath.htm
//Returns the filename without path
const std::string RemovePath(const std::string& filename)
{
  const int sz = static_cast<int>(filename.size());
  const int path_sz = filename.rfind("\\",filename.size());
  if (path_sz == sz) return filename;
  return filename.substr(path_sz + 1,sz - 1 - path_sz);
}
//---------------------------------------------------------------------------


