//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "lsqfilter.h"

#include <cassert>
#include <cstdlib>

LsqFilter::LsqFilter(
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

int64_t LsqFilter::Estimate(const int64_t measurement)
{
  m_value_hidden += ((measurement    - m_value_hidden) >> m_filter_shift);
  m_value_active += ((m_value_hidden - m_value_active) >> m_filter_shift);
  return m_value_active;
}
