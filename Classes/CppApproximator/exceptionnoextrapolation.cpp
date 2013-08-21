/*
#include "exceptionnoextrapolation.h"

#include <cassert>

ExceptionNoExtrapolation::ExceptionNoExtrapolation(const std::string& what,
  const bool above_max,
  const bool below_min)
  : m_what(what), m_above_max(above_max), m_below_min(below_min)
{
  assert((above_max ^ below_min) && "An extrapolation is above max XOR below min");
}
*/
