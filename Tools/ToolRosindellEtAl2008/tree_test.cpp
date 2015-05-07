//---------------------------------------------------------------------------
/*
RosindellEtAl2008, refactoring an extension of Rosindel at al., 2008 [1]
Copyright (C) 2015 Richel Bilderbeek
Original version by James Rosindell

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
//From http://www.richelbilderbeek.nl/ToolRosindellEtAl2008.htm
//
//Article with original code:
//
// [1] Rosindell, James, Yan Wong, and Rampal S. Etienne.
//     "A coalescence approach to spatial neutral ecology."
//      Ecological Informatics 3.3 (2008): 259-271.
//---------------------------------------------------------------------------
#ifndef NDEBUG
#include "tree.h"

#include <cassert>
#include <iostream>

#include "testtimer.h"

void Tree::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    Rng::Test();
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,2.0);
  Rng rng(0,Rng::Type::bilderbeek);
  const int area_width{4};
  const int area_length{1};
  const double min_speciation_rate{0.0};
  const int dispersal_distance{1};
  const double tolerance{0.1};
  const DispersalKernel dispersal_kernel{
    DispersalKernel::square
  };

  Tree tree(
    rng,
    area_width,
    area_length,
    min_speciation_rate,
    dispersal_distance,
    tolerance,
    dispersal_kernel
  );
  assert(!tree.IsDone());
  std::vector<TreeDataPoint> active_now{tree.GetActive()};
  for (int i=0; i!=20; ++i)
  {
    tree.Update();
    /*
    const std::vector<TreeDataPoint>& active_new{tree.GetActive()};
    if (active_now != active_new)
    {
      active_now = active_new;
      tree.DisplayActive(std::cout);
      std::cout << std::endl;
    }
    */
    if (tree.IsDone()) break;
  }
}

#endif
