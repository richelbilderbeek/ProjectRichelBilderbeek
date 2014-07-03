#include <iostream>
#include <cln/cln.h>

//From http://www.richelbilderbeek.nl/CppClnExample1.htm
int main()
{
  //Regular int
  int x = 1;

  //CLN int
  ::cln::cl_I y = 1;

  for (int i=1; i!=50; ++i)
  {
    x*=i;
    y*=i;
    std::cout << i << "! : " << x << '\t' << y << '\n';
  }
}
