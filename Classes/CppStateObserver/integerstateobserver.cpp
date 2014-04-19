#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "integerstateobserver.h"

#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

std::string ribi::IntegerStateObserver::GetVersion() noexcept
{
  return "1.0";
}

std::vector<std::string> ribi::IntegerStateObserver::GetVersionHistory() noexcept
{
  return {
    "2013-06-04: version 1.0: initial version"
  };
}
