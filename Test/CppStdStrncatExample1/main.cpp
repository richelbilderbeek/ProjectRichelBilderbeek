#include <cstring>
#include <iostream>

int main()
{
  const char a[] = "X";
  const char b[] = "0123456789";

  const int sz = std::strlen(b) + 1; //Show both empty and complete string
  for (int i=0; i!=sz; ++i)
  {
    char * c = new char[ std::strlen(a) + i + 1 ]; //+1 for null terminator
    std::strcpy(c,a);
    std::strncat(c,b,i);
    std::cout << c << '\n';
  }
}

/* Screen output:

X
X0
X01
X012
X0123
X01234
X012345
X0123456
X01234567
X012345678
X0123456789
Press <RETURN> to close this window...

*/
