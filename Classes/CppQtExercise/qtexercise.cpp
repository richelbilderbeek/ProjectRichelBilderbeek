//---------------------------------------------------------------------------
/*
QtExercise, Qt GUI of Exercise
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
//From http://www.richelbilderbeek.nl/CppQtExercise.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtexercise.h"

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
#include "qtmultiplechoicequestiondialog.h"
#include "qtopenquestiondialog.h"
#include "qtquestiondialog.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::QtExercise::MyUi::MyUi()
  : m_box(new QGroupBox),
    m_label_score(new QLabel)
{

}

ribi::QtExercise::QtExercise()
  : m_exercise{},
    m_n_answered(0),
    m_n_correct(0),
    m_ui{},
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

void ribi::QtExercise::DisplayCurrentQuestion()
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

  question->GetDialog()->m_signal_submitted.connect(
    boost::bind(&ribi::QtExercise::OnSubmittedAnswer,this,boost::lambda::_1));

}

const ribi::Exercise * ribi::QtExercise::GetExercise() const
{
  assert(m_exercise);
  return m_exercise.get();
}

std::string ribi::QtExercise::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtExercise::GetVersionHistory() noexcept
{
  return {
    "2012-12-23: Version 1.0: initial version"
  };
}

void ribi::QtExercise::OnSubmittedAnswer(const bool answered_correct)
{
  if (answered_correct) ++m_n_correct;
  ++m_n_answered;
  m_ui.m_label_score->setText(
    QString("Score: {1}/{2}").arg(m_n_correct).arg(m_n_answered));
  QTimer::singleShot(
    answered_correct ? m_waiting_time_correct : m_waiting_time_incorrect,
    this,
    SLOT(&ribi::QtExercise::OnViewedAnswer));
}

void ribi::QtExercise::OnViewedAnswer()
{
  this->m_exercise->Next();
  this->DisplayCurrentQuestion();
}

void ribi::QtExercise::SetQuestions(const std::string& filename)
{
  m_exercise.reset(new Exercise(filename));
  DisplayCurrentQuestion();
}

void ribi::QtExercise::SetWaitingTimeCorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_correct = msecs;
}

void ribi::QtExercise::SetWaitingTimeIncorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_incorrect = msecs;
}

