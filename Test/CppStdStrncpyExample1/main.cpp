#include <cassert>
#include <cstring>
#include <iostream>

int main()
{
  const char s[] = "0123456789";

  const int sz = static_cast<int>(std::strlen(s));
  assert(sz == 10);
  for (int i=0; i!=sz + 1; ++i) //+1 because both empty and full string are shown
  {
    char * const t = new char[i + 1]; //+1 for null terminator
    std::strncpy(t,s,i);
    t[i] = '\0';
    std::cout << t << '\n';
    delete[] t;
  }
}

/* Screen output:


0
01
012
0123
01234
012345
0123456
01234567
012345678
0123456789
Press <RETURN> to close this window...

*/
