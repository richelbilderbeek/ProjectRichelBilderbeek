//---------------------------------------------------------------------------
/*
Help, class for a program its help information
Copyright (C) 2013-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppHelp.htm
//---------------------------------------------------------------------------
#include "help.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "trace.h"

ribi::Help::Option::Option(
  const char option_short,
  const std::string& option_long,
  const std::string& option_description)
  : m_short(option_short),
    m_long(option_long),
    m_description(option_description)
{
  #ifndef NDEBUG
  const int max_chars_per_line = 80;
  const int chars_for_padding = 7;
  const int max_chars = max_chars_per_line - chars_for_padding;
  const int chars_used = static_cast<int>(1 + m_long.size() + m_description.size());
  if (chars_used > max_chars)
  {
    TRACE("ERROR");
    TRACE(chars_used);
    TRACE(max_chars);
    TRACE(option_short);
    TRACE(option_long);
    TRACE(option_description);
  }
  assert(chars_used <= max_chars && "Options must be kept short to fit on a line");
  //os << "-" << p.m_short << ", --" << p.m_long << "  " << p.m_description << '\n';
  #endif
}


ribi::Help::Help(
  const std::string& program_name,
  const std::string& program_description,
  const std::vector<Option>& options,
  const std::vector<std::string> example_uses)
  : m_example_uses(example_uses),
    m_options(AddDefaultOptions(options)),
    m_program_description(program_description),
    m_program_name(program_name)
{
  #ifndef NDEBUG
  Test();

  //checks if there are no short or long option occurring twice
  const std::size_t sz = m_options.size();
  for (std::size_t i=0; i!=sz-1; ++i)
  {
    const Option& a { m_options[i] };
    for (std::size_t j=i+1; j!=sz; ++j)
    {
      assert(j < m_options.size());
      const Option& b { m_options[j] };
      if (a.m_short == b.m_short
        || a.m_long == b.m_long)
      {
        TRACE(a.m_short);
        TRACE(a.m_long);
        TRACE(a.m_description);
        TRACE(b.m_short);
        TRACE(b.m_long);
        TRACE(b.m_description);
      }
      assert(a.m_short != b.m_short
        && "Every short option must be unique");
      assert(a.m_long != b.m_long
        && "Every long option must be unique");
    }
  }
  #endif
}

const std::vector<ribi::Help::Option> ribi::Help::AddDefaultOptions(const std::vector<Option>& options)
{
  //v: unpadded Options
  std::vector<Option> v { options };
  v.push_back(Option('a',"about","display about message"));
  v.push_back(Option('h',"help","display this help message"));
  v.push_back(Option('i',"history","display version history"));
  v.push_back(Option('l',"licence","display licence"));
  v.push_back(Option('v',"version","display version"));

  //Find the longest long option, for padding
  const int max_length {
    static_cast<int>(
      std::max_element(
        v.begin(), v.end(),
        [](const Option& lhs, const Option& rhs)
        {
          return lhs.m_long.size() < rhs.m_long.size();
        }
      )->m_long.size()
    )
  };
  //w: padded options
  std::vector<Option> w;
  for (Option& p: v)
  {
    const int sz = static_cast<int>(p.m_long.size());
    assert(max_length >= sz);
    const int n_spaces = max_length - sz;
    assert(n_spaces >= 0);
    const std::string s = p.m_long
      + (n_spaces > 0 ? std::string(n_spaces,' '): std::string());
    assert(max_length == static_cast<int>(s.size()));
    const Option q(p.m_short,s,p.m_description);
    w.push_back(q);
  }

  //Sorts by short option
  //Also checks if there are no short or long option occurring twice
  std::sort(
    w.begin(),w.end(),
    [](const Option& lhs, const Option& rhs)
      {
        #ifndef NDEBUG
        if (lhs.m_short == rhs.m_short
          || lhs.m_long == rhs.m_long)
        {
          TRACE(lhs.m_short);
          TRACE(lhs.m_long);
          TRACE(lhs.m_description);
          TRACE(rhs.m_short);
          TRACE(rhs.m_long);
          TRACE(rhs.m_description);
        }
        #endif
        assert(lhs.m_short != rhs.m_short
          && "Every short option must be unique");
        assert(lhs.m_long != rhs.m_long
          && "Every long option must be unique");
        return lhs.m_short < rhs.m_short;
      }
    );

  return w;
}

std::string ribi::Help::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Help::GetVersionHistory() noexcept
{
  return {
    "201x-xx-xx: Version 1.0: initial version",
    "2014-02-27: Version 1.1: started versioning"
  };
}

#ifndef NDEBUG
void ribi::Help::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::Help::Test");
  TRACE("Finished ribi::Help::Test successfully");
}
#endif

std::ostream& ribi::operator<<(std::ostream& os, const Help& help)
{
  os
    << help.GetProgramName() << " help menu\n"
    << "\n"
    << help.GetProgramDescription() << "\n"
    << "\n"
    << "Allowed options for " << help.GetProgramName() << ":\n";
  for (const Help::Option& p: help.GetOptions())
  {
    os << "-" << p.m_short << ", --" << p.m_long << "  " << p.m_description << '\n';
  }
  os
    << "\n"
    << "Example uses:\n";
  for (const std::string& s: help.GetExampleUses())
  {
    os << "  " << s << '\n';
  }
  return os;
}
