//---------------------------------------------------------------------------
/*
RibiRegex, class for working with regular expressions
Copyright (C) 2014-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRibiRegex.htm
//---------------------------------------------------------------------------
#ifndef RIBI_REGEX_H
#define RIBI_REGEX_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <string>
#include <vector>
#pragma GCC diagnostic pop

namespace ribi {

///Regex functions
struct Regex
{
  Regex();

  //From http://www.richelbilderbeek.nl/CppGetRegexMatches.htm
  std::vector<std::string>
    GetRegexMatches(
    const std::string& s,
    const std::string& regex_str
  ) const noexcept { return GetRegexMatchesXpressive(s,regex_str); }

  std::vector<std::string>
    GetRegexMatchesQRegExp(
    const std::string& s,
    const std::string& regex_str
  ) const noexcept;

  std::vector<std::string>
    GetRegexMatchesXpressive(
    const std::string& s,
    const std::string& regex_str
  ) const noexcept;

  std::string GetRegexDutchPostalCode() const noexcept;
  std::string GetRegexPolygon() const noexcept;
  std::string GetRegexShapes() const noexcept;

  bool IsValidXpressive(const std::string& regex_str) const noexcept;
  bool IsValid(const std::string& regex_str) const noexcept { return IsValidXpressive(regex_str); }

  private:

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

} //~namespace ribi

#endif // RIBI_REGEX_H
