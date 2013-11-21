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

#include "codetohtmlfiletype.h"

bool ribi::c2h::FileTypes::CanStrToFileType(const std::string& s) noexcept
{
  try
  {
    StrToFileType(s);
    return true;
  }
  catch (std::logic_error&)
  {
    return false;
  }
}

const std::string ribi::c2h::FileTypes::FileTypeToStr(const FileType t)
{
  switch (t)
  {
    //case FileType::code_snippet: return "code_snippet";
    case FileType::cpp: return "cpp";
    case FileType::pri: return "pri";
    case FileType::pro: return "pro";
    case FileType::py: return "py";
    case FileType::sh: return "sh";
    case FileType::txt: return "txt";
    //case FileType::other: return "other";
    case FileType::n_types:
      assert(!"Should never use FileType::n_types");
      throw std::logic_error("Must never use FileType::n_types");
  }
  assert(!"Should not get here");
  throw std::logic_error("c2h::FileTypeToStr");
}

const std::vector<ribi::c2h::FileType> ribi::c2h::FileTypes::GetAllFileTypes() noexcept
{
  const std::vector<FileType> v {
    //FileType::code_snippet,
    FileType::cpp,
    FileType::pri,
    FileType::pro,
    FileType::py,
    FileType::sh,
    FileType::txt
    //FileType::other
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(FileType::n_types));
  return v;
}

ribi::c2h::FileType ribi::c2h::FileTypes::StrToFileType(const std::string& s)
{
  //if (s == "code_snippet") return FileType::code_snippet;
  if (s == "cpp") return FileType::cpp;
  if (s == "pri") return FileType::pri;
  if (s == "pro") return FileType::pro;
  if (s == "py") return FileType::py;
  if (s == "sh") return FileType::sh;
  if (s == "txt") return FileType::txt;
  //if (s == "other") return FileType::other;
  if (s == "n_types")
  {
    assert(!"Should not use FileType::n_types");
    throw std::logic_error("Must not use FileType::n_types");
  }
  throw std::logic_error("Invalid string in StrToFileType");
}

