#include <iostream>

void SayA() { std::cout << "A\n"; }
void SayB() { std::cout << "B\n"; }

struct Person
{
  void SayBye() const noexcept { std::cout << "Bye\n"; }
  void SayHello() const noexcept { std::cout << "Hello\n"; }
};

int main()
{
  //Ordinay pointer to functions
  {
    typedef void (*Function)();
    const Function a = SayA;
    const Function b = SayB;
    a();
    b();
    Function c = SayA;
    c();
    c = SayB;
    c();
  }
  //Pointer to member functions
  {
    typedef void (Person::*MemberFunction)() const; //Note: do not add noexcept
    const Person p;
    const MemberFunction a = &Person::SayHello;
    ((&p)->*a)();
    const MemberFunction b = &Person::SayBye;
    ((&p)->*b)();
    MemberFunction c = &Person::SayHello;
    ((&p)->*c)();
    c = &Person::SayBye;
    ((&p)->*c)();
  }
}

/* Screen output

A
B
A
B
Hello
Bye
Hello
Bye
Press <RETURN> to close this window...

*/
