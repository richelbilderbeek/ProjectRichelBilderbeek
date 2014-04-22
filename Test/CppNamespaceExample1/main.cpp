#include <iostream>

namespace loud
{
  void SayHello() { std::cout << "HELLO WORLD!\n"; }
}

//SayHello in the global namespace, ::SayHello()
void SayHello() { std::cout << "Hello world\n"; }

namespace soft
{
  void SayHello() { std::cout << "H.e.l.l.o w.o.r.l.d...\n"; }
}

int main()
{
  loud::SayHello();     //Call loud::SayHello
  ::SayHello();         //Explicity call SayHello from global namespace
  SayHello();           //Call the SayHello used, which is ::SayHello by default
  using soft::SayHello; //Start using soft::SayHello
  SayHello();           //Call the SayHello used, which is soft::SayHello now
  soft::SayHello();     //Call soft::SayHello
}

/* Screen output:

HELLO WORLD!
Hello world
Hello world
H.e.l.l.o w.o.r.l.d...
H.e.l.l.o w.o.r.l.d...
Press <RETURN> to close this window...

*/
