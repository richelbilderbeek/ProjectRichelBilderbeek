#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/ref.hpp>
#pragma GCC diagnostic pop

int main()
{
  int a = 42;

  //Reference-wrap a
  const boost::reference_wrapper<int> b(a);

  //Const-reference-wrap the reference-wrap of a
  const boost::reference_wrapper<const int> c(b);

  //Cannot do a non-const wrap around const-wrap c
  //const boost::reference_wrapper<int> d(c); //Won't compile

  assert(a == 42 && a == b && b == c);
  ++a;
  assert(a == 43 && a == b && b == c);
  ++b;
  assert(a == 44 && a == b && b == c);

  //Cannot modify a const-wrap
  //++c; //Won't compile
}
