#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "integerstateobserver.h"

#include <boost/numeric/conversion/cast.hpp>
#pragma GCC diagnostic pop

const std::string ribi::IntegerStateObserver::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::IntegerStateObserver::GetVersionHistory()
{
  return {
    "2013-06-04: version 1.0: initial version"
  };
}
