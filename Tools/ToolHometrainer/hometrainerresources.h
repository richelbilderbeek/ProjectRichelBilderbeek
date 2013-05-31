//---------------------------------------------------------------------------
/*
Hometrainer, exercise and survey suite
Copyright (C) 2009-2013 Richel Bilderbeek

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

struct HometrainerResources
{
  HometrainerResources();
  const std::string GetQuestion() const { return "ToolHometrainerQuestion.png"; }
  const std::string GetExerciseClouds() const { return "ToolHometrainerExerciseClouds.txt"; }
  const std::string GetExerciseTest() const { return "ToolHometrainerExerciseTest.txt"; }
  const std::string GetQuestionMark() const { return "ToolHometrainerQuestionmark.png"; }
  const std::string GetWelcome() const { return "ToolHometrainerWelcome.png"; }
};

#endif // HOMETRAINERRESOURCES_H
