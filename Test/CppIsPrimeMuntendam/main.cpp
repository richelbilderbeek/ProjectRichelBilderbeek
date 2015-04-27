#include <cassert>
#include <cmath>
#include <iostream>

bool IsPrime(const int x)
{
  assert(x > 1);
  const int max{
    static_cast<int>(
      std::sqrt(static_cast<double>(x))
    ) + 1
  };
  for (int i=2; i!=max; ++i)
  {
    if (x % i == 0) return false;
  }
  return true;
}

int main()
{
  assert(IsPrime(2));
  assert(IsPrime(3));
  assert(!IsPrime(4));
  assert(!IsPrime(9));
  assert(!IsPrime(16));
  assert(!IsPrime(3569));
  assert(IsPrime(3571));

  //There will be a value of i of which all i + n*12 are
  // - either prime
  // - or divisible by 5,7 or eleven
  //
  for (int i=2; i!=14; ++i) //Skip 1, start at 13 instead
  {
    for (int j=i; ;j+=12)
    {
      if (!IsPrime(j) && (j%5!=0) && (j%7!=0) && (j%11!=0))
      {
        std::cout << i << " " << j << std::endl;
        break;
      }
    }
  }
  /*
  2 26
  3 27
  4 4
  5 221
  6 6
  7 247
  8 8
  9 9
  10 34
  11 299
  12 12
  13 169
  */
  assert(!IsPrime(221));
  assert(!IsPrime(247));
  assert(!IsPrime(299));
  assert(!IsPrime(169));
  assert(221 % 7 != 0);
  assert(247 % 7 != 0);
  assert(299 % 7 != 0);
  assert(169 % 7 != 0);
  assert(221 % 11 != 0);
  assert(247 % 11 != 0);
  assert(299 % 11 != 0);
  assert(169 % 11 != 0);
}
