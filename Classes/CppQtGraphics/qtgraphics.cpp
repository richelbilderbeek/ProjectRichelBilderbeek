//---------------------------------------------------------------------------
/*
QtGraphics, Qt graphics code snippets
Copyright (C) 2015-2015 Richel Bilderbeek

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
//From http://www.richelbilderbeek.nl/CppQtArrowItem.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "qtgraphics.h"

#include <cassert>



#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop


ribi::QtGraphics::QtGraphics()
{
  #ifndef NDEBUG
  Test();
  #endif
}

std::string ribi::QtGraphics::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::QtGraphics::GetVersionHistory() noexcept
{
  return {
    "2015-02-22: version 1.0: initial version"
  };
}

#ifndef NDEBUG
void ribi::QtGraphics::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  const bool verbose{false};
  if (verbose) { TRACE("Default-construction of QtGraphics"); }
  {
    const QtGraphics q;
  }
}
#endif
