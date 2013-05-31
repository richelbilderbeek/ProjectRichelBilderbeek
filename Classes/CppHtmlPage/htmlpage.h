//---------------------------------------------------------------------------
/*
HtmlPage, HTML page class
Copyright (C) 2011 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppHtmlPage.htm
//---------------------------------------------------------------------------
#ifndef HTMLPAGE_H
#define HTMLPAGE_H
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
struct HtmlPage
{
  explicit HtmlPage(const std::string& filename);

  ///Obtain the filename of the HTML page
  const std::string& GetFilename() const { return m_filename; }

  ///Obtain the title of the HTML page
  const std::string& GetTitle() const { return m_title; }

  ///Obtain the version of this class
  static const std::string GetVersion();

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory();

  private:
  ///The filename of the HTML page
  std::string m_filename;

  ///The title of the HTML page
  std::string m_title;

  public:

  ///FileToVector reads a file and converts it to a std::vector<std::string>
  ///From http://www.richelbilderbeek.nl/CppFileToVector.htm
  static const std::vector<std::string> FileToVector(const std::string& filename);

  ///Replace all occurrences of a string within a string
  ///From http://www.richelbilderbeek.nl/CppReplaceAll.htm
  static const std::string ReplaceAll(
    std::string s,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat);

};
//---------------------------------------------------------------------------
bool operator<(const HtmlPage& lhs, const HtmlPage& rhs);
//---------------------------------------------------------------------------
#endif // HTMLPAGE_H
//---------------------------------------------------------------------------
