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
#ifndef UnitFormQuestionH
#define UnitFormQuestionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include "UnitQuestion.h"
//---------------------------------------------------------------------------
class TFormQuestion : public TForm
{
__published:	// IDE-managed Components

private:	// User declarations
public:
  enum Question_state { unanswered, correct, incorrect };
private:
  const boost::shared_ptr<Question> m_question; //Keeps the pointer alive
protected:
  Question_state m_state;
  const bool m_is_test;
public:		// User declarations
  __fastcall TFormQuestion(
    TComponent* Owner,
    const boost::shared_ptr<Question>& question,
    const bool is_test);
  const Question_state Get_state() const { return m_state; }
  const std::string Get_question_string() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormQuestion *FormQuestion;
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRemovePath.htm
//Returns the filename without path
const std::string RemovePath(const std::string& filename);
//---------------------------------------------------------------------------
#endif
