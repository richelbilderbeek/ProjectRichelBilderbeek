#include <iostream>
#include <functional>

struct Speaker
{
  Speaker() {}

  void SayHello(const std::string& name) const noexcept
  {
    std::cout << "Hello " << name << '\n';
  }
  void SayBye(const std::string& name) const noexcept
  {
    std::cout << "Bye " << name << '\n';
  }
};

int main()
{
  const Speaker s1;
  const Speaker s2;

  const std::function<void (const Speaker*, const std::string&)> say_hello_function = &Speaker::SayHello;
  const std::function<void (const Speaker*, const std::string&)> say_bye_function = &Speaker::SayBye;

  say_hello_function(&s1,"speaker 1");
  say_bye_function(&s1,"speaker 1");

  say_hello_function(&s2,"speaker 2");
  say_bye_function(&s2,"speaker 2");
}

/* Screen output:

Hello speaker 1
Bye speaker 1
Hello speaker 2
Bye speaker 2
Press <RETURN> to close this window...

*/
