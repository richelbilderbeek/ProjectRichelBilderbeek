#include <cassert>
#include <iostream>
#include <string>
#include <tuple>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#pragma GCC diagnostic pop


int main()
{
  //C++11 std::make_tuple
  {
    std::tuple<int,double,std::string> t {
      std::make_tuple(1,1.1,"x")
    };

    assert(std::get<0>(t) == 1);
    assert(std::get<1>(t) == 1.1);
    assert(std::get<2>(t) == "x");

    std::get<0>(t) += 1;
    std::get<1>(t) += 1.1;
    std::get<2>(t) += "x";

    assert(std::get<0>(t) == 2);
    assert(std::get<1>(t) == 2.2);
    assert(std::get<2>(t) == "xx");

    //std::cout << t << '\n';
  }
  //Boost.Tuple
  {
    boost::tuple<int,double,std::string> t {
      boost::tuples::make_tuple(1,1.1,"x")
    };

    assert(t.get<0>() == 1);
    assert(t.get<1>() == 1.1);
    assert(t.get<2>() == "x");

    t.get<0>() += 1;
    t.get<1>() += 1.1;
    t.get<2>() += "x";

    assert(t.get<0>() == 2);
    assert(t.get<1>() == 2.2);
    assert(t.get<2>() == "xx");

    std::cout << t << '\n';
  }
}

/* Screen output

(2 2.2 xx)
Press <RETURN> to close this window...

*/
