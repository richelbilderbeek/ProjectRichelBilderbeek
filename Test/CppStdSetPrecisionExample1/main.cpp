#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>

const std::string FormatDigitsBehindTheComma(const double x, const std::size_t n)
{
  std::stringstream s;
  s << std::setprecision(n) << std::fixed << x;
  const std::string t = s.str();
  return t;
}

int main()
{
  const double x = 4.0 / 3.0;
  assert(FormatDigitsBehindTheComma(x, 0) == std::string("1"));
  assert(FormatDigitsBehindTheComma(x, 1) == std::string("1.3"));
  assert(FormatDigitsBehindTheComma(x, 2) == std::string("1.33"));
  assert(FormatDigitsBehindTheComma(x, 3) == std::string("1.333"));
  assert(FormatDigitsBehindTheComma(x, 4) == std::string("1.3333"));
  assert(FormatDigitsBehindTheComma(x, 5) == std::string("1.33333"));
  assert(FormatDigitsBehindTheComma(x, 6) == std::string("1.333333"));
  assert(FormatDigitsBehindTheComma(x, 7) == std::string("1.3333333"));
  assert(FormatDigitsBehindTheComma(x, 8) == std::string("1.33333333"));
  assert(FormatDigitsBehindTheComma(x, 9) == std::string("1.333333333"));
  assert(FormatDigitsBehindTheComma(x,10) == std::string("1.3333333333"));
  assert(FormatDigitsBehindTheComma(x,11) == std::string("1.33333333333"));
  assert(FormatDigitsBehindTheComma(x,12) == std::string("1.333333333333"));
  assert(FormatDigitsBehindTheComma(x,13) == std::string("1.3333333333333"));
  assert(FormatDigitsBehindTheComma(x,14) == std::string("1.33333333333333"));
  assert(FormatDigitsBehindTheComma(x,15) == std::string("1.333333333333333"));
  assert(FormatDigitsBehindTheComma(x,16) == std::string("1.3333333333333333"));
  //assert(FormatDigitsBehindTheComma(x,17) == std::string("1.33333333333333333")); //Fails due to precision of double
}
