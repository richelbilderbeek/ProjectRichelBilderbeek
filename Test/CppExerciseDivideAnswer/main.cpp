#include <cassert>
#include <stdexcept>
#include <memory>

//Features:
// - client has to check the four outputs of this function:
//   - returns std::numeric_limits<double>::infinity() if numerator less than zero and denominator equals zero
//   - returns NaN if numerator and denominator are zero
//   - returns -std::numeric_limits<double>::infinity() if numerator above zero and denominator equals zero
//   - returns correct value if denominator is unequal to zero
// - noexcept
double DivideNaive(const double numerator, const double denominator) noexcept
{
  return numerator / denominator;
}

//Features:
// - clear interface for client to use this function
// - no decrease in run-time speed during release, as denominator is not checked then
// - noexcept
double DivideBilderbeek(const double numerator, const double denominator) noexcept
{
  assert(denominator != 0.0);
  return numerator / denominator;
}

//Features:
// - clear interface for client to use this function
// - decrease in run-time speed during release, as denominator is still checked then
double DivideMeyers(const double numerator, const double denominator)
{
  assert(denominator != 0.0);
  if (denominator == 0.0) throw std::logic_error("Cannot divide by 0.0");
  return numerator / denominator;
}

//Features:
// - client has to check the outputs of this function:
//   - returns nullptr if denominator is equal to zero
//   - returns correct value if denominator is unequal to zero
// - noexcept
// - client has to delete the pointer
double * DivideRawPointer(const double numerator, const double denominator) noexcept
{
  if (denominator == 0.0) return nullptr;
  return new double(numerator / denominator);
}

//Features:
// - client has to check the outputs of this function:
//   - returns empty std::unique_ptr if denominator is equal to zero
//   - returns correct value if denominator is unequal to zero
// - noexcept
// - std::unique_ptr takes care of its own deletion
std::unique_ptr<double> DivideUnique_ptr(const double numerator, const double denominator) noexcept
{
  if (denominator == 0.0) return nullptr;
  return std::make_unique<double>(numerator / denominator);
}

//Features:
// - client has to check the outputs of this function:
//   - first is false, if denominator is equal to zero
//   - if first is true, the correct value is in second
// - noexcept
std::pair<bool,double> DividePair(const double numerator, const double denominator) noexcept
{
  if (denominator == 0.0) return std::make_pair(false,0.0);
  return std::make_pair(true,numerator / denominator);
}

//Features:
// - client has to supply both arguments
// - client has to check the outputs of this function:
//   - sets success to false if denominator is equal to zero
//   - sets success to true and result to the correct value if denominator is unequal to zero
// - noexcept
void DivideReference(const double numerator, const double denominator, bool& success, double& result) noexcept
{
  if (denominator == 0.0)
  {
    success = false;
    result = 0.0;
  }
  else
  {
    success = true;
    result = numerator / denominator;
  }
}

#include <iostream>
#include <limits>
int main()
{
  for (int i=-1; i!=2; ++i)
  {
    const double result{DivideNaive(static_cast<double>(i),0.0)};
    if (result != result) {std::cout << "NaN detected" << '\n';}
    if (result == std::numeric_limits<double>::infinity()) {std::cout << "Infinity detected" << '\n';}
    if (result == -std::numeric_limits<double>::infinity()) {std::cout << "-Infinity detected" << '\n';}

  }
}
