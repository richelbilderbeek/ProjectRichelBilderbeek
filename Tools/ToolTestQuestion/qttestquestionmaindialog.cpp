//---------------------------------------------------------------------------
/*
TestQuestion, tool to test the Question and QuestionDialog classes
Copyright (C) 2011-2012 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestQuestion.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "qttestquestionmaindialog.h"

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "qtopenquestiondialog.h"
#include "qtmultiplechoicequestiondialog.h"
#include "multiplechoicequestion.h"
#include "multiplechoicequestiondialog.h"
#include "openquestion.h"
#include "openquestiondialog.h"
#include "questiondialog.h"
#include "testquestionmaindialog.h"
#include "ui_qttestquestionmaindialog.h"

QtTestQuestionMainDialog::QtTestQuestionMainDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtTestQuestionMainDialog),
    m_dialog(new TestQuestionMainDialog)
{
  ui->setupUi(this);

  BOOST_FOREACH(boost::shared_ptr<QuestionDialog>& dialog,
    m_dialog->GetQuestions())
  {
    //const QuestionDialog * const p = dialog.get();
    if (dynamic_cast<OpenQuestionDialog*>(dialog.get()))
    {
      boost::shared_ptr<QtQuestionDialog> d(
        new QtOpenQuestionDialog(dialog));
      m_dialogs.push_back(d);
      ui->my_layout->addWidget(d.get());
    }
    else if (dynamic_cast<MultipleChoiceQuestionDialog*>(dialog.get()))
    {
      boost::shared_ptr<QtQuestionDialog> d(
        new QtMultipleChoiceQuestionDialog(dialog));
      m_dialogs.push_back(d);
      ui->my_layout->addWidget(d.get());
    }
    else
    {
      assert(!"Should not get here");
    }
  }

  BOOST_FOREACH(const boost::shared_ptr<QtQuestionDialog>& d,m_dialogs)
  {
    d->m_signal_submitted.connect(
      boost::bind(
        &QtTestQuestionMainDialog::OnSubmit,this));
  }
  OnSubmit();
}

QtTestQuestionMainDialog::~QtTestQuestionMainDialog()
{
  delete ui;
}

void QtTestQuestionMainDialog::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}


void QtTestQuestionMainDialog::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) { close(); return; }
}

void QtTestQuestionMainDialog::OnSubmit()
{
  const int n = boost::numeric_cast<int>(m_dialogs.size());
  int n_submitted = 0;
  int n_correct = 0;
  BOOST_FOREACH(const boost::shared_ptr<QtQuestionDialog>& d,m_dialogs)
  {
    if (d->GetDialog()->HasSubmitted())
    {
      ++n_submitted;
      if (d->GetDialog()->IsAnswerCorrect())
      {
        ++n_correct;
      }
    }
  }
  ui->label_score->setText(
    (std::string("Submitted: ")
    + boost::lexical_cast<std::string>(n_submitted)
    + std::string("/")
    + boost::lexical_cast<std::string>(n)
    + std::string(", Correct: ")
    + boost::lexical_cast<std::string>(n_correct)
    + std::string("/")
    + boost::lexical_cast<std::string>(n_submitted)).c_str());
}

