#ifdef _WIN32
//See http://www.richelbilderbeek.nl/CppCompileErrorSwprintfHasNotBeenDeclared.htm
#undef __STRICT_ANSI__
#endif

//#include own header file as first substantive line of code, from:
// * John Lakos. Large-Scale C++ Software Design. 1996. ISBN: 0-201-63362-0. Section 3.2, page 110
#include "integerfloatingpoint.h"

#include <cassert>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <iostream>

IntegerFloatingPoint::IntegerFloatingPoint(
  const int multiplicand, const int exponent)
  : m_exponent(exponent),
    m_multiplicand(multiplicand)
{
  #ifndef NDEBUG
  test();
  #endif
}

IntegerFloatingPoint::IntegerFloatingPoint(const double floating_point)
{

  if (floating_point < 0.0)
  {
    IntegerFloatingPoint p(-floating_point);
    m_multiplicand = -p.getValue();
    m_exponent = p.getExponent();
    return;
  }
  if (floating_point == 0.0)
  {
    m_exponent = 0;
    m_multiplicand = 0;
    return;
  }
  double x = floating_point;
  assert(x > 0.0);

  m_exponent = 0;
  m_multiplicand = 0;

  while(x > 1.0)
  {
    ++m_exponent;
    x *= 0.5;
  }
  assert(x > 0.0 && x <= 1.0);

  while(x < 0.5)
  {
    --m_exponent;
    x *= 2.0;
  }
  assert(x >= 0.5 && x <= 1.0);

  const int big_bits = 30;
  assert(big_bits <= 30
    && "Must not be too big, otherwise 'static_cast<int>(x * big_value)' will result in a negative value");

  const double big_value = std::pow(2.0,static_cast<double>(big_bits));
  m_multiplicand = static_cast<int>(x * big_value);
  m_exponent -= big_bits;
  assert(m_multiplicand > 0.0);
}

int64_t IntegerFloatingPoint::mult(const int64_t value) const
{
  const int64_t result
    = m_exponent >= 0
    ? (m_multiplicand * value) <<  m_exponent
    : (m_multiplicand * value) >> -m_exponent;

  #ifndef NDEBUG
  const int64_t expected = static_cast<int64_t>(
    static_cast<double>(value) * toDouble()
    );
  if (!(std::abs(result-expected) <= 1))
  {
    //std::cerr << "Error in " << __func__ << ":\n"
    //  << "this.multiplicand: " << this->getMultiplicand() << '\n'
    //  << "this.exponent: " << this->getExponent() << '\n'
    //  << "this: " << this->toDouble() << '\n'
    //  << "multiplier: " << value << '\n'
    //  << "result: " << result << '\n'
    //  << "expected: " << expected << '\n';
    //std::cerr << __func__ << " failed, use floating point" << '\n';
    return expected;
  }
  assert(std::abs(result-expected) <= 1);
  #endif
  return result;
}

void IntegerFloatingPoint::set(const int32_t value, const int32_t shift)
{
  m_multiplicand = value;
  m_exponent = -shift;
}

void IntegerFloatingPoint::set(double value)
{
  IntegerFloatingPoint p(value);
  m_multiplicand = p.getValue();
  m_exponent = p.getShift();
}

#ifndef NDEBUG
void IntegerFloatingPoint::test()
{
  {
    static bool is_tested = false;
    if (is_tested) return;
    is_tested = true;
  }
  //Test for zero
  {
    const IntegerFloatingPoint p = IntegerFloatingPoint::fromFloat(0.0);
    assert(p.toDouble() == 0.0);
  }

  //Test for correct conversion from and to float
  //For positive powers of 2
  for (int i=-65; i!=65; ++i)
  {
    const double x = std::pow(2.0,static_cast<double>(i));
    const IntegerFloatingPoint p = IntegerFloatingPoint::fromFloat(x);
    const double y = p.toDouble();
    assert(std::abs(x-y) <  std::numeric_limits<double>::epsilon());
  }
  //Test for correct conversion from and to float
  //For negative values of 2
  for (int i=-65; i!=65; ++i)
  {
    const double x = -std::pow(2.0,static_cast<double>(i));
    assert(x < 0.0);
    const IntegerFloatingPoint p = IntegerFloatingPoint::fromFloat(x);
    const double y = p.toDouble();
    assert(y < 0.0);
    assert(std::abs(x-y) < std::numeric_limits<double>::epsilon());
  }

  //Test for correct conversion from and to float
  //For positive powers of 2 with random noise added
  for (int i=-65; i!=65; ++i)
  {
    const int n_tests_per_power = 100;
    for (int j = 0; j!=n_tests_per_power; ++j)
    {
      const double f
        = static_cast<double>(std::rand())
        / static_cast<double>(RAND_MAX);
      const double x
        = std::pow(2.0,static_cast<double>(i))
        * (0.5 + f);
      const IntegerFloatingPoint p = IntegerFloatingPoint::fromFloat(x);
      const double y = p.toDouble();
      if (x == 0.0)
      {
        assert(std::abs(x-y) < std::numeric_limits<double>::epsilon());
      }
      else
      {
        assert(x != 0.0);
        const double ratio = y/x;
        assert(ratio >= 0.9999);
        assert(ratio <= 1.0001);
      }
    }
  }
  //Test for correct conversion from and to float
  //For negative values of 2 with random noise added
  for (int i=-65; i!=65; ++i)
  {
    const int n_tests_per_power = 100;
    for (int j = 0; j!=n_tests_per_power; ++j)
    {
      const double f
        = static_cast<double>(std::rand())
        / static_cast<double>(RAND_MAX);
      const double x
        = -std::pow(2.0,static_cast<double>(i))
        * (0.5 * f);
      const IntegerFloatingPoint p = IntegerFloatingPoint::fromFloat(x);
      const double y = p.toDouble();
      if (x == 0.0)
      {
        assert(std::abs(x-y) < std::numeric_limits<double>::epsilon());
      }
      else
      {
        assert(x != 0.0);
        const double ratio = y/x;
        assert(ratio >= 0.9999);
        assert(ratio <= 1.0001);
      }
    }
  }
  //Test IntegerFloatingPoint::mult
  {
    for (int a_sign = 0; a_sign != 4; ++a_sign)
    {
      for (int i=-100; i<100; i+=4)
      {
        const int x_multiplicand = i * (a_sign / 2 ? -1 : 1);
        const int x_exponent = i / 4;

        const double x
          = static_cast<double>(x_multiplicand)
          * std::pow(2.0,static_cast<double>(x_exponent));

        const int64_t y = i * i * i * i * i * (a_sign % 2 ? -1 : 1);

        const int64_t expected
          = static_cast<int64_t>(
            x*static_cast<double>(y)
          );

        const IntegerFloatingPoint ifp(x_multiplicand,x_exponent);
        const int64_t result = ifp.mult(y);
        assert(std::abs(result-expected) <= 1);
      }
    }
  }
}
#endif

#ifndef NDEBUG
double IntegerFloatingPoint::toDouble() const
{
  return m_multiplicand * std::pow(2.0,static_cast<double>(m_exponent));
}
#endif
