
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

//From http://www.richelbilderbeek.nl/CppHtmlPage.htm

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "htmlpage.h"

#include <fstream>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
  #include <boost/filesystem.hpp>
  #include <boost/regex.hpp>
  #include <boost/algorithm/string.hpp>
#pragma GCC diagnostic pop

HtmlPage::HtmlPage(const std::string& filename)
  : m_filename(filename)
{
  assert(boost::filesystem::exists(filename));

  const boost::regex title_regex("<title>.*</title>");

  //Copy all filenames matching the regex in the resulting std::vector
  const std::vector<std::string> v = FileToVector(filename);
  std::for_each(v.begin(),v.end(),
    [this,title_regex](const std::string& s)
    {
      if (boost::regex_search(s,title_regex))
      {
        std::string t = s;
        //Trim leading whitespace
        while (!std::isgraph(t[0])) t = t.substr(1,t.size() - 1);
        //Trim trailing whitespace
        while (!std::isgraph(t[t.size()-1])) t.resize(t.size() - 1);
        //Extract title
        assert(t.substr(0,7)=="<title>");
        assert(t.substr(t.size()-8,8)=="</title>");
        m_title = t.substr(7,t.size()-8-7);
        m_title = ReplaceAll(m_title,"&amp;","&");

      }
    }
  );
}

const std::vector<std::string> HtmlPage::FileToVector(const std::string& filename)
{
  assert(boost::filesystem::exists(filename));
  std::vector<std::string> v;
  std::ifstream in(filename.c_str());
  std::string s;
  for (int i=0; !in.eof(); ++i)
  {
    std::getline(in,s);
    v.push_back(s);
  }
  return v;
}

const std::string HtmlPage::GetVersion()
{
  return "1.1";
}

const std::vector<std::string> HtmlPage::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2011-xx-xx: version 1.0: initial version");
  v.push_back("2012-08-12: version 1.1: started versioning this class");
  return v;
}

const std::string HtmlPage::ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  while(1)
  {
    const int pos = s.find(replaceWhat);
    if (pos==-1) break;
    s.replace(pos,replaceWhat.size(),replaceWithWhat);
  }
  return s;
}

bool operator<(const HtmlPage& lhs, const HtmlPage& rhs)
{
  //Case insensitive compare
  return boost::algorithm::to_lower_copy(lhs.GetTitle())
       < boost::algorithm::to_lower_copy(rhs.GetTitle());
}

