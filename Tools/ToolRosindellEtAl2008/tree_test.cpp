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
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
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
    const std::vector<TreeDataPoint>& active_new{tree.GetActive()};
    if (active_now != active_new)
    {
      active_now = active_new;
      tree.DisplayActive(std::cout);
      std::cout << std::endl;
    }
    if (tree.IsDone()) break;
  }
}

#endif
