//---------------------------------------------------------------------------
/*
CodeBreaker, code breaking class
Copyright (C) 2010-2014 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppCodeBreaker.htm
//---------------------------------------------------------------------------
#include "codebreaker.h"

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

#include "trace.h"
#include "loopreader.h"

ribi::CodeBreaker::CodeBreaker()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::CodeBreaker::Deencrypt(std::string s) const noexcept
{
  return s;
}

std::string ribi::CodeBreaker::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::CodeBreaker::GetVersionHistory() noexcept
{
  return {
    "2014-04-04: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::CodeBreaker::Test() noexcept
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  TRACE("Starting ribi::CodeBreaker::Test");
  TRACE("Finished ribi::CodeBreaker::Test successfully");
}
#endif
