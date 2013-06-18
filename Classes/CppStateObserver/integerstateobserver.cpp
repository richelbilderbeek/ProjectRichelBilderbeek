#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "integerstateobserver.h"

#include <boost/numeric/conversion/cast.hpp>

const std::string IntegerStateObserver::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> IntegerStateObserver::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-04: version 1.0: initial version");
  return v;
}
