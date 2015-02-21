#include <cassert>
#include "symbolicc++.h"

int main()
{
  const Symbolic x("x");
  const Symbolic f = (3.0*x*x) + (2.0 * x) + 1.0;
  const Equation value = x == 3;
  const double result = f.subst(value);
  assert(result >= 33.9999 && result <= 34.0001);
}
