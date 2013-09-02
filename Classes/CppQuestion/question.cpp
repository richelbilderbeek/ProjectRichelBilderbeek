//---------------------------------------------------------------------------
/*
Question, class for a question
Copyright (C) 2011  Richl Bilderbeek

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
// From http://www.richelbilderbeek.nl/CppQuestion
//---------------------------------------------------------------------------
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "question.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>

Question::Question(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers)
: m_filename(filename),
  m_question(question),
  m_answers(answers)
{
  if (m_question.empty()) throw std::logic_error("Question must not be empty");
  if (m_answers.empty()) throw std::logic_error("Answers must not be empty");
}

const std::string Question::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> Question::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-27: version 1.0: initial version");
  v.push_back("2011-09-16: version 1.1: contructor throws error when input is invalid");
  return v;
}

bool Question::IsCorrect(const std::string& s) const
{
  return std::find(m_answers.begin(),m_answers.end(),s) != m_answers.end();
}
