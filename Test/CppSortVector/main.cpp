#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/foreach.hpp>

//From http://www.richelbilderbeek.nl/CppSortContainer.htm
template <class T>
T SortContainer(const T& v)
{
  T w(v);
  std::sort(w.begin(),w.end());
  return w;
}

int main()
{
  //Create a std::vector with five random values
  std::vector<int> v(5);
  std::generate(std::begin(v),std::end(v), []() { return std::rand() % 1000; } );

  //Display the std::vector
  std::copy(std::begin(v),std::end(v),std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';

  //Sort the std::vector
  const std::vector<int> w(SortContainer(v));

  //Display the std::vector again
  std::copy(std::begin(v),std::end(v),std::ostream_iterator<int>(std::cout," "));
  std::cout << '\n';
}
