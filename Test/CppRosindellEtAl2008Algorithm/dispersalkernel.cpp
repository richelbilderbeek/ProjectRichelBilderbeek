#include "dispersalkernel.h"

#include <iostream>
#include <string>
#include <cassert>
#include <stdexcept>

std::string ToStr(const DispersalKernel kernel) noexcept
{
  switch (kernel)
  {
    case DispersalKernel::normal: return "normal";
    case DispersalKernel::square: return "square";
  }
  throw std::logic_error("ToStr(const DispersalKernel kernel)");
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
