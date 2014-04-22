#include <cassert>
#include <string>
#include <tuple>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#pragma GCC diagnostic pop


int main()
{
  //C++11 std::tuple
  {
    int i = 0;
    double d = 0.0;
    std::string s;
    std::tie(i,d,s) = std::make_tuple(1,1.1,"x");
    assert(i == 1);
    assert(d == 1.1);
    assert(s == "x");
  }
  //boost::tie
  {
    int i = 0;
    double d = 0.0;
    std::string s;
    boost::tie(i,d,s) = boost::make_tuple(1,1.1,"x");
    assert(i == 1);
    assert(d == 1.1);
    assert(s == "x");
  }
  //Boost.Tuple
  {
    int i = 0;
    double d = 0.0;
    std::string s;
    boost::tuples::tie(i,d,s) = boost::tuples::make_tuple(1,1.1,"x");
    assert(i == 1);
    assert(d == 1.1);
    assert(s == "x");
  }
  assert(1==2);
}
