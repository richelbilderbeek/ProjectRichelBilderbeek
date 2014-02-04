#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/function.hpp>
#pragma GCC diagnostic pop

struct Speaker
{
  Speaker(const std::string hello_message, const std::string bye_message)
    : m_hello_message(hello_message),
      m_bye_message(bye_message)
  {

  }

  void SayHello() const { std::cout << m_hello_message << '\n'; }
  void SayBye() const { std::cout << m_bye_message << '\n'; }

  const std::string m_hello_message;
  const std::string m_bye_message;
};

int main()
{
  const Speaker s1("Hello!","Bye!");
  const Speaker s2("HELLO!","BYE!");

  const boost::function<void (const Speaker*)> say_hello_function = &Speaker::SayHello;
  const boost::function<void (const Speaker*)> say_bye_function = &Speaker::SayBye;

  say_hello_function(&s1);
  say_bye_function(&s1);

  say_hello_function(&s2);
  say_bye_function(&s2);
}

/* Screen output:

Hello!
Bye!
HELLO!
BYE!
Press <RETURN> to close this window...

*/
