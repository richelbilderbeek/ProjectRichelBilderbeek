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


#include "codetohtmlfooter.h"

#include <cassert>

const std::vector<std::string> ribi::c2h::Footer::ToHtml(const FooterType page_type) noexcept
{
  #ifndef NDEBUG
  //Test();
  #endif
  std::vector<std::string> v;
  switch (page_type)
  {
    case FooterType::cpp:
      v.push_back("<p><a href=\"Cpp.htm\">Go back to Richel Bilderbeek's C++ page</a>.</p>");
      break;

    //v.push_back("<p><a href=\"ToolOpenFoam.htm\">Go back to Richel Bilderbeek's OpenFOAM page</a>.</p>");
    //v.push_back("<p><a href=\"Music.htm\">Go back to Richel Bilderbeek's music page</a>.</p>");
    //v.push_back("<p><a href=\"Tools.htm\">Go back to Richel Bilderbeek's tools</a>.</p>");

  }
  v.push_back("<p><a href=\"index.htm\">Go back to Richel Bilderbeek's homepage</a>.</p>");
  v.push_back("<p>&nbsp;</p>");
  v.push_back("<p><a href=\"http://validator.w3.org/check?uri=referer\"><img src=\"valid-xhtml10.png\" alt=\"Valid XHTML 1.0 Strict\" height=\"31\" width=\"88\" /></a></p>");
  v.push_back("<p>This page has been created by the <a href=\"Tools.htm\">tool</a> <a href=\"ToolCodeToHtml.htm\">CodeToHtml</a></p>");
  v.push_back("</body>");
  v.push_back("</html>");
  return v;
}
