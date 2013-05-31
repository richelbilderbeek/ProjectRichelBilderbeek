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
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <cassert>
#include <stdexcept>

#include "codetohtmlcontenttype.h"

namespace c2h {

bool CanStrToContentType(const std::string& s)
{
  try
  {
    StrToContentType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

const std::string ContentTypeToStr(const ContentType t)
{
  switch (t)
  {
    case ContentType::code_snippet: return "code_snippet";
    case ContentType::cpp: return "cpp";
    case ContentType::pro: return "pro";
    case ContentType::sh: return "sh";
    case ContentType::txt: return "txt";
    case ContentType::other: return "other";
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::ContentTypeToStr");
}

const std::vector<ContentType> GetAllContentTypes()
{
  return
  {
    ContentType::code_snippet,
    ContentType::cpp,
    ContentType::pro,
    ContentType::sh,
    ContentType::txt,
    ContentType::other
  };
}

ContentType StrToContentType(const std::string& s)
{
  if (s == "code_snippet") return ContentType::code_snippet;
  if (s == "cpp") return ContentType::cpp;
  if (s == "pro") return ContentType::pro;
  if (s == "sh") return ContentType::sh;
  if (s == "txt") return ContentType::txt;
  if (s == "other") return ContentType::other;
  throw std::logic_error("Invalid string in StrToContentType");
}

} //~namespace CodeToHtml

