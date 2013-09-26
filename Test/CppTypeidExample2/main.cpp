#include <cassert>
#include <string>
#include <typeinfo>
#include <iostream>


struct MyClass
{
  MyClass() {}
};

int main()
{
  const auto deleter = [](const MyClass * const p) { delete p; };

  std::cout << std::string(typeid(deleter).name()) << '\n';
}

/* Screen output:

Z4mainEUlPK7MyClassE_
Press <RETURN> to close this window...

*/
