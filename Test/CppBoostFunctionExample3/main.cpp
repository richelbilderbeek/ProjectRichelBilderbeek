#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/function.hpp>
#pragma GCC diagnostic pop

struct MyClass
{
  MyClass(const int x = 0) : m_x(x) {}
  int Plus( const int x) const { return m_x + x; }
  int Minus(const int x) const { return m_x - x; }
  int m_x;
};

int main()
{
  typedef boost::function<int(const MyClass*,int)> Function;
  MyClass c;
  Function f1 = &MyClass::Plus;
  Function f2 = &MyClass::Minus;
  assert( f1(&c,1000) ==  1000 );
  assert( f2(&c,1000) == -1000 );
}
