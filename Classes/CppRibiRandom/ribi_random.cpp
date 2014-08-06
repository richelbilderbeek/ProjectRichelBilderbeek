//---------------------------------------------------------------------------
/*
RibiRandom, class for working with random numbers
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
//From http://www.richelbilderbeek.nl/CppRibiRandom.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "ribi_random.h"

#include <cassert>

#include "testtimer.h"
#include "trace.h"

#pragma GCC diagnostic pop

ribi::Random::Random()
{
  #ifndef NDEBUG
  Test();
  #endif
}

bool ribi::Random::GetBool() const noexcept
{
  const int i{std::rand() >> 4};
  const bool b{i % 2 == 0};
  return b;
}

char ribi::Random::GetChar() const noexcept
{
  const char c = 'a' + std::rand() % 26;
  assert(c >= 'a');
  assert(c <= 'z');
  return c;
}


double ribi::Random::GetFraction() const noexcept
{
  const double f{static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX)};
  assert(f >= 0.0);
  assert(f <  1.0);
  return f;
}

std::string ribi::Random::GetString() const noexcept
{
  const int sz = 8;
  std::string s{};
  for (int i=0; i!=sz; ++i)
  {
    s += GetChar();
  }
  return s;
}

std::string ribi::Random::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::Random::GetVersionHistory() noexcept
{
  return {
    "2014-07-29: Version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::Random::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
