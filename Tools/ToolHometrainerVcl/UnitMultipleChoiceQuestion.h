//---------------------------------------------------------------------------
/*
  Hometrainer 2, tool to make exercises and tests
  Copyright (C) 2009  Rich�l Bilderbeek

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
#ifndef UnitMultipleChoiceQuestionH
#define UnitMultipleChoiceQuestionH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include "UnitQuestion.h"
struct TFormMultipleChoiceQuestion;
//---------------------------------------------------------------------------
struct MultipleChoiceQuestion : public Question
{
  MultipleChoiceQuestion(
    const std::string& filename,
    const std::string& question,
    const std::string& answer,
    const std::vector<std::string>& wrong_answers);
  private:
  std::vector<std::string> mWrongAnswers;
  friend boost::checked_delete(MultipleChoiceQuestion *);
  friend TFormMultipleChoiceQuestion;

};
//---------------------------------------------------------------------------
#endif
