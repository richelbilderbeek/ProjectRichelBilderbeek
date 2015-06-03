#include "ribi_apfloat.h"

#include <cassert>
#include <iomanip>
#include <sstream>
#include "apfloat.h"
#include "trace.h"
#include "testtimer.h"

ribi::Apfloat::Apfloat() noexcept
{
  #ifndef NDEBUG
  Test();
  #endif
}


double ribi::Apfloat::ToDouble(const apfloat& a) const noexcept
{
  return ap2double(a.ap);
}

std::string ribi::Apfloat::ToStr(const apfloat& a) const noexcept
{
  std::stringstream s;
  s << pretty << a;
  return s.str();
}

#ifndef NDEBUG
void ribi::Apfloat::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const ribi::TestTimer test_timer(__func__,__FILE__,1.0);
  {
    const double a{4818656.433841671999999998};
    const apfloat b(a);
    const double c{Apfloat().ToDouble(b)};
    assert(c > 4818656.43384167);
    assert(c < 4818656.43384168);
  }
  {
    const std::string s{"4818656.433841671999999998"};
    //Apfloat is not const-correct. Grumble, grumble...
    const apfloat a(const_cast<char*>(s.c_str()));
    const std::string t{Apfloat().ToStr(a)};
    assert(s == t);
  }
}
#endif
