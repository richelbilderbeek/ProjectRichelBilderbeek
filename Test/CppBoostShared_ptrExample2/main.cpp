#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#pragma GCC diagnostic pop

struct MyClass
{
  MyClass(const int x) : m_x{x} {}
  int m_x;
};

bool operator==(const MyClass& lhs, const MyClass& rhs)
{
  return lhs.m_x == rhs.m_x;
}

int main()
{
  const boost::shared_ptr<MyClass> p
    = boost::make_shared<MyClass>(42);
  const boost::shared_ptr<MyClass> q(p);
  assert( p ==  q);
  assert(*p == *q);
  p->m_x = 69;
  assert( p ==  q);
  assert(*p == *q);
  q->m_x = 123;
  assert( p ==  q);
  assert(*p == *q);
}
