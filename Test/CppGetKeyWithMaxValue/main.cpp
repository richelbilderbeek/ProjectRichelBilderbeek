#include <algorithm>
#include <cassert>
#include <map>

#include <iostream>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#pragma GCC diagnostic pop

///Obtain the key that corresponds to the highest value
//From http://www.richelbilderbeek.nl/CppGetKeyWithMaxValue.htm
template <class Key, class Value>
const Key GetKeyWithMaxValue(const std::map<Key,Value>& v)
{
  assert(!v.empty());
  return std::max_element(
    v.begin(),v.end(),
    boost::lambda::bind(&std::pair<Key,Value>::second, boost::lambda::_2)
     > boost::lambda::bind(&std::pair<Key,Value>::second, boost::lambda::_1)
   )->first;
}

int main()
{
  std::map<std::string,int> m;
  m.insert(std::make_pair("eight",8));
  m.insert(std::make_pair("four",4));
  m.insert(std::make_pair("one",1));
  m.insert(std::make_pair("sixteen",16));
  m.insert(std::make_pair("two",2));
  assert(GetKeyWithMaxValue(m) == "sixteen");
}
