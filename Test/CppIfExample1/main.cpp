#include <cstdlib>
#include <iostream>

int main()
{
  //Draw a random number
  const int x = std::rand();

  std::cout << "Drew random number: " << x << '\n';

  //If statement
  if (x == 42)
  {
    std::cout
      << "The value of x is the Answer to The Ultimate Question of Life, "
      << "the Universe, and Everything.\n";
  }

  //If-else statement
  if (x % 2 == 0)
  {
    std::cout << "The value of x is even.\n";
  }
  else
  {
    std::cout << "The value of x is odd.\n";
  }
}

/* Screen output:

Drew random number: 41
The value of x is odd.
Press <RETURN> to close this window...

*/
