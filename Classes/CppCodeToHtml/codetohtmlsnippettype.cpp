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
#include "codetohtmlsnippettype.h"

/*
#include <cassert>
#include <stdexcept>

bool CanStrToPageType(const std::string& s)
{
  try
  {
    StrToPageType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

const std::string PageTypeToStr(const PageType t)
{
  switch (t)
  {
    case PageType::cpp: return "cpp";
    case PageType::foam: return "foam";
    case PageType::text: return "text";
    case PageType::music: return "music";
    //case PageType::tool: return "tool";
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::PageTypeToStr");
}

const std::vector<PageType> GetAllPageTypes()
{
  return
  {
    PageType::cpp,
    PageType::foam,
    PageType::text,
    PageType::music
    //,PageType::tool
  };
}

PageType StrToPageType(const std::string& s)
{
  if (s == "cpp") return PageType::cpp;
  if (s == "foam") return PageType::foam;
  if (s == "music") return PageType::music;
  if (s == "text") return PageType::text;
  throw std::logic_error("Invalid string in StrToCodeToHtmlPageType");
}
*/
