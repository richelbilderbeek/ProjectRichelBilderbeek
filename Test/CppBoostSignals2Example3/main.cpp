#include <iostream>

#include <boost/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/signals2.hpp>

//NoIdea is a class that can ask for an answer, but
//has no idea what this answer is. It relies on a
//Boost.Units2 signal its return value
struct NoIdea
{
  NoIdea() : m_signal{} {}
  void Ask()
  {
    if (m_signal())
    {
      std::cout << *m_signal() << '\n';
    }
    else
    {
      std::cout << "[No one answers]" << '\n';
    }
  }
  boost::signals2::signal<std::string()> m_signal;
};

std::string SayX() { return "The answer"; }

int main()
{
  NoIdea x;
  x.Ask();
  x.m_signal.connect(&SayX);
  x.Ask();
}
