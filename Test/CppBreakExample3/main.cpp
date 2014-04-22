#include <cstdlib>
#include <iostream>

int main()
{
  switch(std::rand()%2)
  {
    case 0: std::cout << "Threw heads.\n"; break;
    case 1: std::cout << "Threw tail.\n" ; break;
  }
}

/* Possible screen output:

Threw tail.
Press <RETURN> to close this window...

*/
