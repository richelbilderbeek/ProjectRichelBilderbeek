#include <iostream>

struct A
{
  ~A() noexcept { std::cout << "~A\n"; }
};

struct B {
  ~B() noexcept { std::cout << "~B\n"; }
};

struct Alphabetic
{
  A a;
  B b;
};

struct Reverse
{
  B b;
  A a;
};

int main()
{
  {
    Alphabetic();
  }
  {
    Reverse();
  }
}

/* Screen output:

~B
~A
~A
~B

*/
