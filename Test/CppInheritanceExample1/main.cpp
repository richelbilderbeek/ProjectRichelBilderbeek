#include <iostream>

struct Person
{
  ~Person() {}
  virtual void SayHello() const = 0;
};

struct GrumpyPerson : public Person
{
  void SayHello() const { std::cout << "...\n"; }
};

struct HappyPerson : public Person
{
  void SayHello() const { std::cout << "Hello!\n"; }
};

int main()
{
  //Base b; //Cannot create instance of abstract class

  const GrumpyPerson g;
  g.SayHello();

  const HappyPerson h;
  h.SayHello();
}

/* Screen output:

...
Hello!
Press <RETURN> to close this window...

*/
