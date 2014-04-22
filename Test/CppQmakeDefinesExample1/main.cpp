#include <iostream>

int main()
{
  #ifdef SHOW_A
  std::cout << "A";
  #endif
  #ifdef SHOW_B
  std::cout << "B";
  #endif
  #ifdef SHOW_C
  std::cout << "C";
  #endif
  #ifdef SHOW_D
  std::cout << "D";
  #endif
  #ifdef SHOW_E
  std::cout << "E";
  #endif
  std::cout << '\n';
}

/* Screen output:

ABC
Press <RETURN> to close this window...

*/
