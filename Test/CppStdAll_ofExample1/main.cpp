#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <vector>

//From http://www.richelbilderbeek.nl/CppIsPrime.htm
bool IsPrime(const int x)
{
  const int max
  = static_cast<int>(
      std::sqrt(static_cast<double>(x))
    ) + 1;

  for (int i=2; i!=max; ++i)
  {
    if (x % i == 0) return false;
  }

  return true;
}

int main()
{
  std::vector<int> v;
  for (int i=1; i!=10; ++i) v.push_back(i);

  std::vector<int> primes;
  std::vector<int> non_primes;

  //Partition the std::vector in primes and non-primes
  std::partition_copy(
    v.begin(),
    v.end(),
    std::back_inserter(primes),
    std::back_inserter(non_primes),
    IsPrime
  );

  std::cout << "Primes: ";
  std::copy(std::begin(primes),std::end(primes),std::ostream_iterator<int>(std::cout," "));
  std::cout << "\nNon-primes: ";
  std::copy(std::begin(non_primes),std::end(non_primes),std::ostream_iterator<int>(std::cout," "));
  std::cout << "\n";
}

/* Screen output:

Primes: 1 2 3 5 7
Non-primes: 4 6 8 9
Press <RETURN> to close this window...

*/
