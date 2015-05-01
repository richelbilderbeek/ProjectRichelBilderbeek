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
