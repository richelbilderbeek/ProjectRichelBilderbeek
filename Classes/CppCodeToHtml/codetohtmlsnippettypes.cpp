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
#include "codetohtmlsnippettypes.h"

#include <cassert>
#include <stdexcept>

#include "codetohtmlsnippettype.h"

bool ribi::c2h::SnippetTypes::CanStrToSnippetType(const std::string& s)
{
  try
  {
    StrToSnippetType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

std::string ribi::c2h::SnippetTypes::SnippetTypeToStr(const SnippetType t) noexcept
{
  switch (t)
  {
    case SnippetType::cpp: return "cpp";
    case SnippetType::text: return "text";
    case SnippetType::n_snippets:
      assert(!"Never use SnippetType::n_snippets");
      throw std::logic_error("Never use SnippetType::n_snippets");
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::SnippetTypeToStr");
}

std::vector<ribi::c2h::SnippetType> ribi::c2h::SnippetTypes::GetAllSnippetTypes() noexcept
{
  const std::vector<SnippetType> v {
    SnippetType::cpp,
    SnippetType::text
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(SnippetType::n_snippets));
  return v;
}

ribi::c2h::SnippetType ribi::c2h::SnippetTypes::StrToSnippetType(const std::string& s)
{
  if (s == "cpp") return SnippetType::cpp;
  if (s == "text") return SnippetType::text;
  throw std::logic_error("Invalid string in StrToCodeToHtmlSnippetType");
}
