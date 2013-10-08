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
#include "codetohtmldialog.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/scoped_ptr.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string.hpp>

#include "codetohtmlcontent.h"
#include "codetohtmldialog.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlinfo.h"
#include "codetohtmltechinfo.h"
#include "codetohtmlversion.h"
#include "trace.h"
#pragma GCC diagnostic pop

c2h::Dialog::Dialog(
  const PageType page_type,
  const std::string& source,
  const ContentType content_type,
  const TechInfoType tech_info)
  :
    m_content_type(content_type),
    m_info { new Info },
    m_page_type(page_type),
    m_source(source),
    m_tech_info(tech_info)
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(m_info);

  //Check source
  if(!( (IsFolder(source) || IsRegularFile(source))))
  {
    TRACE("ERROR");
    TRACE(source);
    const std::string error = "Source '" + source
      + "' is neither a folder nor a file";
    throw std::runtime_error(error.c_str());
  }

  assert( (IsFolder(source) || IsRegularFile(source))
    && "Source can be a file or a path");
}

c2h::Dialog::~Dialog() noexcept
{

}

const std::string c2h::Dialog::ExtractPageName(const std::string& s) noexcept
{
  // /home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml
  // /home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml/
  // should become
  // ToolCodeToHtml'

  static const boost::xpressive::sregex r
    = boost::xpressive::sregex::compile("[A-Za-z0-9_\\.]*");

  std::vector<std::string> v;
  boost::xpressive::sregex_iterator i(s.begin(),s.end(),r);
  while (i != boost::xpressive::sregex_iterator())
  {
    v.push_back(i->str());
    ++i;
  }
  //Clean up the vector: remove filenames and empty strings
  while (1)
  {
    if (v.empty()) break;
    const std::string t = boost::algorithm::trim_copy( v[ v.size() - 1] );
    if (t.find('.') != std::string::npos || t.empty())
    {
      v.pop_back();
    }
    else break;
  }

  #ifdef REALLY_TRACE_THIS_20130929_28764723047972338294764627389
  const std::size_t sz = v.size();
  TRACE(sz);
  for (std::size_t i=0; i!=sz; ++i)
  {
    std::stringstream s;
    s << i << '/' << sz << ": '" << v[i] << "'";
    TRACE(s.str());
  }
  #endif
  const std::string t = v.empty() ? std::string() : v[v.size() - 1];


  #ifdef USE_BOOST_XPRESSIVE_78263785634856349
  static const boost::xpressive::sregex rex
    = boost::xpressive::sregex::compile(
      "(.*)?"          //Optional super folders
      "(/|\\\\)?"      //(back)slash
      "([A-Za-z0-9]*)" //Here is the booty
      "(/|\\\\)?"      //(back)slash
      "(([A-Za-z0-9]*)(\\.)([A-Za-z0-9]*))?" //An optional filename
      "(/|\\\\)?"    //Perhaps possible trailing (back)slash
      "\\>");

  boost::xpressive::smatch what;

  std::string t;
  if( boost::xpressive::regex_match(s, what, rex ) )
  {
    const std::size_t sz = what.size();
    for (std::size_t i=0; i!=sz; ++i)
    {
      std::stringstream s;
      s << i << "/" << sz << ": '" << what[i] << "'";
      TRACE(s.str());
    }
    t = what[1];
  }
  #endif //USE_BOOST_XPRESSIVE_78263785634856349

  assert(t.find('/') == std::string::npos
    && "A c2h::Info page must not contain a slash");
  assert(t.find('\\') == std::string::npos
    && "A c2h::Info page must not contain a backslash");

  return t;
}

