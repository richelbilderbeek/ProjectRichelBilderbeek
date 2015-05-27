#include "positivenonzerodouble.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

///Throws std::logic_error if x is zero or negative
PositiveNonZeroDouble::PositiveNonZeroDouble(const double x)
  : m_x{x}
{
  if (x <= 0.0)
  {
    std::stringstream s;
    s << __func__ << ": x must be non-zero and positive, x given: " << x;
    throw std::logic_error(s.str());
  }

}

std::ostream& operator<<(std::ostream& os, const PositiveNonZeroDouble d)
{
  os << d.Get();
  return os;
}
