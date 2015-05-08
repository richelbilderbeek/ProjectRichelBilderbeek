#include "parameters.h"

#include <cassert>

#include <iostream>

Parameters::Parameters(
  const int any_n,
  const double any_mean_a,
  const double any_stddev_a,
  const double any_mean_b,
  const double any_stddev_b
) :
    n{any_n},
    mean_a{any_mean_a},
    stddev_a{any_stddev_a},
    mean_b{any_mean_b},
    stddev_b{any_stddev_b}
{
  #ifndef NDEBUG
  Test();
  #endif
  assert(n > 0);
  assert(stddev_a >= 0.0);
  assert(stddev_b >= 0.0);
}

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept
{
  os
    << parameter.n << " "
    << parameter.mean_a << " "
    << parameter.stddev_a << " "
    << parameter.mean_b << " "
    << parameter.stddev_b << '\n'
  ;
  return os;
}

std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept
{
  is
    >> parameter.n
    >> parameter.mean_a
    >> parameter.stddev_a
    >> parameter.mean_b
    >> parameter.stddev_b
  ;
  return is;
}

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return
       lhs.n == rhs.n
    && lhs.mean_a == rhs.mean_a
    && lhs.stddev_a == rhs.stddev_a
    && lhs.mean_b == rhs.mean_b
    && lhs.stddev_b == rhs.stddev_b
  ;

}

bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept
{
  return !(lhs == rhs);
}
