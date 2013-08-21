#include <cassert>
#include <cmath>
#include <string>

#include "data.h"

int main()
{
  const double x = 123.456;
  const Data d(42,x,"Hello world");
  assert(Get<int>(d) == 42);
  assert(Get<double>(d) == x);
  assert(Get<std::string>(d) == "Hello world");
}
