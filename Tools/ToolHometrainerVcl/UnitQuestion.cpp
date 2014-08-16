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

#include "UnitQuestion.h"

//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <ExtCtrls.hpp>
#include <string>
#include <fstream>
//---------------------------------------------------------------------------
Question::Question(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers)
: m_filename(filename),
  m_question(question),
  m_answers(answers)
{
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  assert(!m_question.empty() && "Question must not be empty");
  assert(!m_answers.empty() && "Answers must not be empty");
}
//---------------------------------------------------------------------------
const bool Question::IsCorrect(const std::string& s) const
{
  return (std::find(m_answers.begin(),m_answers.end(),s) != m_answers.end());
}
//---------------------------------------------------------------------------

//From http://www.richelbilderbeek.nl/CppFileExists.htm
const bool FileExists(const std::string& fileName)
{
  std::fstream fin;
  fin.open(fileName.c_str(),std::ios::in);
  if( fin.is_open() )
  {
    fin.close();
    return true;
  }
  fin.close();
  return false;
}
//---------------------------------------------------------------------------




#pragma package(smart_init)
