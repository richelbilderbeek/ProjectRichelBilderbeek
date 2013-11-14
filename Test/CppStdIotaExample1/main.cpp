#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  //Create a std::vector consisting of ten zeroes
  std::vector<int> v(10,0);

  //Let iota assign incrementing values to the std::vector,
  //starting from zero
  std::iota(v.begin(),v.end(),0);

  //Show the std::vector
  std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
}

/*

Screen output

0 1 2 3 4 5 6 7 8 9

*/
