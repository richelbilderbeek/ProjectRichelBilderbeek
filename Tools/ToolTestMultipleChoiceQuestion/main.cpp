#include <iostream>
#include <boost/scoped_ptr.hpp>
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"

template <typename T>
const T AskUserForInput()
{
  T t;
  std::getline(std::cin,t);
  return t;
}

int main()
{
  const std::string default_question = "-,1+1=,2,3,4,0,1";

  #ifndef NDEBUG
  {
    boost::scoped_ptr<ribi::MultipleChoiceQuestion> q {
      new ribi::MultipleChoiceQuestion(default_question)
    };
    assert(q->GetAnswer() == std::string("2"));
  }
  #endif
  std::cout << "Please enter a multiple choice question.\n";
  std::cout << "Press enter to submit '" << default_question << "'\n";
  std::string question_str = AskUserForInput<std::string>();
  if (question_str.empty()) question_str = default_question;

  try
  {
    new ribi::MultipleChoiceQuestion(question_str);
  }
  catch (std::exception&)
  {
    std::cout << "Invalid mutiple choice question input.\n";
    std::cout << "Please enter an example like '" << default_question << "'\n";
    return 1;
  }
  const boost::scoped_ptr<ribi::MultipleChoiceQuestionDialog> dialog {
    new ribi::MultipleChoiceQuestionDialog(question_str)
  };

  std::cout << "Please submit an answer.\n";
  const std::string answer_str = AskUserForInput<std::string>();

  dialog->Submit(answer_str);

  if (dialog->IsAnswerCorrect())
  {
    std::cout << "Correct!\n";
  }
  else
  {
    std::cout << "Incorrect!\n";
    std::cout << "Correct answers are:\n";
    for(const std::string& s: dialog->GetQuestion()->GetCorrectAnswers())
    {
      std::cout << s << '\n';
    }
  }
}
