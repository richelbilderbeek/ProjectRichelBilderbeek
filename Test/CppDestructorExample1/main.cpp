#include <iostream>

struct MyClass
{
  ~MyClass() noexcept { std::cout << "Destructor\n"; }
};

int main()
{
  const MyClass m;
} //MyClass destructor called at end of main

/* Screen output:

Destructor
Press <RETURN> to close this window...

*/
