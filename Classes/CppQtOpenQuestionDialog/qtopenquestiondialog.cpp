//---------------------------------------------------------------------------
/*
QtOpenQuestionDialog, Qt dialog for OpenQuestionDialog
Copyright (C) 2011-2013 Richel Bilderbeek

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
//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qtopenquestiondialog.h"

#include "openquestion.h"
#include "openquestiondialog.h"
//#include "trace.h"
#include "ui_qtopenquestiondialog.h"

#include <QFile>

QtOpenQuestionDialog::QtOpenQuestionDialog(QWidget *parent) 
  : QtQuestionDialog(
      boost::shared_ptr<QuestionDialog>(
        new OpenQuestionDialog(
          boost::shared_ptr<OpenQuestion>(
            new OpenQuestion("*","*",{"*"} )))),
    parent),
    ui(new Ui::QtOpenQuestionDialog)
{
  ui->setupUi(this);
}

QtOpenQuestionDialog::QtOpenQuestionDialog(
  const boost::shared_ptr<QuestionDialog>& dialog,
  QWidget *parent)
  : QtQuestionDialog(dialog,parent),
    ui(new Ui::QtOpenQuestionDialog)
    //m_dialog(new OpenQuestionDialog(question))
{
  ui->setupUi(this);
  assert(dialog);
  SetQuestion(dialog->GetQuestion());
}

QtOpenQuestionDialog::~QtOpenQuestionDialog()
{
  delete ui;
}

const std::string QtOpenQuestionDialog::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtOpenQuestionDialog::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-06-28: version 1.0: initial version");
  return v;
}

///Set the Question
void QtOpenQuestionDialog::SetQuestion(
  const boost::shared_ptr<Question>& question)
{
  m_dialog->SetQuestion(question);

  if (QFile::exists(question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(question->GetFilename().c_str()));
  }

  const OpenQuestion * const q
    = dynamic_cast<const OpenQuestion *>(question.get());
  assert(q);

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(question->GetQuestion().c_str());
  ui->label_question_again->setText(question->GetQuestion().c_str());
  ui->label_answer->setText(q->GetAnswers()[0].c_str());
}

void QtOpenQuestionDialog::on_button_submit_clicked()
{
  assert(m_dialog->CanSubmit());
  m_dialog->Submit(this->ui->edit_answer->text().toStdString());

  const bool is_correct = m_dialog->IsAnswerCorrect();
  this->ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect);

  m_signal_submitted(is_correct);
}

