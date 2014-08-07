#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "hometrainermaindialog.h"

#include <cassert>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>

#include "fileio.h"
#include "openquestion.h"
#include "openquestionfactory.h"
#include "openquestiondialog.h"
#include "openquestiondialogfactory.h"
#include "questiondialog.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::HometrainerMainDialog::HometrainerMainDialog(
  const std::string& filename)
  : HometrainerMainDialog(CreateQuestions(filename))
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::HometrainerMainDialog::HometrainerMainDialog(
  const std::vector<boost::shared_ptr<const ribi::Question> >& questions)
  : m_current_question_index(0),
    m_n_correct(0),
    m_n_incorrect(0),
    m_question_dialog{},
    m_questions(questions),
    m_quit(false)

{
  #ifndef NDEBUG
  Test();
  #endif
  if (m_questions.empty())
  {
    throw std::logic_error("HometrainerMainDialog: no valid question");
  }

  #ifndef NDEBUG
  for(const boost::shared_ptr<const Question> question: m_questions) assert(question);
  #endif

  #ifdef NDEBUG
  //Only randomize in release mode
  std::srand(std::time(0));
  #endif

  std::random_shuffle(m_questions.begin(),m_questions.end());
}

const boost::shared_ptr<const ribi::Question> ribi::HometrainerMainDialog::CreateQuestion(
  const std::string& s) noexcept
{
  try
  {
    const auto q = OpenQuestionFactory().Create(s);
    //const boost::shared_ptr<const Question> q(new OpenQuestion(s));
    assert(q);
    return q;
  }
  catch (std::exception&)
  {
    //Question could not be parsed
  }
  try
  {
    //const auto q = MultipleChoiceQuestionFactory().Create(s);
    const boost::shared_ptr<const Question> q(new MultipleChoiceQuestion(s));
    assert(q);
    return q;
  }
  catch (std::exception&)
  {
    //Question could not be parsed
  }
  boost::shared_ptr<const ribi::Question> q;
  assert(!q);
  return q;
}

boost::shared_ptr<ribi::QuestionDialog> ribi::HometrainerMainDialog::CreateQuestionDialog(
  boost::shared_ptr<const Question> question) noexcept
{
  assert(question);
  //Open q
  try
  {
    const auto d = OpenQuestionDialogFactory().Create(question->ToStr());
    if (d) return d;
  }
  catch (std::logic_error&)
  {
    //OK
  }
  {
    const boost::shared_ptr<const MultipleChoiceQuestion> mc_question {
      boost::dynamic_pointer_cast<const MultipleChoiceQuestion>(question)
    };
    if (mc_question)
    {
      assert(mc_question);
      const boost::shared_ptr<ribi::QuestionDialog> d {
        new MultipleChoiceQuestionDialog(mc_question)
      };
      assert(d);
      return d;
    }
  }
  assert(!"Should not get here");
  throw std::logic_error("ribi::HometrainerMainDialog::CreateQuestionDialog: unimplemented question type");
}

std::vector<boost::shared_ptr<const ribi::Question> >
  ribi::HometrainerMainDialog::CreateQuestions(
    const std::string& filename)
{
  if (!fileio::FileIo().IsRegularFile(filename))
  {
    throw std::logic_error("HometrainerMainDialog: no valid file");
  }
  const std::vector<std::string> text { fileio::FileIo().FileToVector(filename) };

  std::vector<boost::shared_ptr<const Question> > v;
  for (const std::string s: text)
  {
    const boost::shared_ptr<const Question> q = CreateQuestion(s);
    //q will be nullptr if no Question could be created
    if (q)
    {
      v.push_back(q);
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
    ///Prepare the current question
    assert(GetCurrentQuestion());
    m_question_dialog = CreateQuestionDialog(GetCurrentQuestion());
    assert(m_question_dialog);
    assert(m_question_dialog->GetQuestion());
    m_question_dialog->m_signal_submitted.connect(
      boost::bind(&ribi::HometrainerMainDialog::OnSubmitted,this,boost::lambda::_1));
    m_question_dialog->m_signal_request_quit.connect(
      boost::bind(&ribi::HometrainerMainDialog::OnRequestQuit,this));

    //Interface with the user about the current question
    //const std::string s = AskUserForInput();
    //Submit(s);
    //DisplayScore();
    m_question_dialog->Execute();

    DisplayScore();

    if (m_quit) return;

    ///Set up a next question
    NewQuestion();
  }
}

boost::shared_ptr<const ribi::Question> ribi::HometrainerMainDialog::GetCurrentQuestion() const noexcept
{
  assert(m_current_question_index < static_cast<int>(GetQuestions().size()));
  const boost::shared_ptr<const ribi::Question> question {
    GetQuestions()[m_current_question_index]
  };
  assert(question);
  return question;
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
}

void ribi::HometrainerMainDialog::OnRequestQuit() noexcept
{
  m_quit = true;
}

void ribi::HometrainerMainDialog::OnSubmitted(const bool is_correct) noexcept
{
  if (is_correct) ++m_n_correct; else ++m_n_incorrect;
}

void ribi::HometrainerMainDialog::Submit(const std::string& answer_from_user)
{
  const bool is_correct = this->GetCurrentQuestion()->IsCorrect(answer_from_user);
  if (is_correct) ++m_n_correct; else ++m_n_incorrect;
  NewQuestion();
}

#ifndef NDEBUG
void ribi::HometrainerMainDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    OpenQuestionFactory();
    {
      const std::string q{MultipleChoiceQuestion::GetValidMultipleChoiceQuestions()[0]};
      boost::shared_ptr<MultipleChoiceQuestion> m{new MultipleChoiceQuestion(q)};
      boost::shared_ptr<MultipleChoiceQuestionDialog> d{new MultipleChoiceQuestionDialog(m)};
    }
    { boost::shared_ptr<OpenQuestionDialog> d{new OpenQuestionDialog};}
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  for(const std::string& s: OpenQuestionFactory().GetValidOpenQuestionStrings())
  {
    assert(CreateQuestion(s));
    assert(CreateQuestionDialog(CreateQuestion(s)));
  }
  for(const std::string& s: MultipleChoiceQuestion::GetValidMultipleChoiceQuestions())
  {
    assert(CreateQuestion(s));
    assert(CreateQuestionDialog(CreateQuestion(s)));
  }

}
#endif
