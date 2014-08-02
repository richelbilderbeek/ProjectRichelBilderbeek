//---------------------------------------------------------------------------
/*
Counter, an incrementing counter
Copyright (C) 2011-2014 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppCounter.htm
//---------------------------------------------------------------------------
#include "counter.h"

#include <cassert>

#include "testtimer.h"
#include "trace.h"

ribi::Counter::Counter(const int initial_count) noexcept
  : m_count(initial_count)
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::Counter::GetVersion() noexcept
{
  return "1.1";
}

std::vector<std::string> ribi::Counter::GetVersionHistory() noexcept
{
  return {
    "2011-08-20: Version 1.0: initial version",
    "2014-08-01: Version 1.1: added tests"
  };
}

#ifndef NDEBUG
void ribi::Counter::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction must have value zero"); }
  {
    const Counter c;
    assert(c.Get() == 0);
  }
  if (verbose) { TRACE("Construction with value must return it"); }
  {
    const Counter c(42);
    assert(c.Get() == 42);
  }
  if (verbose) { TRACE("Increment must increment"); }
  {
    Counter c;
    const int old_value = c.Get();
    c.Inc();
    assert(c.Get() == old_value + 1);
  }

}
#endif
