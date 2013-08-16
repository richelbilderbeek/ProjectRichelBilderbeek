//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2013  Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/ToolCodeToHtml.htm
//---------------------------------------------------------------------------
#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorUnableToFindNumericLiteralOperatorOperatorQ.htm
#if !(__GNUC__ >= 4 && __GNUC_MINOR__ >= 8)
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "codetohtmlcontent.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <boost/regex.hpp>

#include "codetohtml.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"

#define PROGRAM_HANGS

namespace c2h {

const CodeToHtmlReplacements Content::m_replacements_cpp
  = Content::CreateCppReplacements();
const CodeToHtmlReplacements Content::m_replacements_pro
  = Content::CreateProReplacements();
const CodeToHtmlReplacements Content::m_replacements_txt
  = CodeToHtmlReplacements(std::vector<std::pair<std::string,std::string> >());

Content::Content(
  const std::string& filename,
  const std::vector<std::string>& content)
    : m_content_type(DeduceContentType(filename)),
      m_contents(content),
      m_filename(GetFileBasename(filename) + GetExtension(filename))
{

}

Content::Content(
  const std::string& filename,
  const std::vector<std::string>& content,
  const ContentType content_type)
    : m_content_type(content_type),
      m_contents(content),
      m_filename(GetFileBasename(filename) + GetExtension(filename))
{

}

ContentType Content::DeduceContentType(const std::string& filename)
{
  if (boost::regex_match(filename,boost::regex(".*\\.(pro)\\z")))
  {
    return ContentType::pro;
  }
  else if (boost::regex_match(filename,boost::regex(".*\\.(c|cpp|h|hpp)\\z")))
  {
    return ContentType::cpp;
  }
  else if (boost::regex_match(filename,boost::regex(".*\\.(sh)\\z")))
  {
    return ContentType::sh;
  }
  else if (boost::regex_match(filename,boost::regex(".*\\.(txt)\\z")))
  {
    return ContentType::txt;
  }
  else if (boost::regex_match(filename,boost::regex(".*\\.(py)\\z")))
  {
    return ContentType::py;
  }
  return ContentType::other;
}

const std::vector<std::string> Content::ToHtml() const
{
  std::vector<std::string> v;
  switch(m_content_type)
  {
    case ContentType::code_snippet:
    case ContentType::cpp:
    {
      v.push_back(
        std::string("<h2>") + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      //v.push_back("<table border = \"1\"><tr><td><code>");
      const auto r = m_replacements_cpp.Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return Content::MultiReplace(s,r) + "<br/>";
        }
      );
      //const std::vector<std::string> w = MultiReplace(m_contents,m_replacements_cpp.m_all_replacements);
      //std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    break;
    case ContentType::pro:
    {
      v.push_back(
        std::string("<h2><a href=\"CppQtProjectFile.htm\">Qt project file</a>: ")
        + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      //v.push_back("<table border = \"1\"><tr><td><code>");

      const auto r = m_replacements_pro.Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return Content::MultiReplace(s,r) + "<br/>";
        }
      );
      //const std::vector<std::string> w = MultiReplace(m_contents,m_replacements_pro.m_all_replacements);
      //std::copy(w.begin(),w.end(),std::back_inserter(v));

    }
    break;
    case ContentType::py:
    case ContentType::sh:
    case ContentType::txt:
    {
      v.push_back(
        std::string("<h2>") + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      //v.push_back("<table border = \"1\"><tr><td><code>");
      const auto r = m_replacements_txt.Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return Content::MultiReplace(s,r) + "<br/>";
        }
      );
      //const std::vector<std::string> w = MultiReplace(m_contents,m_replacements_txt.m_all_replacements);
      //std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    break;
    case ContentType::other:
      return v;
  }
  //Remove empty lines
  while (v.back() == "<br/>") v.pop_back();
  assert(v.back()!="<br/>");
  v.push_back("</code></td></tr></table>");
  v.push_back("<!-- end of the code -->");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  return v;
}

const std::string Content::MultiReplace(const std::string& line, const std::vector<std::pair<std::string,std::string> >& replacements)
{
  std::string s(line);
  #ifdef DEBUG_PROGRAM_HANGS
  { const std::string debug_str = "Before: " + s; TRACE(debug_str); }
  #endif
  typedef std::vector<std::pair<std::string,std::string> >::const_iterator Iterator;
  const Iterator j = replacements.end();
  for (Iterator i = replacements.begin(); i!=j; ++i)
  {
    std::string from = i->first;
    const std::string to = i->second;
    s = ReplaceAll(s,from,to);
  }
  return s;
}

//From http://www.richelbilderbeek.nl/CppReplaceAll.htm
const std::string Content::ReplaceAll(
  std::string s,
  const std::string& replaceWhat,
  const std::string& replaceWithWhat)
{
  while(1)
  {
    const size_t pos = s.find(replaceWhat);
    if (pos==std::string::npos) break;
    s.replace(pos,replaceWhat.size(),replaceWithWhat);
  }
  return s;
}

} //~namespace CodeToHtml

