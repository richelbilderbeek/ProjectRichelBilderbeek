//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "floatingpointstateobserver.h"

const std::string ribi::FloatingPointStateObserver::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> ribi::FloatingPointStateObserver::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-18: version 1.0: initial version");
  return v;
}
