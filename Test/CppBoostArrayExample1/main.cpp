#include <cassert>
#include <boost/array.hpp>

int main()
{
  //const boost::array<int,3> v = { 0,1 }; //Does compile: too few elements is not checked in assignment
  //const boost::array<int,3> v = { 0,1,2,3 }; //Does not compile: too many elements is checked in assignment

  //Note: at around 2013-05-01, v needed to be initialized with double braces:
  //  const boost::array<int,3> v = {{ 0,1,2 }};
  const boost::array<int,3> v = { 0,1,2 };

  //static_assert(v.size() == 3,""); //Not allowed, v.size() is not a constexpr
  assert(v.size() == 3);
  assert(v[1] == 1);
}
