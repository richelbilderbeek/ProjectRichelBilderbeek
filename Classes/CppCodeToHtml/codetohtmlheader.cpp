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
#include "codetohtmlheader.h"

#include <cassert>
#include <stdexcept>

#include "codetohtml.h"
#include "fileio.h"

/*
ribi::c2h::Header::Header(
  const HeaderType page_type,
  const std::string& filename)
  : m_filename(CreateFilename(page_type,filename)),
    m_page_type(page_type),
    m_title(CreateTitle(page_type,filename))
{

}
*/

const std::string ribi::c2h::Header::CreateFilename(
  const HeaderType page_type,
  const std::string& filename_original)
{
  if (filename_original.empty())
  {
    switch (page_type)
    {
      case HeaderType::cpp:   return "Cpp.htm";
      //case HeaderType::music: return "SongXXX.htm";
      //case HeaderType::text:  return "CppXXX.htm";
      case HeaderType::foam:  return "ToolOpenFoam.htm";
    }
    assert(!"Should not get here");
    throw std::logic_error("ribi::c2h::Header::CreateFilename");
  }
  else
  {
    assert(!filename_original.empty());
    return ribi::fileio::GetFileBasename(filename_original) + ".htm";
  }
}

const std::string ribi::c2h::Header::CreateTitle(
  const HeaderType page_type,
  const std::string& filename)
{
  if (filename.empty())
  {
    switch (page_type)
    {
      case HeaderType::cpp:
      case HeaderType::foam:
        return filename;
    }
    assert(!"Should not get here");
    throw std::logic_error("ribi::c2h::Header::CreateTitle");
  }
  else
  {
    assert(!filename.empty());
    std::string s = ribi::fileio::GetFileBasename(filename);
    int chars_to_strip = 0;
    if (s.size() > 3 && s.substr(0,3) == "Cpp") chars_to_strip = 3;
    else if (s.size() > 4 && s.substr(0,4) == "Song") chars_to_strip = 4;
    else if (s.size() > 4 && s.substr(0,4) == "Tool") chars_to_strip = 4;
    else if (s.size() > 7 && s.substr(0,7) == "Project") chars_to_strip = 7;
    return s.substr(chars_to_strip,s.size() - chars_to_strip);
  }
}

const std::vector<std::string> ribi::c2h::Header::ToHtml(
  const HeaderType header_type,
  const std::string& filename
  ) noexcept
{
  const std::string m_filename { CreateFilename(header_type,filename) };
  const std::string m_title { CreateTitle(header_type,filename) };

  std::vector<std::string> v;
  v.push_back("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
  v.push_back("\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
  v.push_back("<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">");
  v.push_back("<head>");
  v.push_back("  <meta http-equiv=\"Content-Type\" content=\"text/html;charset=utf-8\"/>");
  switch (header_type)
  {
    //case HeaderType::text:
    case HeaderType::cpp:
      v.push_back("  <title>" + m_title + "</title>");
      v.push_back("  <meta name=\"description\" content=\"C++ " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"C++ " + m_title + " \"/>");
    break;
    case HeaderType::foam:
      v.push_back("  <title>" + m_title + "</title>");
      v.push_back("  <meta name=\"description\" content=\"OpenFOAM " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"OpenFOAM " + m_title + " \"/>");
    break;
    /*
    case HeaderType::music:
      v.push_back("  <title>" + m_title + "</title>");
      v.push_back("  <meta name=\"description\" content=\"Song " + m_title + "\"/>");
      v.push_back("  <meta name=\"keywords\" content=\"Richel Bilderbeek Music Song " + m_title + " free legal\"/>");
    break;
    //case HeaderType::tool:
    //  v.push_back("  <title>XXX</title>");
    //  v.push_back("  <meta name=\"description\" content=\"C++ Tool " + m_title + "\"/>");
    //  v.push_back("  <meta name=\"keywords\" content=\"C++ Tool " + m_title + " GPL open source freeware\"/>");
    //break;
    default:
      assert(!"Should not get here");
    break;
    */
  }
  v.push_back("  <link rel=\"stylesheet\" href=\"Richelbilderbeek.css\" type=\"text/css\"/>");
  v.push_back("</head>");
  v.push_back("<!-- End of head, start of body -->");
  v.push_back("<body>");
  v.push_back("<p><a href=\"index.htm\">Go back to Richel Bilderbeek's homepage</a>.</p>");
  switch (header_type)
  {
    case HeaderType::cpp:
      v.push_back("<p><a href=\"Cpp.htm\">Go back to Richel Bilderbeek's C++ page</a>.</p>");
      break;
    case HeaderType::foam:
      v.push_back("<p><a href=\"ToolOpenFoam.htm\">Go back to Richel Bilderbeek's OpenFOAM page</a>.</p>");
      break;
    /*
    case HeaderType::text:
    case HeaderType::music:
      v.push_back("<p><a href=\"Music.htm\">Go back to Richel Bilderbeek's music page</a>.</p>");
      break;
    //case HeaderType::tool:
    //  v.push_back("<p><a href=\"Tools.htm\">Go back to Richel Bilderbeek's tools</a>.</p>");
    //  break;
    default:
      assert(!"Should not get here");
    break;
    */
  }
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<!-- Page header -->");

  switch (header_type)
  {
    case HeaderType::cpp:
      v.push_back("<h1>(<a href=\"Cpp.htm\">C++</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    case HeaderType::foam:
      v.push_back("<h1>(<a href=\"ToolOpenFoam.htm\">OpenFOAM</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    /*
    case HeaderType::text:
    case HeaderType::music:
      v.push_back("<h1>(<a href=\"Music.htm\">Music</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
      break;
    //case HeaderType::tool:
    //  v.push_back("<h1>(<a href=\"Tools.htm\">Tool</a>) <a href=\"" + m_filename + "\">" + m_title + "</a></h1>");
    //  break;
    default:
      assert(!"Should not get here");
    break;
    */
  }
  v.push_back("<p>&nbsp;</p>");
  return v;
}
