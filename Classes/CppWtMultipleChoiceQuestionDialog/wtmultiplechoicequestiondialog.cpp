//---------------------------------------------------------------------------
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
//---------------------------------------------------------------------------
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "wtmultiplechoicequestiondialog.h"
//---------------------------------------------------------------------------
#include <Wt/WBreak>
#include <Wt/WButtonGroup>
#include <Wt/WGroupBox>
#include <Wt/WImage>
#include <Wt/WLabel>
//#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WRadioButton>
#include <Wt/WStackedWidget>
//#include <Wt/WGroupBox>
//---------------------------------------------------------------------------
WtMultipleChoiceQuestionDialog::Ui::Ui()
 : m_button_submit(new Wt::WPushButton("Submit")),
   m_stacked_widget(new Wt::WStackedWidget)
{

}
//---------------------------------------------------------------------------
WtMultipleChoiceQuestionDialog::WtMultipleChoiceQuestionDialog(
  const std::string& s)
  : WtQuestionDialog(
    boost::shared_ptr<QuestionDialog>(
      new MultipleChoiceQuestionDialog(s)))
{
  Show();
}
//---------------------------------------------------------------------------
WtMultipleChoiceQuestionDialog::WtMultipleChoiceQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog)
  : WtQuestionDialog(dialog)
{
  Show();
}
//---------------------------------------------------------------------------
const std::string WtMultipleChoiceQuestionDialog::GetVersion()
{
  return "1.1";
}
//---------------------------------------------------------------------------
const std::vector<std::string> WtMultipleChoiceQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-29: version 1.0: initial version");
  v.push_back("2011-09-15: version 1.1: added internal Ui struct");
  return v;
}
//---------------------------------------------------------------------------
void WtMultipleChoiceQuestionDialog::OnButtonSubmitClicked()
{
  assert(m_dialog->CanSubmit());

  if (std::find_if(
    ui.m_radio_buttons.begin(), ui.m_radio_buttons.end(),
    boost::bind(&Wt::WRadioButton::isChecked,boost::lambda::_1)
      == true) == ui.m_radio_buttons.end()) return;

  const std::string s =
    (*std::find_if(
      ui.m_radio_buttons.begin(), ui.m_radio_buttons.end(),
      boost::bind(&Wt::WRadioButton::isChecked,boost::lambda::_1)
        == true))->text().toUTF8();

  this->m_dialog->Submit(s);

  this->ui.m_stacked_widget->setCurrentIndex(m_dialog->IsAnswerCorrect()
    ? 1
    : 2);

  m_signal_submitted(m_dialog->IsAnswerCorrect());
}
//---------------------------------------------------------------------------
void WtMultipleChoiceQuestionDialog::Show()
{
  const auto question = m_dialog->GetQuestion();
  m_dialog->SetQuestion(question);

  this->setContentAlignment(Wt::AlignCenter);

  if (boost::filesystem::exists(question->GetFilename()))
  {
    this->addWidget(new Wt::WImage(question->GetFilename().c_str()));
  }

  const MultipleChoiceQuestion * const q
    = dynamic_cast<const MultipleChoiceQuestion *>(question.get());
  assert(q);

  this->addWidget(ui.m_stacked_widget);
  //Create the question page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel(question->GetQuestion().c_str()));
    page->addWidget(new Wt::WBreak);
    //RadioButtons
    {
      Wt::WGroupBox * container = new Wt::WGroupBox("Answers");
      container->setContentAlignment(Wt::AlignLeft);
      Wt::WButtonGroup * const group = new Wt::WButtonGroup(container);
      const int n = boost::numeric_cast<int>(q->GetOptions().size());
      for (int i=0;i!=n;++i)
      {
        Wt::WRadioButton * button
          = new Wt::WRadioButton(q->GetOptions()[i].c_str(),container);
        group->addButton(button);
        new Wt::WBreak(container);
        ui.m_radio_buttons.push_back(button);
      }
      page->addWidget(container);
    }
    //Button
    page->addWidget(ui.m_button_submit);
    page->addWidget(new Wt::WBreak);
    ui.m_button_submit->clicked().connect(
      this,&WtMultipleChoiceQuestionDialog::OnButtonSubmitClicked);
    ui.m_stacked_widget->addWidget(page);
  }
  //Create the correct page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel("Correct"));
    page->addWidget(new Wt::WBreak);
    ui.m_stacked_widget->addWidget(page);
  }
  //Create the incorrect page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel("Incorrect"));
    page->addWidget(new Wt::WBreak);
    page->addWidget(new Wt::WLabel(question->GetQuestion().c_str()));
    page->addWidget(new Wt::WBreak);
    page->addWidget(new Wt::WLabel(q->GetAnswer().c_str()));
    page->addWidget(new Wt::WBreak);
    ui.m_stacked_widget->addWidget(page);
  }
  ui.m_stacked_widget->setCurrentIndex(0);
}
//---------------------------------------------------------------------------

