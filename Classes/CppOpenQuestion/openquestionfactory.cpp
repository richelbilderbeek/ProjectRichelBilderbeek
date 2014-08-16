#include "openquestionfactory.h"

#include <cassert>
#include <stdexcept>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include <boost/algorithm/string/split.hpp>
#include <boost/make_shared.hpp>

#include "container.h"
#include "openquestion.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::OpenQuestionFactory::OpenQuestionFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}

boost::shared_ptr<ribi::OpenQuestion>
  ribi::OpenQuestionFactory::Create(const std::string& s
) const
{
  const bool verbose{false};
  if (s.empty())
  {
    throw std::logic_error("An open question must contain text");
  }
  if (s[0] == ',')
  {
    throw std::logic_error("An open question must not start with a comma");
  }
  if (s[s.size() - 1] == ',')
  {
    throw std::logic_error("An open question must not end with a comma");
  }
  if (s.find(",,") != std::string::npos)
  {
    throw std::logic_error("An open question cannot contain two consecutive commas");
  }
  const auto v = Container().SeperateString(s,',');
  if (v.size() != 3)
  {
    if (verbose) { TRACE(s); }
    throw std::logic_error("An open question has exactly three comma-seperated elements");
  }
  const auto filename = v[0];
  const auto question = v[1];
  const auto answers = Container().SeperateString(v[2],'/');
  if (answers.size() == 0)
  {
    throw std::logic_error("An open question has at least one correct answer");
  }
  return Create(filename,question,answers);

}

boost::shared_ptr<ribi::OpenQuestion>
  ribi::OpenQuestionFactory::Create(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers
) const noexcept
{
  boost::shared_ptr<OpenQuestion> openquestion(
    new OpenQuestion(
      filename,question,answers
    )
  );
  return openquestion;
  //assert(!filename.empty() && "Filename must not be empty");
  //assert(FileExists(filename) == true && "File must exists");
  //assert(!question.empty() && "OpenQuestion must not be empty");
  //assert(!correct_answers.empty() && "Correct answer must not be empty");
}

/*
std::vector<std::string> ribi::OpenQuestionFactory::ExtractAnswers(const std::string& input)
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
*/

std::vector<std::string>
  ribi::OpenQuestionFactory::GetInvalidOpenQuestionStrings() const noexcept
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

std::vector<boost::shared_ptr<ribi::OpenQuestion>>
  ribi::OpenQuestionFactory::GetTestOpenQuestions() const noexcept
{
  std::vector<boost::shared_ptr<OpenQuestion>> v;
  for (const auto& s: GetValidOpenQuestionStrings())
  {
    v.push_back(Create(s));
  }
  return v;
}

std::vector<std::string>
  ribi::OpenQuestionFactory::GetValidOpenQuestionStrings() const noexcept
{
  return {
    "-,1+1=,2",
    "tmp.png,1+1=,2/Two",
    "-,1+1=,Two/2/two"
  };
}

std::string ribi::OpenQuestionFactory::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::OpenQuestionFactory::GetVersionHistory() noexcept
{
  return {
    "2014-06-05: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::OpenQuestionFactory::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Container();
  OpenQuestionFactory().GetTestOpenQuestions();
  const TestTimer test_timer(__func__,__FILE__,1.0);
  OpenQuestionFactory f;
  try
  {
    const auto q = f.Create(f.GetExampleOpenQuestionString());
    assert(q);
  }
  catch (std::exception& e)
  {
    assert("OpenQuestionFactory::GetExampleOpenQuestion()"
        && "must yield a valid OpenQuestion");
  }
  //Test valid multiple choice questions for validity
  {
    for (const std::string& s: f.GetValidOpenQuestionStrings())
    {
      try
      {
        const auto q = f.Create(s);
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
    for (const std::string& s: f.GetInvalidOpenQuestionStrings())
    {
      try
      {
        const auto q = f.Create(s);
        TRACE("ERROR");
        TRACE(s);
        assert(!"Invalid questions must be rejected");
        assert(q); //To make the compiler happy
      }
      catch (std::exception& e)
      {
        //OK
      }
    }
  }
}
#endif
