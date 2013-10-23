#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "hometrainermaindialog.h"

#include <cassert>
#include <fstream>
#include <stdexcept>

#include "fileio.h"
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
  : m_current_question_index(0),
    m_n_correct(0),
    m_n_incorrect(0),
    m_questions(questions)

{
  if (m_questions.empty())
  {
    throw std::logic_error("HometrainerMainDialog: no valid question");
  }

  #ifndef NDEBUG
  for(const boost::shared_ptr<const Question> question: m_questions) assert(question);
  #endif
}

const std::string ribi::HometrainerMainDialog::AskUserForInput() const noexcept
{
  std::string t;
  std::getline(std::cin,t);
  return t;
}

const std::vector<boost::shared_ptr<const ribi::Question> >
  ribi::HometrainerMainDialog::CreateQuestions(
    const std::string& filename)
{
  if (!fileio::IsRegularFile(filename))
  {
    throw std::logic_error("HometrainerMainDialog: no valid file");
  }


  const std::vector<std::string> text { fileio::FileToVector(filename) };

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

void ribi::HometrainerMainDialog::DisplayScore() const noexcept
{
  const int total = m_n_correct + m_n_incorrect;
  const double fraction_correct = static_cast<double>(m_n_correct) / static_cast<double>(total);
  const int percentage_correct = static_cast<int>(100.0 * fraction_correct);

  std::cout
    << "Current score: "
    << m_n_correct
    << " / "
    << total
    << " ("
    << percentage_correct
    << "%)"
    << '\n';
}

void ribi::HometrainerMainDialog::Execute()
{
  assert(!m_questions.empty());
  if (m_questions.empty())
  {
    throw std::logic_error("HometrainerMainDialog: must have questions");
  }

  while (1)
  {
    SetQuestion(GetCurrentQuestion());
    const std::string s = AskUserForInput();
    Submit(s);
    DisplayScore();
  }
}

const boost::shared_ptr<const ribi::Question> ribi::HometrainerMainDialog::GetCurrentQuestion() const noexcept
{
  assert(m_current_question_index < static_cast<int>(GetQuestions().size()));
  return GetQuestions()[m_current_question_index];
}


void ribi::HometrainerMainDialog::NewQuestion()
{
  ++m_current_question_index;
  if (m_current_question_index == static_cast<int>(m_questions.size()))
  {
    std::random_shuffle(m_questions.begin(),m_questions.end());
    m_current_question_index = 0;
  }
  assert(m_current_question_index < static_cast<int>(m_questions.size()));
  SetQuestion(m_questions[m_current_question_index]);
}

void ribi::HometrainerMainDialog::Submit(const std::string& answer_from_user)
{
  const bool is_correct = this->GetCurrentQuestion()->IsCorrect(answer_from_user);
  if (is_correct) ++m_n_correct; else ++m_n_incorrect;
  NewQuestion();
}

void ribi::HometrainerMainDialog::SetQuestion(const boost::shared_ptr<const Question> s)
{
  std::cout << (*s);
}
