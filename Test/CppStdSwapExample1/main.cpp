#include <algorithm>
#include <cassert>

int main()
{
  int a = 1;
  int b = 2;

  std::swap(a,b);

  assert(a == 2);
  assert(b == 1);
}
