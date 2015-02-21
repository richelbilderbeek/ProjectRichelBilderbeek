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
#ifndef CODETOHTMLSNIPPETTYPES_H
#define CODETOHTMLSNIPPETTYPES_H

#include <string>
#include <vector>
#include "codetohtmlfwd.h"

namespace ribi {
namespace c2h {

struct SnippetTypes
{
  static bool CanStrToSnippetType(const std::string& s);
  static std::string SnippetTypeToStr(const SnippetType t) noexcept;
  static std::vector<SnippetType> GetAllSnippetTypes() noexcept;
  static SnippetType StrToSnippetType(const std::string& s);
};

} //~namespace c2h
} //~namespace ribi

#endif // CODETOHTMLSNIPPETTYPES_H
