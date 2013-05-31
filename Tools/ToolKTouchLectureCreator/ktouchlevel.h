//---------------------------------------------------------------------------
/*
KTouchLectureCreator, create KTouch lecture for C++ programmers
Copyright (C) 2013 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolKTouchLectureCreator.htm
//---------------------------------------------------------------------------
#ifndef KTOUCHLEVEL_H
#define KTOUCHLEVEL_H

#include <string>
#include <vector>

struct KTouchLevel
{
  KTouchLevel(const std::string& chars, const std::string& new_chars);
  const std::vector<std::string> ToXml() const;

  private:
  const std::vector<std::string> m_lines;
  const std::string m_new_chars;

  static const std::vector<std::string> CreateLines(const std::string& chars);
  static const std::string CreateLine(const std::string& chars);

  ///Are all chars in s present in all?
  static bool DoesFit(const std::string& s, const std::string all);

  static void Test();
};

#endif // KTOUCHLEVEL_H
