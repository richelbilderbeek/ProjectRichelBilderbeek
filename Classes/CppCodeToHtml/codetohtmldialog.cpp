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
#include <string>
#include <vector>

#include "codetohtmlcontent.h"
#include "codetohtmldialog.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlinfo.h"
#include "codetohtmltechinfo.h"
#include "codetohtmlversion.h"
#include "trace.h"


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
  assert( (IsFolder(source) || IsRegularFile(source))
    && "Source can be a file or a path");
}

#ifndef NDEBUG
void c2h::Dialog::Test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
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
    if (!IsRegularFile(path))
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
    Header header(m_page_type,m_source);
    const std::vector<std::string> w = header.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  //Text about this page (if known)
  {
    const std::vector<std::string> w = m_info->ToHtml(m_source);
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

      TechInfo info(pro_files);
      const std::vector<std::string> w = info.ToHtml();
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
    Footer footer(m_page_type);
    const std::vector<std::string> w = footer.ToHtml();
    std::copy(w.begin(),w.end(),std::back_inserter(v));
  }
  #ifndef _WIN32
  assert(IsCleanHtml(v));
  #endif
  return v;
}
