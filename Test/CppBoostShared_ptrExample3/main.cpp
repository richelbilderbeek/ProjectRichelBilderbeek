#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

int main()
{
  const boost::shared_ptr<int> p
    = boost::make_shared<int>(42);
  const boost::shared_ptr<int> q(p);
  assert( p ==  q);
  assert(*p == *q);
  *p.get() = 69;
  assert( p ==  q);
  assert(*p == *q);
  *q.get() = 123;
  assert( p ==  q);
  assert(*p == *q);
}
