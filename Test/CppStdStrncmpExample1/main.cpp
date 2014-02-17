#include <cassert>
#include <cstring>

int main()
{
  const char a[] = "AB";
  const char b[] = "AC";
  assert(std::strncmp(a,b,1) ==  0);
  assert(std::strncmp(a,b,2) == -1);
}
