#ifndef HOMETRAINERMAINDIALOG_H
#define HOMETRAINERMAINDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <vector>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct Question;
struct QuestionDialog;

///HometrainerMainDialog loads a collection of questions from file.
///From then on, it selects questions and keeps track of the score.
///The user comminication is done via a QuestionDialog
struct HometrainerMainDialog
{
  ///Load questions from file
  HometrainerMainDialog(const std::string& filename);

  HometrainerMainDialog(const std::vector<boost::shared_ptr<const ribi::Question> >& questions);

  ///Start the command-line version
  void Execute();

  boost::shared_ptr<const Question> GetCurrentQuestion() const noexcept;

  int GetNumberCorrect() const noexcept { return m_n_correct; }
  int GetNumberIncorrect() const noexcept { return m_n_incorrect; }

  ///Get the parsed questions
  std::vector<boost::shared_ptr<const Question>> GetQuestions() const noexcept
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

  ///Interfacing with the user about a certain Question
  boost::shared_ptr<QuestionDialog> m_question_dialog;

  ///The questions loaded
  std::vector<boost::shared_ptr<const Question> > m_questions;

  ///Does the user want to quit?
  bool m_quit;

  ///Create a Question from a std::string
  ///Returns nullptr if the string cannot be converted to a question
  static const boost::shared_ptr<const Question > CreateQuestion(
    const std::string& s) noexcept;

  ///Build the correct dialog for a (derived class of) question
  static boost::shared_ptr<QuestionDialog> CreateQuestionDialog(
    boost::shared_ptr<const Question> question) noexcept;


  static std::vector<boost::shared_ptr<const Question>> CreateQuestions(
    const std::string& filename);

  void DisplayScore() const noexcept;

  ///Create a new question
  void NewQuestion();

  ///Respond to the user requesting to quit
  void OnRequestQuit() noexcept;

  ///Respond to the user submitting an answer
  void OnSubmitted(const bool is_correct) noexcept;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //namespace ribi

#endif // HOMETRAINERMAINDIALOG_H
