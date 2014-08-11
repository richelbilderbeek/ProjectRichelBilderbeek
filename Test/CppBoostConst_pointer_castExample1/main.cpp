#include <cassert>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct MyClass {};

int main()
{
  boost::shared_ptr<MyClass> p{new MyClass};
  assert(p);
  assert(p.use_count() == 1);
  boost::shared_ptr<const MyClass> q{p}; //No boost::const_pointer_cast needed when adding constness
  assert(q);
  assert(p == q);
  assert(p.use_count() == 2);
  boost::shared_ptr<MyClass> r{boost::const_pointer_cast<MyClass>(q)};
  assert(r);
  assert(r == q);
  assert(p.use_count() == 3);
}
