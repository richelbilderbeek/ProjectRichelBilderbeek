#ifndef HOMETRAINERMAINDIALOG_H
#define HOMETRAINERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <vector>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct Question;

struct HometrainerMainDialog
{
  ///Load questions from file
  HometrainerMainDialog(const std::string& filename);

  HometrainerMainDialog(const std::vector<boost::shared_ptr<const ribi::Question> >& questions);

  ///Start the command-line version
  void Execute();

  const boost::shared_ptr<const Question> GetCurrentQuestion() const noexcept;

  int GetNumberCorrect() const noexcept { return m_n_correct; }
  int GetNumberIncorrect() const noexcept { return m_n_incorrect; }

  ///Get the parsed questions
  const std::vector<boost::shared_ptr<const Question> > GetQuestions() const noexcept
  {
    return m_questions;
  }


  void Submit(const std::string& answer_from_user);

  private:
  ///The current question its index
  int m_current_question_index;

  ///Number of correct answers
  int m_n_correct;

  ///Number of incorrect answers
  int m_n_incorrect;

  ///The questions loaded
  std::vector<boost::shared_ptr<const Question> > m_questions;

  const std::string AskUserForInput() const noexcept;

  static const std::vector<boost::shared_ptr<const Question> > CreateQuestions(
    const std::string& filename);


  void DisplayScore() const noexcept;

  ///Create a new question
  void NewQuestion();

  void OnSubmitted(const bool is_correct);

  ///Display the question
  void SetQuestion(const boost::shared_ptr<const Question> s);
};

} //namespace ribi

#endif // HOMETRAINERMAINDIALOG_H
