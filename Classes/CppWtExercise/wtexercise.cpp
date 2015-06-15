//---------------------------------------------------------------------------
/*
WtExercise, Wt GUI of Exercise
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
//From http://www.richelbilderbeek.nl/CppWtExercise.htm
//---------------------------------------------------------------------------
#include <fstream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WTimer>

#include "exercise.h"
#include "trace.h"
#include "question.h"
#include "questiondialog.h"
#include "wtexercise.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtopenquestiondialog.h"
#include "wtquestiondialog.h"
#pragma GCC diagnostic pop

ribi::WtExercise::Ui::Ui()
  : m_box(new Wt::WGroupBox),
    m_label_score(new Wt::WLabel)
{

}

ribi::WtExercise::WtExercise()
  : m_exercise{},
    m_n_answered(0),
    m_n_correct(0),
    m_ui{},
    m_waiting_time_correct(1000),
    m_waiting_time_incorrect(5000)
{
  assert(m_ui.m_box);
  assert(m_ui.m_label_score);

  TRACE_FUNC();
  this->clear();
  this->addWidget(m_ui.m_box);
  this->addWidget(new Wt::WBreak);
  this->addWidget(m_ui.m_label_score);

  TRACE("ribi::WtExercise::WtExercise #1");

  m_ui.m_label_score->setText("Score: 0/0");

  TRACE("ribi::WtExercise::WtExercise end");
}

void ribi::WtExercise::DisplayCurrentQuestion()
{
  const std::string s = m_exercise->GetCurrentQuestion();

  WtQuestionDialog * question = 0;
  try
  {
    question = new WtOpenQuestionDialog(s);
  }
  catch(std::exception&) {}
  if (!question)
  {
    try
    {
      question = new WtMultipleChoiceQuestionDialog(s);
    }
    catch(std::exception&) {}
  }
  assert(question && "Exercise only contains valid question");

  //Add
  assert(m_ui.m_box);
  m_ui.m_box->clear();
  m_ui.m_box->setContentAlignment(Wt::AlignLeft);
  m_ui.m_box->addWidget(new Wt::WBreak);

  question->m_signal_submitted.connect(
    boost::bind(&ribi::WtExercise::OnSubmittedAnswer,this,boost::lambda::_1));
  m_ui.m_box->addWidget(question);
  m_ui.m_box->addWidget(new Wt::WBreak);

}

const ribi::Exercise * ribi::WtExercise::GetExercise() const
{
  assert(m_exercise);
  return m_exercise.get();
}

std::string ribi::WtExercise::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::WtExercise::GetVersionHistory()
{
  return {
    "2011-09-26: Version 1.0: initial version"
  };
}

void ribi::WtExercise::OnSubmittedAnswer(const bool answered_correct)
{
  if (answered_correct) ++m_n_correct;
  ++m_n_answered;
  m_ui.m_label_score->setText(
    Wt::WString("Score: {1}/{2}").arg(m_n_correct).arg(m_n_answered));
  Wt::WTimer::singleShot(
    answered_correct ? m_waiting_time_correct : m_waiting_time_incorrect,
    boost::bind(&ribi::WtExercise::OnViewedAnswer,this));
}

void ribi::WtExercise::OnViewedAnswer()
{
  this->m_exercise->Next();
  this->DisplayCurrentQuestion();
}

void ribi::WtExercise::SetQuestions(const std::string& filename)
{
  m_exercise.reset(new Exercise(filename));
  DisplayCurrentQuestion();
}

void ribi::WtExercise::SetWaitingTimeCorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_correct = msecs;
}

void ribi::WtExercise::SetWaitingTimeIncorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_incorrect = msecs;
}

