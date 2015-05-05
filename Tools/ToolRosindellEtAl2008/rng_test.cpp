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
#include "rng.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "testtimer.h"

void Rng::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  Rng a(0,Type::rosindell);
  Rng b(0,Type::bilderbeek);
  //GetRandomInt
  {
    //Should have same minimum, maximum and mean
    std::vector<int> v;
    std::vector<int> w;
    const int min{0};
    const int max{10};
    const int n{1000};
    const double mean{static_cast<double>(min + max) / 2.0};
    for (int i=0; i!=n; ++i)
    {
      v.emplace_back(a.GetRandomInt(max));
      w.emplace_back(b.GetRandomInt(max));
    }
    const int sum_a{std::accumulate(std::begin(v),std::end(v),0)};
    const int sum_b{std::accumulate(std::begin(w),std::end(w),0)};

    const int min_a{*std::min_element(std::begin(v),std::end(v))};
    const int min_b{*std::min_element(std::begin(w),std::end(w))};

    const int max_a{*std::max_element(std::begin(v),std::end(v))};
    const int max_b{*std::max_element(std::begin(w),std::end(w))};

    const double mean_a{static_cast<double>(sum_a)/static_cast<double>(n)};
    const double mean_b{static_cast<double>(sum_b)/static_cast<double>(n)};

    assert(std::abs(mean_a - mean) < 0.11);
    assert(std::abs(mean_b - mean) < 0.11);
    assert(min_a == min_b);
    assert(max_a == max_b);
  }
  //GetRandomNormal
  {
    std::vector<double> v;
    std::vector<double> w;
    const int n{1000};
    for (int i=0; i!=n; ++i)
    {
      v.emplace_back(a.GetRandomNormal());
      w.emplace_back(b.GetRandomNormal());
    }
    const double sum_a{std::accumulate(std::begin(v),std::end(v),0.0)};
    const double sum_b{std::accumulate(std::begin(w),std::end(w),0.0)};
    const int n_68_a{ std::count_if(std::begin(v),std::end(v),[](const double x) { return x >= -1.0 && x <= 1.0; })};
    const int n_68_b{ std::count_if(std::begin(w),std::end(w),[](const double x) { return x >= -1.0 && x <= 1.0; })};
    const int n_95_a{ std::count_if(std::begin(v),std::end(v),[](const double x) { return x >= -2.0 && x <= 2.0; })};
    const int n_95_b{ std::count_if(std::begin(w),std::end(w),[](const double x) { return x >= -2.0 && x <= 2.0; })};
    const double mean_a{static_cast<double>(sum_a)/static_cast<double>(n)};
    const double mean_b{static_cast<double>(sum_b)/static_cast<double>(n)};
    const double f_68_a{static_cast<double>(n_68_a)/static_cast<double>(n)};
    const double f_68_b{static_cast<double>(n_68_b)/static_cast<double>(n)};
    const double f_95_a{static_cast<double>(n_95_a)/static_cast<double>(n)};
    const double f_95_b{static_cast<double>(n_95_b)/static_cast<double>(n)};
    std::cout << mean_a << " " << mean_b << std::endl;
    std::cout << f_68_a << " " << f_68_b << std::endl;
    std::cout << f_95_a << " " << f_95_b << std::endl;
    assert(std::abs(mean_a - 0.0) < 0.05);
    assert(std::abs(mean_b - 0.0) < 0.05);
    assert(std::abs(f_68_a - 0.68) < 0.02);
    assert(std::abs(f_68_b - 0.68) < 0.02);
    assert(std::abs(f_95_a - 0.95) < 0.02);
    assert(std::abs(f_95_b - 0.95) < 0.02);
  }
}
#endif
