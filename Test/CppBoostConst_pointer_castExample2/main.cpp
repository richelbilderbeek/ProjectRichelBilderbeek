#include <cassert>
#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct MyClass { int x{42}; };

void f(const boost::shared_ptr<const MyClass>& p) { std::cout << p->x << std::endl; }
void g(const boost::shared_ptr<const MyClass>  p) { std::cout << p->x << std::endl; }

int main()
{
  const boost::shared_ptr<MyClass> p{new MyClass};
  f(p); //No boost::const_pointer_cast needed
  g(p); //No boost::const_pointer_cast needed
  const boost::shared_ptr<const MyClass> q{p};
  f(q);
  g(q);
}

/* Screen output

42
42
42
42

*/
