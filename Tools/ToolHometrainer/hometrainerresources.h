//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolHometrainer.htm
//---------------------------------------------------------------------------
#ifndef HOMETRAINERRESOURCES_H
#define HOMETRAINERRESOURCES_H

#include <string>

namespace ribi {

struct HometrainerResources
{
  ///Creates the resources from the resource file
  ///Throws a std::runtime_error if one of these is not found
  HometrainerResources();
  std::string GetQuestion() const noexcept { return "ToolHometrainerQuestion.png"; }
  std::string GetExerciseClouds() const noexcept { return "ToolHometrainerExerciseClouds.txt"; }
  std::string GetExerciseTest() const noexcept { return "ToolHometrainerExerciseTest.txt"; }
  std::string GetQuestionMark() const noexcept { return "ToolHometrainerQuestionmark.png"; }
  std::string GetWelcome() const noexcept { return "ToolHometrainerWelcome.png"; }
};

} //~namespace ribi

#endif // HOMETRAINERRESOURCES_H
