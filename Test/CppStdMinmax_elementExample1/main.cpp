#include <algorithm>
#include <cassert>
#include <iostream>

int main()
{
  const std::vector<int> v = { 1,100,2,3,4,5,6,7,-100,8,9 };
  const std::pair<std::vector<int>::const_iterator,std::vector<int>::const_iterator> p
    = std::minmax_element(v.begin(),v.end());
  const int min = *(p.first);
  const int max = *(p.second);
  assert(min == -100);
  assert(max ==  100);
}
