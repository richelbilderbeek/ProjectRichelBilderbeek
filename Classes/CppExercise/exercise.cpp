
/*
Exercise, a collection of Questions
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

//From http://www.richelbilderbeek.nl/CppExercise.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "exercise.h"

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
//#include "trace.h"

Exercise::Exercise(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  if (!boost::filesystem::exists(filename))
  {
    throw std::logic_error("File does not exist");
  }
  const std::vector<std::string> v = FileToVector(filename);
  m_questions.reserve(v.size());
  BOOST_FOREACH(const std::string& s,v)
  {
    try
    {
      boost::shared_ptr<QuestionDialog> tmp(new OpenQuestionDialog(s));
      m_questions.push_back(s);
      continue;
    }
    catch (std::exception&)
    {
      //No problem
    }
    try
    {
      boost::shared_ptr<QuestionDialog> tmp(new MultipleChoiceQuestionDialog(s));
      m_questions.push_back(s);
      continue;
    }
    catch (std::exception&)
    {
      //No problem
    }
  }

  //Shuffle the questions at start
  std::random_shuffle(m_questions.begin(),m_questions.end());

  m_current = m_questions.begin();
}

const std::vector<std::string> Exercise::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

const std::string Exercise::GetCurrentQuestion() const
{
  return *m_current;
}

int Exercise::GetNumberOfQuestions() const
{
  return boost::numeric_cast<int>(m_questions.size());
}

const std::string Exercise::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> Exercise::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-26: Version 1.0: initial version");
  v.push_back("2011-10-30: Version 1.1: shuffle questions at start");
  return v;
}

void Exercise::Next()
{
  ++m_current;
  if (m_current == m_questions.end())
  {
    std::random_shuffle(m_questions.begin(),m_questions.end());
    m_current = m_questions.begin();
  }
}

