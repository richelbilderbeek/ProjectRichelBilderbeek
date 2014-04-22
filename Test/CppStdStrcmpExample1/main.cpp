#include <cassert>
#include <cstring>

int main()
{
  const char a[] = "Aaron A. Aardvark";
  const char b[] = "Zachary Zziiz";

  assert(std::strcmp(a,a) ==  0 && "first == second yield   0");
  assert(std::strcmp(a,b) == -1 && "first  < second yields -1");
  assert(std::strcmp(b,a) ==  1 && "second < first  yields  1");
  assert(std::strcmp(b,b) ==  0 && "first == second yields  0");
}
