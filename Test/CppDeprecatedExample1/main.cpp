#include <iostream>

//Say hello in Dutch
__attribute__ ((deprecated))
void SayHoi()
{
  std::cout << "Hoi" << std::endl;
}

void SayHello()
{
  std::cout << "Hello" << std::endl;
}

int main()
{
  //SayHoi(); //Uncommenting this will result in a warning
  SayHello();
}
