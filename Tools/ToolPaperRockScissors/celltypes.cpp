#include "celltypes.h"

bool DoesBeat(const CellType lhs, const CellType rhs)
{
  const int a{static_cast<int>(lhs)};
  const int b{static_cast<int>(rhs)};
  return (a + 1) % 3 == b;
}

