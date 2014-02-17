#include <cassert>
#include <cstring>

int main()
{
  const char a[] = "ABC";
  const char b[] = "DEFG";
  char * c = new char[ std::strlen(a) + std::strlen(b) + 1 ]; //+1 for null terminator
  std::strcpy(c,a);
  assert(std::strcmp(c,"ABC") == 0);
  std::strcat(c,b);
  assert(std::strcmp(c,"ABCDEFG") == 0);
  delete[] c;
}
