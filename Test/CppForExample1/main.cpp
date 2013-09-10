#include <iostream>

int main()
{
  for (
    int i=0; //Create an in-loop integer variable called i
    i!=5; //Enter loop while i!=5
    ++i) //After looping, increment i
  {
    std::cout << i << ": Hello!\n";
  }
}

/* Screen output:

0: Hello!
1: Hello!
2: Hello!
3: Hello!
4: Hello!
Press <RETURN> to close this window...

*/
