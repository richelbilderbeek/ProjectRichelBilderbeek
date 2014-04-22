#include <cassert>
#include <iostream>

int main()
{
  #ifndef NDEBUG
  assert(1 + 1 == 2);
  std::cout << "Debug mode\n";
  #else
  assert(1 == 2 && "assert must be removed by NDEBUG");
  std::cout << "Release mode\n";
  #endif
}
