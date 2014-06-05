#include "openquestiondialogfactory.h"

#include <cassert>

#include "openquestiondialog.h"
#include "openquestionfactory.h"
#include "trace.h"

ribi::OpenQuestionDialogFactory::OpenQuestionDialogFactory()
{
  #ifndef NDEBUG
  Test();
  #endif
}


boost::shared_ptr<ribi::OpenQuestionDialog> ribi::OpenQuestionDialogFactory::Create(
  const std::string& s
) const
{
  const auto open_question
    = OpenQuestionFactory().Create(s);
  return Create(open_question);
}

boost::shared_ptr<ribi::OpenQuestionDialog>
  ribi::OpenQuestionDialogFactory::Create(
    const std::string& filename,
    const std::string& question,
    const std::vector<std::string>& answers
) const noexcept
{
  const auto open_question
    = OpenQuestionFactory().Create(filename,question,answers);
  return Create(open_question);
}

boost::shared_ptr<ribi::OpenQuestionDialog> ribi::OpenQuestionDialogFactory::Create(
  const boost::shared_ptr<OpenQuestion>& open_question
) const noexcept
{
  assert(open_question);
  boost::shared_ptr<OpenQuestionDialog> dialog(new OpenQuestionDialog);
  assert(dialog);
  dialog->SetOpenQuestion(open_question);
  return dialog;
}

std::vector<boost::shared_ptr<ribi::OpenQuestionDialog>>
  ribi::OpenQuestionDialogFactory::GetTestOpenQuestionDialogs() const noexcept
{
  std::vector<boost::shared_ptr<OpenQuestionDialog>> v;
  for (auto open_question: OpenQuestionFactory().GetTestOpenQuestions())
  {
    v.push_back(Create(open_question));
  }
  return v;
}

std::string ribi::OpenQuestionDialogFactory::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::OpenQuestionDialogFactory::GetVersionHistory() noexcept
{
  return {
    "2014-06-05: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::OpenQuestionDialogFactory::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::OpenQuestionDialogFactory::Test");
  //Test setting the open questions
  for(const std::string& s: OpenQuestionFactory().GetValidOpenQuestionStrings())
  {
    const auto q = OpenQuestionDialogFactory().Create(s);
    assert(q);
  }
  TRACE("Finished ribi::OpenQuestionDialogFactory::Test successfully");
}
#endif
