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
#ifndef UnitOpenQuestionH
#define UnitOpenQuestionH
//---------------------------------------------------------------------------
#include <vector>
#include <string>
#include "UnitQuestion.h"
struct TFormOpenQuestion;
//---------------------------------------------------------------------------
struct OpenQuestion : public Question
{
  OpenQuestion(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers);
  private:
  friend boost::checked_delete(OpenQuestion *);
  friend TFormOpenQuestion;
};
//---------------------------------------------------------------------------



#endif
