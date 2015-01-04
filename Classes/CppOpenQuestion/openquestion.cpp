//---------------------------------------------------------------------------
/*
OpenQuestion, class for an open question
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "openquestion.h"

#include <cassert>
#include <string>
#include <fstream>
#include <stdexcept>

#include <boost/algorithm/string/split.hpp>
#include <boost/scoped_ptr.hpp>

#include "imagecanvas.h"
#include "openquestionfactory.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

/*
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
*/

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

//const std::vector<std::string>& ribi::OpenQuestion::GetAnswers() const noexcept
//{
//  this->GetCorrectAnswers()
//}




std::string ribi::OpenQuestion::GetVersion() noexcept
{
  return "1.3";
}

std::vector<std::string> ribi::OpenQuestion::GetVersionHistory() noexcept
{
  return {
    "2011-06-27: version 1.0: initial version",
    "2011-09-16: version 1.1: allow parsing from std::string"
    "2013-10-24: version 1.2: added tests",
    "2014-06-05: version 1.3: moved parts to OpenQuestionFactory"
  };
}

#ifndef NDEBUG
void ribi::OpenQuestion::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    try { std::make_shared<ImageCanvas>("",0); } catch (std::logic_error&) { /* fine */ }
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  //Test simple get/set with single answer
  {
    const std::string filename = "-";
    const std::string question = "1+1=";
    const std::string answer_1 = "2";
    const std::vector<std::string> answers { answer_1 };
    const auto q = OpenQuestionFactory().Create(filename,question,answers);
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
    const auto q = OpenQuestionFactory().Create(filename,question,answers);
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
    const auto valid = OpenQuestionFactory().GetValidOpenQuestionStrings();
    for (const std::string& s: valid)
    {
      const auto q = OpenQuestionFactory().Create(s);
      assert(s == q->ToStr());
    }
  }
  //Test that ToLines always yields the same result
  {
    const auto valid = OpenQuestionFactory().GetValidOpenQuestionStrings();
    for (const std::string& s: valid)
    {
      const auto q = OpenQuestionFactory().Create(s);
      const auto v = q->ToLines();
      const auto w = q->ToLines();
      assert(v == w);
    }
  }
}
#endif

std::vector<std::string> ribi::OpenQuestion::ToLines() const noexcept
{
  std::vector<std::string> v;

  const int screen_rows { 23 };
  const int question_rows { 1 };
  const int n_rows { screen_rows - question_rows };
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
        v = canvas->ToStrings();
        break;
      }
      if (n_cols == 5) break;
    }
  }
  v.push_back(this->GetQuestion()); //The one question_row
  return v;
}

std::string ribi::OpenQuestion::ToStr() const noexcept
{
  //Concatenate the correct answer
  assert(!GetCorrectAnswers().empty());
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
