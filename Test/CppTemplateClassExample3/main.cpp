#include <iostream>

template <int I>
struct Person
{
  ///Every Person<I> can say hello
  void SayHello() const;
};


//Person<0> says hello in a happy way
template <>
void Person<0>::SayHello() const { std::cout << "Hello!\n"; }

//Person<1> says hello in a grumpy way
template <>
void Person<1>::SayHello() const { std::cout << "Moi\n"; }

int main()
{
  const Person<0> p;
  p.SayHello();
  const Person<1> q;
  q.SayHello();
}
