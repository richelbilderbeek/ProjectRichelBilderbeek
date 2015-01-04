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
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtopenquestiondialog.h"

#include <boost/lambda/lambda.hpp>

#include "fileio.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "trace.h"
#include "ui_qtopenquestiondialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::QtOpenQuestionDialog::QtOpenQuestionDialog(QWidget *parent)
  : QtQuestionDialog(parent),
    ui(new Ui::QtOpenQuestionDialog),
    m_openquestiondialog{}
{
  ui->setupUi(this);

}

ribi::QtOpenQuestionDialog::~QtOpenQuestionDialog() noexcept
{
  delete ui;
}

boost::shared_ptr<const ribi::QuestionDialog> ribi::QtOpenQuestionDialog::GetDialog() const
{
  return m_openquestiondialog;
}

void ribi::QtOpenQuestionDialog::OnOpenQuestionDialogChanged(OpenQuestionDialog * const open_question_dialog) noexcept
{
  assert(open_question_dialog);

  ui->edit_answer->setText(open_question_dialog->GetAnswerInProgress().c_str());

  OnOpenQuestionChanged(open_question_dialog->GetOpenQuestion());
}

void ribi::QtOpenQuestionDialog::OnOpenQuestionChanged(const boost::shared_ptr<OpenQuestion>& open_question) noexcept
{
  assert(open_question);
  if (fileio::FileIo().IsRegularFile(open_question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(open_question->GetFilename().c_str()));
  }

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(open_question->GetQuestion().c_str());
  ui->label_question_again->setText(open_question->GetQuestion().c_str());
  ui->label_answer->setText(open_question->GetCorrectAnswers()[0].c_str());

}

void ribi::QtOpenQuestionDialog::SetDialog(const boost::shared_ptr<QuestionDialog>& dialog)
{
  const bool verbose{false};

  const boost::shared_ptr<OpenQuestionDialog> openquestiondialog
    = boost::dynamic_pointer_cast<OpenQuestionDialog>(dialog);
  if (!openquestiondialog)
  {
    std::stringstream s;
    s << "QtOpenQuestionDialog::SetDialog: not an OpenQuestionDialog '" << dialog->ToStr() << "'\n";
    //this->ui->stackedWidget->setVisible(false);
    //this->ui->image->setVisible(false);
    return;
  }

  //this->ui->stackedWidget->setVisible(true);
  //this->ui->image->setVisible(true);

  assert(openquestiondialog);
  if (m_openquestiondialog == openquestiondialog)
  {
    return;
  }
  if (verbose)
  {
    std::stringstream s;
    s << "Setting openquestiondialog '" << openquestiondialog->ToStr() << "'\n";
  }
  const auto open_question_after = openquestiondialog->GetOpenQuestion();

  bool open_question_changed  = true;

  if (m_openquestiondialog)
  {
    const auto open_question_before = m_openquestiondialog->GetOpenQuestion();

    open_question_changed = open_question_before != open_question_after;

    if (verbose)
    {
      if (open_question_changed)
      {
        std::stringstream s;
        s
          << "open_question will change from "
          << open_question_before->ToStr()
          << " to "
          << open_question_after->ToStr()
          << '\n'
        ;
        TRACE(s.str());
      }
    }
    //Disconnect
    m_openquestiondialog->m_signal_open_question_changed.disconnect(
      boost::bind(&ribi::QtOpenQuestionDialog::OnOpenQuestionDialogChanged,this,boost::lambda::_1)
    );

    m_openquestiondialog->m_signal_request_quit.disconnect(
      boost::bind(&ribi::QtOpenQuestionDialog::OnQuit,this)
    );
    m_openquestiondialog->m_signal_submitted.disconnect(
      boost::bind(&ribi::QtOpenQuestionDialog::OnSubmit,this,boost::lambda::_1)
    );
  }

  //Replace m_example by the new one
  m_openquestiondialog = openquestiondialog;

  assert(m_openquestiondialog->GetOpenQuestion() == open_question_after);

  m_openquestiondialog->m_signal_open_question_changed.connect(
    boost::bind(&ribi::QtOpenQuestionDialog::OnOpenQuestionDialogChanged,this,boost::lambda::_1)
  );
  m_openquestiondialog->m_signal_request_quit.connect(
    boost::bind(&ribi::QtOpenQuestionDialog::OnQuit,this)
  );
  m_openquestiondialog->m_signal_submitted.connect(
    boost::bind(&ribi::QtOpenQuestionDialog::OnSubmit,this,boost::lambda::_1)
  );


  //Emit everything that has changed
  if (open_question_changed)
  {
    m_openquestiondialog->m_signal_open_question_changed(m_openquestiondialog.get());
  }

  assert(openquestiondialog == m_openquestiondialog);
}

std::string ribi::QtOpenQuestionDialog::GetVersion() noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::QtOpenQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-28: version 1.0: initial version",
    "2014-06-04: version 1.1: added SetDialog member function",
    "2014-06-13: version 1.2: support for displaying an answer-in-progress"
  };
}

void ribi::QtOpenQuestionDialog::OnQuit() noexcept
{
  close();
}

void ribi::QtOpenQuestionDialog::OnSubmit(const bool /*was_answer_correct*/) noexcept
{
  //Do the change in GUI as on_button_submit_clicked
  const bool is_correct = m_openquestiondialog->IsAnswerCorrect();
  ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect
  );
}

void ribi::QtOpenQuestionDialog::on_button_submit_clicked() noexcept
{
  assert(m_openquestiondialog);
  assert(!m_openquestiondialog->HasSubmitted());
  m_openquestiondialog->Submit(this->ui->edit_answer->text().toStdString());

  const bool is_correct = m_openquestiondialog->IsAnswerCorrect();
  ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect
  );
}



void ribi::QtOpenQuestionDialog::on_edit_answer_textChanged(const QString &arg1)
{
  m_openquestiondialog->SetAnswerInProgress(arg1.toStdString());
}
