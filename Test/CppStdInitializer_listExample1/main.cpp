#include <cassert>
#include <initializer_list>

int main()
{
  const std::initializer_list<int> v { 1,4,9,16 };

  assert(v.size() == 4);

  assert(*(std::begin(v) + 0) ==  1);
  assert(*(std::begin(v) + 1) ==  4);
  assert(*(std::begin(v) + 2) ==  9);
  assert(*(std::begin(v) + 3) == 16);

  assert(*(v.begin() + 0) ==  1);
  assert(*(v.begin() + 1) ==  4);
  assert(*(v.begin() + 2) ==  9);
  assert(*(v.begin() + 3) == 16);
}
