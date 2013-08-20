#include <iostream>

template <class T>
struct MyClass
{
  T x;
};

int main()
{
  MyClass<int> m;
  m.x = 10;
  std::cout << m.x << std::endl;
}
