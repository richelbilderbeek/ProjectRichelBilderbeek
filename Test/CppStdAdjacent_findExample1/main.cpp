#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
  std::vector<int> v;
  v.push_back(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);

  assert(std::adjacent_find(v.begin(),v.end())!=v.end());
  assert(*std::adjacent_find(v.begin(),v.end())==2);

  //Remove duplicate
  v[2]=5;

  assert(std::adjacent_find(v.begin(),v.end())==v.end());
}
