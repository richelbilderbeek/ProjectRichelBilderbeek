#include "wtmultiplechoicequestiondialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/bind.hpp>

#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/make_shared.hpp>

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

#include "fileio.h"
#include "multiplechoicequestiondialog.h"
#include "multiplechoicequestion.h"
#pragma GCC diagnostic pop

ribi::WtMultipleChoiceQuestionDialog::Ui::Ui()
 : m_button_submit(new Wt::WPushButton("Submit")),
   m_radio_buttons{},
   m_stacked_widget(new Wt::WStackedWidget)
{

}


ribi::WtMultipleChoiceQuestionDialog::WtMultipleChoiceQuestionDialog(
  const std::string& s)
  : m_ui{},
    m_dialog(boost::make_shared<MultipleChoiceQuestionDialog>(s))
{
  Show();
}

ribi::WtMultipleChoiceQuestionDialog::WtMultipleChoiceQuestionDialog(
  const boost::shared_ptr<MultipleChoiceQuestionDialog>& dialog)
  : m_ui{},
    m_dialog(dialog)
{
  Show();
}

boost::shared_ptr<const ribi::QuestionDialog> ribi::WtMultipleChoiceQuestionDialog::GetDialog() const noexcept
{
  return m_dialog;
}

boost::shared_ptr<const ribi::MultipleChoiceQuestionDialog> ribi::WtMultipleChoiceQuestionDialog::GetMultipleChoiceQuestionDialog() const noexcept
{
  return m_dialog;
}

std::string ribi::WtMultipleChoiceQuestionDialog::GetVersion()
{
  return "1.1";
}

std::vector<std::string> ribi::WtMultipleChoiceQuestionDialog::GetVersionHistory()
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2011-09-15: version 1.1: added internal Ui struct"
  };
}

void ribi::WtMultipleChoiceQuestionDialog::OnButtonSubmitClicked()
{
  assert(!m_dialog->HasSubmitted());

  if (std::find_if(
    m_ui.m_radio_buttons.begin(), m_ui.m_radio_buttons.end(),
    boost::bind(&Wt::WRadioButton::isChecked,boost::lambda::_1)
      == true) == m_ui.m_radio_buttons.end()) return;

  const std::string s =
    (*std::find_if(
      m_ui.m_radio_buttons.begin(), m_ui.m_radio_buttons.end(),
      boost::bind(&Wt::WRadioButton::isChecked,boost::lambda::_1)
        == true))->text().toUTF8();

  this->m_dialog->Submit(s);

  this->m_ui.m_stacked_widget->setCurrentIndex(m_dialog->IsAnswerCorrect()
    ? 1
    : 2);

  m_signal_submitted(m_dialog->IsAnswerCorrect());
}

void ribi::WtMultipleChoiceQuestionDialog::Show()
{
  const auto question = m_dialog->GetMultipleChoiceQuestion();
  //const auto question = m_dialog->GetMultipleChoiceQuestion();
  //m_dialog->SetQuestion(question);

  this->setContentAlignment(Wt::AlignCenter);


  if (ribi::fileio::FileIo().IsRegularFile(GetDialog()->GetQuestion()->GetFilename()))
  {
    this->addWidget(new Wt::WImage(GetDialog()->GetQuestion()->GetFilename().c_str()));
  }

  const MultipleChoiceQuestion * const q
    = dynamic_cast<const MultipleChoiceQuestion *>(GetDialog()->GetQuestion().get());
  assert(q);

  this->addWidget(m_ui.m_stacked_widget);
  //Create the question page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel(GetDialog()->GetQuestion()->GetQuestion().c_str()));
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
        m_ui.m_radio_buttons.push_back(button);
      }
      page->addWidget(container);
    }
    //Button
    page->addWidget(m_ui.m_button_submit);
    page->addWidget(new Wt::WBreak);
    m_ui.m_button_submit->clicked().connect(
      this,&ribi::WtMultipleChoiceQuestionDialog::OnButtonSubmitClicked);
    m_ui.m_stacked_widget->addWidget(page);
  }
  //Create the correct page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel("Correct"));
    page->addWidget(new Wt::WBreak);
    m_ui.m_stacked_widget->addWidget(page);
  }
  //Create the incorrect page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel("Incorrect"));
    page->addWidget(new Wt::WBreak);
    page->addWidget(new Wt::WLabel(GetDialog()->GetQuestion()->GetQuestion().c_str()));
    page->addWidget(new Wt::WBreak);
    page->addWidget(new Wt::WLabel(q->GetAnswer().c_str()));
    page->addWidget(new Wt::WBreak);
    m_ui.m_stacked_widget->addWidget(page);
  }
  m_ui.m_stacked_widget->setCurrentIndex(0);
}
