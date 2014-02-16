#include <cassert>
#include <initializer_list>

int main()
{
  const auto v { 1,4,9,16 };

  assert(*(std::begin(v) + 0) ==  1);
  assert(*(std::begin(v) + 1) ==  4);
  assert(*(std::begin(v) + 2) ==  9);
  assert(*(std::begin(v) + 3) == 16);
}
