#include <algorithm>
#include <iostream>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#pragma GCC diagnostic pop

int f1(const int i) { return i + 1; }
int f2(const int i) { return i + 2; }
int f3(const int i) { return i + 3; }

int main()
{
  std::vector<boost::function<int(const int)> > v;
  v.push_back(f1);
  v.push_back(f2);
  v.push_back(f3);
  std::random_shuffle(v.begin(),v.end());

  int x = 0;
  BOOST_FOREACH(const boost::function<int(const int)>& f,v)
  {
    x = f(x);
    std::cout << x << '\n';
  }
}

/* Possible screen output:

1
4
6
Press <RETURN> to close this window...

*/
