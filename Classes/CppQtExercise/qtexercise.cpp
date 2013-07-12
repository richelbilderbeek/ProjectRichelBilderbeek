//---------------------------------------------------------------------------
/*
QtExercise, Qt GUI of Exercise
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
//From http://www.richelbilderbeek.nl/CppQtExercise.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

#include <fstream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>

#include "exercise.h"
#include "multiplechoicequestiondialog.h"
#include "openquestiondialog.h"
#include "qtexercise.h"
#include "qtmultiplechoicequestiondialog.h"
#include "qtopenquestiondialog.h"
#include "qtquestiondialog.h"
#include "trace.h"

QtExercise::MyUi::MyUi()
  : m_box(new QGroupBox),
    m_label_score(new QLabel)
{

}

QtExercise::QtExercise()
  : m_n_answered(0),
    m_n_correct(0),
    m_waiting_time_correct(1000),
    m_waiting_time_incorrect(5000)
{
  assert(m_ui.m_box);
  assert(m_ui.m_label_score);

  QVBoxLayout * const layout = new QVBoxLayout;
  this->setLayout(layout);
  layout->addWidget(m_ui.m_box);
  layout->addWidget(m_ui.m_label_score);

  m_ui.m_label_score->setText("Score: 0/0");
}

void QtExercise::DisplayCurrentQuestion()
{
  const std::string s = m_exercise->GetCurrentQuestion();

  QtQuestionDialog * question = 0;
  try
  {
    const boost::shared_ptr<OpenQuestionDialog> d(new OpenQuestionDialog(s));
    question = new QtOpenQuestionDialog(d);
  }
  catch(std::exception&) {}
  if (!question)
  {
    try
    {
      const boost::shared_ptr<MultipleChoiceQuestionDialog> d(new MultipleChoiceQuestionDialog(s));
      question = new QtMultipleChoiceQuestionDialog(d);
    }
    catch(std::exception&) {}
  }
  assert(question && "Exercise only contains valid question");

  //Add QtQuestionDialog
  assert(m_ui.m_box);
  if (m_ui.m_box->layout()) delete m_ui.m_box->layout();
  QVBoxLayout * const layout = new QVBoxLayout;
  m_ui.m_box->setLayout(layout);
  layout->addWidget(question);

  question->m_signal_submitted.connect(
    boost::bind(&QtExercise::OnSubmittedAnswer,this,boost::lambda::_1));

}

const Exercise * QtExercise::GetExercise() const
{
  assert(m_exercise);
  return m_exercise.get();
}

const std::string QtExercise::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> QtExercise::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2012-12-23: Version 1.0: initial version");
  return v;
}

void QtExercise::OnSubmittedAnswer(const bool answered_correct)
{
  if (answered_correct) ++m_n_correct;
  ++m_n_answered;
  m_ui.m_label_score->setText(
    QString("Score: {1}/{2}").arg(m_n_correct).arg(m_n_answered));
  QTimer::singleShot(
    answered_correct ? m_waiting_time_correct : m_waiting_time_incorrect,
    this,
    SLOT(&QtExercise::OnViewedAnswer));
}

void QtExercise::OnViewedAnswer()
{
  this->m_exercise->Next();
  this->DisplayCurrentQuestion();
}

void QtExercise::SetQuestions(const std::string& filename)
{
  m_exercise.reset(new Exercise(filename));
  DisplayCurrentQuestion();
}

void QtExercise::SetWaitingTimeCorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_correct = msecs;
}

void QtExercise::SetWaitingTimeIncorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_incorrect = msecs;
}

