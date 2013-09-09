#include <iostream>

struct Human
{
  virtual ~Human() {}
  virtual void SayHello() const = 0;
};

struct SilentHuman : public Human
{
  void SayHello() const { std::cout << "...hello...\n"; }
};

struct LoudHuman : public Human
{
  void SayHello() const { std::cout << "HELLO!\n"; }
};

int main()
{
  LoudHuman l;
  l.SayHello();

  SilentHuman s;
  s.SayHello();
}

/* Screen output

HELLO!
...hello...
Press <RETURN> to close this window...

*/
