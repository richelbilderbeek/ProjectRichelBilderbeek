//---------------------------------------------------------------------------
/*
OpenQuestion, class for an open question
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
// From http://www.richelbilderbeek.nl/CppOpenQuestion
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "openquestion.h"

#include <cassert>
#include <string>
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/algorithm/string/split.hpp>
#pragma GCC diagnostic pop

OpenQuestion::OpenQuestion(const std::string& question)
  : Question(
      SeperateString(question,',').at(0),
      SeperateString(question,',').at(1),
      ExtractAnswers(question))
{

}

OpenQuestion::OpenQuestion(
  const std::string& filename,
  const std::string& question,
  const std::vector<std::string>& answers)
: Question(filename,question, answers )
{
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "OpenQuestion must not be empty");
  //assert(!correct_answers.empty() && "Correct answer must not be empty");
}

///Create a copy of the Question, depending on the derived class its type
Question * OpenQuestion::Clone() const
{
  return new OpenQuestion(
    this->GetFilename(),
    this->GetQuestion(),
    this->GetAnswers());
}

const std::vector<std::string> OpenQuestion::ExtractAnswers(const std::string& input)
{
  const std::vector<std::string> v = SeperateString(input,',');
  if (v.size() != 3)
  {
    throw std::logic_error("An open question has exactly three comma-seperated elements");
  }

  const std::vector<std::string> w = SeperateString(v[2],'/');
  if (w.size() == 0)
  {
    throw std::logic_error("An open question has at least one correct answer");
  }
  return w;
}

const std::vector<std::string>& OpenQuestion::GetAnswers() const
{
  return this->Question::GetAnswers();
}

const std::string OpenQuestion::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> OpenQuestion::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-27: version 1.0: initial version");
  v.push_back("2011-09-16: version 1.1: allow parsing from std::string");
  return v;
}

const std::vector<std::string> OpenQuestion::SeperateString(
  const std::string& input,
  const char seperator)
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

