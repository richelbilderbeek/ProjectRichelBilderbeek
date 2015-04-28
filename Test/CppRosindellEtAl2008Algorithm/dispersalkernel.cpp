#include "dispersalkernel.h"

#include <iostream>
#include <string>
#include <cassert>

std::string ToStr(const DispersalKernel kernel) noexcept
{
  switch (kernel)
  {
    case DispersalKernel::normal: return "normal";
    case DispersalKernel::square: return "square";
  }
  assert(!"Should not get here");
  exit(1);
}

std::ostream& operator<<(std::ostream& os, const DispersalKernel kernel) noexcept
{
  os << static_cast<int>(kernel);
  return os;
}

std::istream& operator>>(std::istream& is, DispersalKernel& kernel) noexcept
{
  int i = 0;
  is >> i;
  kernel = static_cast<DispersalKernel>(i);
  return is;
}
