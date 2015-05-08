#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <iosfwd>

struct Parameters
{
  Parameters()
    :
      n{0},
      mean_a{0.0},
      stddev_a{0.0},
      mean_b{0.0},
      stddev_b{0.0}
  {

  }
  Parameters(
    const int any_n,
    const double any_mean_a,
    const double any_stddev_a,
    const double any_mean_b,
    const double any_stddev_b
  );
  int n;
  double mean_a;
  double stddev_a;
  double mean_b;
  double stddev_b;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

bool operator==(const Parameters& lhs, const Parameters& rhs) noexcept;
bool operator!=(const Parameters& lhs, const Parameters& rhs) noexcept;

std::ostream& operator<<(std::ostream& os, const Parameters& parameter) noexcept;
std::istream& operator>>(std::istream& is, Parameters& parameter) noexcept;

#endif // PARAMETERS_H
