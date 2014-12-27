#include <cassert>
#include <random>
#include <iostream>

///GetRandomUniform draws a random number from 0.0 to and excluding 1.0.
///From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double GetRandomUniform()
{
  //rd is used only to initialize mt with a truly random seed
  static std::random_device rd;
  //mt generates random numbers
  static std::mt19937 mt(rd());
  //d puts these random numbers in the correct distribution
  static std::uniform_real_distribution<double> d(0.0,1.0);
  //The random value x gets drawn here
  const double x{d(mt)};
  return x;
}

int main()
{
  for (int i=0; i!=10; ++i)
  {
    const double x{GetRandomUniform()};
    assert(x >= 0.0 && x < 1.0);
    std::cout << x << '\n';
  }
}
