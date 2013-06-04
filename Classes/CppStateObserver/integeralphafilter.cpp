#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "integeralphafilter.h"

#include <cassert>
#include <cstdlib>

IntegerAlphaFilter::IntegerAlphaFilter(
  const int alpha,
  const int64_t value_active)
  : m_alpha(alpha),
    m_value_active(value_active)
{
  assert(m_alpha >=  0 && "A bitshift should not be done with negative values");
  assert(m_alpha <= 63 && "An int64_t can maximally be shifted 63 bits to the right");
}

int64_t IntegerAlphaFilter::Estimate(const int64_t measurement)
{
  m_value_active += ((measurement - m_value_active) >> m_alpha);
  return m_value_active;
}

const std::string IntegerAlphaFilter::GetVersion()
{
  return "1.0";
}

const std::vector<std::string> IntegerAlphaFilter::GetVersionHistory()
{
  std::vector<std::string> v;
  v.push_back("2013-06-04: version 1.0: initial version");
  return v;
}
