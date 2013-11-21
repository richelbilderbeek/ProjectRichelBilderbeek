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
#include <fileio.h>
#include <iostream>

#include <boost/xpressive/xpressive.hpp>

#include "codetohtml.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"
#include "trace.h"
#pragma GCC diagnostic pop

#define PROGRAM_HANGS

boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::File::m_replacements_cpp {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::File::m_replacements_pro {};
boost::scoped_ptr<const ribi::c2h::Replacements> ribi::c2h::File::m_replacements_txt {};

ribi::c2h::File::File(const std::string& filename)
    : m_html(CreateHtml(filename,DeduceContentType(filename)))
{
  #ifndef NDEBUG
  Test();
  #endif
}

ribi::c2h::File::File(
  const std::string& filename,
  const FileType content_type)
    : m_html(CreateHtml(filename,content_type))
{
  #ifndef NDEBUG
  Test();
  #endif
}

/*
ribi::c2h::File::Content(
  const std::string& filename,
  const std::vector<std::string>& content,
  const ContentType content_type)
    : m_content_type(content_type),
      m_contents(content),
      m_filename(ribi::fileio::GetFileBasename(filename) + ribi::fileio::GetExtension(filename))
{
  #ifndef NDEBUG
  Test();
  #endif
}
*/

c2h::ContentType ribi::c2h::File::DeduceFileType(const std::string& filename)
{
  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pri)\\>") ) )
  {
    return FileType::pri;
  }
  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pro)\\>") ) )
  {
    return FileType::pro;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(c|cpp|h|hpp)\\>") ) )
  {
    return FileType::cpp;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(sh)\\>") ) )
  {
    return FileType::sh;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(txt)\\>") ) )
  {
    return FileType::txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(py)\\>") ) )
  {
    return FileType::py;
  }
  return FileType::other;
}

const Replacements& ribi::c2h::File::GetReplacementsCpp()
{
  if (!m_replacements_cpp)
  {
    m_replacements_cpp.reset(
      new Replacements(
        ribi::c2h::File::CreateCppReplacements()));
  }
  assert(m_replacements_cpp);
  return *m_replacements_cpp;
}

const Replacements& ribi::c2h::File::GetReplacementsPro()
{
  if (!m_replacements_pro)
  {
    m_replacements_pro.reset(
      new Replacements(
        ribi::c2h::File::CreateProReplacements()));
  }
  assert(m_replacements_pro);
  return *m_replacements_pro;
}
const Replacements& ribi::c2h::File::GetReplacementsTxt()
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

const std::vector<std::string> ribi::c2h::File::ToHtml() const
{
  std::vector<std::string> v;
  switch(m_content_type)
  {
    case FileType::code_snippet:
    case FileType::cpp:
    {
      v.push_back(
        std::string("<h2>") + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      const auto r = GetReplacementsCpp().Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return ribi::c2h::File::MultiReplace(s,r) + "<br/>";
        }
      );
    }
    break;
    case FileType::pro:
    {
      v.push_back(
        std::string("<h2><a href=\"CppQtProjectFile.htm\">Qt project file</a>: ")
        + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      //v.push_back("<table border = \"1\"><tr><td><code>");
      const std::vector<std::pair<std::string,std::string> > r = GetReplacementsPro().Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return ribi::c2h::File::MultiReplace(s,r) + "<br/>";
        }
      );
    }
    break;
    case FileType::pri:
    {
      v.push_back(
        std::string("<h2>")
        + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      const auto r = GetReplacementsPro().Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return ribi::c2h::File::MultiReplace(s,r) + "<br/>";
        }
      );
    }
    break;
    case FileType::py:
    case FileType::sh:
    case FileType::txt:
    {
      v.push_back(
        std::string("<h2>") + m_filename + std::string("</h2>"));
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<!-- start of code -->");
      v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");
      //v.push_back("<table border = \"1\"><tr><td><code>");
      const auto r = GetReplacementsTxt().Get();
      std::transform(m_contents.begin(),m_contents.end(),
        std::back_inserter(v),
        [this,r](const std::string& s)
        {
          return ribi::c2h::File::MultiReplace(s,r) + "<br/>";
        }
      );
      //const std::vector<std::string> w = MultiReplace(m_contents,m_replacements_txt.m_all_replacements);
      //std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    break;
    case FileType::other:
      return v;
    case FileType::n_types:
      assert(!"Should not use FileType::n_types");
      throw std::logic_error("Must not use FileType::n_types");
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

const std::string ribi::c2h::File::MultiReplace(const std::string& line, const std::vector<std::pair<std::string,std::string> >& replacements)
{
  TRACE(line);
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
const std::string ribi::c2h::File::ReplaceAll(
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
void ribi::c2h::File::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::c2h::File::Test");
  //Be gentle
  assert(DeduceFileType("tmp.pro") == FileType::pro);
  assert(DeduceFileType("tmp.c"  ) == FileType::cpp);
  assert(DeduceFileType("tmp.cpp") == FileType::cpp);
  assert(DeduceFileType("tmp.h"  ) == FileType::cpp);
  assert(DeduceFileType("tmp.hpp") == FileType::cpp);
  assert(DeduceFileType("tmp.sh" ) == FileType::sh);
  assert(DeduceFileType("tmp.txt") == FileType::txt);
  assert(DeduceFileType("tmp.py" ) == FileType::py);
  assert(DeduceFileType("tmp.xyz") == FileType::other);
  //Be nasty
  assert(DeduceFileType("cpp.pro") == FileType::pro);
  assert(DeduceFileType("h.c"    ) == FileType::cpp);
  assert(DeduceFileType("hpp.cpp") == FileType::cpp);
  assert(DeduceFileType("sh.h"   ) == FileType::cpp);
  assert(DeduceFileType("txt.hpp") == FileType::cpp);
  assert(DeduceFileType("py.sh"  ) == FileType::sh);
  assert(DeduceFileType("xyz.txt") == FileType::txt);
  assert(DeduceFileType("pro.py" ) == FileType::py);
  assert(DeduceFileType("c.xyz"  ) == FileType::other);

  assert(!GetReplacementsCpp().Get().empty());
  assert(!GetReplacementsPro().Get().empty());
  assert(!GetReplacementsTxt().Get().empty());

  //Test for correct replacements
  {
    const std::vector<std::pair<std::string,std::string> > v {
      { "C++ Builder", "(<a href=\"CppBuilder.htm\">C++ Builder</a>)" },
      { "BeerWanter", "(<a href=\"GameBeerWanter.htm\">BeerWanter</a>)" },
      { "int main()", "(<b><a href=\"CppInt.htm\">int</a></b> <a href=\"CppMain.htm\">main</a>())" },
      { "boenken", "(<a href=\"GameBoenken.htm\">boenken</a>)" },
      { "; ++i)", "(; <a href=\"CppOperatorIncrement.htm\">++</a>i))" },
      { "C++11", "(<a href=\"Cpp11.htm\">C++11</a>)" },
      { "C++0x", "(<a href=\"Cpp0x.htm\">C++0x</a>)" },
      { "C++", "(<a href=\"Cpp.htm\">C++</a>)" },
      { "++", "(<a href=\"CppOperatorIncrement.htm\">++</a>)" },
      { "--", "(<a href=\"CppOperatorDecrement.htm\">--</a>)" }
    };
    std::for_each(v.begin(),v.end(),
      [](const std::pair<std::string,std::string>& p)
      {
        const std::string& s = p.first;
        const std::string t = MultiReplace(s,GetReplacementsCpp().Get());
        const std::string expected = p.second;
        if (t != expected)
        {
          TRACE("ERROR");
          TRACE(expected);
          TRACE(t);
        }
        assert(t == expected);
      }
    );
  }
  TRACE("Finished ribi::c2h::File::Test successfully");
}
#endif
