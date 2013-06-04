#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "slsqfilter.h"

#include <cassert>
#include <cstdlib>

SlsqFilter::SlsqFilter(
  const int filter_shift,
  const int64_t value_active,
  const int64_t value_hidden)
  : m_filter_shift(filter_shift),
    m_value_active(value_active),
    m_value_hidden(value_hidden)
{
  assert(m_filter_shift >=  0 && "A bitshift should not be done with negative values");
  assert(m_filter_shift <= 63 && "An int can maximally be shifted 63 bits to the right");
}

int64_t SlsqFilter::Estimate(const int64_t measurement)
{
  const int64_t delta_1 = ((measurement  - m_value_hidden) >> m_filter_shift);
  m_value_hidden += delta_1 + (delta_1 == 0 && measurement  - m_value_hidden > 0 ? 1 : 0);
  const int64_t delta_2 = ((m_value_hidden - m_value_active) >> m_filter_shift);
  m_value_active += delta_2 + (delta_2 == 0 && m_value_hidden - m_value_active > 0 ? 1 : 0);
  return m_value_active;
}
