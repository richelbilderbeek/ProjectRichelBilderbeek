#ifndef POSITIVENONZERODOUBLE_H
#define POSITIVENONZERODOUBLE_H

///Only allows values that are positive and non-zero
struct PositiveNonZeroDouble
{
  ///Throws std::logic_error if x is zero or negative
  explicit PositiveNonZeroDouble(const double x);
  double Get() const noexcept { return m_x; }
  const double m_x;
};

#endif // POSITIVENONZERODOUBLE_H
