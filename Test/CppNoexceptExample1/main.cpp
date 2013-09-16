#include <cassert>

int Square(const int x) noexcept
{
  return x * x;
}

int main()
{
  assert(Square(0) == 0);
  assert(Square(1) == 1);
  assert(Square(2) == 4);
}
