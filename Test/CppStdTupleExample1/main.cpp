#include <cassert>
#include <string>
#include <tuple>
#include <typeinfo>

int main()
{
  typedef std::tuple<int,double,std::string> Tuple;

  static_assert(std::tuple_size<Tuple>::value == 3,"Tuple has size 3");
  static_assert(std::is_same<std::tuple_element<0,Tuple>::type,int>(),"First element is int");
  static_assert(std::is_same<std::tuple_element<1,Tuple>::type,double>(),"Second element is double");
  static_assert(std::is_same<std::tuple_element<2,Tuple>::type,std::string>(),"Third element is std::string");

  Tuple t = std::make_tuple(123,3.14159,"Bilderbikkel");


  const int x1 = std::get<0>(t);
  const double x2 = std::get<1>(t);
  const std::string x3 = std::get<2>(t);

  std::get<0>(t) = x1 + 1;
  std::get<1>(t) = x2 + 1.0;
  std::get<2>(t) = x3 + " was here";

  assert(std::get<0>(t) == 124);
  assert(std::get<1>(t) == 4.14159);
  assert(std::get<2>(t) == "Bilderbikkel was here");

}
