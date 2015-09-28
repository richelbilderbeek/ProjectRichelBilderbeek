#include "ribi_rinside.h"

#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wextra"
#include "RInside.h"
#pragma GCC diagnostic push

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
{
  return "1.0";
}

std::vector<std::string> ribi::Rinside::GetVersionHistory() const noexcept
{
  return {
    "2015-06-13: Version 1.0: started versioning"
  };
}
