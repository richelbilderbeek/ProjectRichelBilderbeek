#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic pop

int main()
{
  //v contains all values from zero to ten
  const std::vector<int> v { 0,1,2,3,4,5,6,7,8,9 };

  //w contains all squares from 1 to an including 25
  std::vector<int> w { 1,4,9,16,25 };

  assert(std::is_sorted(v.begin(),v.end())
    && "std::set_difference expects a sorted container");
  assert(std::is_sorted(w.begin(),w.end())
    && "std::set_difference expects a sorted container");

  //x is the difference of v and w:
  //that is, the elements in v, that are
  //not in w
  std::vector<int> x;

  std::set_difference(v.begin(),v.end(),w.begin(),w.end(),
    std::back_inserter(x));

  //so x contains all non-squares between zero to ten
  assert(x.size() == 7);
  assert(x[0] == 0);
  assert(x[1] == 2);
  assert(x[2] == 3);
  assert(x[3] == 5);
  assert(x[4] == 6);
  assert(x[5] == 7);
  assert(x[6] == 8);

  //Show x on screen
  std::copy(x.begin(),x.end(),std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';
}

/* Screen output

0 2 3 5 6 7 8

*/
