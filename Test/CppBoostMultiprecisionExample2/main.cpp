#include <iostream>
#include <iomanip>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/multiprecision/gmp.hpp>
#pragma GCC diagnostic pop

int main()
{
  // Arbitrary precision integer type
  boost::multiprecision::mpz_int myint { 1 };
  while (1)
  {
    std::cout << myint << std::endl;
    myint *= 2;
  }
}
