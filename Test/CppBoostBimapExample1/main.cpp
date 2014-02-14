#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

int main()
{
  boost::bimap<int,int> m;
  typedef boost::bimap<int,int>::value_type Pair;
  m.insert(Pair(1, 1));
  m.insert(Pair(2, 4));
  m.insert(Pair(3, 9));
  m.insert(Pair(4,16));
  m.insert(Pair(5,25));
  assert(m.left.find( 0) == m.left.end());
  assert(m.left.find( 4) != m.left.end());
  assert(m.left.find( 5) != m.left.end());
  assert(m.left.find(16) == m.left.end());
  assert(m.right.find( 0) == m.right.end());
  assert(m.right.find( 4) != m.right.end());
  assert(m.right.find( 5) == m.right.end());
  assert(m.right.find(16) != m.right.end());
}
