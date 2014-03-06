#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "floatingpointstateobserver.h"
#pragma GCC diagnostic pop

std::string ribi::FloatingPointStateObserver::GetVersion()
{
  return "1.0";
}

std::vector<std::string> ribi::FloatingPointStateObserver::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-18: version 1.0: initial version");
  return v;
}
