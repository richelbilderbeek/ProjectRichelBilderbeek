//---------------------------------------------------------------------------
/*
Exercise, a collection of Questions
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
//From http://www.richelbilderbeek.nl/CppExercise.htm
//---------------------------------------------------------------------------
#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

namespace ribi {

///A Exercise is a collection of questions
struct Exercise
{
  ///Construct a Exercise from file
  ///The file needs to contain at least one question
  ///Throws std::logic_error if file does not exist
  ///Throws std::runtime_error if file does not contain a single question
  explicit Exercise(const std::string& filename);

  ///Read the current question
  std::string GetCurrentQuestion() const noexcept;

  ///Get the number of questions, will be at least one
  int GetNumberOfQuestions() const noexcept;

  ///Obtain this class its version
  static std::string GetVersion() noexcept;

  ///Obtain this class its version history
  static std::vector<std::string> GetVersionHistory() noexcept;

  ///Go to the next question
  void Next() noexcept;

  private:
  ~Exercise() noexcept {}
  friend void boost::checked_delete<>(Exercise *);
  friend void boost::checked_delete<>(const Exercise *);

  ///An iterator pointing to the current question
  std::vector<std::string>::iterator m_current;

  ///The questions
  std::vector<std::string> m_questions;
};

} //~namespace ribi

#endif // EXERCISE_H
