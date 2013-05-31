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
#include "ktouchlecture.h"

#include <algorithm>

KTouchLecture::KTouchLecture()
  : m_comment("KTouch lecture file created by KTouchLectureCreator, www.richelbilderbeek.nl/ToolKTouchLectureCreator.htm"),
    m_font_suggestion("Monospace"),
    m_levels(CreateLevels()),
    m_title("C++")
{

}

const KTouchLevels KTouchLecture::CreateLevels()
{
  return KTouchLevels();
}

const std::vector<std::string> KTouchLecture::ToXml() const
{
  std::vector<std::string> v;
  v.push_back("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
  v.push_back("<KTouchLecture>");
  {
    const std::string s = "<Title>" + m_title + "</Title>";
    v.push_back(s);
  }
  {
    const std::string s = "<Comment>" + m_comment+ "</Comment>";
    v.push_back(s);
  }
  {
    const std::string s = "<FontSuggestions>" + m_font_suggestion + "</FontSuggestions>";
    v.push_back(s);
  }
  const std::vector<std::string> w = m_levels.ToXml();
  std::transform(w.begin(),w.end(),std::back_inserter(v),
    [](const std::string& s)
    {
      return std::string("  ") + s;
    }
  );
  v.push_back("</KTouchLecture>");
  return v;
}
