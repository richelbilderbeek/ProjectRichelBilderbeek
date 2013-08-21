#include <iostream>

enum class PersonType { happy, grumpy };

template <PersonType T>
struct Person
{
  ///Every Person<T> can say hello
  void SayHello() const;
};


//Person<PersonType::happy> says hello in a happy way
template <>
void Person<PersonType::happy>::SayHello() const { std::cout << "Hello!\n"; }

//Person<PersonType::grumpy> says hello in a grumpy way
template <>
void Person<PersonType::grumpy>::SayHello() const { std::cout << "Moi\n"; }

int main()
{
  const Person<PersonType::happy> p;
  p.SayHello();
  const Person<PersonType::grumpy> q;
  q.SayHello();
}
