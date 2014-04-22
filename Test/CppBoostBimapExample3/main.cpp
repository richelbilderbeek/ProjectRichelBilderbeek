#include <cassert>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/bimap.hpp>
#pragma GCC diagnostic pop

int main()
{
  boost::bimap<int,std::string> m;
  typedef boost::bimap<int,std::string>::value_type Pair;
  m.insert(Pair(0,"zero"));
  m.insert(Pair(1,"one"));
  m.insert(Pair(2,"two"));
  m.insert(Pair(3,"three"));
  m.insert(Pair(4,"four"));
  m.insert(Pair(5,"five"));

  for (int i=0; i!=6; ++i)
  {
    std::cout << i << " " << (*m.left.find(i)).second << '\n';
  }

  for (std::string s: { "zero", "one", "two", "three", "four", "five" } )
  {
    std::cout << s << " " << (*m.right.find(s)).second << '\n';
  }

}

/* Screen output:

0 zero
1 one
2 two
3 three
4 four
5 five
zero 0
one 1
two 2
three 3
four 4
five 5
Press <RETURN> to close this window...

*/
