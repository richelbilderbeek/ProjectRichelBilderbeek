//---------------------------------------------------------------------------
/*
CodeToHtml, converts C++ code to HTML
Copyright (C) 2010-2014 Richel Bilderbeek

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


#include "codetohtml.h"
#include "codetohtmlfooter.h"
#include "codetohtmlheader.h"
#include "codetohtmlreplacements.h"
#include "codetohtmlreplacer.h"
#include "codetohtmlfiletypes.h"
#include "trace.h"
#pragma GCC diagnostic pop

#define PROGRAM_HANGS


ribi::c2h::File::File(const std::string& filename)
    : m_html(CreateHtml(filename,FileTypes::DeduceFileType(filename)))
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

const std::vector<std::string> ribi::c2h::File::CreateHtml(
  const std::string& m_filename,
  const FileType file_type
  ) noexcept
{
  assert(fileio::IsRegularFile(m_filename));

  std::vector<std::string> v;
  if (m_filename == "Licence.txt" || m_filename == "License.txt") return v;

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
    case FileType::license_txt:
      assert(!"Should not HTML-ify FileType::license_txt");
      throw std::logic_error("Should not HTML-ify FileType::license_txt");
    case FileType::n_types:
      assert(!"Should never use FileType::n_types");
      throw std::logic_error("Should never use FileType::n_types");
  }

  //Add end of heading and start of code
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<!-- start of code -->");
  v.push_back("<table summary=\"" + m_filename + "\" border = \"1\"><tr><td><code>");

  //Add the HTMLified content
  {
    assert(fileio::IsRegularFile(m_filename));
    const std::vector<std::string> w {
      Replacer::ToHtml(fileio::FileToVector(m_filename),file_type)
    };
    std::transform(w.begin(),w.end(),std::back_inserter(v),
      [](const std::string& s)
      {
        return s + std::string("<br/>");
      }
    );
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
void ribi::c2h::File::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::c2h::File::Test");
  TRACE("Finished ribi::c2h::File::Test successfully");
}
#endif
