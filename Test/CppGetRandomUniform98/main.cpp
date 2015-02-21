#include <cstdlib>
#include <iostream>

///GetRandomUniform98 draws a random number from 0.0 to and excluding 1.0.
///GetRandomUniform98 is deprecated from C++11, use GetRandomUniform instead.
///From http://www.richelbilderbeek.nl/CppGetRandomUniform98.htm
#if __cplusplus >= 201103L
[[deprecated]]
#endif
double GetRandomUniform98()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}

int main()
{
  for (int i=0; i!=10; ++i)
  {
    std::cout << GetRandomUniform98() << '\n';
  }
}
