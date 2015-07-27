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

std::string ribi::Rinside::GetVersion() const noexcept
{b
  return "1.0";
}

std::vector<std::string> ribi::Rinside::GetVersionHistory() const noexcept
{
  return {
    "2015-06-13: Version 1.0: started versioning"
  };
}
