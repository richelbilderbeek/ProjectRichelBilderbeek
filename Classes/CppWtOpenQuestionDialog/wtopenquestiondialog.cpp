//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
Copyright (C) 2011-2015 Richel Bilderbeek

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include "wtopenquestiondialog.h"

#include <boost/make_shared.hpp>

#include <Wt/WBreak>
#include <Wt/WImage>
#include <Wt/WLabel>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WStackedWidget>

#include "fileio.h"
#include "openquestion.h"
#include "openquestionfactory.h"
#include "openquestiondialog.h"
//#include "trace.h"
#pragma GCC diagnostic pop

ribi::WtOpenQuestionDialog::Ui::Ui()
  : m_button_submit(new Wt::WPushButton("Submit")),
    m_edit_answer(new Wt::WLineEdit),
    m_stacked_widget(new Wt::WStackedWidget)
{

}

ribi::WtOpenQuestionDialog::WtOpenQuestionDialog(
  const std::string& question)
  : WtQuestionDialog(),
    m_ui{},
    m_dialog(boost::make_shared<ribi::OpenQuestionDialog>())
{
  assert(m_dialog);
  m_dialog->SetOpenQuestion(OpenQuestionFactory().Create(question));
  SetQuestion(m_dialog->GetQuestion());
}

ribi::WtOpenQuestionDialog::WtOpenQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog)
  : WtQuestionDialog(),
    m_ui{},
    m_dialog(boost::dynamic_pointer_cast<OpenQuestionDialog>(dialog))
{
  if (!m_dialog)
  {
    throw std::logic_error("WtOpenQuestionDialog must be supplied an OpenQuestionDialog");
  }
  assert(m_dialog);
  SetQuestion(dialog->GetQuestion());
}

boost::shared_ptr<const ribi::QuestionDialog> ribi::WtOpenQuestionDialog::GetDialog() const noexcept
{
  return m_dialog;
}

boost::shared_ptr<const ribi::OpenQuestionDialog> ribi::WtOpenQuestionDialog::GetOpenQuestionDialog() const noexcept
{
  return m_dialog;
}

std::string ribi::WtOpenQuestionDialog::GetVersion()
{
  return "1.1";
}

std::vector<std::string> ribi::WtOpenQuestionDialog::GetVersionHistory()
{
  return {
    "2011-06-29: version 1.0: initial version",
    "2011-09-15: version 1.1: created internal Ui struct"
  };
}

///Set the Question
void ribi::WtOpenQuestionDialog::SetQuestion(
  const boost::shared_ptr<const Question> question)
{
  assert(question);
  assert(m_dialog);

  #ifdef TODO
  m_dialog->SetQuestion(question.get());
  #endif

  clear();
  setContentAlignment(Wt::AlignCenter);

  if (fileio::FileIo().IsRegularFile(question->GetFilename()))
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
    page->addWidget(new Wt::WLabel(q->GetCorrectAnswers()[0].c_str()));
    page->addWidget(new Wt::WBreak);
    m_ui.m_stacked_widget->addWidget(page);
  }
  m_ui.m_stacked_widget->setCurrentIndex(0);

}

void ribi::WtOpenQuestionDialog::OnButtonSubmitClicked()
{
  assert(!m_dialog->HasSubmitted());

  m_dialog->Submit(m_ui.m_edit_answer->text().toUTF8());

  this->m_ui.m_stacked_widget->setCurrentIndex(m_dialog->IsAnswerCorrect()
    ? 1
    : 2
  );

  m_signal_submitted(m_dialog->IsAnswerCorrect());
}

