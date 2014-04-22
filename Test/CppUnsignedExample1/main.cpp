#include <cassert>
#include <limits>

int main()
{
  const unsigned int a = 1;
  const unsigned int b = 2;
  const unsigned int c = std::numeric_limits<unsigned int>::max();
  assert(a - b == c);
}
