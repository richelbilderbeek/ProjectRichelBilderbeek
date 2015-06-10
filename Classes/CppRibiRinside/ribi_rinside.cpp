#include "ribi_rinside.h"

#include <cassert>
#include "RInside.h"

ribi::Rinside::Rinside()
{
  #ifndef NDEBUG
  Test();
  #endif
}

RInside& ribi::Rinside::Get()
{
  static RInside * p{new RInside};
  assert(p);
  return *p;
}