#ifndef NDEBUG
void c2h::Dialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  assert(ExtractPageName("X") == std::string("X"));
  assert(ExtractPageName("/X") == std::string("X"));
  assert(ExtractPageName("/A/X") == std::string("X"));
  assert(ExtractPageName("/A/B/X") == std::string("X"));
  assert(ExtractPageName("/A/B/C/X") == std::string("X"));
  assert(ExtractPageName("/X/") == std::string("X"));
  assert(ExtractPageName("/A/X/") == std::string("X"));
  assert(ExtractPageName("/A/B/X/") == std::string("X"));
  assert(ExtractPageName("/A/B/C/X/") == std::string("X"));

  assert(ExtractPageName("\\X") == std::string("X"));
  assert(ExtractPageName("\\A\\X") == std::string("X"));
  assert(ExtractPageName("\\A\\B\\X") == std::string("X"));
  assert(ExtractPageName("\\A\\B\\C\\X") == std::string("X"));
  assert(ExtractPageName("\\X\\") == std::string("X"));
  assert(ExtractPageName("\\A\\X\\") == std::string("X"));
  assert(ExtractPageName("\\A\\B\\X\\") == std::string("X"));
  assert(ExtractPageName("\\A\\B\\C\\X\\") == std::string("X"));

  assert(ExtractPageName("/X") == std::string("X"));
  assert(ExtractPageName("/A\\X") == std::string("X"));
  assert(ExtractPageName("/A\\B/X") == std::string("X"));
  assert(ExtractPageName("\\A\\B/C/X") == std::string("X"));
  assert(ExtractPageName("\\X/") == std::string("X"));
  assert(ExtractPageName("/A\\X/") == std::string("X"));
  assert(ExtractPageName("/A/B\\X/") == std::string("X"));
  assert(ExtractPageName("/A/B\\C/X/") == std::string("X"));

  assert(ExtractPageName("main.cpp") == std::string(""));
  assert(ExtractPageName("/X/main.cpp") == std::string("X"));
  assert(ExtractPageName("/A/X/main.cpp") == std::string("X"));
  assert(ExtractPageName("/A/B/X/main.cpp") == std::string("X"));
  assert(ExtractPageName("/A/B/C/X/main.cpp") == std::string("X"));
  assert(ExtractPageName("/X/main.cpp/") == std::string("X"));
  assert(ExtractPageName("/A/X/main.cpp/") == std::string("X"));
  assert(ExtractPageName("/A/B/X/main.cpp/") == std::string("X"));
  assert(ExtractPageName("/A/B/C/X/main.cpp/") == std::string("X"));

  assert(ExtractPageName("/home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml")
    == std::string("ToolCodeToHtml"));

  //Check if CodeToHtml creates a clean HTML file when it converts itself
  #ifndef _WIN32
  assert(IsTidyInstalled() && "While I know I have tidy installed");
  if (IsTidyInstalled())
  {
    const std::string filename = "../ToolCodeToHtml/qtmain.cpp";
    if (IsRegularFile(filename))
    {
      Dialog d(PageType::cpp,filename,ContentType::cpp,TechInfoType::automatic);
      const std::vector<std::string> v = d.ToHtml();
      assert(IsCleanHtml(v) && "Assume tidy HTML");
    }
    else
    {
      TRACE("Warning: ToolCodeToHtml has not tested itself on its own code upon construction");
    }
  }
  else
  {
    TRACE("WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped");
  }
  if (IsTidyInstalled())
  {
    const std::string path = "../ToolCodeToHtml";
    if (IsFolder(path))
    {
      Dialog d(PageType::cpp,path,ContentType::cpp,TechInfoType::automatic);
      const std::vector<std::string> v = d.ToHtml();
      assert(IsCleanHtml(v) && "Assume tidy HTML");
    }
    else
    {
      TRACE("Warning: ToolCodeToHtml has not tested itself on its own code upon construction");
    }
  }
  else
  {
    TRACE("WARNING: 'tidy' not found, check if CodeToHtml generates clean HTML code is skipped");
  }
  #endif
}
#endif

const std::vector<std::string> c2h::Dialog::ToHtml() const
{
  std::vector<std::string> v;

  //Add header
  {
    const boost::scoped_ptr<const Header> header(new Header(m_page_type,m_source));
    const std::vector<std::string> w = header->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Text about this page (if known)
  {
    //Find the page name:
    //m_source can be something like this:
    // /home/richel/ProjectRichelBilderbeek/Tools/ToolCodeToHtml
    // ../ToolCodeToHtml/qtmain.cpp
    //page_name must be
    // ToolCodeToHtml
    const std::string page_name = ExtractPageName(m_source);
    assert(page_name.find('/') == std::string::npos
      && "A c2h::Info page must not contain a slash");
    assert(page_name.find('\\') == std::string::npos
      && "A c2h::Info page must not contain a backslash");

    const std::vector<std::string> w = m_info->ToHtml(page_name);
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Technical info
  {
    TechInfoType t = m_tech_info;
    if (m_tech_info == TechInfoType::automatic)
    {
      if (m_page_type == PageType::cpp
        || m_content_type == ContentType::cpp)
      {
        t = TechInfoType::yes;
      }
    }
    if (t == TechInfoType::yes)
    {
      //Add tech info
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<p>&nbsp;</p>");
      v.push_back("<p>&nbsp;</p>");
      std::vector<std::string> pro_files = GetProFilesInFolder(m_source);
      for (std::string& pro_file: pro_files)
      {
        pro_file = m_source + "/" + pro_file;
        assert(IsRegularFile(pro_file));
      }

      const boost::scoped_ptr<const TechInfo> info(new TechInfo(pro_files));
      const std::vector<std::string> w = info->ToHtml();
      std::copy(w.begin(),w.end(),std::back_inserter(v));
    }
    else
    {
      //Display no technical information
    }
  }

  //Source
  {
    const std::vector<std::string> w
      = !IsFolder(m_source)
     ? c2h::ConvertFile(m_source,m_content_type)
     : c2h::ConvertFiles(m_source) ;
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }

  //Add footer
  {
    const boost::scoped_ptr<Footer> footer(new Footer(m_page_type));
    const std::vector<std::string> w = footer->ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  #ifndef _WIN32
  assert(IsCleanHtml(v));
  #endif
  return v;
}
