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
#include "codetohtmlfiletypes.h"

#include <cassert>
#include <stdexcept>

bool ribi::c2h::CanStrToContentType(const std::string& s) noexcept
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

const std::string ribi::c2h::ContentTypeToStr(const ContentType t)
{
  switch (t)
  {
    case ContentType::code_snippet: return "code_snippet";
    case ContentType::cpp: return "cpp";
    case ContentType::pri: return "pri";
    case ContentType::pro: return "pro";
    case ContentType::py: return "py";
    case ContentType::sh: return "sh";
    case ContentType::txt: return "txt";
    case ContentType::other: return "other";
    case ContentType::n_types:
      assert(!"Should not use ContentType::n_types");
      throw std::logic_error("Must not use ContentType::n_types");
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::ContentTypeToStr");
}

const std::vector<ContentType> GetAllContentTypes() noexcept
{
  const std::vector<ContentType> v {
    ContentType::code_snippet,
    ContentType::cpp,
    ContentType::pri,
    ContentType::pro,
    ContentType::py,
    ContentType::sh,
    ContentType::txt,
    ContentType::other
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(ContentType::n_types));
  return v;
}

ribi::c2h::ContentType ribi::c2h::StrToContentType(const std::string& s)
{
  if (s == "code_snippet") return ContentType::code_snippet;
  if (s == "cpp") return ContentType::cpp;
  if (s == "pri") return ContentType::pri;
  if (s == "pro") return ContentType::pro;
  if (s == "py") return ContentType::py;
  if (s == "sh") return ContentType::sh;
  if (s == "txt") return ContentType::txt;
  if (s == "other") return ContentType::other;
  if (s == "n_types")
  {
    assert(!"Should not use ContentType::n_types");
    throw std::logic_error("Must not use ContentType::n_types");
  }
  throw std::logic_error("Invalid string in StrToContentType");
}

