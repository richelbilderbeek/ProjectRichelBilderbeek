#include <cassert>
#include <iostream>
#include <boost/shared_ptr.hpp>

int main()
{
  const boost::shared_ptr<int> p_a(new int);
  const boost::shared_ptr<int> p_b;
  const bool a = p_a;
  const bool b = p_b;
  assert(a && !b);
  if (a && !b) { std::cout << "Hello bool example 1" << std::endl; }
}
