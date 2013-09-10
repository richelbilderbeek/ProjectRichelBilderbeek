//---------------------------------------------------------------------------
/*
Exercise, a collection of Questions
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
  //Construct a Exercise from file
  explicit Exercise(const std::string& filename);

  ///Read the current question
  const std::string GetCurrentQuestion() const;

  ///Get the number of questions
  int GetNumberOfQuestions() const;

  ///Obtain this class its version
  static const std::string GetVersion();

  ///Obtain this class its version history
  static const std::vector<std::string> GetVersionHistory();

  ///Go to the next question
  void Next();

  private:
  friend void boost::checked_delete<>(Exercise *);
  ~Exercise() {}

  ///An iterator pointing to the current question
  std::vector<std::string>::iterator m_current;

  ///The questions
  std::vector<std::string> m_questions;


  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);
};

} //~namespace ribi

#endif // EXERCISE_H
