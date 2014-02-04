#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

int main()
{
  const boost::shared_ptr<int> p_a(new int);
  const boost::shared_ptr<int> p_b;
  const bool a = p_a.get();
  const bool b = p_b.get();
  assert(a && !b);
  if (a && !b) { std::cout << "Hello bool example 1" << std::endl; }
}
