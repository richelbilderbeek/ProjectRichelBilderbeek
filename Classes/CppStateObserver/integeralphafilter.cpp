#include "integeralphafilter.h"

#include <cassert>
#include <cstdlib>

ribi::IntegerAlphaFilter::IntegerAlphaFilter(
  const int alpha,
  const int64_t value_active)
  : m_alpha(alpha),
    m_value_active(value_active)
{
  assert(m_alpha >=  0 && "A bitshift should not be done with negative values");
  assert(m_alpha <= 63 && "An int64_t can maximally be shifted 63 bits to the right");
}

void ribi::IntegerAlphaFilter::Update(const int64_t measurement)
{
  m_value_active += ((measurement - m_value_active) >> m_alpha);
}

const std::string ribi::IntegerAlphaFilter::GetVersion() noexcept
{
  return "1.1";
}

const std::vector<std::string> ribi::IntegerAlphaFilter::GetVersionHistory() noexcept
{
  std::vector<std::string> v;
  v.push_back("2013-06-04: version 1.0: initial version");
  v.push_back("2013-06-18: version 1.1: refactoring of IntegerStateObserver");
  return v;
}
