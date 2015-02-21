//---------------------------------------------------------------------------
/*
Biology, biology-related functions and classes
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
//From http://www.richelbilderbeek.nl/CppBiology.htm
//---------------------------------------------------------------------------
#include "biology.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "testtimer.h"
#pragma GCC diagnostic pop

ribi::Biology::Biology() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif //NDEBUG
}

ribi::Biology::DnDt ribi::Biology::LogisticGrowth(
  const PopSize carrying_capacity,
  const PopSize current_population_size,
  const double intrinsic_growth_rate)
{
  return  intrinsic_growth_rate * current_population_size
  * ( (carrying_capacity - current_population_size) / carrying_capacity );
}

#ifndef NDEBUG
void ribi::Biology::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);

  {
    const PopSize K{1.0};
    const double r{2.0};
    assert(LogisticGrowth(K,0.5 * K,r) > 0.0);
    assert(LogisticGrowth(K,2.0 * K,r) < 0.0);
  }
}
#endif // NDEBUG
