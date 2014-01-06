//---------------------------------------------------------------------------
/*
OpenQuestion, class for an open question
Copyright (C) 2011-2014 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "openquestion.h"

#include <cassert>
#include <string>
#include <fstream>
#include <stdexcept>

#include <boost/algorithm/string/split.hpp>
#include <boost/scoped_ptr.hpp>

#include "trace.h"
#pragma GCC diagnostic pop

ribi::OpenQuestion::OpenQuestion(const std::string& question)
  : Question(
      SeperateString(question,',').at(0),
      SeperateString(question,',').at(1),
      ExtractAnswers(question))
{
  #ifndef NDEBUG
  Test();
  #endif

  if (question.empty())
  {
    throw std::logic_error("An open question must contain text");
  }
  if (question[0] == ',')
  {
    throw std::logic_error("An open question must not start with a comma");
  }
  if (question[question.size() - 1] == ',')
  {
    throw std::logic_error("An open question must not end with a comma");
  }
  if (question.find(",,") != std::string::npos)
  {
    throw std::logic_error("An open question cannot contain two consecutive commas");
  }

}

ribi::OpenQuestion::OpenQuestion(
  const std::string& filename,
  const std::string& question,
  const std::vector<std::string>& answers)
: Question(filename,question, answers )
{
  #ifndef NDEBUG
  Test();
  #endif
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "OpenQuestion must not be empty");
  //assert(!correct_answers.empty() && "Correct answer must not be empty");
}

ribi::Question * ribi::OpenQuestion::Clone() const noexcept
{
  return new OpenQuestion(
    this->GetFilename(),
    this->GetQuestion(),
    this->GetCorrectAnswers()
  );
}

const std::vector<std::string> ribi::OpenQuestion::ExtractAnswers(const std::string& input)
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

//const std::vector<std::string>& ribi::OpenQuestion::GetAnswers() const noexcept
//{
//  this->GetCorrectAnswers()
//}

const std::vector<std::string> ribi::OpenQuestion::GetInvalidOpenQuestions() noexcept
{
  return {
    "-,1+1=,2,3", //Incorrect options are
    "-,1+1=",   //No answer
    "-",        //No question
    "tmp.png",  //No question
    "",         //Nothing
    ",tmp.png,1+1=,2", //Start with comma
    "tmp.png,,1+1=,2", //Two consecutive comma's
    "tmp.png,1+1=,,2", //Two consecutive comma's
    "tmp.png,1+1=,2,", //Two consecutive comma's
    "tmp.png,1+1=,2,", //End with comma
    ",tmp.png,1+1=,2,", //Start and end with comma
    ",,tmp.png,1+1=,2,",
    ",tmp.png,,1+1=,2,",
    ",tmp.png,1+1=,,2,",
    ",tmp.png,1+1=,2,,",
    ",",
    ",,",
    ",,,",
    ",,,,",
    ",,,,,",
    ",,,,,,"
  };
}

const std::vector<std::string> ribi::OpenQuestion::GetValidOpenQuestions() noexcept
{
  return {
    "-,1+1=,2",
    "tmp.png,1+1=,2/Two",
    "-,1+1=,Two/2/two"
  };
}


const std::string ribi::OpenQuestion::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::OpenQuestion::GetVersionHistory() noexcept
{
  return {
    "2011-06-27: version 1.0: initial version",
    "2011-09-16: version 1.1: allow parsing from std::string"
    "2013-10-24: version 1.2: added tests"
  };
}

const std::vector<std::string> ribi::OpenQuestion::SeperateString(
  const std::string& input,
  const char seperator) noexcept
{
  std::vector<std::string> v;
  boost::algorithm::split(v,input,
    std::bind2nd(std::equal_to<char>(),seperator),
    boost::algorithm::token_compress_on);
  return v;
}

#ifndef NDEBUG
void ribi::OpenQuestion::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::OpenQuestion::Test");
  try
  {
    boost::scoped_ptr<OpenQuestion> q {
      new OpenQuestion(
        OpenQuestion::GetExampleOpenQuestion()
      )
    };
    assert(q);
  }
  catch (std::exception& e)
  {
    assert("OpenQuestion::GetExampleOpenQuestion()"
        && "must yield a valid OpenQuestion");
  }
  //Test valid multiple choice questions for validity
  {
    const std::vector<std::string> valid { GetValidOpenQuestions() };
    for (const std::string& s: valid)
    {
      try
      {
        boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(s) };
        assert(q); //To make the compiler happy
        //OK
      }
      catch (std::exception& e)
      {
        TRACE("ERROR");
        TRACE(s);
        assert(!"Valid questions must be accepted");
      }
    }
  }
  //Test invalid multiple choice questions for invalidity
  {
    const std::vector<std::string> invalid { GetInvalidOpenQuestions()  };
    for (const std::string& s: invalid)
    {
      try
      {
        boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(s) };
        TRACE("ERROR");
        TRACE(s);
        assert(!"Invalid questions must be rejected");
      }
      catch (std::exception& e)
      {
        //OK
      }
    }
  }
  //Test simple get/set with single answer
  {
    const std::string filename = "-";
    const std::string question = "1+1=";
    const std::string answer_1 { "2" };
    const std::vector<std::string> answers { answer_1 };
    boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(filename,question,answers) };
    assert(q->GetFilename() == filename);
    assert(q->GetQuestion() == question);
    assert(q->GetCorrectAnswers() == answers);
    assert(q->IsCorrect(answer_1));
    assert(!q->IsCorrect("3"));
    assert(!q->IsCorrect(filename));
    assert(!q->IsCorrect(question));
  }
  //Test simple get/set with two answers
  {
    const std::string filename = "-";
    const std::string question = "1+1=";
    const std::string answer_1 { "2" };
    const std::string answer_2 { "Two" };
    const std::vector<std::string> answers { answer_1, answer_2 };
    boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(filename,question,answers) };
    assert(q->GetFilename() == filename);
    assert(q->GetQuestion() == question);
    assert(q->GetCorrectAnswers() == answers);
    assert(q->IsCorrect(answer_1));
    assert(q->IsCorrect(answer_2));
    assert(!q->IsCorrect( answer_1 + "/" + answer_2));
    assert(!q->IsCorrect(filename));
    assert(!q->IsCorrect(question));
  }
  //Test conversion std::string to OpenQuestion and back
  {
    const std::vector<std::string> valid { GetValidOpenQuestions() };
    for (const std::string& s: valid)
    {
      const boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(s) };
      assert(s == q->ToStr());
    }
  }
  //Test that ToLines always yields the same result
  {
    const std::vector<std::string> valid { GetValidOpenQuestions() };
    for (const std::string& s: valid)
    {
      const boost::scoped_ptr<OpenQuestion> q { new OpenQuestion(s) };
      const std::vector<std::string> v { q->ToLines() };
      const std::vector<std::string> w { q->ToLines() };
      assert(v == w);
    }
  }
  TRACE("Finished ribi::OpenQuestion::Test successfully");
}
#endif

const std::vector<std::string> ribi::OpenQuestion::ToLines() const
{
  std::vector<std::string> v;
  v.push_back(this->GetQuestion());
  return v;
}

const std::string ribi::OpenQuestion::ToStr() const noexcept
{
  //Concatenate the correct answer
  assert(!this->GetCorrectAnswers().empty());
  std::string correct_answers_str;

  for (const std::string s: this->GetCorrectAnswers()) { correct_answers_str += s + "/"; }
  assert(!correct_answers_str.empty());
  correct_answers_str.resize(correct_answers_str.size() - 1);

  std::string s
    = this->GetFilename()
    + "," + this->GetQuestion()
    + "," + correct_answers_str;
  return s;
}
