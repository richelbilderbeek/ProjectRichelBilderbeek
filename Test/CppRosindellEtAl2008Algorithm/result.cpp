#include "result.h"
#include <ostream>

Result::Result(
  const int any_area1,
  const int any_area2,
  const double any_specset,
  const double any_L,
  const bool any_type,
  const double any_temprichness
) : area1{any_area1},
    area2{any_area2},
    specset{any_specset},
    L{any_L},
    type{any_type},
    temprichness{any_temprichness}

{
}

std::ostream& operator<<(std::ostream& os,const Result& result)
{
  os
    << result.area1 << " "
    << result.area2 << " "
    << result.specset << " "
    << result.L << " "
    << (result.type ? " normal " : " square ")
    << result.temprichness
    << " \n"
  ;
  return os;
}
