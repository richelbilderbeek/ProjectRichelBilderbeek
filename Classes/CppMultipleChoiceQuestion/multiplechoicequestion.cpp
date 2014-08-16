//---------------------------------------------------------------------------
/*
MultipleChoiceQuestion, class for a multiple choice question
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
// From http://www.richelbilderbeek.nl/CppMultipleChoiceQuestion
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "multiplechoicequestion.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/scoped_ptr.hpp>

#include "container.h"
#include "imagecanvas.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::MultipleChoiceQuestion::MultipleChoiceQuestion(const std::string& question)
  : Question(
      Container().SeperateString(question,',').at(0),
      Container().SeperateString(question,',').at(1),
      { Container().SeperateString(question,',').at(2) }),
    m_wrong_answers(ExtractWrongAnswers(question)),
    m_options(ExtractOptions(question))
{
  #ifndef NDEBUG
  Test();
  #endif
  if (question.empty())
  {
    throw std::logic_error("A multiple choice question must contain text");
  }
  if (question[0] == ',')
  {
    throw std::logic_error("A multiple choice question must not start with a comma");
  }
  if (question[question.size() - 1] == ',')
  {
    throw std::logic_error("A multiple choice question must not end with a comma");
  }
  if (question.find(",,") != std::string::npos)
  {
    throw std::logic_error("A multiple choice question cannot contain two consecutive commas");
  }
}

ribi::MultipleChoiceQuestion::MultipleChoiceQuestion(
  const std::string& filename,
  const std::string& question,
  const std::string& answer,
  const std::vector<std::string>& wrong_answers)
: Question(filename,question, {answer} ),
  m_wrong_answers(wrong_answers),
  m_options(CreateOptions(wrong_answers,answer))
{
  #ifndef NDEBUG
  Test();
  #endif
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "MultipleChoiceQuestion must not be empty");
  //assert(!correct_answer.empty() && "Correct answer must not be empty");
  if (this->GetWrongAnswers().empty())
  {
    throw std::logic_error("a MultipleChoiceQuestion must have at least one incorrect option");
  }

  assert(!GetCorrectAnswers().empty() && "There must be a correct answer");
  assert(!GetWrongAnswers().empty() && "Wrong answers must not be empty");

  //Why did I put this max here? I think this is something that might be constrained by a GUI only
  //assert(wrong_answers.size() <= 5 && "There is a maximum of five wrong answers");
}

ribi::Question * ribi::MultipleChoiceQuestion::Clone() const noexcept
{
  return new MultipleChoiceQuestion(
    this->GetFilename(),
    this->GetQuestion(),
    this->GetAnswer(),
    this->GetWrongAnswers());
}

const std::string& ribi::MultipleChoiceQuestion::GetAnswer() const noexcept
{
  assert(!GetCorrectAnswers().empty());
  return GetCorrectAnswers()[0];
}

std::vector<std::string> ribi::MultipleChoiceQuestion::CreateOptions(
  const std::vector<std::string>& wrong_answers,
  const std::string& answer) noexcept
{
  std::vector<std::string> v = wrong_answers;
  v.push_back(answer);
  std::random_shuffle(v.begin(),v.end());
  return v;
}

std::vector<std::string> ribi::MultipleChoiceQuestion::ExtractOptions(const std::string& input)
{
  const auto v = Container().SeperateString(input,',');
  std::vector<std::string> w;
  std::copy(v.begin() + 2,v.end(),std::back_inserter(w));
  std::random_shuffle(w.begin(),w.end());
  return w;
}

std::vector<std::string> ribi::MultipleChoiceQuestion::ExtractWrongAnswers(const std::string& input)
{
  const auto v = Container().SeperateString(input,',');
  if (v.size() < 4)
  {
    throw std::logic_error(
      "A multiple choice question must contain at least four elements:"
      "[0] image,"
      "[1] question,"
      "[2] answer,"
      "[3-x] incorrect answers");
  }
  std::vector<std::string> w;
  std::copy(v.begin() + 3,v.end(),std::back_inserter(w));
  return w;
}

std::vector<std::string> ribi::MultipleChoiceQuestion::GetInvalidMultipleChoiceQuestions() noexcept
{
  return {
    "-,1+1=,2", //No incorrect options
    "-,1+1=",   //No answer
    "-",        //No question
    "tmp.png",  //No question
    "",         //Nothing
    ",tmp.png,1+1=,2,1", //Start with comma
    "tmp.png,,1+1=,2,1", //Two consecutive comma's
    "tmp.png,1+1=,,2,1", //Two consecutive comma's
    "tmp.png,1+1=,2,,1", //Two consecutive comma's
    "tmp.png,1+1=,2,1,", //End with comma
    ",tmp.png,1+1=,2,1,", //Start and end with comma
    ",,tmp.png,1+1=,2,1,",
    ",tmp.png,,1+1=,2,1,",
    ",tmp.png,1+1=,,2,1,",
    ",tmp.png,1+1=,2,,1,",
    ",tmp.png,1+1=,2,1,,",
    ",",
    ",,",
    ",,,",
    ",,,,",
    ",,,,,",
    ",,,,,,"
  };
}

const std::vector<std::string>& ribi::MultipleChoiceQuestion::GetOptions() const noexcept
{
  return m_options;
}

std::vector<std::string> ribi::MultipleChoiceQuestion::GetValidMultipleChoiceQuestions() noexcept
{
  return {
    "-,1+1=,2,1",
    "tmp.png,1+1=,2,1",
    "-,1+1=,2,1,0,3,4,5,6,7,8,9,0"
  };
}

std::string ribi::MultipleChoiceQuestion::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::MultipleChoiceQuestion::GetVersionHistory() noexcept
{
  return {
    "2011-06-27: version 1.0: initial version",
    "2011-09-16: version 1.1: allow parsing from std::string"
    "2013-09-26: version 1.2: added testing"
  };
}

#ifndef NDEBUG
void ribi::MultipleChoiceQuestion::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Container();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  try
  {
    const boost::scoped_ptr<MultipleChoiceQuestion> q {
      new MultipleChoiceQuestion(
        MultipleChoiceQuestion::GetExampleMultipleChoiceQuestion()
      )
    };
    assert(q);
  }
  catch (std::exception& e)
  {
    assert("MultipleChoiceQuestion::GetExampleMultipleChoiceQuestion()"
        && "must yield a valid MultipleChoiceQuestion");
  }
  //Test valid multiple choice questions for validity
  {
    const std::vector<std::string> valid { GetValidMultipleChoiceQuestions() };
    for (const std::string& s: valid)
    {
      try
      {
        boost::scoped_ptr<MultipleChoiceQuestion> q { new MultipleChoiceQuestion(s) };
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
    const std::vector<std::string> invalid { GetInvalidMultipleChoiceQuestions()  };
    for (const std::string& s: invalid)
    {
      try
      {
        const boost::scoped_ptr<MultipleChoiceQuestion> q { new MultipleChoiceQuestion(s) };
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
  //Test simple get/set
  {
    const std::string filename = "-";
    const std::string question = "1+1=";
    const std::string answer = "2";
    const std::vector<std::string> wrong_answers { "chicken", "cow" };
    const boost::scoped_ptr<MultipleChoiceQuestion> q { new MultipleChoiceQuestion(filename,question,answer,wrong_answers) };
    assert(q->GetFilename() == filename);
    assert(q->GetQuestion() == question);
    assert(q->GetAnswer() == answer);
    assert(q->GetWrongAnswers() == wrong_answers);
    assert(q->GetOptions().size() == wrong_answers.size() + 1); //The options are the incorrect answers and the correct answer(s)
    assert(q->IsCorrect(answer));
    assert(!q->IsCorrect(wrong_answers.at(0)));
    assert(!q->IsCorrect(wrong_answers.at(1)));
  }
  //Test conversion std::string to MultipleChoiceQuestion and back
  {
    const std::vector<std::string> valid { GetValidMultipleChoiceQuestions() };
    for (const std::string& s: valid)
    {
      const boost::scoped_ptr<MultipleChoiceQuestion> q { new MultipleChoiceQuestion(s) };
      assert(s == q->ToStr());
    }
  }
  //Test that ToLines always yields the same result
  {
    const std::vector<std::string> valid { GetValidMultipleChoiceQuestions() };
    for (const std::string& s: valid)
    {
      const boost::scoped_ptr<MultipleChoiceQuestion> q { new MultipleChoiceQuestion(s) };
      const std::vector<std::string> v { q->ToLines() };
      const std::vector<std::string> w { q->ToLines() };
      assert(v == w);
    }
  }
}
#endif

std::vector<std::string> ribi::MultipleChoiceQuestion::ToLines() const noexcept
{
  std::vector<std::string> question_lines;
  question_lines.push_back(this->GetQuestion());
  question_lines.push_back("");
  const std::vector<std::string> w { this->GetOptions() };

  int i=0;
  for (const std::string& s: w)
  {
    std::stringstream t;
    t << '[' << i << "] " << s;
    question_lines.push_back(t.str());
    ++i;
  }

  const int screen_rows { 23 };
  const int question_rows { static_cast<int>(question_lines.size()) };
  const int n_rows { screen_rows - question_rows };

  std::vector<std::string> lines;

  if (!GetFilename().empty())
  {
    int n_cols = 78;

    while (1)
    {
      const boost::shared_ptr<ImageCanvas> canvas {
        new ImageCanvas(GetFilename(),n_cols)
      };
      if (canvas->GetHeight() > n_rows)
      {
        --n_cols;
      }
      else
      {
        lines = canvas->ToStrings();
        break;
      }
      if (n_cols == 5) break;
    }
  }
  std::copy(question_lines.begin(),question_lines.end(),std::back_inserter(lines));
  return lines;
}

std::string ribi::MultipleChoiceQuestion::ToStr() const noexcept
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
    + "," + correct_answers_str
    + ",";
  for (const std::string t: this->GetWrongAnswers()) { s += t + ","; }
  //Remove tailing comma
  assert(!s.empty());
  s.resize(s.size() - 1);
  return s;
}
