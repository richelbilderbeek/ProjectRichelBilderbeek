#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "hometrainermaindialog.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "openquestion.h"
#include "multiplechoicequestion.h"
#pragma GCC diagnostic pop

ribi::HometrainerMainDialog::HometrainerMainDialog(
  const std::string& filename)
  : HometrainerMainDialog(CreateQuestions(filename))
{

}

ribi::HometrainerMainDialog::HometrainerMainDialog(
  const std::vector<boost::shared_ptr<const ribi::Question> >& questions)
  : m_questions(questions)
{
  if (m_questions.empty())
  {
    throw std::logic_error("HometrainerMainDialog: no valid question");
  }

  #ifndef NDEBUG
  for(const boost::shared_ptr<const Question> question: m_questions) assert(question);
  #endif
}

const std::vector<boost::shared_ptr<const ribi::Question> >
  ribi::HometrainerMainDialog::CreateQuestions(
    const std::string& filename)
{
  if (!IsRegularFile(filename))
  {
    throw std::logic_error("HometrainerMainDialog: no valid file");
  }


  const std::vector<std::string> text { FileToVector(filename) };

  std::vector<boost::shared_ptr<const Question> > v;
  for (const std::string s: text)
  {
    try
    {
      boost::shared_ptr<const Question> q(new OpenQuestion(s));
      v.push_back(q);
      continue;
    }
    catch (std::exception&)
    {
      //Question could not be parsed
    }
    try
    {
      boost::shared_ptr<const Question> q(new MultipleChoiceQuestion(s));
      v.push_back(q);
      continue;
    }
    catch (std::exception&)
    {
      //Question could not be parsed
    }
  }
  return v;
}


const std::vector<std::string> ribi::HometrainerMainDialog::FileToVector(const std::string& filename)
{
  assert(IsRegularFile(filename));
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

bool ribi::HometrainerMainDialog::IsRegularFile(const std::string& filename) noexcept
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}
