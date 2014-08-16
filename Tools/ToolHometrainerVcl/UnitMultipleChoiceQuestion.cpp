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
#pragma hdrstop

#include "UnitMultipleChoiceQuestion.h"

//---------------------------------------------------------------------------
#include <cassert>
#include <ExtCtrls.hpp>
#include <string>
#include <fstream>
//---------------------------------------------------------------------------
MultipleChoiceQuestion::MultipleChoiceQuestion(
  const std::string& filename,
  const std::string& question,
  const std::string& answer,
  const std::vector<std::string>& wrong_answers)
: Question(filename,question,std::vector<std::string>(1,answer)),
  mWrongAnswers(wrong_answers)
{
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "MultipleChoiceQuestion must not be empty");
  //assert(!correct_answer.empty() && "Correct answer must not be empty");
  assert(!wrong_answers.empty() && "Wrong answers must not be empty");
}
//---------------------------------------------------------------------------
#pragma package(smart_init)

