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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "codetohtmlcontent.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include <boost/xpressive/xpressive.hpp>

#include "codetohtml.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"
#include "trace.h"
#pragma GCC diagnostic pop

#define PROGRAM_HANGS

boost::scoped_ptr<const Replacements> c2h::Content::m_replacements_cpp {};
boost::scoped_ptr<const Replacements> c2h::Content::m_replacements_pro {};
boost::scoped_ptr<const Replacements> c2h::Content::m_replacements_txt {};

c2h::Content::Content(
  const std::string& filename,
  const std::vector<std::string>& content)
    : m_content_type(DeduceContentType(filename)),
      m_contents(content),
      m_filename(GetFileBasename(filename) + GetExtension(filename))
{
  #ifndef NDEBUG
  Test();
  #endif
}

c2h::Content::Content(
  const std::string& filename,
  const std::vector<std::string>& content,
  const ContentType content_type)
    : m_content_type(content_type),
      m_contents(content),
      m_filename(GetFileBasename(filename) + GetExtension(filename))
{
  #ifndef NDEBUG
  Test();
  #endif
}

c2h::ContentType c2h::Content::DeduceContentType(const std::string& filename)
{
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pri)\\>") ) )
  {
    return ContentType::pri;
  }
  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pro)\\>") ) )
  {
    return ContentType::pro;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(c|cpp|h|hpp)\\>") ) )
  {
    return ContentType::cpp;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(sh)\\>") ) )
  {
    return ContentType::sh;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(txt)\\>") ) )
  {
    return ContentType::txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(py)\\>") ) )
  {
    return ContentType::py;
  }
  return ContentType::other;
}

const Replacements& c2h::Content::GetReplacementsCpp()
{
  if (!m_replacements_cpp)
  {
    m_replacements_cpp.reset(
      new Replacements(
        c2h::Content::CreateCppReplacements()));
  }
  assert(m_replacements_cpp);
  return *m_replacements_cpp;
}

const Replacements& c2h::Content::GetReplacementsPro()
{
  if (!m_replacements_pro)
  {
    m_replacements_pro.reset(
      new Replacements(
        c2h::Content::CreateProReplacements()));
  }
  assert(m_replacements_pro);
  return *m_replacements_pro;
}
const Replacements& c2h::Content::GetReplacementsTxt()
{
  if (!m_replacements_txt)
  {
    m_replacements_txt.reset(
      new Replacements(
        std::vector<std::pair<std::string,std::string> >()));
  }
  assert(m_replacements_txt);
  return *m_replacements_txt;
}

const std::vector<std::string> c2h::Content::ToHtml() const
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
      assert(m_replacements_cpp);
      const auto r = m_replacements_cpp->Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return c2h::Content::MultiReplace(s,r) + "<br/>";
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
      assert(m_replacements_pro);
      const auto r = m_replacements_pro->Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return c2h::Content::MultiReplace(s,r) + "<br/>";
        }
      );
    }
    break;
    case ContentType::pri:
    {
      v.push_back(
        std::string("<h2>")
        + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      assert(m_replacements_pro);
      const auto r = m_replacements_pro->Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return c2h::Content::MultiReplace(s,r) + "<br/>";
        }
      );
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
      assert(m_replacements_txt);
      const auto r = m_replacements_txt->Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return c2h::Content::MultiReplace(s,r) + "<br/>";
        }
      );
      //const std::vector<std::string> w = MultiReplace(m_contents,m_replacements_txt.m_all_replacements);
      //std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    break;
    case ContentType::other:
      return v;
    case ContentType::n_types:
      assert(!"Should not use ContentType::n_types");
      throw std::logic_error("Must not use ContentType::n_types");
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

const std::string c2h::Content::MultiReplace(const std::string& line, const std::vector<std::pair<std::string,std::string> >& replacements)
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
const std::string c2h::Content::ReplaceAll(
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

#ifndef NDEBUG
void c2h::Content::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting c2h::Content::Test");
  //Be gentle
  assert(DeduceContentType("tmp.pro") == ContentType::pro);
  assert(DeduceContentType("tmp.c"  ) == ContentType::cpp);
  assert(DeduceContentType("tmp.cpp") == ContentType::cpp);
  assert(DeduceContentType("tmp.h"  ) == ContentType::cpp);
  assert(DeduceContentType("tmp.hpp") == ContentType::cpp);
  assert(DeduceContentType("tmp.sh" ) == ContentType::sh);
  assert(DeduceContentType("tmp.txt") == ContentType::txt);
  assert(DeduceContentType("tmp.py" ) == ContentType::py);
  assert(DeduceContentType("tmp.xyz") == ContentType::other);
  //Be nasty
  assert(DeduceContentType("cpp.pro") == ContentType::pro);
  assert(DeduceContentType("h.c"    ) == ContentType::cpp);
  assert(DeduceContentType("hpp.cpp") == ContentType::cpp);
  assert(DeduceContentType("sh.h"   ) == ContentType::cpp);
  assert(DeduceContentType("txt.hpp") == ContentType::cpp);
  assert(DeduceContentType("py.sh"  ) == ContentType::sh);
  assert(DeduceContentType("xyz.txt") == ContentType::txt);
  assert(DeduceContentType("pro.py" ) == ContentType::py);
  assert(DeduceContentType("c.xyz"  ) == ContentType::other);

  assert(!GetReplacementsCpp().Get().empty());
  assert(!GetReplacementsPro().Get().empty());
  assert(!GetReplacementsTxt().Get().empty());

  TRACE("Finished c2h::Content::Test successfully");
}
#endif
