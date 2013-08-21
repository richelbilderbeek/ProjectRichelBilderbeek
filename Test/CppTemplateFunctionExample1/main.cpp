int AbsInt(const int n) { return n < 0 ? -n : n; }

double AbsDouble(const double n) { return (n < 0 ? -n : n); }

template <class T>
T Abs(const T n) { return n < 0 ? -n : n; }

#include <cassert>
#include <cmath>

int main()
{
  const double pi = M_PI;

  assert(AbsInt( 42) == 42);
  assert(AbsInt(-42) == 42);
  assert(AbsDouble( pi) == pi);
  assert(AbsDouble(-pi) == pi);

  assert(Abs( 42) == 42);
  assert(Abs(-42) == 42);
  assert(Abs( pi) == pi);
  assert(Abs(-pi) == pi);
}
