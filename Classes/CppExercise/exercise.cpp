//---------------------------------------------------------------------------
/*
Exercise, a collection of Questions
Copyright (C) 2011-2015 Richel Bilderbeek

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
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppExercise.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "exercise.h"

#include <fstream>
#include <stdexcept>


#include <boost/numeric/conversion/cast.hpp>

#include "fileio.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "openquestiondialogfactory.h"
//#include "trace.h"

#include <QFile>

#pragma GCC diagnostic pop

ribi::Exercise::Exercise(const std::string& filename)
  : m_current{},
    m_questions{}
{
  assert(QFile::exists(filename.c_str()));
  if (!QFile::exists(filename.c_str()))
  {
    throw std::logic_error("File does not exist");
  }
  const std::vector<std::string> v {
    ribi::fileio::FileIo().FileToVector(filename)
  };
  m_questions.reserve(v.size());
  for(const std::string& s: v)
  {
    try
    {
      boost::shared_ptr<QuestionDialog> tmp
        = OpenQuestionDialogFactory().Create(s);
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

  if (m_questions.empty())
  {
    throw std::runtime_error("No questions found in loading the Exercise");
  }
  assert(!m_questions.empty());

  //Shuffle the questions at start
  std::random_shuffle(m_questions.begin(),m_questions.end());
  m_current = m_questions.begin();
  assert(m_current != m_questions.end());
}

std::string ribi::Exercise::GetCurrentQuestion() const noexcept
{
  assert(m_current != m_questions.end());
  return *m_current;
}

int ribi::Exercise::GetNumberOfQuestions() const noexcept
{
  assert(!m_questions.empty());
  return boost::numeric_cast<int>(m_questions.size());
}

std::string ribi::Exercise::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Exercise::GetVersionHistory() noexcept
{
  return {
    "2011-09-26: Version 1.0: initial version",
    "2011-10-30: Version 1.1: shuffle questions at start"
  };
}

void ribi::Exercise::Next() noexcept
{
  ++m_current;
  if (m_current == m_questions.end())
  {
    std::random_shuffle(m_questions.begin(),m_questions.end());
    m_current = m_questions.begin();
  }
}

