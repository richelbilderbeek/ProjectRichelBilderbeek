#ifndef POSITIVENONZERODOUBLE_H
#define POSITIVENONZERODOUBLE_H

#include <iostream>

///Only allows values that are positive and non-zero
struct PositiveNonZeroDouble
{
  ///Throws std::logic_error if x is zero or negative
  explicit PositiveNonZeroDouble(const double x);
  double Get() const noexcept { return m_x; }

  private:
  double m_x;
};

std::ostream& operator<<(std::ostream& os, const PositiveNonZeroDouble d);

#endif // POSITIVENONZERODOUBLE_H
