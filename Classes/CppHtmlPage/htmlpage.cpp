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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "htmlpage.h"

#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>

#include <QDir>
#include <QFile>

#include "fileio.h"
#pragma GCC diagnostic pop

ribi::HtmlPage::HtmlPage(const std::string& filename)
  : m_filename{filename},
    m_title{FindTitle(filename)}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(ribi::fileio::IsRegularFile(filename));

}

const std::string ribi::HtmlPage::FindTitle(const std::string& filename)
{
  const boost::xpressive::sregex title_regex
    = boost::xpressive::sregex::compile("<title>.*</title>");

  //Copy all filenames matching the regex in the resulting std::vector
  const std::vector<std::string> v = ribi::fileio::FileToVector(filename);
  for (const std::string s: v)
  {
    if (boost::xpressive::regex_search(s,title_regex))
    {
      std::string t = s;
      //Trim leading whitespace
      while (!std::isgraph(t[0])) t = t.substr(1,t.size() - 1);
      //Trim trailing whitespace
      while (!std::isgraph(t[t.size()-1])) t.resize(t.size() - 1);
      //Extract title
      assert(t.substr(0,7)=="<title>");
      assert(t.substr(t.size()-8,8)=="</title>");
      const std::string title = t.substr(7,t.size()-8-7);
      const std::string title_clean = ReplaceAll(title,"&amp;","&");
      return title_clean;
    }
  }
  return {};
}

const std::string ribi::HtmlPage::GetVersion() noexcept
{
  return "1.2";
}

const std::vector<std::string> ribi::HtmlPage::GetVersionHistory() noexcept
{
  return {
    "2011-xx-xx: version 1.0: initial version",
    "2012-08-12: version 1.1: started versioning this class",
    "2013-09-02: version 1.2: replaced Boost.Regex by Boost.Xpressive"
  };
}

const std::string ribi::HtmlPage::ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat) noexcept
{
  while(1)
  {
    const int pos = s.find(replaceWhat);
    if (pos==-1) break;
    s.replace(pos,replaceWhat.size(),replaceWithWhat);
  }
  return s;
}

#ifndef NDEBUG
void ribi::HtmlPage::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test finding
  {
    const std::string filename { "tmp.txt" };
    std::ofstream file(filename);
    file << "Nothing";
    file.close();
    assert(FindTitle(filename)=="");
    std::remove(filename.c_str());
  }
  {
    const std::string filename { "tmp.txt" };
    std::ofstream file(filename);
    file << "Nothing\n";
    file << "<title>Something</title>\n";
    file << "Nothing\n";
    file.close();
    assert(FindTitle(filename)=="Something");
    std::remove(filename.c_str());
  }
}
#endif

bool ribi::operator<(const HtmlPage& lhs, const HtmlPage& rhs) noexcept
{
  //Case insensitive compare
  return boost::algorithm::to_lower_copy(lhs.GetTitle())
       < boost::algorithm::to_lower_copy(rhs.GetTitle());
}

