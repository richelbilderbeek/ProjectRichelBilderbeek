#ifndef INTEGERFLOATINGPOINT_H
#define INTEGERFLOATINGPOINT_H

#include <cinttypes>
#include "MathBase.h"

///Correct BinaryPointInt implementation
///IntegerFloatingPoint simulate a double and a double multiplication using integers only
struct IntegerFloatingPoint
{
  IntegerFloatingPoint(const int multiplicand = 0, const int exponent = 0);

  ///(conform version of) BPI interface
  IntegerFloatingPoint& operator=(const double floating_point)
  {
    *this = IntegerFloatingPoint::fromFloat(floating_point);
    return *this;
  }

  ///Explicit reading from float
  static IntegerFloatingPoint fromFloat(const double floating_point)
  {
    #ifndef NDEBUG
    test();
    #endif
    return IntegerFloatingPoint(floating_point);
  }

  ///BPI interface
  void set(const int32_t value, const int32_t shift);

  //Explicit version of operator=
  void set(const double value);

  ///Obtain the exponent used for determining the true value
  ///The true value equals 'm_multiplicand * (2 ^ m_exponent)'
  int getExponent() const { return m_exponent; }

  ///Obtain the multiplicand used for determining the true value
  ///The true value equals 'm_multiplicand * (2 ^ m_exponent)'
  ///BPI interface
  int getMultiplicand() const { return m_multiplicand; }

  ///Obtain the negated exponent used for determining the true value
  ///The true value equals 'm_multiplicand * (2 ^ m_exponent)'
  ///BPI interface
  int getShift() const { return -getExponent(); }

  ///BPI interface
  int getValue() const { return getMultiplicand(); }

  ///BPI interface for operator*
  ///The original BPI interface returned an Int56. This is changed
  ///to int64_t, because Int56 has an implicit limiting of
  ///its value (which results in Int56(x).get() being unequal to x)
  ///which interfered with this class from testing itself
  int64_t mult(const int64_t value) const;
  int64_t mult(const Int56& value) const { return mult(value.get()); }
  int64_t mult(const Int64& value) const { return mult(value.get()); }

  #ifndef NDEBUG
  ///Convert the internally stored integers to doubles
  ///It is the goal of IntegerFloatingPoint to not use doubles,
  ///so this member function can be used in debugging only
  double toDouble() const;
  #endif

  private:
  ///The exponent used for determining the true value
  ///The true value equals 'm_multiplicand * (2 ^ m_exponent)'
  int m_exponent;

  ///The multiplicand used for determining the true value
  ///The true value equals 'm_multiplicand * (2 ^ m_exponent)'
  int m_multiplicand;

  #ifndef NDEBUG
  static void test();
  #endif

  ///Use the more explicit fromFloat
  IntegerFloatingPoint(const double floating_point);
};

#endif // INTEGERFLOATINGPOINT_H
