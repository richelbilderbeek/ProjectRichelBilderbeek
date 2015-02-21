#include <cassert>
#include <iostream>
#include <string>

int main()
{
  assert(std::to_string(1.5) == "1.500000");
  assert(std::to_string(42) == "42");
}
