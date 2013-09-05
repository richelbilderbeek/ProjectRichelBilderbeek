#include "integerstateobserver.h"

#include <boost/numeric/conversion/cast.hpp>

const std::string ribi::IntegerStateObserver::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::IntegerStateObserver::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-04: version 1.0: initial version");
  return v;
}
