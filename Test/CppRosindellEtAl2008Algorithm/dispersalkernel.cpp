#include "dispersalkernel.h"

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
  os << kernel;
  return os;
}
