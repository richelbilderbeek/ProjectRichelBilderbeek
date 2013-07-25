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
#include "codetohtmlheader.h"

#include <cassert>
#include <stdexcept>

#include <boost/filesystem.hpp>


namespace c2h {

Header::Header(
  const PageType page_type,
  const std::string& filename)
  : m_filename(CreateFilename(page_type,filename)),
    m_page_type(page_type),
    m_title(CreateTitle(page_type,filename))
{

}

const std::string Header::CreateFilename(
  const PageType page_type,
  const std::string& filename_original)
{
  if (filename_original.empty())
  {
    switch (page_type)
    {
      case PageType::cpp:   return "CppXXX.htm";
      case PageType::music: return "SongXXX.htm";
      case PageType::text:  return "CppXXX.htm";
      case PageType::tool:  return "ToolXXX.htm";
    }
    assert(!"Should not get here");
    throw std::logic_error("c2h::Header::CreateFilename");
  }
  else
  {
    assert(!filename_original.empty());
    return boost::filesystem::basename(filename_original) + ".htm";
  }
}

const std::string Header::CreateTitle(
  const PageType page_type,
  const std::string& filename)
{
  if (filename.empty())
  {
    switch (page_type)
    {
      case PageType::cpp:
      case PageType::music:
      case PageType::text:
      case PageType::tool:
       return "XXX";
    }
    assert(!"Should not get here");
    throw std::logic_error("c2h::Header::CreateTitle");
  }
  else
  {
    assert(!filename.empty());
    std::string s = boost::filesystem::basename(filename);
    int chars_to_strip = 0;
    if (s.size() > 3 && s.substr(0,3) == "Cpp") chars_to_strip = 3;
    else if (s.size() > 4 && s.substr(0,4) == "Song") chars_to_strip = 4;
    else if (s.size() > 4 && s.substr(0,4) == "Tool") chars_to_strip = 4;
    else if (s.size() > 7 && s.substr(0,7) == "Project") chars_to_strip = 7;
    return s.substr(chars_to_strip,s.size() - chars_to_strip);
  }
}

/*
void Header::SetPageType(const CodeToHtml::PageType page_type)
{
  m_page_type = page_type;
  switch (m_page_type)
  {
    case CodeToHtml::cpp:   m_filename = "CppXXX.htm"; m_title = "XXX"; break;
    case CodeToHtml::text:  m_filename = "CppXXX.htm"; m_title = "XXX"; break;
    case CodeToHtml::music: m_filename = "SongXXX.htm"; m_title = "XXX"; break;
    case CodeToHtml::tool:  m_filename = "ToolXXX.htm"; m_title = "XXX"; break;
  }
}
*/

const std::vector<std::string> Header::ToHtml() const
{
  std::vector<std::string> v;
  v.push_back("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
  v.push_back("\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
  v.push_back("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">");
  v.push_back("<head>");
  v.push_back("  <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"/>");
  switch (m_page_type)
  {
    case PageType::text:
    case PageType::cpp:
      v.push_back("  <title>" + m_title + "</title>");
      v.push_back("  <meta name=\"description\" content=\"C++ " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"C++ " + m_title + " code snippet\"/>");
    break;
    case PageType::music:
      v.push_back("  <title>" + m_title + "</title>");
      v.push_back("  <meta name=\"description\" content=\"Song " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"Richel Bilderbeek Music Song " + m_title + " free legal\"/>");
    break;
    case PageType::tool:
      v.push_back("  <title>XXX</title>");
      v.push_back("  <meta name=\"description\" content=\"C++ Tool " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"C++ Tool " + m_title + " GPL open source freeware\"/>");
    break;
    default:
      assert(!"Should not get here");
    break;
  }
  v.push_back("  <link rel=\"stylesheet\" href=\"Richelbilderbeek.css\" type=\"text/css\"/>");
  v.push_back("</head>");
  v.push_back("<!-- End of head, start of body -->");
  v.push_back("<body>");
  v.push_back("<p><a href=\"index.htm\">Go back to Richel Bilderbeek's homepage</a>.</p>");
  switch (m_page_type)
  {
    case PageType::cpp:
    case PageType::text:
      v.push_back("<p><a href=\"Cpp.htm\">Go back to Richel Bilderbeek's C++ page</a>.</p>");
      break;
    case PageType::music:
      v.push_back("<p><a href=\"Music.htm\">Go back to Richel Bilderbeek's music page</a>.</p>");
      break;
    case PageType::tool:
      v.push_back("<p><a href=\"Tools.htm\">Go back to Richel Bilderbeek's tools</a>.</p>");
      break;
    default:
      assert(!"Should not get here");
    break;
  }
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<!-- Page header -->");

  switch (m_page_type)
  {
    case PageType::cpp:
    case PageType::text:
      v.push_back("<h1>(<a href=\"Cpp.htm\">C++</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    case PageType::music:
      v.push_back("<h1>(<a href=\"Music.htm\">Music</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    case PageType::tool:
      v.push_back("<h1>(<a href=\"Tools.htm\">Tool</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    default:
      assert(!"Should not get here");
    break;
  }
  v.push_back("<p>&nbsp;</p>");
  return v;
}

} //~namespace CodeToHtml

