#include <cassert>
#include <cmath>

bool IsPrime(const int x)
{
  //assert(x > 1);
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
  assert(!IsPrime(0));
  assert(IsPrime(2));
  //assert(IsPrime(3));
  assert(!IsPrime(4));
  assert(!IsPrime(9));
  //assert(!IsPrime(16));
  //assert(!IsPrime(3569));
  //assert(IsPrime(3571));
}
