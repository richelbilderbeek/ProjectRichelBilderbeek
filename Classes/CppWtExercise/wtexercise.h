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
#ifndef WTEXERCISE_H
#define WTEXERCISE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/shared_ptr.hpp>

#include <Wt/WContainerWidget>
#pragma GCC diagnostic pop

namespace ribi {

struct Exercise;

///A WtExercise is the Wt dialog of Exercise
struct WtExercise : public Wt::WContainerWidget
{
  ///Construct a WtExercise without questions
  WtExercise();

  ///Obtain the user its score: its number of correctly answered
  ///questions and the total number of questions answered
  std::pair<int,int> GetCurrentScore() const;

  ///Get the Exercise
  const Exercise * GetExercise() const;

  ///Obtain this class its version
  static std::string GetVersion();

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory();

  ///Set the questions
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

  struct Ui
  {
    Ui();
    Wt::WGroupBox * const m_box;
    Wt::WLabel * const m_label_score;
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

#endif // WTEXERCISE_H
