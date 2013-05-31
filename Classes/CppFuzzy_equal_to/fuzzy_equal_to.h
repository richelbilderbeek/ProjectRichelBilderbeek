//---------------------------------------------------------------------------
/*
fuzzy_equal_to, fuzzy equal_to predicate
Copyright (C) 2011-2012 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppFuzzy_equal_to.htm
//---------------------------------------------------------------------------
#ifndef FUZZY_EQUAL_TO_H
#define FUZZY_EQUAL_TO_H

#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

#include <cassert>
#include <functional>
#include <limits>
#include <string>
#include <vector>

//Temporarily suppress Weffc++ warning below, because I won't change std::binary_function
//error: base class 'struct std::binary_function<double, double, bool>' has a non-virtual destructor [-Werror=effc++]
#pragma GCC diagnostic ignored "-Weffc++"

///fuzzy_equal_to is a predicate to test two doubles for equality
///with a certain tolerance. A tolerance of 0.0 denotes that
///an exact match is requested. Note that the value of 0.0 cannot
///be compared fuzzily.
///From http://www.richelbilderbeek.nl/CppFuzzy_equal_to.htm
struct fuzzy_equal_to
  : public std::binary_function<double,double,bool>
{
  explicit fuzzy_equal_to(const double tolerance = std::numeric_limits<double>::epsilon())
    : m_tolerance(tolerance)
  {
    assert(tolerance >= 0.0);
  }
  bool operator()(const double lhs, const double rhs) const
  {
    assert(lhs != 0.0);
    return rhs > (1.0 - m_tolerance) * lhs
        && rhs < (1.0 + m_tolerance) * lhs;
  }
  const double m_tolerance;

  static const std::string GetVersion()
  {
    return "1.3";
  }
  static const std::vector<std::string> GetVersionHistory()
  {
    std::vector<std::string> v;
    v.push_back("2011-02-24: version 1.0: initial version");
    v.push_back("2012-11-14: version 1.1: set default tolerance to std::numeric_limits<double>::epsilon()");
    v.push_back("2012-11-18: version 1.2: added #pragma's to file to suppress -Weffc++ warnings");
    v.push_back("2012-11-18: version 1.3: added #include <limits>");
    return v;
  }
};

//Get back -Weffc++ warnings again
#pragma GCC diagnostic pop

#endif // FUZZY_EQUAL_TO_H
