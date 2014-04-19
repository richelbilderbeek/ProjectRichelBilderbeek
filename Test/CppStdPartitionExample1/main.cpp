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

  //Partition the std::vector in primes and non-primes
  typedef std::vector<int>::iterator Iterator;
  const Iterator p_end = std::partition(v.begin(),v.end(),IsPrime);

  std::cout << "Primes: ";
  std::copy(v.begin(),p_end,std::ostream_iterator<int>(std::cout," "));
  std::cout << "\nNon-primes: ";
  std::copy(p_end,v.end(),std::ostream_iterator<int>(std::cout," "));
  std::cout << "\n";
}

/* Screen output:

Primes: 1 2 3 7 5
Non-primes: 6 4 8 9
Press <RETURN> to close this window...

*/
