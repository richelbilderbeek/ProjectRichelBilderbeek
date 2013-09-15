//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
Copyright (C) 2011 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppQtOpenQuestionDialog.htm
//---------------------------------------------------------------------------
#include <boost/filesystem.hpp>

#include <Wt/WBreak>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>

#include "openquestion.h"
#include "openquestiondialog.h"
#include "wtopenquestiondialog.h"
//#include "trace.h"

ribi::WtOpenQuestionDialog::Ui::Ui()
  : m_button_submit(new Wt::WPushButton("Submit")),
    m_edit_answer(new Wt::WLineEdit),
    m_stacked_widget(new Wt::WStackedWidget)
{

}

ribi::WtOpenQuestionDialog::WtOpenQuestionDialog(const std::string& question)
  : WtQuestionDialog(
     boost::shared_ptr<QuestionDialog>(new OpenQuestionDialog(
       question))),
    m_ui{}
{
  assert(m_dialog);
  SetQuestion(m_dialog->GetQuestion());
}

ribi::WtOpenQuestionDialog::WtOpenQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog)
  : WtQuestionDialog(dialog),
    m_ui{}
{
  assert(dialog);
  assert(m_dialog);
  SetQuestion(dialog->GetQuestion());
}

const std::string ribi::WtOpenQuestionDialog::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> ribi::WtOpenQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-29: version 1.0: initial version");
  v.push_back("2011-09-15: version 1.1: created internal Ui struct");
  return v;
}

///Set the Question
void ribi::WtOpenQuestionDialog::SetQuestion(
  const boost::shared_ptr<Question>& question)
{
  assert(question);
  assert(m_dialog);

  m_dialog->SetQuestion(question);

  clear();
  setContentAlignment(Wt::AlignCenter);


  if (boost::filesystem::exists(question->GetFilename()))
  {
    this->addWidget(
      new Wt::WImage(question->GetFilename().c_str()));
  }

  const OpenQuestion * const q
    = dynamic_cast<const OpenQuestion *>(question.get());
  assert(q);

  this->addWidget(m_ui.m_stacked_widget);
  //Create the question page
  {
    Wt::WContainerWidget * const page = new Wt::WContainerWidget;
    page->addWidget(new Wt::WLabel(question->GetQuestion().c_str()));
    page->addWidget(new Wt::WBreak);
    page->addWidget(m_ui.m_edit_answer);
    page->addWidget(new Wt::WBreak);
    //Button
    page->addWidget(m_ui.m_button_submit);
    page->addWidget(new Wt::WBreak);
    m_ui.m_button_submit->clicked().connect(
      this,&ribi::WtOpenQuestionDialog::OnButtonSubmitClicked);
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
    page->addWidget(new Wt::WLabel(question->GetQuestion().c_str()));
    page->addWidget(new Wt::WBreak);
    page->addWidget(new Wt::WLabel(q->GetAnswers()[0].c_str()));
    page->addWidget(new Wt::WBreak);
    m_ui.m_stacked_widget->addWidget(page);
  }
  m_ui.m_stacked_widget->setCurrentIndex(0);

}

void ribi::WtOpenQuestionDialog::OnButtonSubmitClicked()
{
  assert(m_dialog->CanSubmit());

  m_dialog->Submit(m_ui.m_edit_answer->text().toUTF8());

  this->m_ui.m_stacked_widget->setCurrentIndex(m_dialog->IsAnswerCorrect()
    ? 1
    : 2);

  m_signal_submitted(m_dialog->IsAnswerCorrect());
}

