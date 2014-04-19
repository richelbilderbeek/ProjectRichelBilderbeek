//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
Copyright (C) 2011-2014 Richel Bilderbeek

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
#include "qtopenquestiondialog.h"

#include "fileio.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "trace.h"
#include "ui_qtopenquestiondialog.h"

#include <QFile>
#pragma GCC diagnostic pop

ribi::QtOpenQuestionDialog::QtOpenQuestionDialog(
  const boost::shared_ptr<OpenQuestionDialog> dialog,
  QWidget *parent)
  : QtQuestionDialog(parent),
    ui(new Ui::QtOpenQuestionDialog),
    m_dialog(dialog)
{
  assert(m_dialog);
  assert(GetDialog());

  ui->setupUi(this);

  const boost::shared_ptr<const OpenQuestion> question {
    m_dialog->GetOpenQuestion()
  };
  assert(question);

  if (fileio::FileIo().IsRegularFile(question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(question->GetFilename().c_str()));
  }

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(question->GetQuestion().c_str());
  ui->label_question_again->setText(question->GetQuestion().c_str());
  ui->label_answer->setText(question->GetCorrectAnswers()[0].c_str());
}

ribi::QtOpenQuestionDialog::~QtOpenQuestionDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<const ribi::QuestionDialog> ribi::QtOpenQuestionDialog::GetDialog() const
{
  return m_dialog;
}

std::string ribi::QtOpenQuestionDialog::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtOpenQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-28: version 1.0: initial version"
  };
}

void ribi::QtOpenQuestionDialog::on_button_submit_clicked() noexcept
{
  assert(!m_dialog->HasSubmitted());
  m_dialog->Submit(this->ui->edit_answer->text().toStdString());

  const bool is_correct = m_dialog->IsAnswerCorrect();
  this->ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect);
}

