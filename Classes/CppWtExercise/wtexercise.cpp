//---------------------------------------------------------------------------
/*
WtExercise, Wt GUI of Exercise
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
//From http://www.richelbilderbeek.nl/CppWtExercise.htm
//---------------------------------------------------------------------------
#include <fstream>

#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

#include <Wt/WBreak>
#include <Wt/WGroupBox>
#include <Wt/WLabel>
#include <Wt/WTimer>

#include "exercise.h"
#include "trace.h"
#include "wtexercise.h"
#include "wtmultiplechoicequestiondialog.h"
#include "wtopenquestiondialog.h"
#include "wtquestiondialog.h"


WtExercise::Ui::Ui()
  : m_box(new Wt::WGroupBox),
    m_label_score(new Wt::WLabel)
{

}

WtExercise::WtExercise()
  : m_n_answered(0),
    m_n_correct(0),
    m_waiting_time_correct(1000),
    m_waiting_time_incorrect(5000)
{
  assert(ui.m_box);
  assert(ui.m_label_score);

  TRACE_FUNC();
  this->clear();
  this->addWidget(ui.m_box);
  this->addWidget(new Wt::WBreak);
  this->addWidget(ui.m_label_score);

  TRACE("WtExercise::WtExercise #1");

  ui.m_label_score->setText("Score: 0/0");

  TRACE("WtExercise::WtExercise end");
}

void WtExercise::DisplayCurrentQuestion()
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
  assert(ui.m_box);
  ui.m_box->clear();
  ui.m_box->setContentAlignment(Wt::AlignLeft);
  ui.m_box->addWidget(new Wt::WBreak);

  question->m_signal_submitted.connect(
    boost::bind(&WtExercise::OnSubmittedAnswer,this,boost::lambda::_1));
  ui.m_box->addWidget(question);
  ui.m_box->addWidget(new Wt::WBreak);

}

const Exercise * WtExercise::GetExercise() const
{
  assert(m_exercise);
  return m_exercise.get();
}

const std::string WtExercise::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> WtExercise::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-09-26: Version 1.0: initial version");
  return v;
}

void WtExercise::OnSubmittedAnswer(const bool answered_correct)
{
  if (answered_correct) ++m_n_correct;
  ++m_n_answered;
  ui.m_label_score->setText(
    Wt::WString("Score: {1}/{2}").arg(m_n_correct).arg(m_n_answered));
  Wt::WTimer::singleShot(
    answered_correct ? m_waiting_time_correct : m_waiting_time_incorrect,
    boost::bind(&WtExercise::OnViewedAnswer,this));
}

void WtExercise::OnViewedAnswer()
{
  this->m_exercise->Next();
  this->DisplayCurrentQuestion();
}

void WtExercise::SetQuestions(const std::string& filename)
{
  m_exercise.reset(new Exercise(filename));
  DisplayCurrentQuestion();
}

void WtExercise::SetWaitingTimeCorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_correct = msecs;
}

void WtExercise::SetWaitingTimeIncorrect(const int msecs)
{
  assert(msecs >= 0);
  m_waiting_time_incorrect = msecs;
}

