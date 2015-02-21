//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2015 Richel Bilderbeek

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
#include <iostream>

#include "codetohtmlfiletypes.h"
#include "codetohtmlfooter.h"
#include "codetohtml.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"
#include "codetohtmlreplacer.h"
#include "fileio.h"
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

#define PROGRAM_HANGS


ribi::c2h::File::File(const std::string& filename)
  : m_html(CreateHtml(filename,FileTypes().DeduceFileType(filename)))
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

std::vector<std::string> ribi::c2h::File::CreateHtml(
  const std::string& filename,
  const FileType file_type
  ) noexcept
{
  assert(fileio::FileIo().IsRegularFile(filename));

  std::vector<std::string> v;
  if (filename == "Licence.txt" || filename == "License.txt") return v;

  //Add heading
  switch(file_type)
  {
    case FileType::cpp:
    case FileType::png:
      v.push_back("<h2>" + filename + "</h2>");
    break;
    case FileType::pro:
      v.push_back(
        "<h2><a href=\"CppQtProjectFile.htm\">Qt project file</a>: "
        + filename + "</h2>");
    break;
    case FileType::foam:
    case FileType::pri:
    case FileType::py:
    case FileType::sh:
    case FileType::txt:
      v.push_back("<h2>" + filename + "</h2>");
    break;
    case FileType::license_txt:
      assert(!"Should not HTML-ify FileType::license_txt");
      throw std::logic_error("Should not HTML-ify FileType::license_txt");
    case FileType::n_types:
      assert(!"Should never use FileType::n_types");
      throw std::logic_error("Should never use FileType::n_types");
  }

  //Add end of heading
  v.push_back("<p>&nbsp;</p>");

  //Start of code
  if (file_type == FileType::png)
  {
    v.push_back("<p><img src=\"" + filename + "\" alt=\"" + filename + "\"/></p>");
  }
  else
  {
    v.push_back("<!-- start of code -->");
    v.push_back("<table summary=\"" + filename + "\" border = \"1\"><tr><td><code>");

    //Add the HTMLified content
    {
      assert(fileio::FileIo().IsRegularFile(filename));
      auto lines_text = fileio::FileIo().FileToVector(filename);
      if (file_type == FileType::foam)
      {
        //Keep lines 0-100 and last-50,last
        const int n_lines_begin = 100;
        const int n_lines_end = 50;
        if (static_cast<int>(lines_text.size() > n_lines_begin + n_lines_end))
        {
          std::vector<std::string> lines_shorter;
          std::copy(lines_text.begin(),lines_text.begin() + n_lines_begin,std::back_inserter(lines_shorter));
          lines_shorter.push_back("[...]");
          std::copy(lines_text.end() - n_lines_end,lines_text.end(),std::back_inserter(lines_shorter));
          std::swap(lines_shorter,lines_text);
        }
      }
      const auto lines_html = Replacer().ToHtml(lines_text,file_type);
      std::transform(lines_html.begin(),lines_html.end(),std::back_inserter(v),
        [](const std::string& s)
        {
          return s + "<br/>";
        }
      );
    }

    //Remove empty lines
    while (v.back() == "<br/>") v.pop_back();
    assert(v.back()!="<br/>");

    //Add end of code and and end of page
    v.push_back("</code></td></tr></table>");
    v.push_back("<!-- end of the code -->");
  }
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  return v;
}

#ifndef NDEBUG
void ribi::c2h::File::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  ribi::fileio::FileIo();
  Replacer();
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
