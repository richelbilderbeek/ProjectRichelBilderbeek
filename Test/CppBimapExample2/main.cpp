#include <cassert>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

enum class Number { one, two, three };

int main()
{
  boost::bimap<Number,std::string> m;
  typedef boost::bimap<Number,std::string>::value_type Pair;
  m.insert(Pair(Number::one,"one"));
  m.insert(Pair(Number::two,"two"));
  m.insert(Pair(Number::three,"three"));

  assert(m.left.size() == m.right.size());

  //Copy left
  {
    std::vector<Number> v;
    for (auto n: m.left) { v.push_back(n.first); }
    assert(m.left.size() == v.size());
  }
  //Copy right
  {
    std::vector<std::string> v;
    for (auto n: m.right) { v.push_back(n.first); }
    assert(m.right.size() == v.size());
  }
}
