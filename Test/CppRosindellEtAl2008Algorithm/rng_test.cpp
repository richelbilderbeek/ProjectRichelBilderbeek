#ifndef NDEBUG
#include "rng.h"


#include <algorithm>
#include <cassert>
#include <iostream>

void Rng::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  Rng a(0,Type::rosindell);
  Rng b(0,Type::bilderbeek);
  //GetRandomFraction
  {
    std::vector<double> v;
    std::vector<double> w;
    for (int i=0; i!=1000; ++i)
    {
      v.emplace_back(a.GetRandomFraction());
      w.emplace_back(b.GetRandomFraction());
    }
    const double sum_a{std::accumulate(std::begin(v),std::end(v),0.0)};
    const double sum_b{std::accumulate(std::begin(w),std::end(w),0.0)};
    std::cout << sum_a << " " << sum_b << std::endl;
    assert(std::abs(sum_a - sum_b) < 1.0);
  }
  //GetRandomInt
  {
    std::vector<int> v;
    std::vector<int> w;
    for (int i=0; i!=1000; ++i)
    {
      v.emplace_back(a.GetRandomInt(10));
      w.emplace_back(b.GetRandomInt(10));
    }
    const int sum_a{std::accumulate(std::begin(v),std::end(v),0)};
    const int sum_b{std::accumulate(std::begin(w),std::end(w),0)};
    std::cout << sum_a << " " << sum_b << std::endl;
    assert(std::abs(sum_a - sum_b) < 100);
  }
  //GetRandomNormal
  {
    std::vector<double> v;
    std::vector<double> w;
    for (int i=0; i!=1000; ++i)
    {
      v.emplace_back(a.GetRandomNormal());
      w.emplace_back(b.GetRandomNormal());
    }
    const double sum_a{std::accumulate(std::begin(v),std::end(v),0.0)};
    const double sum_b{std::accumulate(std::begin(w),std::end(w),0.0)};
    std::cout << sum_a << " " << sum_b << std::endl;
    assert(std::abs(sum_a - sum_b) < 20.0);
  }
}
#endif

