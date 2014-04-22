#include <iostream>

struct HelloWorld
{
  void SayHelloWorld() const noexcept { std::cout << "Hello World\n"; }
};

int main()
{
  const HelloWorld h;
  h.SayHelloWorld();
}
