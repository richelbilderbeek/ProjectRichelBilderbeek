//---------------------------------------------------------------------------
/*
QtExercise, Qt GUI of Exercise
Copyright (C) 2012 Richel Bilderbeek

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
#ifndef QTEXERCISE_H
#define QTEXERCISE_H

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "qthideandshowdialog.h"

struct QGroupBox;
struct QLabel;

namespace ribi {

struct Exercise;

///A QtExercise is the Qt dialog of Exercise
struct QtExercise : public QtHideAndShowDialog
{
  ///Construct a QtExercise without questions
  QtExercise();
  ~QtExercise() noexcept {}

  ///Obtain the user its score: its number of correctly answered
  ///questions and the total number of questions answered
  const std::pair<int,int> GetCurrentScore() const;

  ///Get the Exercise
  const Exercise * GetExercise() const;

  ///Obtain this class its version
  static const std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Set the questions, read from a file
  ///Throws std::logic_error if file does not exist
  ///Throws std::runtime_error if file does not contain a single question
  void SetQuestions(const std::string& filename);

  ///Set the time the user has to wait when he/she answered correctly, in milliseconds
  void SetWaitingTimeCorrect(const int msecs);

  ///Set the time the user has to wait when he/she answered incorrectly, in milliseconds
  void SetWaitingTimeIncorrect(const int msecs);

  private:
  ///The Exercise
  boost::shared_ptr<Exercise> m_exercise;

  ///The number of answered questions
  int m_n_answered;

  ///The number of correctly answered questions
  int m_n_correct;

  struct MyUi
  {
    MyUi();
    QGroupBox * const m_box;
    QLabel * const m_label_score;
  } m_ui;

  ///The time the user has to wait when he/she answered correctly, in milliseconds
  int m_waiting_time_correct;

  ///The time the user has to wait when he/she answered incorrectly, in milliseconds
  int m_waiting_time_incorrect;

  ///Displays m_dialog its current question
  void DisplayCurrentQuestion();

  ///Respond to the client having answered a question
  void OnSubmittedAnswer(const bool answered_correct);

  ///Respond to the client having viewed the answer of a question
  void OnViewedAnswer();
};

} //~namespace ribi

#endif // QTEXERCISE_H
