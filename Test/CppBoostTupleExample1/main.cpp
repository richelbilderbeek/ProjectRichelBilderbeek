#include <cassert>
#include <string>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/tuple/tuple.hpp>
#pragma GCC diagnostic pop

int main()
{
  typedef boost::tuple<int,double,std::string> Tuple;

  static_assert(boost::tuples::length<Tuple>::value == 3,"Tuple has size 3");
  static_assert(std::is_same<boost::tuples::element<0,Tuple>::type,int>(),"First element is int");
  static_assert(std::is_same<boost::tuples::element<1,Tuple>::type,double>(),"Second element is double");
  static_assert(std::is_same<boost::tuples::element<2,Tuple>::type,std::string>(),"Third element is std::string");

  Tuple t = boost::tuples::make_tuple(123,3.14159,"Bilderbikkel");


  const int x1 = boost::get<0>(t);
  const double x2 = boost::get<1>(t);
  const std::string x3 = boost::get<2>(t);

  boost::get<0>(t) = x1 + 1;
  boost::get<1>(t) = x2 + 1.0;
  boost::get<2>(t) = x3 + " was here";

  assert(boost::get<0>(t) == 124);
  assert(boost::get<1>(t) == 4.14159);
  assert(boost::get<2>(t) == "Bilderbikkel was here");

}
