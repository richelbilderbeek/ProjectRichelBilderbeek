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

#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/checked_delete.hpp>
#pragma GCC diagnostic pop

namespace ribi {

struct HtmlPage
{
  explicit HtmlPage(const std::string& filename);
  HtmlPage(const HtmlPage&) = delete;
  HtmlPage& operator=(const HtmlPage&) = delete;

  ///Obtain the filename of the HTML page
  const std::string& GetFilename() const noexcept { return m_filename; }

  ///Obtain the title of the HTML page
  const std::string& GetTitle() const noexcept { return m_title; }

  ///Obtain the version of this class
  static const std::string GetVersion() noexcept;

  ///Obtain the version history of this class
  static const std::vector<std::string> GetVersionHistory() noexcept;

  ///Replace all occurrences of a string within a string
  ///From http://www.richelbilderbeek.nl/CppReplaceAll.htm
  static const std::string ReplaceAll(
    std::string s,
    const std::string& replaceWhat,
    const std::string& replaceWithWhat) noexcept;


  private:
  ~HtmlPage() noexcept {}
  friend void boost::checked_delete<>(HtmlPage* x);
  friend void boost::checked_delete<>(const HtmlPage* x);

  ///The filename of the HTML page
  const std::string m_filename;

  ///The title of the HTML page
  const std::string m_title;

  ///Find the <title> in an HTML document
  static const std::string FindTitle(const std::string& filename);

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator<(const HtmlPage& lhs, const HtmlPage& rhs) noexcept;

} //~namespace ribi

#endif // HTMLPAGE_H

