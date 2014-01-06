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
#include "codetohtmlfiletypes.h"

#include <cassert>
#include <stdexcept>

#include <boost/xpressive/xpressive.hpp>

#include "codetohtmlfiletype.h"
#include "trace.h"
#pragma GCC diagnostic pop

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

ribi::c2h::FileType ribi::c2h::FileTypes::DeduceFileType(const std::string& filename)
{
  #ifndef NDEBUG
  Test();
  #endif

  boost::xpressive::smatch what;

  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pri)\\>") ) )
  {
    return FileType::pri;
  }
  if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(pro)\\>") ) )
  {
    return FileType::pro;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(c|cpp|h|hpp)\\>") ) )
  {
    return FileType::cpp;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(sh)\\>") ) )
  {
    return FileType::sh;
  }
  else if(filename == "Licence.txt" || filename == "License.txt")
  {
    return FileType::license_txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(txt)\\>") ) )
  {
    return FileType::txt;
  }
  else if( boost::xpressive::regex_match( filename, what,
    boost::xpressive::sregex::compile( ".*\\.(py)\\>") ) )
  {
    return FileType::py;
  }
  //return FileType::other;
  return FileType::txt;
}

const std::string ribi::c2h::FileTypes::FileTypeToStr(const FileType t)
{
  switch (t)
  {
    case FileType::cpp: return "cpp";
    case FileType::license_txt: return "license_txt";
    case FileType::pri: return "pri";
    case FileType::pro: return "pro";
    case FileType::py: return "py";
    case FileType::sh: return "sh";
    case FileType::txt: return "txt";
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
    FileType::cpp,
    FileType::license_txt,
    FileType::pri,
    FileType::pro,
    FileType::py,
    FileType::sh,
    FileType::txt
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(FileType::n_types));
  return v;
}

ribi::c2h::FileType ribi::c2h::FileTypes::StrToFileType(const std::string& s)
{
  //if (s == "code_snippet") return FileType::code_snippet;
  if (s == "cpp") return FileType::cpp;
  if (s == "license_txt") return FileType::license_txt;
  if (s == "pri") return FileType::pri;
  if (s == "pro") return FileType::pro;
  if (s == "py") return FileType::py;
  if (s == "sh") return FileType::sh;
  if (s == "txt") return FileType::txt;
  if (s == "n_types")
  {
    assert(!"Should not use FileType::n_types");
    throw std::logic_error("Must not use FileType::n_types");
  }
  throw std::logic_error("Invalid string in StrToFileType");
}

#ifndef NDEBUG
void ribi::c2h::FileTypes::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::c2h::FileTypes::Test");
  //Be gentle
  assert(DeduceFileType("tmp.pro") == FileType::pro);
  assert(DeduceFileType("tmp.c"  ) == FileType::cpp);
  assert(DeduceFileType("tmp.cpp") == FileType::cpp);
  assert(DeduceFileType("tmp.h"  ) == FileType::cpp);
  assert(DeduceFileType("tmp.hpp") == FileType::cpp);
  assert(DeduceFileType("tmp.sh" ) == FileType::sh);
  assert(DeduceFileType("tmp.txt") == FileType::txt);
  assert(DeduceFileType("tmp.py" ) == FileType::py);
  assert(DeduceFileType("tmp.xyz") == FileType::txt);
  //Be nasty
  assert(DeduceFileType("cpp.pro") == FileType::pro);
  assert(DeduceFileType("h.c"    ) == FileType::cpp);
  assert(DeduceFileType("hpp.cpp") == FileType::cpp);
  assert(DeduceFileType("sh.h"   ) == FileType::cpp);
  assert(DeduceFileType("txt.hpp") == FileType::cpp);
  assert(DeduceFileType("py.sh"  ) == FileType::sh);
  assert(DeduceFileType("xyz.txt") == FileType::txt);
  assert(DeduceFileType("pro.py" ) == FileType::py);
  assert(DeduceFileType("c.xyz"  ) == FileType::txt);
  TRACE("Finished ribi::c2h::FileTypes::Test successfully");
}
#endif
