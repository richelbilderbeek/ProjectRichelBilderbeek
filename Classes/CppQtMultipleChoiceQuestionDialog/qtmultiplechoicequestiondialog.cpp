//---------------------------------------------------------------------------
/*
QtMultipleChoiceQuestionDialog, Qt dialog for MultipleChoiceQuestion
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
//From http://www.richelbilderbeek.nl/QtMultipleChoiceQuestionDialog.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtmultiplechoicequestiondialog.h"

#include <array>
#include <boost/bind.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QFile>

#include "fileio.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "qtquestiondialog.h"
#include "questiondialog.h"
#include "ui_qtmultiplechoicequestiondialog.h"

#pragma GCC diagnostic pop

/*
ribi::QtMultipleChoiceQuestionDialog::QtMultipleChoiceQuestionDialog(QWidget *parent)
  : QtQuestionDialog(parent),
    ui(new Ui::QtMultipleChoiceQuestionDialog),
    m_dialog(
      new MultipleChoiceQuestionDialog(
        boost::shared_ptr<MultipleChoiceQuestion>(
          new MultipleChoiceQuestion(
            "*","1+1=","2",{"1","3","4"}))))
{
  assert(m_dialog);
  assert(GetDialog());

  ui->setupUi(this);
}
*/

ribi::QtMultipleChoiceQuestionDialog::QtMultipleChoiceQuestionDialog(
  const boost::shared_ptr<MultipleChoiceQuestionDialog>& dialog,
  QWidget *parent)
  : QtQuestionDialog(parent),
    ui(new Ui::QtMultipleChoiceQuestionDialog),
    m_dialog(dialog)
{
  assert(m_dialog);
  assert(GetDialog());

  ui->setupUi(this);
  //this->SetQuestion(m_dialog->GetMultipleChoiceQuestion());

  const boost::shared_ptr<const MultipleChoiceQuestion> question {
    m_dialog->GetMultipleChoiceQuestion()
  };
  assert(question);

  if (fileio::IsRegularFile(question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(question->GetFilename().c_str()));
  }

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(question->GetQuestion().c_str());
  ui->label_question_again->setText(question->GetQuestion().c_str());
  ui->label_answer->setText(question->GetAnswer().c_str());

  const int sz = 7;
  const std::array<QRadioButton*,sz> buttons {
    { ui->radio_1, ui->radio_2, ui->radio_3, ui->radio_4, ui->radio_5, ui->radio_6, ui->radio_7 }
  };
  const std::vector<std::string> options = question->GetOptions();
  static_assert(sz == static_cast<int>(buttons.size()),"std::array<T,sz> will have size sz");
  assert(sz >= boost::numeric_cast<int>(options.size()));
  for (int i = 0; i!=sz; ++i)
  {
    if (i < boost::numeric_cast<int>(options.size()))
    {
      buttons[i]->setText(options[i].c_str());
    }
    else
    {
      buttons[i]->setVisible(false);
    }
  }

}

ribi::QtMultipleChoiceQuestionDialog::~QtMultipleChoiceQuestionDialog() noexcept
{
  delete ui;
}

const boost::shared_ptr<const ribi::QuestionDialog> ribi::QtMultipleChoiceQuestionDialog::GetDialog() const
{
  return m_dialog;
}

std::string ribi::QtMultipleChoiceQuestionDialog::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtMultipleChoiceQuestionDialog::GetVersionHistory() noexcept
{
  return {
    "2011-06-28: version 1.0: initial version"
  };
}
/*
void ribi::QtMultipleChoiceQuestionDialog::SetQuestion(
  const boost::shared_ptr<const MultipleChoiceQuestion>& question) noexcept
{
  m_dialog->SetQuestion(question);

  if (QFile::exists(question->GetFilename().c_str()))
  {
    ui->image->setPixmap(QPixmap(question->GetFilename().c_str()));
  }

  const MultipleChoiceQuestion * const q
    = dynamic_cast<const MultipleChoiceQuestion *>(question.get());
  assert(q);

  ui->stackedWidget->setCurrentWidget(ui->page_question);
  ui->label_question->setText(question->GetQuestion().c_str());
  ui->label_question_again->setText(q->GetQuestion().c_str());
  ui->label_answer->setText(q->GetAnswer().c_str());


  const int sz = 7;
  const std::array<QRadioButton*,sz> buttons
    = { ui->radio_1, ui->radio_2, ui->radio_3, ui->radio_4, ui->radio_5, ui->radio_6, ui->radio_7 };
  const std::vector<std::string> options = q->GetOptions();
  static_assert(sz == buttons.size(),"std::array<T,sz> will have size sz");
  assert(sz >= boost::numeric_cast<int>(options.size()));
  for (int i = 0; i!=sz; ++i)
  {
    if (i < boost::numeric_cast<int>(options.size()))
    {
      buttons[i]->setText(options[i].c_str());
    }
    else
    {
      buttons[i]->setVisible(false);
    }
  }


}
*/

void ribi::QtMultipleChoiceQuestionDialog::on_button_submit_clicked() noexcept
{
  assert(!m_dialog->HasSubmitted());
  const std::vector<const QRadioButton* > buttons
    = { ui->radio_1, ui->radio_2, ui->radio_3, ui->radio_4, ui->radio_5, ui->radio_6 };

  if (std::find_if(
    buttons.begin(), buttons.end(),
    boost::bind(&QRadioButton::isChecked,boost::lambda::_1)
      == true) == buttons.end()) return;

  const std::string index {
    boost::lexical_cast<std::string>(
      std::distance(
        buttons.begin(),
        std::find_if(
          buttons.begin(), buttons.end(),
          boost::bind(&QRadioButton::isChecked,boost::lambda::_1) == true
        )
      )
    )
  };


  this->m_dialog->Submit(index);

  const bool is_correct = m_dialog->IsAnswerCorrect();

  this->ui->stackedWidget->setCurrentWidget(is_correct
    ? ui->page_correct
    : ui->page_incorrect);
}

