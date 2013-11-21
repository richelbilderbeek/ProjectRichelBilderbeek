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
#include "codetohtmlfile.h"

#include <algorithm>
#include <cassert>
#include <fileio.h>
#include <iostream>

#include <boost/xpressive/xpressive.hpp>

#include "codetohtml.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"
#include "codetohtmlreplacer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#define PROGRAM_HANGS


ribi::c2h::File::File(const std::string& filename)
    : m_html(CreateHtml(filename,DeduceFileType(filename)))
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

ribi::c2h::FileType ribi::c2h::File::DeduceFileType(const std::string& filename)
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
  //return FileType::other;
  return FileType::txt;
}




const std::vector<std::string> ribi::c2h::File::CreateHtml(
  const std::string& m_filename,
  const FileType file_type
  ) noexcept
{
  std::vector<std::string> v;

  //Add heading
  switch(file_type)
  {
    case FileType::cpp:
      v.push_back(std::string("<h2>") + m_filename + std::string("</h2>"));
    break;
    case FileType::pro:
      v.push_back(
        std::string("<h2><a href=\"CppQtProjectFile.htm\">Qt project file</a>: ")
        + m_filename + std::string("</h2>"));
    break;
    case FileType::pri:
      v.push_back(std::string("<h2>") + m_filename + std::string("</h2>"));
    break;
    case FileType::py:
    case FileType::sh:
    case FileType::txt:
      v.push_back(std::string("<h2>") + m_filename + std::string("</h2>"));
    break;
  }

  //Add end of heading and start of code
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<!-- start of code -->");
  v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");

  //Add the HTMLified content
  {
    const std::vector<std::string> w {
      Replacer::ToHtml(fileio::FileToVector(m_filename),file_type)
    };
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  //Remove empty lines
  while (v.back() == "<br/>") v.pop_back();
  assert(v.back()!="<br/>");

  //Add end of code and and end of page
  v.push_back("</code></td></tr></table>");
  v.push_back("<!-- end of the code -->");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  return v;
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
  assert(DeduceFileType("tmp.xyz") == FileType::txt);
  //Be nasty
  assert(DeduceFileType("cpp.pro") == FileType::pro);
  assert(DeduceFileType("h.c"    ) == FileType::cpp);
  assert(DeduceFileType("hpp.cpp") == FileType::cpp);
  assert(DeduceFileType("sh.h"   ) == FileType::cpp);
  assert(DeduceFileType("txt.hpp") == FileType::cpp);
  assert(DeduceFileType("py.sh"  ) == FileType::sh);
  assert(DeduceFileType("xyz.txt") == FileType::txt);
  assert(DeduceFileType("pro.py" ) == FileType::py);
  assert(DeduceFileType("c.xyz"  ) == FileType::txt);


  //Test for correct replacements
  /*
  assert(!GetReplacementsCpp().Get().empty());
  assert(!GetReplacementsPro().Get().empty());
  assert(!GetReplacementsTxt().Get().empty());

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
  */
  TRACE("Finished ribi::c2h::File::Test successfully");
}
#endif
